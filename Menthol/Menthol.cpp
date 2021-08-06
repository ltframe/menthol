
#include "stdafx.h"
#include "Menthol.h"
#include "StatementList.h"
#include "Vm.h"
#include <Windows.h>
#include <intrin.h>

//正在编译的文件名，给menthol-flex.l使用
char* currentyyfile;

static PrintErrorFunc _PrintCompileErrorFunc = 0;
static PrintErrorFunc _PrintRunTimerrorFunc = 0;
static bool iscompile = false;

//设置编译错误提示全局静态变量
void SetPrintCompileErrorFunc(PrintErrorFunc _pef)
{
	_PrintCompileErrorFunc = _pef;
}
//设置运行错误提示全局静态变量
void SetPrintRunTimeErrorFunc(PrintErrorFunc _pef)
{
	_PrintRunTimerrorFunc = _pef;
}

//编译源文件
//char* cfile：文件路径
int Compile(char* cfile)
{

	StatementList *als =new StatementList();
	MError* _MError = new MError();
	MError::CreateInstance()->SetCompilePrintErrorFunc(_PrintCompileErrorFunc);
	FILE* file;
	file = fopen(cfile, "r");
	currentyyfile = cfile;
	if (!file) {
		char str[256]={0};
		sprintf(str,"could not open %s",cfile);		
		MError::CreateInstance()->PrintError(str,-1);
		delete _MError;
		delete als;
		fclose(file);
		return 1;
	}

	MCommon* _WCommon  = new MCommon();
	MBinary *wb =new  MBinary();
	iscompile = true;
	yyin = file;

	yyrestart(yyin);
	yyparse(als);
	PathInfo pinfo = MCommon::CreateInstance()->StringPathSplit(cfile);

	//如果被编译的文件不是可执行文件，也不是包文件
	if(!MCommon::CreateInstance()->StrCmpNoCase(pinfo.extension,MENTHOLEXTENSION) && !MCommon::CreateInstance()->StrCmpNoCase(pinfo.extension,MENTHOLPACKAGEEXTENSION))
	{
		delete als;
		delete _WCommon;	
		delete wb;
		char str[256]={0};
		sprintf(str,"%s is not menthol execute or package",cfile);
		MError::CreateInstance()->PrintError(str,-1);
		delete _MError;
		iscompile = false;
		fclose(file);
		return 1;
	}
	als->CreateCode(als->CompileStructTable,pinfo.extension);
	//如果编译中、生成代码中都没有错误产生，则输出编译后的文件
	if(!yyerrorcount){
		MFile::CreateInstance()->GenerateFileData(als->CodeList,0,0,0,pinfo.extension,pinfo.name);
	}

	VECTORFORSTART(Statement*,als->CompileStructTable,it)
		(*it)->Release();
	VECTORFOREND
	fclose(file);
	
	als->CodeList->clear();
	als->GetGlobalMemory()->clear();

	als->CompileStructTable->clear();
	lineno  = 1;
	delete als;
	delete _WCommon;
	delete _MError;	
	delete wb;
	iscompile = false;
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

	VmState* vmstate = Vm::NewVmState();
	Vm::_NewVm(vmstate);

	StackState v1;
	v1.v = M_NULL;
	v1.i=0;
		
	StackState v2;
	v2.v = M_NULL;
	v2.i=0;


	if(arg1){
		v1.str=Vm::CreateString(arg1,vmstate);
		v1.v = M_STRING;
	}
	if(arg2){
		v2.str=Vm::CreateString(arg2,vmstate);
		v2.v = M_STRING;
	}



	Vm::InitStack(v1,v2,vmstate);

	PathInfo pinfo = MCommon::CreateInstance()->StringPathSplit(files);

	string flag = MBinary::CreateInstance()->ReadPackageFormat(files);

	//检查被调用文件是不是含有mmain的启动文件
	if(flag != MENTHOLEXECUTEEXTENSION2){
		MError::CreateInstance()->PrintRunTimeError(files+string(" is not menthol executable program"),vmstate);
		return 0;
	}

	
	ImportFileAttr ifa = {files,MPA_USER_PACKAGE};
	Vm::EntryPoint(ifa,CONSTCAST(char)((pinfo.drive+pinfo.dir).c_str()),vmstate);
	return 0;
}

RunTimeState* CreateModuleRunTime(char* modulename,VmState *vmstate)
{
	//如果是编译的话，则加入编译使用的modulelist列表，否则加入运行时的modulelist
	if(iscompile)
	{
		StatementList::GetInstance()->AddExternalModuleList(modulename);
		return 0;
	}
	return Vm::CreateModuleRunTime(modulename,vmstate);
}

void RegisterModuleFunciton(RunTimeState* moduleinst,UserFunctionAtter* functionlist)
{

	if(!moduleinst)return;

	HMODULE hCallerModule = NULL;  
    char szModuleName[MAX_PATH];  
    void *callerAddress = _ReturnAddress();  
    if (GetModuleHandleExA(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS, (char*)callerAddress, &hCallerModule))  
    {  
		while ((*functionlist).name!=0){
			UserFunctionAtter _u = *functionlist;
			FunctionAtter fa = {_u.name,(Instruction*)_u.postion,0,_u.paramcount,-1};
			Vm::CreateFunctionRecoredList(moduleinst,fa);
			functionlist++;
		}
    }  
}

StackState GetParam(int index,VmState * vmstate)
{
	return Vm::GetParam(index,vmstate);
}

StackState Array_CreateArray(VmState * vmstate)
{
	StackState sk;
	sk.parray = Vm::CreateArray(vmstate);
	sk.v= M_ARRAY;	
	return sk;
}


int Array_Length(pArray p)
{
	VECOTRSTACKSTATEPOINTER ar  = STATICCASTPARRAY(p);
	return ar->size();
}

StackState Array_Get(pArray sk1,int index){

	VECOTRSTACKSTATEPOINTER ar  = STATICCASTPARRAY(sk1);
	return ar->at(index);;
}

void Array_Set(pArray sk1,StackState sk2,int index){

	VECOTRSTACKSTATEPOINTER ar  = STATICCASTPARRAY(sk1);
	ar->at(index)=sk2;
}

pString Array_Join(pArray a1,char* link,VmState *vmstate)
{
	VECOTRSTACKSTATEPOINTER ar1  = STATICCASTPARRAY(a1);
	string str;
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
		if ((*it).v == M_MODULE){
			str+="Module";
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
	return  Vm::CreateString(CONSTCAST(char)(str.c_str()),vmstate);
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



StackState Dict_CreateDict(VmState * vmstate)
{
	StackState sk;
	sk.pdict = Vm::CreateDict(vmstate);
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

pString Dict_Key(pDict pdict,hashValue sk2,VmState *vmstate)
{
	map<hashValue,StackState>* _ss = (map<hashValue,StackState>*)(pdict->dict);	
	for(map <hashValue, StackState>::iterator m1_Iter = _ss->begin( ); m1_Iter != _ss->end( ); m1_Iter++)
	{
		if((*m1_Iter).first==sk2)
		{
			return Vm::CreateDictKeyString(sk2,vmstate);
		}
	}
	return 0;
}



StackState String_CreateString(char* str,VmState *vmstate)
{
	StackState sk;
	sk.str = Vm::CreateString(str,vmstate);
	sk.v= M_STRING;	
	return sk;
}




void CreateFunctionCall(int pc,VmState * vmstate)
{
	Vm::CreateFunctionCall(pc,vmstate);
}
void PushNumber(double d,VmState * vmstate)
{
	Vm::Push_Number(d,vmstate);	
}

void PushString(pString str,VmState * vmstate)
{
	Vm::Push_String(str,vmstate);
}

void PushArray(pArray arr,VmState * vmstate)
{
	Vm::Push_Array(arr,vmstate);
}

void PushDict(pDict dict,VmState * vmstate)
{
	Vm::Push_Dict(dict,vmstate);
}

void PushBool(bool arr,VmState * vmstate)
{
	Vm::Push_Bool(arr,vmstate);
}
void PushObject(pInst arr,VmState * vmstate)
{
	Vm::Push_Object(arr,vmstate);
}



StackState CallFunction(StackState fu,VmState * vmstate)
{
	StackState func = Vm::CallFunction(fu,vmstate);
	return func;
}


StackState Number_CreateNumber(double d)
{
	StackState sk;
	sk.d = d;
	sk.v=M_NUMBER;	
	return sk;
}

StackState Null_CreateNull()
{
	StackState sk;
	sk.v=M_NULL;	
	return sk;	

}

StackState Bool_CreateBool(bool b)
{
	StackState sk;
	sk.b = b;
	sk.v=M_BOOL;	
	return sk;	

}

StackState Object_CreateObject(pInst p)
{
	StackState sk;
	sk.p = p;
	sk.v=M_OBJECT;	
	return sk;
}

VmState* NewVmState()
{
	return Vm::NewVmState();
}

void NewVm(VmState* vmstate)
{
	Vm::NewVm(vmstate);
}
//多线程，用于清楚多线成产生的垃圾
void ClearVmState(VmState* vmstate)
{
	Vm::ClearVmState(vmstate);
}