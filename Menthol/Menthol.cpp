
#include "stdafx.h"
#include "Menthol.h"
#include "StatementList.h"
#include "Vm.h"
#include <Windows.h>
#include <intrin.h>
char* currentyyfile;
// 这是导出函数的一个示例。

static PrintErrorFunc _PrintCompileErrorFunc = 0;
static PrintErrorFunc _PrintRunTimerrorFunc = 0;


void SetPrintCompileErrorFunc(PrintErrorFunc _pef)
{
	_PrintCompileErrorFunc = _pef;
}
void SetPrintRunTimeErrorFunc(PrintErrorFunc _pef)
{
	_PrintRunTimerrorFunc = _pef;
}


int Compile(char* cfile,bool isdebug)
{
	StatementList *als =new StatementList();
	MCommon* _WCommon  = new MCommon();
	MError* _MError = new MError();
	MError::CreateInstance()->SetCompilePrintErrorFunc(_PrintCompileErrorFunc);
	FILE* file;
	file = fopen(cfile, "r");
	currentyyfile = cfile;
	if (!file) {
		char str[256]={0};
		sprintf(str,"could not open %s",cfile);
		MError::CreateInstance()->PrintError(str,-1);
		return 1;
	}
	
	yyin = file;
	yyrestart(yyin);
	als->currentpackagename = _WCommon->StringPathSplit(string(cfile)).name;
	//als->ResetInitPackageList();
	yyparse(als);
	PathInfo pinfo = MCommon::CreateInstance()->StringPathSplit(cfile);

	if(!MCommon::CreateInstance()->StrCmpNoCase(pinfo.extension,MENTHOLEXTENSION) && !MCommon::CreateInstance()->StrCmpNoCase(pinfo.extension,MENTHOLPACKAGEEXTENSION))
	{
		delete als;
		delete _WCommon;
		delete _MError;
		char str[256]={0};
		sprintf(str,"%s is not menthol execute or package",cfile);
		MError::CreateInstance()->PrintError(str,-1);
		return 1;
	}
	als->CreateCode(als->CompileStructTable,pinfo.extension,isdebug);
	if(!yyerrorcount){
		MFile::CreateInstance()->GenerateFileData(als->CodeList,0,0,0,pinfo.extension,pinfo.name);
	}
	/*for (std::vector<Statement*>::iterator it =als->CompileStructTable->begin() ; it != als->CompileStructTable->end(); ++it)
	{*/
	VECTORFORSTART(Statement*,als->CompileStructTable,it)
		(*it)->Release();
	VECTORFOREND
	/*}*/
	fclose(file);
	
	als->ResetIpi();
	als->SetLocalCountValue(0);
	als->CodeList->clear();
	als->GetPackAgeList()->clear();	
	als->GetGlobalMemory()->clear();
	als->GetDoubleConstants()->clear();
	als->GetFunctionList()->clear();
	als->GetStringConstants()->clear();
	als->GetDictKeyConstants()->clear();
	als->GetMentholDebug()->clear();
	als->CompileStructTable->clear();
	lineno  = 1;
	delete als;
	delete _WCommon;
	delete _MError;
	if(yyerrorcount){
		return yyerrorcount;
	}
	yyerrorcount = 0;
	return 0;
}


int Run(char* files,char* arg1,char* arg2)
{
	new MCommon();
	new MError();
	MError::CreateInstance()->SetRunTimePrintErrorFunc(_PrintRunTimerrorFunc);
	Vm::Init();

	StackState v1;
	v1.v = M_NULL;
	v1.i=0;
		
	StackState v2;
	v2.v = M_NULL;
	v2.i=0;


	if(arg1){
		v1.str=Vm::CreateString(arg1);
		v1.v = M_STRING;
	}
	if(arg2){
		v2.str=Vm::CreateString(arg2);
		v2.v = M_STRING;
	}



	Vm::InitStack(v1,v2);

	PathInfo pinfo = MCommon::CreateInstance()->StringPathSplit(files);

	PackageAttr pa;
	strcpy(pa.pname,pinfo.name.c_str());
	strcpy(pa.fname,files);
	pa.ptype = MPA_PACKAGE;


	std::ifstream t;  
	int length;  
	t.open(files,std::ios::in | ofstream::binary);      // open input file  
	t.seekg(0, std::ios::end);    // go to the end  
	length = t.tellg();           // report location (this is the length)  
	t.seekg(0, std::ios::beg);    // go back to the beginning  
	char *bufferf = new char[length];    // allocate memory for a buffer of appropriate dimension  
	t.read(bufferf, length);       // read the whole file into the buffer  
	t.close();                    // close file handle  


	string flag;
	int i=0;


	CodeInst ci;
	ci.m.c1 = bufferf[i++];
	ci.m.c2 = bufferf[i++];
	ci.m.c3 = bufferf[i++];
	ci.m.c4 = bufferf[i++];
	flag.push_back(ci.i);

	ci.m.c1 = bufferf[i++];
	ci.m.c2 = bufferf[i++];
	ci.m.c3 = bufferf[i++];
	ci.m.c4 = bufferf[i++];
	flag.push_back(ci.i);

	ci.m.c1 = bufferf[i++];
	ci.m.c2 = bufferf[i++];
	ci.m.c3 = bufferf[i++];
	ci.m.c4 = bufferf[i++];
	flag.push_back(ci.i);

	if(flag == MENTHOLPACKAGEDLLEXTENSION2){
		MError::CreateInstance()->PrintRunTimeError(files+string(" is menthol package"));
		return 0;
	}

	if(flag != MENTHOLEXECUTEEXTENSION2){
		MError::CreateInstance()->PrintRunTimeError(files+string(" is not menthol executable program"));
		return 0;
	}

	delete[] bufferf;
	Vm::EntryPoint(pa,CONSTCAST(char)((pinfo.drive+pinfo.dir).c_str()));
	
	return 0;
}

void RegisterPackAgeFunciton(char* name,funcallback fun,int paramcount)
{
	HMODULE hCallerModule = NULL;  
    char szModuleName[MAX_PATH];  
    void *callerAddress = _ReturnAddress();  
    if (GetModuleHandleExA(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS, (char*)callerAddress, &hCallerModule))  
    {  
		FunctionAtter fa = {name,(Instruction*)fun,0,paramcount,-1};
		Vm::CreateFunctionRecoredList(fa);	
    }  
}

StackState GetParam(int index)
{
	return Vm::GetParam(index);
}

StackState Array_CreateArray()
{
	StackState sk;
	sk.parray = Vm::CreateArray();
	sk.v= M_ARRAY;	
	return sk;
}


int Array_Length(pArray p)
{
	VECOTRSTACKSTATEPOINTER ar  = STATICCASTPARRAY(p);
	return ar->size();
}

StackState Array_Get(pArray sk1,int index){

	//vector<StackState>* ar  = static_cast<vector<StackState>*>(sk1->array);
	VECOTRSTACKSTATEPOINTER ar  = STATICCASTPARRAY(sk1);
	return ar->at(index);;
}

void Array_Set(pArray sk1,StackState sk2,int index){

	VECOTRSTACKSTATEPOINTER ar  = STATICCASTPARRAY(sk1);
	ar->at(index)=sk2;
}

pString Array_Join(pArray a1,char* link)
{
	VECOTRSTACKSTATEPOINTER ar1  = STATICCASTPARRAY(a1);
	string str;
	//for (std::vector<StackState>::iterator it = ar1->begin() ; it != ar1->end(); ++it)
	//{
	VECTORFORSTART(StackState,ar1,it)
		if((*it).v==M_ARRAY){
			str+= "{Array}";
		}
		if((*it).v==M_DICT){
			str+="{Dict}";
		}
		if((*it).v==M_STRING){
			str+= (*it).str->string;
		}
		if((*it).v==M_NULL){
			str+= "NULL";
		}
		if((*it).v==M_PACKAGE){
			str+="PACKAGE";
		}
		if((*it).v==M_FUN){
			str+="Function";
		}
		if((*it).v==M_BOOL){
			if((*it).d==0){
				str+="False";
			}else
			{
				str+="True";
			}
		}
		if((*it).v==M_NUMBER){
			
			char in[4];
			itoa((*it).d,in,10);
			str+=in;
		}
		str+=link;
	//}
	VECTORFOREND
	str.erase(str.end() - 1);  
	return  Vm::CreateString(CONSTCAST(char)(str.c_str()));
}

pArray Array_Reverse(pArray a1)
{
	VECOTRSTACKSTATEPOINTER ar1  = STATICCASTPARRAY(a1);
	reverse(ar1->begin(),ar1->end());
	return a1;
}

void Array_Push(pArray p,StackState st){
	VECOTRSTACKSTATEPOINTER ar1  =STATICCASTPARRAY(p);
	ar1->push_back(st);
}



StackState Dict_CreateDict()
{
	//StackState sk={Vm::CreateInstance()->CreateDict(),M_DICT};
	StackState sk;
	sk.pdict = Vm::CreateDict();
	sk.v= M_DICT;	
	return sk;
}


void Dict_Push(char* key,pDict pdict,StackState sk2)
{
	map<hashValue,StackState>* _ss = (map<hashValue,StackState>*)(pdict->dict);	
	string _key = string(key);
	//Vm::CreateString(key);
	Vm::CreateDictKeyString(key);
	hashValue hash = MCommon::CreateInstance()->ELFHash(_key);
	_ss->insert(pair<hashValue,StackState>(hash,sk2));
}

int Dict_Length(pDict pdict)
{
	map<hashValue,StackState>* _ss = (map<hashValue,StackState>*)(pdict->dict);	
	return _ss->size();
}

StackState Dict_Get(pDict pdict,hashValue key){

	map<hashValue,StackState>* _ss = (map<hashValue,StackState>*)(pdict->dict);	
	StackState _systemtype =  _ss->find(key)->second;
	return _systemtype;
}

void Dict_Set(char* key,pDict pdict,StackState sk2)
{
	map<hashValue,StackState>* _ss = (map<hashValue,StackState>*)(pdict->dict);	

	string _key = string(key);
	hashValue hash = MCommon::CreateInstance()->ELFHash(_key);
	_ss->find(hash)->second=sk2;
}

pString Dict_Key(pDict pdict,hashValue sk2)
{
	map<hashValue,StackState>* _ss = (map<hashValue,StackState>*)(pdict->dict);	
	for(map <hashValue, StackState>::iterator m1_Iter = _ss->begin( ); m1_Iter != _ss->end( ); m1_Iter++)
	{
		if((*m1_Iter).first==sk2)
		{
			return Vm::CreateDictKeyString(sk2);
		}
	}
	return 0;
}



StackState String_CreateString(char* str)
{
	//StackState sk={0,0,Vm::CreateInstance()->CreateString(str),M_STRING};
	StackState sk;
	sk.str = Vm::CreateString(str);
	sk.v= M_STRING;	
	return sk;
}




void CreateFunctionCall(int pc)
{
	Vm::CreateFunctionCall(pc);
}
void PushNumber(double d)
{
	Vm::Push_Number(d);	
}

void PushString(pString str)
{
	Vm::Push_String(str);
}

void PushArray(pArray arr)
{
	Vm::Push_Array(arr);
}

void PushDict(pDict dict)
{
	Vm::Push_Dict(dict);
}



StackState CallFunction(StackState fu)
{
	StackState func = Vm::CallFunction(fu);
	return func;
}
