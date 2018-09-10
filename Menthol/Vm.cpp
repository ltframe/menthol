#include "Vm.h"
#include <windows.h>
#include "MMath.h"
#include "MLogic.h"
#include "MBitwise.h"
#include "MGc.h"



namespace Vm
{
	static Instruction* codelist;
	static vector<RunTimeState*> *runtimestatelist;
	static char ModulePath[_MAX_PATH];
	static RunTimeState* currentruntimestate;
	static StackState* sp;
	static StackState* bp;
	static StackState* stackbase;
	static vector<StringValue> *dictkeys;
	static vector<StackState> stacklist;
	static vector<PackageAttr> *filetree;
	static int calltype = 0;
	static StackState* callbp=0;
	static int garbagescount;

	static void MarkStack()
	{
		for(int i=0;i<sp-stackbase;i++)
		{
			StackState* _s = stackbase+i;
			if(_s->v==M_ARRAY)
			{
				MGc::MarkArray(_s->parray->array);
				_s->parray->mark = 1;
				continue;
			}
			if(_s->v==M_DICT)
			{
				MGc::MarkDict(_s->pdict->dict);
				_s->pdict->mark = 1;
				continue;
			}
			if(_s->v==M_STRING)
			{
				_s->str->mark = 1;
				continue;
			}
		}
	}

	static void MarkGarbages()
	{
		if(garbagescount>=MAXGARBAGE||MGc::GetGarBageMemorySize()>=MAXGARBAGEMEMORYSIZE)
		{	
			MGc::MarkAllGarbages();
			MarkStack();
			MGc::MarkGlobalGarBage();	
			MGc::ClearGarbage();
			garbagescount= 0;
		}
		garbagescount++;	
	}

	Garbage* CreateArray()
	{
		MarkGarbages();
		return MGc::CreateArray();
	}

	Garbage* CreateDict()
	{
		MarkGarbages();
		return MGc::CreateDict();
	}


	Garbage* GetStringConstants(int index)
	{
		MarkGarbages();
		return MGc::CollectGarbage_String(const_cast<char*>(currentruntimestate->strings->at(index).c_str()),M_SSTRING);
	}


	Garbage* CreateString(char* str)
	{
		MarkGarbages();
		return MGc::CreateString(str);
	}


	Garbage* CreateDictKeyString(hashValue value)
	{
		MarkGarbages();
		return MGc::CollectGarbage_String(const_cast<char*>(GetDictKeyByHash(value)),M_SSTRING);
	}




	void Init(void)
	{
		
		runtimestatelist = new vector<RunTimeState*>();
		filetree =new vector<PackageAttr>();
		dictkeys =new vector<StringValue>();
		stacklist.resize(1024);
		stackbase = &stacklist[0];
		sp=stackbase;
		bp = stackbase;
			
		StackState vv;
		vv.v = M_BPMARK;
		StackMark m = {0,0};
		vv.m = m;
		*sp++ = vv;
		MGc::InitWGc();

	}
	void AddRunTimeStateList(RunTimeState* rst)
	{

		//VECTORFORSTART(RunTimeState*,runtimestatelist,itx88)
		//	if((*itx88)->pname==rst->pname){
		//		return;
		//	}	
		//VECTORFOREND
		runtimestatelist->push_back(rst);
	}
	static bool IsPackageInRunTimeStateList(string pname,int ptype)
	{
		VECTORFORSTART(RunTimeState*,runtimestatelist,it)
			if((*it)->pname==pname && (*it)->ptype==ptype)
			{
				return 1;
			}
		VECTORFOREND
			return 0;
	}

StackState FindGlobalMemory(hashValue hash)
{
	//for (std::vector<StackState>::iterator it = currentruntimestate->globalvalues->begin() ; it != currentruntimestate->globalvalues->end(); ++it)
	//{
	VECTORFORSTART(StackState,currentruntimestate->globalvalues,it)
		if(hash==(*it).namehash)
		{
			return	(*it);
		}
	VECTORFOREND
	//}
	StackState d = {0,0,0,M_NULL};
	return d;
}

void RestoreGlobalMemory(StackState s)
{
	//for (std::vector<StackState>::iterator it = currentruntimestate->globalvalues->begin() ; it != currentruntimestate->globalvalues->end(); ++it)
	//{		
	VECTORFORSTART(StackState,currentruntimestate->globalvalues,it)
		if(s.namehash==(*it).namehash)
		{
			(*it)=s;
			return;;
		}
	//}
	VECTORFOREND

	currentruntimestate->globalvalues->push_back(s);
	if(s.v==M_STRING){
		MGc::CopyToGlobalGarBage(s.str);
	}
	if(s.v==M_ARRAY){
		MGc::CopyToGlobalGarBage(s.parray);
	}
	if(s.v==M_DICT){
		MGc::CopyToGlobalGarBage(s.pdict);
	}
}


//release function on programe end 
void Release(void)
{
	delete	runtimestatelist;
	delete  filetree;
}


void InitStack(StackState v1,StackState  v2)
{
	*sp++= v1;
	*sp++ = v2;
}


int GetRunTimeRecored(string name)
{
	//for (std::vector<FunctionAtter>::iterator it = currentruntimestate->functionlist->begin() ; it != currentruntimestate->functionlist->end(); ++it)
	//{
	VECTORFORSTART(FunctionAtter,currentruntimestate->functionlist,it)
		
		if((*it).name== name)
		{
			return it-currentruntimestate->functionlist->begin();
		}
	//}
	VECTORFOREND
	return -1;
}


FunctionAtter GetRunTimeFunctionAtter(hashValue hash)
{
	//for (std::vector<FunctionAtter>::iterator it = currentruntimestate->functionlist->begin() ; it != currentruntimestate->functionlist->end(); ++it)
	//{
	VECTORFORSTART(FunctionAtter,currentruntimestate->functionlist,it)
		if((*it).hash== hash)
		{
			return (*it);
		}
	//}
	VECTORFOREND
	FunctionAtter fa = {"",0,-1,-1};
	return fa;
}


FunctionAtter GetRunTimeFunctionAtterByIndex(int index)
{
	
	if(index<0 || index>=currentruntimestate->functionlist->size())
	{
		FunctionAtter fa = {"",0,-1,-1};
		return fa;
	}
	return currentruntimestate->functionlist->at(index);
	
}


void CreateFunctionRecoredList(FunctionAtter fa)
{

	fa.hash =  MCommon::CreateInstance()->ELFHash(fa.name);
	currentruntimestate->functionlist->push_back(fa);
}

void CreateStringConstants(char* s)
{
	//for (std::vector<string>::iterator it = currentruntimestate->strings->begin() ; it != currentruntimestate->strings->end(); ++it)
	//{
	VECTORFORSTART(string,currentruntimestate->strings,it)
		if((*it)==s){
			return;
		}
	//}
	VECTORFOREND
	
	currentruntimestate->strings->push_back(s);
}


const char* GetStringConstantsByHash(hashValue hash)
{
	//for (std::vector<string>::iterator it = currentruntimestate->strings->begin() ; it != currentruntimestate->strings->end(); ++it)
	//{
	VECTORFORSTART(string,currentruntimestate->strings,it)
		if(MCommon::CreateInstance()->ELFHash(*it)==hash){
			return (*it).c_str();
		}
	//}
	VECTORFOREND
	return "";
}

const char* GetDictKeyByHash(hashValue hash)
{
	//for (std::vector<StringValue>::iterator it = dictkeys->begin() ; it != dictkeys->end(); ++it)
	//{
	VECTORFORSTART(StringValue,dictkeys,it)
		if((*it).hash==hash){
			return (*it).str.c_str();
		}
	//}
	VECTORFOREND
	return 0;
}


void CreateDictKeyString(char* s)
{
	//for (std::vector<StringValue>::iterator it = dictkeys->begin() ; it != dictkeys->end(); ++it)
	//{
	VECTORFORSTART(StringValue,dictkeys,it)
		if((*it).str==string(s)){
			return;
		}
	//}
	VECTORFOREND
	StringValue sv = {string(s),MCommon::CreateInstance()->ELFHash(s)};
	dictkeys->push_back(sv);
}



PackageState* GetPackageAttr(int i)
{
	if(i<0 || i>=currentruntimestate->includepackages->size()){
		MError::CreateInstance()->PrintRunTimeError("Package Not Found");
	}
	return currentruntimestate->includepackages->at(i);
}

void Vm::InitCode(Instruction x,int &codep,vector<Instruction>& codealllist){	    
	codealllist.push_back(x);codep++;
}


void Push_Number(double d)
{
	(*sp).v = M_NUMBER;
	(*sp++).d = d;
}

void Push_String(pString str)
{
	(*sp).v= M_STRING;
	(*sp++).str = str;
}

void Push_Array(pArray arr)
{
	(*sp).v= M_ARRAY;
	(*sp++).parray = arr;
}

void Push_Dict(pDict dict)
{
	(*sp).v= M_DICT;
	(*sp++).pdict = dict;
}



void CreateFunctionCall(int paramcount)
{
	StackState value;					
	value.v= M_NULL;
	*sp++ = value;

	value.v= M_BPMARK;
	 //执行函数前，压入MARK记录当前的（函数调用前的，为了返回以后恢复原有）bp,sp,ip					
	StackMark m = {bp,0,paramcount,currentruntimestate};
	value.m = m;				
	//bp = sp - stackbase; //sp为当前栈的栈指针
	*sp++ = value;	
	callbp = bp;
	calltype = 1;
}

StackState CallFunction(StackState fun)
{

	StackState *b = sp-1;
	while (b->v != M_BPMARK) b--;
	bp = b;
	(bp)->m.address = codelist; //保存现在ip

	StackState *func = &fun;
	FunctionAtter fa;

					
	currentruntimestate = static_cast<RunTimeState*>(func->p);

	if(func->v==M_PFUN)
	{
		fa= GetRunTimeFunctionAtter(func->hash);
	}else 
	{
		fa = GetRunTimeFunctionAtterByIndex(func->i);
	}

	if(fa.name=="")
	{
		currentruntimestate = (bp->m.rts);
		MError::CreateInstance()->PrintRunTimeError(GetStringConstantsByHash(func->hash)+string(" is not defined"));
	}

	int stackargcount = sp-1-(bp+1);//当前栈内参数					 
	if(stackargcount>fa.paramcount){
		sp=sp-(stackargcount-fa.paramcount);
	}
	if(stackargcount<fa.paramcount){
		for(int i=0;i<fa.paramcount-stackargcount;i++){
			StackState value;					
			value.v= M_NULL;
			*sp++ = value;	
		}
	}
	if(fa.lenght==-1)//外部扩展的函数
	{
		funcallback f = (funcallback)fa.postion;
		StackState st= f();
		*sp++ = st;
		currentruntimestate =  (bp->m.rts);
		AdjustStack();

	}else
	{
		codelist =fa.postion;
		sp--;
		Execute();
	}
	return *(--sp);
}



inline void MainFuncitonCode(int &codespostion,vector<Instruction>& codealllist)
{
	//InitCode(OP_ADJUSTBP,codespostion,codealllist);
	InitCode(OP_PUSHMARK,codespostion,codealllist);
	InitCode(2,codespostion,codealllist);
	InitCode(OP_LOADS,codespostion,codealllist);
	InitCode(1,codespostion,codealllist);
	InitCode(OP_LOADS,codespostion,codealllist);
	InitCode(2,codespostion,codealllist);
	InitCode(OP_PUSHFUN,codespostion,codealllist);
	InitCode(MMAINHASH,codespostion,codealllist);
	InitCode(OP_CALLFUNC,codespostion,codealllist);
	InitCode(OP_HALT,codespostion,codealllist);

}
void PintCode(int c){

	int i = 0;
	while(i<=c){
		cout<<(codelist[i]);
		cout<<",";
		i++;
	}
	cout<<"\r\n------------------------------------------"<<endl;
}


void EntryPoint(PackageAttr pa,char* workdir)
{
	strcpy(ModulePath,MCommon::CreateInstance()->GetRunPath().c_str());
	int postion=0;
	
	//ImportBuiltinPackAge();//载入系统函数，反转后排在第一个位，保证在所有程序执行前。先执行系统函数
	

	MBinary *wb =new  MBinary();
	//AutoLoadPackAge(filetree,ModulePath);
	filetree->push_back(pa);//压入启动文件，启动文件最后执行
	wb->MReadImportFiles(pa.fname,filetree,ModulePath,workdir);	
	//AutoLoadPackAge(filetree,ModulePath);

	reverse(filetree->begin(),filetree->end());

	int codespostion=0;

	runtimestatelist =new vector<RunTimeState*>();
	vector<Instruction> codealllist;

	MainFuncitonCode(codespostion,codealllist);


	


	for(int f=0;f<filetree->size();f++){

		PackageAttr pa = filetree->at(f);

		if(IsPackageInRunTimeStateList(pa.pname,pa.ptype))
		{
			continue;
		}

		vector<Instruction> globalcodelist;

		currentruntimestate =new RunTimeState();
		currentruntimestate->doubles = new vector<double>();
		currentruntimestate->functionlist = new vector <FunctionAtter>();
		currentruntimestate->strings = new vector<string>();
		currentruntimestate->includepackages = new vector<PackageState*>();
		currentruntimestate->globalvalues =new vector<StackState>();

		
		currentruntimestate->hash = MCommon::CreateInstance()->ELFHash(pa.pname);
		currentruntimestate->pname = pa.pname;
		currentruntimestate->ptype = pa.ptype;
		if(pa.ptype==MPA_PACKAGE || pa.ptype==MPA_SPACKAGE){
			const char* filename = pa.fname;
			wb->ReadBinary(filename,currentruntimestate->functionlist,currentruntimestate->strings,&codealllist,globalcodelist,currentruntimestate->doubles,currentruntimestate->includepackages,runtimestatelist,dictkeys);
			
			///CreateVmState(FunctionRecoredList,stringconstants,doubleconstants,packagelist,f);
			AddRunTimeStateList(currentruntimestate);
			char c;
			codelist =new Instruction[globalcodelist.size()];
			for (int i = 0; i < globalcodelist.size(); i++)
			{
				codelist[i]=(globalcodelist[i]);
			}
			//garbagescope = GLOBAL;
			Instruction* _codelist = codelist; 
			if(!Execute()){
				//ip = 0;
				
				//free(codelist);
				codelist  =_codelist;
				delete[] codelist;
				codelist = 0;
				continue;
			}
		}
		if(pa.ptype==MPA_DLL || pa.ptype==MPA_SDLL)
		{		
			HMODULE h = ::LoadLibraryA(pa.fname);	
			int c = strlen(pa.pname)+7;
			char* _initname =new char[c];
			memset(_initname,0,c);
			strcat(_initname,pa.pname);
			strcat(_initname,"_Init");
			_initname[c] = '\0';
			initfuncallback ProcAdd = (initfuncallback) GetProcAddress(h,_initname); 
			ProcAdd();
			AddRunTimeStateList(currentruntimestate);

		}
		currentruntimestate = 0;
	}
	
	//free(codelist);
	codelist = 0;
	//garbagescope = LOCAL;
	codelist =new Instruction[codealllist.size()];
	memset(codelist,0,codealllist.size()+1);
	for (int i = 0; i < codealllist.size(); i++)
	{
		codelist[i]=(codealllist[i]);
	}

	for (std::vector<RunTimeState*>::iterator it1 = runtimestatelist->begin() ; it1 != runtimestatelist->end(); ++it1){		
		for (std::vector<FunctionAtter>::iterator it = (*it1)->functionlist->begin() ; it != (*it1)->functionlist->end(); ++it)
		{
			if((*it).lenght!=-1){
				(*it).postion = codelist+codespostion;
				codespostion+=(*it).lenght;
			}
		}
	}

#ifndef NDEBUG
	PintCode(codealllist.size());
#endif
	//clock_t start = clock();
	filetree->clear();
  	Execute();
	//clock_t end = clock();

}


int Execute()
{
	 for (;;) {

		switch (*codelist++)
		{	 
			case OP_PUSHNUMBER:
				{
					(*sp).v = M_NUMBER;
					(*sp++).d = *codelist++;
					break;
				}
				
			case OP_PUSHDOUBLE:
				{
					(*sp).v = M_NUMBER;
					(*sp++).d =currentruntimestate->doubles->at(*codelist++);
					break;
				}
				
			case OP_PUSHHASH:
				{

					(*sp).v = M_HASH;
					(*sp++).hash =*codelist++;	
					break;
				}
			case OP_PUSHSTRING:
				{ 
					(*sp).v = M_STRING;
					(*sp++).str=GetStringConstants(*codelist++);
					break;
				}
			case OP_PUSHBOOL:
				{
					(*sp).v = M_BOOL;
					(*sp++).b = (bool)(*codelist++);	
					break;
				}
			case OP_RET:
				 {		
					currentruntimestate = bp->m.rts;
     			 	AdjustStack();
					if(calltype && bp==callbp)
					{
						calltype = 0;
						callbp =0;
						return 1;
					}
					break;
				 }
			case OP_PUSHMARK:
				{
					
					StackState value;					
					value.v= M_BPMARK;
					 //执行函数前，压入MARK记录当前的（函数调用前的，为了返回以后恢复原有）bp,sp,ip					
					StackMark m = {bp,0,*codelist++,currentruntimestate};
					value.m = m;				
					//bp = sp - stackbase; //sp为当前栈的栈指针
					*sp++ = value;	
					break;
				}
			
			case OP_PUSHTRYMARK:
				{
					StackState value;					
					value.v= M_TRYMARK;
					Instruction* _ip = codelist;

					int address = *codelist++;
					unsigned int paramercount= *codelist++;

					TryMark m = {bp,_ip+(address<0?address+1:address),paramercount,currentruntimestate};
					value.m = m;	
					*sp++ = value;
					break;
				}
			case OP_THROWSTART:
				{
					while (sp->v != M_TRYMARK) sp--;
					sp++;
					break;
				}
			case OP_THROWEND:
				{
					StackState *b = sp-1;
					while (b->v != M_TRYMARK) b--;
					int stackargcount = sp-b-1;

					codelist = b->m.address;
					currentruntimestate = b->m.rts;
					bp = b->m.bp;
					if(stackargcount>b->m.paramercount){
						sp=sp-(stackargcount-b->m.paramercount);
					}
					if(stackargcount<b->m.paramercount){
						for(int i=0;i<b->m.paramercount-stackargcount;i++){
							StackState  value;					
							value.v= M_NULL;
							*sp++ = value;	
						}
					}

					break;
				}
			case OP_PUSHFUN:
				{
					(*sp).v = M_FUN;
					(*sp).p = currentruntimestate;
					(*sp++).i = *codelist++;//表示自定义函数名字的hash值
					break;
				}
			case OP_CALLFUNC:
				{						
					StackState *b = sp-1;
					while (b->v != M_BPMARK) b--;
					bp = b;
					(bp)->m.address = codelist; //保存现在ip

					StackState *func = sp-1;
					FunctionAtter fa;

					
					currentruntimestate = static_cast<RunTimeState*>(func->p);

					if(func->v==M_PFUN || func->hash==MMAINHASH)
					{
						fa= GetRunTimeFunctionAtter(func->hash);
					}else 
					{
						fa = GetRunTimeFunctionAtterByIndex(func->i);
					}
					if(fa.name=="")
					{
						string erromsg = "";
						if(func->hash==MMAINHASH){
							erromsg = "mmain";
						}else
						{
							erromsg =GetStringConstantsByHash(func->hash);
						}
						currentruntimestate = (bp->m.rts);
						MError::CreateInstance()->PrintRunTimeError(erromsg+string(" is not defined"));
						return 1;
					}


					int stackargcount = sp-1-(bp+1);//当前栈内参数					 
					if(stackargcount>fa.paramcount){
						sp=sp-(stackargcount-fa.paramcount);
					}
					if(stackargcount<fa.paramcount){
						for(int i=0;i<fa.paramcount-stackargcount;i++){
							StackState value;					
							value.v= M_NULL;
							*sp++ = value;	
						}
					}
					

					if(fa.lenght==-1)//外部扩展的函数
					{
						funcallback f = (funcallback)fa.postion;
						StackState st= f();
						*sp++ = st;
						currentruntimestate =  (bp->m.rts);
						AdjustStack();

					}else
					{
						//currentruntimestate = currentruntimestate->returnruntimestate;
						codelist =fa.postion;
						//if(fa.name=="_wmain"){
							sp--;
						//}
					}
				
				   break;
				}
	
			

			case OP_ADD:
				{
					StackState* value1 =sp-2;
					StackState* value2 =sp-1;
					if(!MMath::Add(value1,value2))
					{
						return 0;
					}
					sp--;
					break;
				}
			case OP_ADD1:
				{
					StackState* _t =(bp+*codelist++); 
					_t->d+=1;
					_t->v=M_NUMBER;
					break;
				}
			case OP_POWER:
				{
					StackState* value1 =sp-2;
					StackState* value2 =sp-1;
					if(!MMath::Power(value1,value2))
					{
						return 0;
					}
					sp--;
					break;
				}
			case OP_SUB:
				{
					StackState* value1 =sp-2;
					StackState* value2 =sp-1;
					if(!MMath::Sub(value1,value2))
					{
						return 0;
					}
					sp--;
					break;
				}
			case OP_MUL:
				{
					StackState* value1 =sp-2;
					StackState* value2 =sp-1;
					if(!MMath::Mul(value1,value2))
					{
						return 0;
					}
					sp--;
					break;
				}
			case OP_DIV:
				{
					StackState* value1 =sp-2;
					StackState* value2 =sp-1;
					if(!MMath::Div(value1,value2))
					{
						return 0;
					}
					sp--;
					break;
				}
			case OP_MOD:
				{
					StackState* value1 =sp-2;
					StackState* value2 =sp-1;
					if(!MMath::Mod(value1,value2))
					{
						return 0;
					}
					sp--;
					break;
				}
			case OP_XOR:
				{
					StackState* value1 =sp-2;
					StackState* value2 =sp-1;
					if(!MLogic::Xor(value1,value2))
					{
						return 0;
					}
					sp--;
					break;
				}
			case OP_STOREM:
				{
					StackState* value = sp-1;
					//int k =_code.i;
					value->namehash = *codelist++; //函数名称的HASH值
					RestoreGlobalMemory(*value);
					
					//sp++;
					break;
				}
			case OP_INITM:
				{
					StackState* value = --sp;
					value->namehash = *codelist++;//函数名称的HASH值
					
					RestoreGlobalMemory(*value);
					break;
				}
			case OP_STORES:
				{
					StackState* v = (bp+*codelist++); //被更新的栈
					*v=*(sp-1);//更新的数据
					break;
				}
		
		  case OP_LOADM:
				{
					StackState value= FindGlobalMemory(*codelist++);
					(*sp++) =value;
					break;
				}
		case OP_LOADS:
				{
					int kkkk = *codelist++;
					*sp++=*(bp+kkkk);
					break;
				}
		 case OP_NOP:
			 {
				break;
			 }
		case OP_LT:
			 {
			 		StackState* value1 =sp-2;
					StackState* value2 =sp-1;
					value1->v = M_BOOL;
					value1->b=(value1->d<value2->d);
					sp--;
					break;
			 }
			 
		 case OP_LE:
			 {
			 		StackState* value1 =sp-2;
					StackState* value2 =sp-1;
					if(!MLogic::Le(value1,value2))
					{
						return 0;
					}
					sp--;
				break;
			 }
		 case OP_GEEQ:
			 {
					StackState* value1 =sp-2;
					StackState* value2 =sp-1;
					if(!MLogic::Geeq(value1,value2))
					{
						return 0;
					}
					sp--;
					break;
			 }
		 case OP_LEEQ:
			 {
				StackState* value1 =sp-2;
					StackState* value2 =sp-1;
					if(!MLogic::Leeq(value1,value2))
					{
						return 0;
					}
					sp--;
					break;
			 }
		   case OP_EQEQ:
			 {
					StackState* value1 =sp-2;
					StackState* value2 =sp-1;
					if(!MLogic::EqEq(value1,value2))
					{
						return 0;
					}
					sp--;
					break;
			 }
		   case  OP_NEQ:
			   {
					StackState* value1 =sp-2;
					StackState* value2 =sp-1;
					if(!MLogic::Neq(value1,value2))
					{
						return 0;
					}
					sp--;
					break;
			   }
		   case OP_SHIFTL:
			   {
					StackState* value1 =sp-2;
					StackState* value2 =sp-1;
					if(!MBitwise::SHIFTL(value1,value2))
					{
						return 0;
					}
					sp--;
					break;
			   }
		 case OP_SHIFTR:
			   {
					StackState* value1 =sp-2;
					StackState* value2 =sp-1;
					if(!MBitwise::SHIFTR(value1,value2))
					{
						return 0;
					}
					sp--;
					break;
			   }
		 case OP_CREATEARRAY:
			 {
				StackState  result;
				result.v = M_ARRAY;
				result.parray = CreateArray();
				*sp++ = result;
				break;
			 }
		 case OP_SETARRAY:
			 {

				unsigned int c =*codelist++;
				vector<StackState>* _ss = (vector<StackState>*)(sp-c-1)->parray->array;	
				_ss->resize(c);
				sp = sp-c;
				for (int i = 0; i < c; i++)
				{
					_ss->at(i)=*(sp+i);
				}
				break;
			 }
		case OP_SETARRAYELEMENT:
			 {				  
				  int index = (--sp)->d;		
				  StackState* pa = (--sp);
				  StackState value =*(sp-1);
				  if(pa->v!=M_ARRAY && pa->v!=M_STRING)
				  {
					MError::CreateInstance()->PrintRunTimeError("It is not an array or a string");
					return 1;
				  }

				  if(pa->v==M_ARRAY){
					  vector<StackState>* _arr = (vector<StackState>*)pa->parray->array; 
					  int size =_arr->size();
					  if(size>index) {
						  _arr->at(index) = value;

					  }else
					  {
						  for(int i=size;i<=index;i++){
							  if(i==index){
								_arr->push_back(value);
							  }else{
								StackState nullvalue;					
								nullvalue.v= M_NULL;
								_arr->push_back(nullvalue);
							  }
						  }
					  }
				  }
				  if(pa->v==M_STRING){
					  if(value.v==M_STRING){
						  pa->str->string[index] = value.str->string[0]; 
					  }
				  }
				  break;
			 }
		case OP_GETARRAYELEMENT:
			{
				int gettype = (--sp)->d;
				int index2= (--sp)->d;
				int index =(--sp)->d;
				
				StackState* stt= (--sp);

				if(stt->v!=M_ARRAY && stt->v!=M_STRING)
				{
					MError::CreateInstance()->PrintRunTimeError("It is not an array or a string");
					return 1;
				}

				if(stt->v==M_STRING)
				{
					if(gettype==0){
						char str[2] = {(stt->str->string)[index],'\0'};
						StackState  result;
						result.v = M_STRING;
						result.str = CreateString(str);
						*sp=result;
					}
					if(gettype==1){
						int stringlenght = strlen(stt->str->string);
						if(index>=stringlenght){
							MError::CreateInstance()->PrintRunTimeError("Array out of bounds");
							return 1;
						}
						int memorylenght = stringlenght-index;
						int length = memorylenght+1;
						char *dest =new char[length];
						char*_dest = dest;
						memset(dest,0,length);
						
						int i = index;
						while(i<stringlenght){
							*dest++ = stt->str->string[i];
							i++;
						}
						dest = _dest;
						dest[memorylenght] = '\0';
						StackState  result;
						result.v = M_STRING;
						result.str = CreateString(dest);
						*sp=result;
						delete[] dest;
					}

					if(gettype==2){
						if(index>=strlen(stt->str->string)){
							MError::CreateInstance()->PrintRunTimeError("Array out of bounds");
							return 1;
						}
						int length = index+2;
						char *dest =new char[length];
						char*_dest = dest;
						memset(dest,0,length);
						
						int i = 0;
						while(i<length){
							*dest++ = stt->str->string[i];
							i++;
						}
						dest = _dest;
						dest[index+1] = '\0';
						StackState  result;
						result.v = M_STRING;
						result.str = CreateString(dest);
						*sp=result;
						delete[] dest;
					}

					if(gettype==3){
						if(index<0 || index2<0){
								MError::CreateInstance()->PrintRunTimeError("index value cannot be less than zero");
								return 1;
						}else
						{
							if(index>=strlen(stt->str->string)){
								MError::CreateInstance()->PrintRunTimeError("Array out of bounds");
								return 1;
							}
							if(index2>=strlen(stt->str->string)){
								MError::CreateInstance()->PrintRunTimeError("Array out of bounds");
								return 1;
							}

							if(index>index2){
								MError::CreateInstance()->PrintRunTimeError("Array out of bounds");
								return 1;
							}						
						}
						

						int length = index2-index+1;
						char *dest =new char[length+1];
						char*_dest = dest;
						memset(dest,0,length);
						for(int i = index;i<=index2;i++){
							*dest++ = stt->str->string[i];
						}						
						dest = _dest;
						dest[length] = '\0';
						StackState  result;
						result.v = M_STRING;
						result.str = CreateString(dest);
						*sp=result;
						delete[] dest;
					}
					
				}else{

					vector<StackState>* _arr = (vector<StackState>*)stt->parray->array;
					if(gettype==0){
						if(index>_arr->size()-1){
							MError::CreateInstance()->PrintRunTimeError("Array out of bounds");
							return 1;
						}else{
							*sp=_arr->at(index);
						}
					}
					if(gettype==1)
					{
						StackState  result;
						result.v = M_ARRAY;
						pArray arr = CreateArray();
						vector<StackState>* _t = arr->array;
						for (int i=index;i<_arr->size();i++){			
							_t->push_back(_arr->at(i));
						}
						result.parray = arr;
						*sp = result;
					}
					if(gettype==2)
					{
						StackState  result;
						result.v = M_ARRAY;
						pArray arr = CreateArray();
						vector<StackState>* _t = arr->array;
						for (int i=0;i<index;i++){			
							_t->push_back(_arr->at(i));
						}
						result.parray = arr;
						*sp = result;
					}
					if(gettype==3)
					{
						StackState  result;
						result.v = M_ARRAY;
						pArray arr = CreateArray();
						vector<StackState>* _t =  arr->array;
						for (int i=index;i<=index2;i++){			
							_t->push_back(_arr->at(i));
						}
						result.parray = arr;
						*sp = result;
					}
				}
				sp++;
				break;
			}

		case OP_CREATEDICT:
			{
				StackState  result;
				result.v = M_DICT;
				result.pdict = CreateDict();	
				*sp++ = result;
				break;
			}
		case OP_SETDICT:
			{

				int c =*codelist++;				
				map<hashValue,StackState>* _ss = (map<hashValue,StackState>*)(sp-(c*2)-1)->pdict->dict;	
				sp = sp-(2*c);
				for (int i = 0; i < c; i++)
				{
					StackState value =*(sp+(i*2));
					
					StackState key =*(sp+(i*2+1));					
					_ss->insert(pair<hashValue,StackState>(key.hash,value));
				}
				break;
			}
		case OP_GETDICTELEMENT:
			{
				hashValue key = *codelist++;			
				StackState* p = --sp;
				if(p->v!=M_DICT){
					MError::CreateInstance()->PrintRunTimeError("It is not a dictionary");
					return 1;
				}
				map<hashValue,StackState>* _ss = (map<hashValue,StackState>*)p->pdict->dict;	
				map<hashValue,StackState>::iterator it = _ss->find(key);
				if (it == _ss->end()){
					StackState _st;
					_st.v = M_NULL;
					*sp=_st;
				}else
				{
					*sp=it->second;
				}			
				sp++;
				break;
			}
		case OP_SETDICTELEMENT:
 			{
				 hashValue key = *codelist++;			
				  StackState* pa = (--sp);
				  if(pa->v!=M_DICT){
					MError::CreateInstance()->PrintRunTimeError("It is not a dictionary");
					return 1;
				  }
				  map<hashValue,StackState>* _ss = (map<hashValue,StackState>*)pa->pdict->dict;	
				  StackState value =*(--sp);
				  if (_ss->find(key) == _ss->end()){
					 _ss->insert(pair<hashValue,StackState>(key,value));
				  }else
				  {
					  _ss->find(key)->second = value;
				  }
				  sp++;
				  break;
			}
		case OP_JMP:
			{
				StackState *b = sp-1;
				if(b->v!=M_BOOL)
				{
					b->v = M_BOOL;
					b->b = b->d;
				}
				if(b->b){ //如果为true顺序执行代码即可
					*codelist++;
				}else
				{
					Instruction _ip = *codelist;
					codelist +=_ip;
				}
				sp--;
				break;
			}
		case OP_UJMPS:
			{
			 	Instruction _ip = *codelist;//为什么没有做*codelist++，因为如果如果在++，则代码现在指向的是要跳跃数字的下一个代码，则下面减的时候需要多减掉1，减去刚才被++的那个代码
				codelist -=_ip;
				break;
				}
		case OP_UJMP:
			{
			 	Instruction _ip = *codelist;
				codelist +=_ip;
				break;
				}
		 case OP_HALT:
			 {				
				return 1;
			 }
		 case OP_OR:
			 {
					StackState* value1 =sp-2;
					StackState* value2 =sp-1;
					if(!MLogic::Or(value1,value2))
					{
						return 0;
					}
					sp--;
					break;
			 }
		 case OP_AND:
			{
				StackState* value1 =sp-2;
					StackState* value2 =sp-1;
					if(!MLogic::And(value1,value2))
					{
						return 0;
					}
					sp--;
					break;
			}
		case OP_BIT_OR:
			 {
				 StackState* value1 =sp-2;
					StackState* value2 =sp-1;
					if(!MBitwise::BitOr(value1,value2))
					{
						return 0;
					}
					sp--;
					break;
			 }
		 case OP_BIT_AND:
			{
					StackState* value1 =sp-2;
					StackState* value2 =sp-1;
					if(!MBitwise::BitAnd(value1,value2))
					{
						return 0;
					}
					sp--;
					break;
			}
		
			case OP_ADJUSTSP:
			{

				StackState* newsp = bp+(*codelist++)+1;		
				sp= newsp;
				break;
			}
			case OP_ADJUSTBP:
			{
				StackState *b = sp-1;
				while (b->v != M_BPMARK) b--;
				bp = b;	
				break;
			}

			case OP_PUSHRS:
			{
				StackState value;					
				value.v= M_NULL;
				value.d = 0;
				/*CodeNumber _code;
				_code.m.c1 = *codelist++; _code.m.c2 = *codelist++;;_code.m.c3 = *codelist++;; _code.m.c4 = *codelist++;*/
				*sp++ = value;
				break;
			}
			case OP_GETSEQ: //for in 的集合专用，in 后面的集合无法判断出是数组还是字典，所以要用专们的指令取出
			{

				int key = (sp-1)->d;	
				StackState* seq=sp-3;
				
				if(seq->v!=M_ARRAY && seq->v!=M_DICT && seq->v!=M_STRING)
				{
					MError::CreateInstance()->PrintRunTimeError("It is not an Collection");
					return 1;
				}

				if(seq->v==M_STRING){
					if(key>=strlen(seq->str->string)){
							codelist +=*codelist;
					}else
					{
						codelist++;					
						//*sp=_arr->at(key);	
						//sp++;
						StackState* _t = bp+*codelist++;
						char str[2] = {(seq->str->string)[key],'\0'};
						_t->v = M_STRING;
						_t->str = CreateString(str);
					}
				}

				if(seq->v==M_ARRAY){
					vector<StackState>* _arr = (vector<StackState>*)seq->parray->array;
					if(key>=_arr->size()){
							codelist +=*codelist;
					}else
					{
						codelist++;					
						//*sp=_arr->at(key);	
						//sp++;
						*(bp+*codelist++) = _arr->at(key);
					}
				}
				if(seq->v==M_DICT){
					map<hashValue,StackState>* _ss = (map<hashValue,StackState>*)seq->pdict->dict;
					//vector<StackState>* _arr = new vector<StackState>();
				
					if(key>=_ss->size())
					{
						codelist +=*codelist;
					}else
					{
							int index = 0;
							codelist++;
							StackState* _t = bp+*codelist++;
							for(map <hashValue, StackState>::iterator m1_Iter = _ss->begin( ); m1_Iter != _ss->end( ); m1_Iter++)
							{
								if(index==key){	
									_t->v = M_HASH;
									_t->hash = (*m1_Iter).first;
									break;
								}
								index++;
							}	
					}
					//delete _arr;
					//此处可能需要删除原来的字典

				}	
				break;
			}
			case OP_PUSHPACKAGE:
			{
				(*sp).v = M_PACKAGE;
				(*sp++).i = *codelist++;
				break;
			}
			case OP_PUSHPACKAGEFUNC:
			{
				StackState *b = sp-1;
				PackageState* pa = GetPackageAttr(b->i);
				b->v = M_PFUN;
				b->hash = *codelist++; //function's hash value
				b->p = pa->rts;
				break;
			}		
			case OP_GETPACKAGEATTER:
				{
					StackState *b = sp-1;
					PackageState* pa = GetPackageAttr(b->i);
					RunTimeState* _rts = currentruntimestate;
					currentruntimestate = pa->rts;

					*b = FindGlobalMemory(*codelist++);
					currentruntimestate = _rts;
					break;
				}
			case OP_SETPACKAGEATTER:
				{
					StackState *attr  = --sp;
					StackState *value = sp-1;
					PackageState* pa = GetPackageAttr(attr->i);
					RunTimeState* _rts = currentruntimestate;
					currentruntimestate = pa->rts;
					*attr = *value;
					attr->namehash = *codelist++;
					
					RestoreGlobalMemory(*attr);
					currentruntimestate = _rts;
					break;
				}
			case OP_MINUS:
				{
					StackState *v = sp-1;
					if(v->v==M_NUMBER){
						v->d = -1*v->d;
					}
					break;
				}
			case OP_POP:
				{
					sp--;
					break;
				}
			case OP_TJMP:
				{
					if((--sp)->b)
					{  
						*codelist++;
					}else
					{
						Instruction _ip = *codelist;
						codelist +=_ip;
					}
					break;
				}
			case OP_INVERTER:
				{
					StackState *v = sp-1;
					if(v->v!=M_BOOL)
					{
						v->b = v->d;
					}
					v->v = M_BOOL;
					v->b=!(v->b);
					break;
				}
			default:
				return 0;
				break;

		}
		//printf("%s\n", OperateCodeString[code.s-1]);
	}
	return 1;
}





StackState GetParam(int x)
{
	StackState _v;
	_v.v = M_UNKONWN;
	StackState v =  *(bp);
	if(x>v.m.paramercount){
		return _v;
	}
	v =  *(bp+x); 	
	return v;
}

void AdjustStack()
{
	*(bp-1) = *(--sp);
	codelist = (bp)->m.address;
	StackState* newsp = (bp);
    sp = newsp;
	bp = ((bp)->m.bp);
}
}