#include "Vm.h"
#include <windows.h>
#include "MMath.h"
#include "MLogic.h"
#include "MBitwise.h"
#include "MGc.h"





namespace Vm
{
	static int runflag = 0; // 0 global init 1 code
	static Instruction *codeliststart;
	static vector<RunTimeState*> *runtimestatelist;
	static char ModulePath[_MAX_PATH];
	static vector<StringValue> *dictkeys;
	static vector<ImportFileAttr> *filetree;
	static PackAgeType loadextpackagetype;
	//static vector<string> *loadedlibrarys;
	char* mtypes[] = {"M_NUMBER","M_LONG","M_DOUBLE","M_STRING","M_STRING","M_FUN","M_PFUN","","M_BOOL","M_ARRAY","M_DICT","M_NULL","","","M_MODULE","M_HASH","M_UNKONWN","M_OBJECT"};


	VmState* NewVmState()
	{
		VmState* vmstate = new VmState();
		vmstate->gc = MGc::NewWGc();
		return vmstate;
		
	}

	void ClearVmState(VmState* vmstate)
	{
		delete vmstate->gc->garbagecollect;
		delete vmstate->gc;
		delete vmstate;
	}


	static void MarkStack(VmState* vmstate)
	{
		for(int i=0;i<VMSTATESP(vmstate)-VMSTATESTACKBASE(vmstate);i++)
		{
			STACKSTATEPOINTER _s = VMSTATESTACKBASE(vmstate)+i;
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

	static void MarkGarbages(VmState* vmstate)
	{
		if(VMSTATEGARBAGECOUNT(vmstate)>=MAXGARBAGE||MGc::GetGarBageMemorySize(VMSTATEGC(vmstate))>=MAXGARBAGEMEMORYSIZE)
		{	
			MGc::MarkAllGarbages(VMSTATEGC(vmstate));
			MarkStack(vmstate);
			MGc::MarkGlobalGarBage();	
			MGc::ClearGarbage(VMSTATEGC(vmstate));
			VMSTATEGARBAGECOUNT(vmstate)= 0;
		}
		VMSTATEGARBAGECOUNT(vmstate)++;	
	}

	Garbage* CreateArray(VmState* vmstate)
	{
		MarkGarbages(vmstate);
		return MGc::CreateArray(VMSTATEGC(vmstate));
	}

	Garbage* CreateDict(VmState* vmstate)
	{
		MarkGarbages(vmstate);
		return MGc::CreateDict(VMSTATEGC(vmstate));
	}


	Garbage* GetStringConstants(int index,VmState* vmstate)
	{
		/*vector<Garbage*>* list = MGc::GetGarbageCollect();
		VECTORFORSTART(Garbage*,list,it)
			if((*it)->v==M_SSTRING && !strcmp((*it)->string,currentruntimestate->strings->at(index).c_str())){
				(*it)->mark = 0;
				return (*it);
			}
		VECTORFOREND*/

		FINDGARBAGE(M_SSTRING,VMSTATECURRENTRUNTIMESTATE(vmstate)->strings->at(index).c_str(),VMSTATEGC(vmstate));
		MarkGarbages(vmstate);
		return MGc::CollectGarbage_String(CONSTCAST(char)(VMSTATECURRENTRUNTIMESTATE(vmstate)->strings->at(index).c_str()),VMSTATEGC(vmstate),M_SSTRING);
	}


	Garbage* CreateString(char* str,VmState* vmstate)
	{
		/*vector<Garbage*>* list = MGc::GetGarbageCollect();
		VECTORFORSTART(Garbage*,list,it)
			if((*it)->v==M_STRING && !strcmp((*it)->string,str)){
				(*it)->mark = 0;
				return (*it);
			}
		VECTORFOREND*/	
		FINDGARBAGE(M_STRING,str,VMSTATEGC(vmstate));
		MarkGarbages(vmstate);
		return MGc::CreateString(str,vmstate);
	}


	Garbage* CreateDictKeyString(hashValue value,VmState* vmstate)
	{
		/*vector<Garbage*>* list = MGc::GetGarbageCollect();
		VECTORFORSTART(Garbage*,list,it)
			if((*it)->v==M_SSTRING && !strcmp((*it)->string,GetDictKeyByHash(value))){
				(*it)->mark = 0;
				return (*it);
			}
		VECTORFOREND*/
		FINDGARBAGE(M_SSTRING,GetDictKeyByHash(value),VMSTATEGC(vmstate));
		MarkGarbages(vmstate);
		return MGc::CollectGarbage_String(CONSTCAST(char)(GetDictKeyByHash(value)),VMSTATEGC(vmstate),M_SSTRING);
	}


	void _NewVm(VmState* vmstate)
	{
		VMSTATESTACKLIST(vmstate).resize(1024);
		VMSTATESTACKBASE(vmstate) = &VMSTATESTACKLIST(vmstate)[0];
		VMSTATESP(vmstate)=VMSTATESTACKBASE(vmstate);
		VMSTATEBP(vmstate) = VMSTATESTACKBASE(vmstate);
			
		StackState vv;
		vv.v = M_BPMARK;
		StackMark m = {0,0};
		vv.m = m;
		*VMSTATESP(vmstate)++ = vv;
	}

	




	void Init(void)
	{
		runtimestatelist = new vector<RunTimeState*>();
		filetree =new vector<ImportFileAttr>();
		dictkeys =new vector<StringValue>();
		MGc::InitWGc();
	}
	void AddRunTimeStateList(RunTimeState* rst)
	{
		runtimestatelist->push_back(rst);
	}
	static bool IsModuleInRunTimeStateList(string pname)
	{
		VECTORFORSTART(RunTimeState*,runtimestatelist,it)
			if ((*it)->modulename == pname)
			{
				return 1;
			}
		VECTORFOREND
		return 0;
	}

StackState FindGlobalMemory(hashValue hash,RunTimeState* _curentruntimestate,RunTimeState* _callruntimestate,VmState* vmstate)
{
	if(IsEXTPackage(_curentruntimestate->ptype))
	{
		VMSTATECURRENTRUNTIMESTATE(vmstate) = _callruntimestate;
		MError::CreateInstance()->PrintRunTimeError(GetStringConstantsByHash(hash,_callruntimestate)+string(" is not defined"),vmstate);
	}
	VECTORFORSTART(StackState,_curentruntimestate->globalvalues,it)
		if(hash==(*it).namehash)
		{
			return	(*it);
		}
	VECTORFOREND

    if(IsPackage(_curentruntimestate->ptype)){
		
		VMSTATECURRENTRUNTIMESTATE(vmstate) = _callruntimestate;
		MError::CreateInstance()->PrintRunTimeError(GetStringConstantsByHash(hash,_callruntimestate)+string(" is not defined"),vmstate);
	}
	StackState d = {0,0,0,M_NULL};
	return d;
}

void RestoreGlobalMemory(StackState s,VmState* vmstate)
{
	//for (std::vector<StackState>::iterator it = currentruntimestate->globalvalues->begin() ; it != currentruntimestate->globalvalues->end(); ++it)
	//{		
	VECTORFORSTART(StackState,VMSTATECURRENTRUNTIMESTATE(vmstate)->globalvalues,it)
		if(s.namehash==(*it).namehash)
		{
			if((*it).constvalue){
				VECTORFORSTART(string, VMSTATECURRENTRUNTIMESTATE(vmstate)->strings, its)
					if ((*it).namehash == MCommon::CreateInstance()->ELFHash(*its)){
						MError::CreateInstance()->PrintRunTimeError((*its) + " is a Constant variable, cannot be assigned", vmstate);
					}
				VECTORFOREND
				return;
			}
			(*it)=s;
			return;;
		}
	//}
	VECTORFOREND

	VMSTATECURRENTRUNTIMESTATE(vmstate)->globalvalues->push_back(s);
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


void InitStack(StackState v1,StackState  v2,VmState* vmstate)
{
	*VMSTATESP(vmstate)++= v1;
	*VMSTATESP(vmstate)++ = v2;
}


void NewVm(VmState* vmstate)
{
	VMSTATESTACKLIST(vmstate).resize(1024);
	VMSTATESTACKBASE(vmstate) = &VMSTATESTACKLIST(vmstate)[0];
	VMSTATESP(vmstate)=VMSTATESTACKBASE(vmstate);
	VMSTATEBP(vmstate) = VMSTATESTACKBASE(vmstate);
			
	StackState vv;
	vv.v = M_BPMARK;
	StackMark m = {0,0};
	vv.m = m;
	*VMSTATESP(vmstate)++ = vv;

	InitStack(Null_CreateNull(),Null_CreateNull(),vmstate);
}

int GetRunTimeRecored(string name,VmState* vmstate)
{
	VECTORFORSTART(FunctionAtter,VMSTATECURRENTRUNTIMESTATE(vmstate)->functionlist,it)
		
		if((*it).name== name)
		{
			return it-VMSTATECURRENTRUNTIMESTATE(vmstate)->functionlist->begin();
		}
	VECTORFOREND
	return -1;
}


FunctionAtter GetRunTimeFunctionAtter(hashValue hash,RunTimeState* _currentruntimestate)
{
	VECTORFORSTART(FunctionAtter,_currentruntimestate->functionlist,it)
		if((*it).hash== hash)
		{
			return (*it);
		}
	//}
	VECTORFOREND
	FunctionAtter fa = {"",0,-1,-1};
	return fa;
}


FunctionAtter GetRunTimeFunctionAtterByIndex(int index,VmState* vmstate)
{
	
	if(index<0 || index>=VMSTATECURRENTRUNTIMESTATE(vmstate)->functionlist->size())
	{
		FunctionAtter fa = {"",0,-1,-1};
		return fa;
	}
	return VMSTATECURRENTRUNTIMESTATE(vmstate)->functionlist->at(index);
	
}


void CreateFunctionRecoredList(RunTimeState* packageinst,FunctionAtter fa)
{
	fa.hash =  MCommon::CreateInstance()->ELFHash(fa.name);
	packageinst->functionlist->push_back(fa);
}


RunTimeState* CreateModuleRunTime(char* modulename,VmState* vmstate)
{
	if(IsModuleInRunTimeStateList(modulename))
	{
		return 0;
	}

	VMSTATECURRENTRUNTIMESTATE(vmstate) =new RunTimeState();
	VMSTATECURRENTRUNTIMESTATE(vmstate)->doubles = new vector<double>();
	VMSTATECURRENTRUNTIMESTATE(vmstate)->functionlist = new vector <FunctionAtter>();
	VMSTATECURRENTRUNTIMESTATE(vmstate)->strings = new vector<string>();
	VMSTATECURRENTRUNTIMESTATE(vmstate)->includemodule = new vector<ModuleState*>();
	VMSTATECURRENTRUNTIMESTATE(vmstate)->globalvalues =new VECOTRSTACKSTATE();
	VMSTATECURRENTRUNTIMESTATE(vmstate)->debuglist =new vector<MentholDebug>();
		
	VMSTATECURRENTRUNTIMESTATE(vmstate)->hash = MCommon::CreateInstance()->ELFHash(modulename);
	VMSTATECURRENTRUNTIMESTATE(vmstate)->modulename = modulename;
	VMSTATECURRENTRUNTIMESTATE(vmstate)->ptype = loadextpackagetype;

	AddRunTimeStateList(VMSTATECURRENTRUNTIMESTATE(vmstate));
	return VMSTATECURRENTRUNTIMESTATE(vmstate);
}

void CreateStringConstants(char* s,VmState* vmstate)
{

	VECTORFORSTART(string,VMSTATECURRENTRUNTIMESTATE(vmstate)->strings,it)
		if((*it)==s){
			return;
		}
	VECTORFOREND
	
	VMSTATECURRENTRUNTIMESTATE(vmstate)->strings->push_back(s);
}


const char* GetStringConstantsByHash(hashValue hash,RunTimeState* _runtimestate)
{

	VECTORFORSTART(string,_runtimestate->strings,it)
		if(MCommon::CreateInstance()->ELFHash(*it)==hash){
			return (*it).c_str();
		}
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



ModuleState* GetModuleAttr(int i,VmState* vmstate)
{
	if (i<0 || i >= VMSTATECURRENTRUNTIMESTATE(vmstate)->includemodule->size()){
		MError::CreateInstance()->PrintRunTimeError("module Not found",vmstate);
	}
	return VMSTATECURRENTRUNTIMESTATE(vmstate)->includemodule->at(i);
}

void Vm::InitCode(Instruction x,int &codep,vector<Instruction>& codealllist){	    
	codealllist.push_back(x);codep++;
}


void Push_Number(double d,VmState* vmstate)
{
	(*VMSTATESP(vmstate)).v = M_NUMBER;
	(*VMSTATESP(vmstate)++).d = d;
}

void Push_String(pString str,VmState* vmstate)
{
	(*VMSTATESP(vmstate)).v= M_STRING;
	(*VMSTATESP(vmstate)++).str = str;
}

void Push_Array(pArray arr,VmState* vmstate)
{
	(*VMSTATESP(vmstate)).v= M_ARRAY;
	(*VMSTATESP(vmstate)++).parray = arr;
}

void Push_Dict(pDict dict,VmState* vmstate)
{
	(*VMSTATESP(vmstate)).v= M_DICT;
	(*VMSTATESP(vmstate)++).pdict = dict;
}

void Push_Bool(bool arr,VmState* vmstate)
{
	(*VMSTATESP(vmstate)).v= M_BOOL;
	(*VMSTATESP(vmstate)++).b = arr;
}
void Push_Object(pInst arr,VmState* vmstate)
{
	(*VMSTATESP(vmstate)).v= M_OBJECT;
	(*VMSTATESP(vmstate)++).p = arr;
}


void CreateFunctionCall(int paramcount,VmState* vmstate)
{
	StackState value;					
	value.v= M_NULL;
	*VMSTATESP(vmstate)++ = value;

	value.v= M_BPMARK;
	 //执行函数前，压入MARK记录当前的（函数调用前的，为了返回以后恢复原有）bp,sp,ip					
	StackMark m = {VMSTATEBP(vmstate),0,paramcount,VMSTATECURRENTRUNTIMESTATE(vmstate),1};
	value.m = m;				
	//bp = sp - stackbase; //sp为当前栈的栈指针
	*VMSTATESP(vmstate)++ = value;	
	//VMSTATECALLBP(vmstate) = VMSTATEBP(vmstate);
	//VMSTATECALLTYPE(vmstate) = 1;
}

StackState CallFunction(StackState fun,VmState* vmstate)
{

	STACKSTATEPOINTER b = VMSTATESP(vmstate)-1;
	while (b->v != M_BPMARK) b--;
	VMSTATEBP(vmstate) = b;
	(VMSTATEBP(vmstate))->m.address = VMSTATECODELIST(vmstate); //保存现在ip

	STACKSTATEPOINTER func = &fun;
	FunctionAtter fa;

					
	VMSTATECURRENTRUNTIMESTATE(vmstate) = STATICCAST(RunTimeState,func->p);

	if(func->v==M_PFUN)
	{
		fa= GetRunTimeFunctionAtter(func->hash,VMSTATECURRENTRUNTIMESTATE(vmstate));
	}else 
	{
		fa = GetRunTimeFunctionAtterByIndex(func->i,vmstate);
	}

	if(fa.name=="")
	{
		VMSTATECURRENTRUNTIMESTATE(vmstate) = (VMSTATEBP(vmstate)->m.rts);
		string functionname = GetStringConstantsByHash(func->hash,VMSTATECURRENTRUNTIMESTATE(vmstate));
		
		MError::CreateInstance()->PrintRunTimeError(functionname+string(" is not defined"),vmstate);
	}

	int stackargcount = VMSTATESP(vmstate)-1-(VMSTATEBP(vmstate)+1);//当前栈内参数					 
	if(stackargcount>fa.paramcount){
		VMSTATESP(vmstate)=VMSTATESP(vmstate)-(stackargcount-fa.paramcount);
	}
	if(stackargcount<fa.paramcount){
		for(int i=0;i<fa.paramcount-stackargcount;i++){
			StackState value;					
			value.v= M_NULL;
			*VMSTATESP(vmstate)++ = value;	
		}
	}
	if(fa.lenght==-1)//外部扩展的函数
	{
		funcallback f = (funcallback)fa.postion;
		StackState st= f(vmstate);
		*VMSTATESP(vmstate)++ = st;
		VMSTATECURRENTRUNTIMESTATE(vmstate) =  (VMSTATEBP(vmstate)->m.rts);
		AdjustStack(vmstate);

	}else
	{
		VMSTATECODELIST(vmstate) =fa.postion;
		VMSTATESP(vmstate)--;
		Execute(vmstate);
	}
	return *(--VMSTATESP(vmstate));
}




inline void MainFuncitonCode(int &codespostion,vector<Instruction>& codealllist,VmState* vmstate)
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
void PintCode(int c,VmState* vmstate){

	int i = 0;
	while(i<c){
		cout<<(VMSTATECODELIST(vmstate)[i]);
		cout<<",";
		i++;
	}
	cout<<"\r\n------------------------------------------"<<endl;
}

Instruction* GetCurrentCodeList(VmState* vmstate){
	return VMSTATECODELIST(vmstate);
}

Instruction* GetCodeListStart(VmState* vmstate){
	if(!codeliststart)return 0;
	return codeliststart+VMSTATECURRENTRUNTIMESTATE(vmstate)->codeoffset;
}

vector<MentholDebug> *GetDebugList(VmState* vmstate){
	if(!VMSTATECURRENTRUNTIMESTATE(vmstate))return 0;

	return VMSTATECURRENTRUNTIMESTATE(vmstate)->debuglist;
}
/*
static bool IsLoadedLibrary(string filename)
{
	VECTORFORSTART(string,loadedlibrarys,it)		
		if((*it)==filename){
			return true;	
		}
	VECTORFOREND
	return false;
}*/

void ExecuteCallBack(vector<Instruction> *globalcodelist,RunTimeState *_currentruntimestate,VmState* vmstate)
{
	VMSTATECURRENTRUNTIMESTATE(vmstate) = _currentruntimestate;
	char c;
	VMSTATECODELIST(vmstate) =new Instruction[globalcodelist->size()];
	for (int i = 0; i < globalcodelist->size(); i++)
	{
		VMSTATECODELIST(vmstate)[i]=(globalcodelist->at(i));
	}
	Instruction* _codelist = VMSTATECODELIST(vmstate); 
	if(!Execute(vmstate)){			
		VMSTATECODELIST(vmstate)  =_codelist;
		delete[] VMSTATECODELIST(vmstate);
		VMSTATECODELIST(vmstate) = 0;
	}
}

void EntryPoint(ImportFileAttr pa,char* workdir,VmState* vmstate)
{
	strcpy(ModulePath,MCommon::CreateInstance()->GetRunPath().c_str());
	int postion=0;
	
	//ImportBuiltinPackAge();//载入系统函数，反转后排在第一个位，保证在所有程序执行前。先执行系统函数
	

	MBinary *wb =new  MBinary();
	//AutoLoadPackAge(filetree,ModulePath);
	filetree->push_back(pa);//压入启动文件，启动文件最后执行
	wb->MReadImportFiles(pa.filename.c_str(),filetree,ModulePath,workdir);	
	//AutoLoadPackAge(filetree,ModulePath);

	reverse(filetree->begin(),filetree->end());

	int codespostion=0;

	runtimestatelist =new vector<RunTimeState*>();
	vector<Instruction> codealllist;

	MainFuncitonCode(codespostion,codealllist,vmstate);


	vector<GlobalCodeRuntimeAtter>* globallist =new vector<GlobalCodeRuntimeAtter>(0);


	for(int f=0;f<filetree->size();f++){

		ImportFileAttr pa = filetree->at(f);
		vector<Instruction> globalcodelist;

		if(IsPackage(pa.ptype))
		{
			wb->ReadBinary(pa,&codealllist,runtimestatelist,dictkeys,AddRunTimeStateList,globallist);			
		}
		if(IsEXTPackage(pa.ptype))
		{					
			loadextpackagetype = pa.ptype;
			HMODULE h = ::LoadLibraryA(pa.filename.c_str());	
			initfuncallback ProcAdd = (initfuncallback) GetProcAddress(h,"MP_Init"); 
			ProcAdd(vmstate);
		}
	}
	VECTORFORSTART(GlobalCodeRuntimeAtter,globallist,it)
			VMSTATECURRENTRUNTIMESTATE(vmstate) = (*it).belongtoruntimestate;
			VMSTATECURRENTRUNTIMESTATE(vmstate)->codeoffset = 0;
			VMSTATECODELIST(vmstate) =new Instruction[(*it).lenght];
			codeliststart = VMSTATECODELIST(vmstate);
			for (int i = 0; i < (*it).lenght; i++)
			{
				VMSTATECODELIST(vmstate)[i]=((*it).globalcodelist->at(i));
			}
			Instruction* _codelist = VMSTATECODELIST(vmstate); 
			if(Execute(vmstate)==1){			
				VMSTATECODELIST(vmstate)  =_codelist;
				delete[] VMSTATECODELIST(vmstate);
			}
			else
			{
				MError::CreateInstance()->PrintRunTimeError("The application is corrupted or missing and the application cannot be launched",vmstate);
				return;
			}
			VMSTATECODELIST(vmstate) = 0;
			delete (*it).globalcodelist;
			VMSTATECURRENTRUNTIMESTATE(vmstate)->codeoffset = -1;
	VECTORFOREND
	delete globallist;
	codeliststart = 0;

	VMSTATECODELIST(vmstate) = 0;
	VMSTATECODELIST(vmstate) =new Instruction[codealllist.size()];
	codeliststart = VMSTATECODELIST(vmstate);
	memset(VMSTATECODELIST(vmstate),0,codealllist.size()+1);
	for (int i = 0; i < codealllist.size(); i++)
	{
		VMSTATECODELIST(vmstate)[i]=(codealllist[i]);
	}

	VECTORFORSTART(RunTimeState*,runtimestatelist,it1)		
		if(IsEXTPackage((*it1)->ptype))
		{
			continue;
		}
		(*it1)->codeoffset=codespostion;
		if ((*it1)->hash == MAINMODULENAMEHASH){
			VMSTATECURRENTRUNTIMESTATE(vmstate) = (*it1);
		}
		VECTORFORSTART(FunctionAtter,(*it1)->functionlist,it)		
			if((*it).lenght!=-1){
				(*it).postion = VMSTATECODELIST(vmstate)+codespostion;
				codespostion+=(*it).lenght;
			}
		VECTORFOREND
	VECTORFOREND

	filetree->clear();
	//clock_t start = clock();
	runflag = 1;

  	Execute(vmstate);
	//clock_t end = clock();
	//printf("the running time is :%f\n", (double)(end -start)); //秒
}


int Execute(VmState* vmstate)
{
	 for (;;) {

		switch (*VMSTATECODELIST(vmstate)++)
		{	 
			SWITCHCASESTART(OP_PUSHNUMBER)
					(*VMSTATESP(vmstate)).v = M_NUMBER;
					(*VMSTATESP(vmstate)++).d = *VMSTATECODELIST(vmstate)++;
			SWITCHCASEEND
				
			SWITCHCASESTART(OP_PUSHDOUBLE)
					(*VMSTATESP(vmstate)).v = M_NUMBER;
					(*VMSTATESP(vmstate)++).d =VMSTATECURRENTRUNTIMESTATE(vmstate)->doubles->at(*VMSTATECODELIST(vmstate)++);
			SWITCHCASEEND
				
			SWITCHCASESTART(OP_PUSHHASH)
					(*VMSTATESP(vmstate)).v = M_HASH;
					(*VMSTATESP(vmstate)++).hash =*VMSTATECODELIST(vmstate)++;	
			SWITCHCASEEND

			SWITCHCASESTART(OP_PUSHSTRING)
					(*VMSTATESP(vmstate)).str=GetStringConstants(*VMSTATECODELIST(vmstate)++,vmstate);
					(*VMSTATESP(vmstate)++).v = M_STRING;			
			SWITCHCASEEND

			SWITCHCASESTART(OP_PUSHBOOL)
					(*VMSTATESP(vmstate)).v = M_BOOL;
					(*VMSTATESP(vmstate)++).b = (bool)(*VMSTATECODELIST(vmstate)++);	
			SWITCHCASEEND

			SWITCHCASESTART(OP_RET)
					VMSTATECURRENTRUNTIMESTATE(vmstate) = VMSTATEBP(vmstate)->m.rts;
					if(VMSTATEBP(vmstate)->m.calltype)
					{
						//VMSTATECALLTYPE(vmstate) = 0;
						//VMSTATECALLBP(vmstate) =0;
						AdjustStack(vmstate);
						return 1;
					}
					AdjustStack(vmstate);
			SWITCHCASEEND

			SWITCHCASESTART(OP_PUSHMARK)					
					StackState value;					
					value.v= M_BPMARK;
					 //执行函数前，压入MARK记录当前的（函数调用前的，为了返回以后恢复原有）bp,sp,ip					
					StackMark m = {VMSTATEBP(vmstate),0,*VMSTATECODELIST(vmstate)++,VMSTATECURRENTRUNTIMESTATE(vmstate),0};
					value.m = m;				
					//bp = sp - stackbase; //sp为当前栈的栈指针
					*VMSTATESP(vmstate)++ = value;	
			SWITCHCASEEND
			
			SWITCHCASESTART(OP_PUSHTRYMARK)
					StackState value;					
					value.v= M_TRYMARK;
					Instruction* _ip = VMSTATECODELIST(vmstate);
					
					int address = *VMSTATECODELIST(vmstate)++;
					M_UInt paramercount= *VMSTATECODELIST(vmstate)++;

					TryMark m = {VMSTATEBP(vmstate),_ip+(address<0?address+1:address),paramercount,VMSTATECURRENTRUNTIMESTATE(vmstate)};
					value.m = m;	
					*VMSTATESP(vmstate)++ = value;
			SWITCHCASEEND

			SWITCHCASESTART(OP_THROWSTART)
					VMSTATESP(vmstate)--;
					while (VMSTATESP(vmstate)->v != M_TRYMARK) 
					{
						if(VMSTATESP(vmstate)==VMSTATESTACKBASE(vmstate))	//如果指到了栈的第一个证明没有try
						{
							break;
						}
						VMSTATESP(vmstate)--;
					}
					VMSTATESP(vmstate)++;
			SWITCHCASEEND

			SWITCHCASESTART(OP_THROWEND)
					STACKSTATEPOINTER b = VMSTATESP(vmstate)-1;
					ValueType valuetypepointer1[] = {M_FUN,M_PFUN,M_BOOL,M_ARRAY,M_DICT,M_NULL,M_MODULE,M_HASH,M_UNKONWN,M_OBJECT};
					ValueType valuetypepointer2[] = {M_NUMBER,M_LONG};
					ValueType valuetypepointer3[] = {M_STRING,M_SSTRING};
					while (b->v != M_TRYMARK)
					{ 
						if(b==VMSTATESTACKBASE(vmstate))
						{		
							char throwstring[5000] = {""};
							int stackargcount = VMSTATESP(vmstate)-b-1;
							for(int i=0;i<stackargcount;i++)
							{
								VMSTATESP(vmstate)--;	
								if(MCommon::CreateInstance()->IsInArray(valuetypepointer1,VMSTATESP(vmstate)->v,10))
								{
									strcat(throwstring,"object");
								}
								if(MCommon::CreateInstance()->IsInArray(valuetypepointer2,VMSTATESP(vmstate)->v,2))
								{
									char a[32];
									if(VMSTATESP(vmstate)->d != (int)VMSTATESP(vmstate)->d){
										sprintf(a,"%.6lf",VMSTATESP(vmstate)->d);
									}
									else{
										sprintf(a,"%d",(int)VMSTATESP(vmstate)->d);
									}	
									strcat(throwstring,a);
								}
								if(MCommon::CreateInstance()->IsInArray(valuetypepointer3,VMSTATESP(vmstate)->v,2))
								{
									strcat(throwstring,VMSTATESP(vmstate)->str->string);			
								}
								strcat(throwstring,",");								
							}
							throwstring[strlen(throwstring)-1] = '\0';
							MError::CreateInstance()->PrintRunTimeError(throwstring,vmstate);
							return 1;
						};
						b--;
					}
					int stackargcount = VMSTATESP(vmstate)-b-1;
					VMSTATECODELIST(vmstate) = b->m.address;
					VMSTATECURRENTRUNTIMESTATE(vmstate) = b->m.rts;
					VMSTATEBP(vmstate) = b->m.bp;
					if(stackargcount>b->m.paramercount){
						VMSTATESP(vmstate)=VMSTATESP(vmstate)-(stackargcount-b->m.paramercount);
					}
					if(stackargcount<b->m.paramercount){
						for(int i=0;i<b->m.paramercount-stackargcount;i++){
							StackState  value;					
							value.v= M_NULL;
							*VMSTATESP(vmstate)++ = value;	
						}
					}
			SWITCHCASEEND

			SWITCHCASESTART(OP_PUSHFUN)
					(*VMSTATESP(vmstate)).v = M_FUN;
					(*VMSTATESP(vmstate)).p = VMSTATECURRENTRUNTIMESTATE(vmstate);
					(*VMSTATESP(vmstate)++).i = *VMSTATECODELIST(vmstate)++;//表示自定义函数名字的hash值
			SWITCHCASEEND

			SWITCHCASESTART(OP_CALLFUNC)
					if(!runflag){
						MError::CreateInstance()->PrintRunTimeError("Global variables  cannot be initialized or assigned to functions call",vmstate);
						return 1;
					}
					STACKSTATEPOINTER b = VMSTATESP(vmstate)-1;
					while (b->v != M_BPMARK) b--;
					VMSTATEBP(vmstate) = b;
					(VMSTATEBP(vmstate))->m.address = VMSTATECODELIST(vmstate); //保存现在ip

					STACKSTATEPOINTER func = --VMSTATESP(vmstate);
					FunctionAtter fa;

					
					VMSTATECURRENTRUNTIMESTATE(vmstate) = STATICCAST(RunTimeState,func->p);


					if(func->v==M_PFUN || func->hash==MMAINHASH)
					{
						fa= GetRunTimeFunctionAtter(func->hash,VMSTATECURRENTRUNTIMESTATE(vmstate));
					}else 
					{
						fa = GetRunTimeFunctionAtterByIndex(func->i,vmstate);
					}
					if(fa.name=="")
					{
						string erromsg = "";
						if(func->hash==MMAINHASH){
							erromsg = "mmain";
						}else
						{
							VMSTATECURRENTRUNTIMESTATE(vmstate) = (VMSTATEBP(vmstate)->m.rts);
							erromsg =GetStringConstantsByHash(func->hash,VMSTATEBP(vmstate)->m.rts);
						}
					

						MError::CreateInstance()->PrintRunTimeError(erromsg+string(" is not defined"),vmstate);
						return 1;
					}


					int stackargcount = VMSTATESP(vmstate)-(VMSTATEBP(vmstate)+1);//当前栈内参数					 
					if(stackargcount>fa.paramcount){
						VMSTATESP(vmstate)=VMSTATESP(vmstate)-(stackargcount-fa.paramcount);
						stackargcount = fa.paramcount;
					}
					
				
					if(fa.lenght==-1)//外部扩展的函数
					{
						if(stackargcount<fa.paramcount)
						{
							for(int i=0;i<fa.paramcount-stackargcount;i++){
								StackState value;					
								value.v= M_NULL;
								*VMSTATESP(vmstate)++ = value;	
							}
						}	
						funcallback f = (funcallback)fa.postion;
						StackState st= f(vmstate);
						*VMSTATESP(vmstate)++ = st;
						VMSTATECURRENTRUNTIMESTATE(vmstate) =  (VMSTATEBP(vmstate)->m.rts);
						AdjustStack(vmstate);
					}else
					{
						
							int dc = fa.defaultvaluelengthlist->size();
							//int _stackargcount = stackargcount;
							
							/*
							for (int i =_stackargcount; i <dc ; i++)
							{
								if(fa.defaultvaluelengthlist->at(i)!=0){
									if(i!=0){
										fa.postion+=fa.defaultvaluelengthlist->at(i-1);
									}
									stackargcount+=(dc-i);
									SWITCHBREAK;
								}
							}*/


							int _i =0; //把已经有的参数的默认参数的字符跳过
							for (;_i <= stackargcount; _i++)
							{
								fa.postion+=fa.defaultvaluelengthlist->at(_i);
							}

							//增加剩余默认参数的个数
							for (int j = _i; j < dc; j++)
							{
								if(fa.defaultvaluelengthlist->at(j)!=0)
								stackargcount++;
							}

							if(stackargcount<fa.paramcount)
							{
								for(int i=0;i<fa.paramcount-stackargcount;i++){
									StackState value;					
									value.v= M_NULL;
									*VMSTATESP(vmstate)++ = value;	
								}
							}	
						VMSTATECODELIST(vmstate) =fa.postion;
						//sp--;
					}
			SWITCHCASEEND
	
			

			SWITCHCASESTART(OP_ADD)
					STACKSTATEPOINTER value1 =VMSTATESP(vmstate)-2;
					STACKSTATEPOINTER value2 =VMSTATESP(vmstate)-1;
					if(!MMath::Add(value1,value2,vmstate))
					{
						return 0;
					}
					VMSTATESP(vmstate)--;
			SWITCHCASEEND

			SWITCHCASESTART(OP_ADD1)
					STACKSTATEPOINTER _t =(VMSTATEBP(vmstate)+*VMSTATECODELIST(vmstate)++); 
					_t->d+=1;
					_t->v=M_NUMBER;
			SWITCHCASEEND

			SWITCHCASESTART(OP_POWER)
					STACKSTATEPOINTER value1 =VMSTATESP(vmstate)-2;
					STACKSTATEPOINTER value2 =VMSTATESP(vmstate)-1;
					if(!MMath::Power(value1,value2,vmstate))
					{
						return 0;
					}
					VMSTATESP(vmstate)--;
			SWITCHCASEEND

			SWITCHCASESTART(OP_SUB)
					STACKSTATEPOINTER value1 =VMSTATESP(vmstate)-2;
					STACKSTATEPOINTER value2 =VMSTATESP(vmstate)-1;
					if(!MMath::Sub(value1,value2,vmstate))
					{
						return 0;
					}
					VMSTATESP(vmstate)--;
			SWITCHCASEEND

			SWITCHCASESTART(OP_MUL)
					STACKSTATEPOINTER value1 =VMSTATESP(vmstate)-2;
					STACKSTATEPOINTER value2 =VMSTATESP(vmstate)-1;
					if(!MMath::Mul(value1,value2,vmstate))
					{
						return 0;
					}
					VMSTATESP(vmstate)--;
			SWITCHCASEEND

			SWITCHCASESTART(OP_DIV)
					STACKSTATEPOINTER value1 =VMSTATESP(vmstate)-2;
					STACKSTATEPOINTER value2 =VMSTATESP(vmstate)-1;
					if(!MMath::Div(value1,value2,vmstate))
					{
						return 0;
					}
					VMSTATESP(vmstate)--;
			SWITCHCASEEND

			SWITCHCASESTART(OP_MOD)
					STACKSTATEPOINTER value1 =VMSTATESP(vmstate)-2;
					STACKSTATEPOINTER value2 =VMSTATESP(vmstate)-1;
					if(!MMath::Mod(value1,value2,vmstate))
					{
						return 0;
					}
					VMSTATESP(vmstate)--;
			SWITCHCASEEND

			SWITCHCASESTART(OP_XOR)
					STACKSTATEPOINTER value1 =VMSTATESP(vmstate)-2;
					STACKSTATEPOINTER value2 =VMSTATESP(vmstate)-1;
					if(!MLogic::Xor(value1,value2))
					{
						return 0;
					}
					VMSTATESP(vmstate)--;
			SWITCHCASEEND

			SWITCHCASESTART(OP_STOREM)
					STACKSTATEPOINTER value = VMSTATESP(vmstate)-1;
					//int k =_code.i;
					value->namehash = *VMSTATECODELIST(vmstate)++; //函数名称的HASH值
					RestoreGlobalMemory(*value,vmstate);					
					//sp++;
			SWITCHCASEEND

			SWITCHCASESTART(OP_INITM)
					STACKSTATEPOINTER value = --VMSTATESP(vmstate);
					value->namehash = *VMSTATECODELIST(vmstate)++;//函数名称的HASH值
					value->constvalue = *VMSTATECODELIST(vmstate)++;//是否为const					
					RestoreGlobalMemory(*value,vmstate);
			SWITCHCASEEND

			SWITCHCASESTART(OP_STORES)
					STACKSTATEPOINTER v = (VMSTATEBP(vmstate)+*VMSTATECODELIST(vmstate)++); //被更新的栈
					*v=*(VMSTATESP(vmstate)-1);//更新的数据
			SWITCHCASEEND

		
		    SWITCHCASESTART(OP_LOADM)
					StackState value= FindGlobalMemory(*VMSTATECODELIST(vmstate)++,VMSTATECURRENTRUNTIMESTATE(vmstate),VMSTATECURRENTRUNTIMESTATE(vmstate),vmstate);
					(*VMSTATESP(vmstate)++) =value;
		    SWITCHCASEEND

		    SWITCHCASESTART(OP_LOADS)
					int kkkk = *VMSTATECODELIST(vmstate)++;
					*VMSTATESP(vmstate)++=*(VMSTATEBP(vmstate)+kkkk);
;		    SWITCHCASEEND

		    SWITCHCASESTART(OP_NOP)
		    SWITCHCASEEND

			SWITCHCASESTART(OP_LT)
			 		STACKSTATEPOINTER value1 =VMSTATESP(vmstate)-2;
					STACKSTATEPOINTER value2 =VMSTATESP(vmstate)-1;
					if(!MLogic::Lt(value1,value2,vmstate))
					{
						return 0;
					}
					VMSTATESP(vmstate)--;
			SWITCHCASEEND
			 
			SWITCHCASESTART(OP_LE)
			 		STACKSTATEPOINTER value1 =VMSTATESP(vmstate)-2;
					STACKSTATEPOINTER value2 =VMSTATESP(vmstate)-1;
					if(!MLogic::Le(value1,value2,vmstate))
					{
						return 0;
					}
					VMSTATESP(vmstate)--;
			SWITCHCASEEND

			SWITCHCASESTART(OP_GEEQ)
					STACKSTATEPOINTER value1 =VMSTATESP(vmstate)-2;
					STACKSTATEPOINTER value2 =VMSTATESP(vmstate)-1;
					if(!MLogic::Geeq(value1,value2,vmstate))
					{
						return 0;
					}
					VMSTATESP(vmstate)--;
			SWITCHCASEEND

			SWITCHCASESTART(OP_LEEQ)
				STACKSTATEPOINTER value1 =VMSTATESP(vmstate)-2;
					STACKSTATEPOINTER value2 =VMSTATESP(vmstate)-1;
					if(!MLogic::Leeq(value1,value2,vmstate))
					{
						return 0;
					}
					VMSTATESP(vmstate)--;
			SWITCHCASEEND

		    SWITCHCASESTART(OP_EQEQ)
					STACKSTATEPOINTER value1 =VMSTATESP(vmstate)-2;
					STACKSTATEPOINTER value2 =VMSTATESP(vmstate)-1;
					if(!MLogic::EqEq(value1,value2,vmstate))
					{
						return 0;
					}
					VMSTATESP(vmstate)--;
			SWITCHCASEEND

		    SWITCHCASESTART(OP_NEQ)
					STACKSTATEPOINTER value1 =VMSTATESP(vmstate)-2;
					STACKSTATEPOINTER value2 =VMSTATESP(vmstate)-1;
					if(!MLogic::Neq(value1,value2,vmstate))
					{
						return 0;
					}
					VMSTATESP(vmstate)--;
			SWITCHCASEEND

		    SWITCHCASESTART(OP_SHIFTL)
					STACKSTATEPOINTER value1 =VMSTATESP(vmstate)-2;
					STACKSTATEPOINTER value2 =VMSTATESP(vmstate)-1;
					if(!MBitwise::SHIFTL(value1,value2))
					{
						return 0;
					}
					VMSTATESP(vmstate)--;
			SWITCHCASEEND

			SWITCHCASESTART(OP_SHIFTR)
					STACKSTATEPOINTER value1 =VMSTATESP(vmstate)-2;
					STACKSTATEPOINTER value2 =VMSTATESP(vmstate)-1;
					if(!MBitwise::SHIFTR(value1,value2))
					{
						return 0;
					}
					VMSTATESP(vmstate)--;
			SWITCHCASEEND

			SWITCHCASESTART(OP_CREATEARRAY)
				StackState  result;
				result.parray = CreateArray(vmstate);
				result.v = M_ARRAY;
				*VMSTATESP(vmstate)++ = result;
			SWITCHCASEEND

			SWITCHCASESTART(OP_SETARRAY)
				M_UInt c =*VMSTATECODELIST(vmstate)++;
				VECOTRSTACKSTATEPOINTER _ss = (VECOTRSTACKSTATEPOINTER)(VMSTATESP(vmstate)-c-1)->parray->array;	
				_ss->resize(c);
				VMSTATESP(vmstate) = VMSTATESP(vmstate)-c;
				for (int i = 0; i < c; i++)
				{
					_ss->at(i)=*(VMSTATESP(vmstate)+i);
				}
			SWITCHCASEEND

			SWITCHCASESTART(OP_SETARRAYELEMENT)
				  int index = (--VMSTATESP(vmstate))->d;		
				  STACKSTATEPOINTER pa = (--VMSTATESP(vmstate));
				  StackState value =*(VMSTATESP(vmstate)-1);
				  if(pa->v!=M_ARRAY && pa->v!=M_STRING)
				  {
					MError::CreateInstance()->PrintRunTimeError("It is not an array or a string",vmstate);
					return 1;
				  }

				  if(pa->v==M_ARRAY){
					  VECOTRSTACKSTATEPOINTER _arr = (VECOTRSTACKSTATEPOINTER)pa->parray->array; 
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
			SWITCHCASEEND

			SWITCHCASESTART(OP_GETARRAYELEMENT)
				int gettype = (--VMSTATESP(vmstate))->d;
				int index2= (--VMSTATESP(vmstate))->d;
				int index =(--VMSTATESP(vmstate))->d;
				
				STACKSTATEPOINTER stt= (--VMSTATESP(vmstate));

				if(stt->v!=M_ARRAY && stt->v!=M_STRING)
				{
					MError::CreateInstance()->PrintRunTimeError("It is not an array or a string",vmstate);
					return 1;
				}

				if(stt->v==M_STRING)
				{
					if(gettype==0){
						if(index>=strlen(stt->str->string)  || index<0){
							MError::CreateInstance()->PrintRunTimeError("Array out of bounds",vmstate);
							return 1;
						}
						char str[2] = {(stt->str->string)[index],'\0'};
						StackState  result;					
						result.str = CreateString(str,vmstate);
						result.v = M_STRING;
						*VMSTATESP(vmstate)=result;
					}
					if(gettype==1){
						int stringlenght = strlen(stt->str->string);
						if(index>=stringlenght  || index<0){
							MError::CreateInstance()->PrintRunTimeError("Array out of bounds",vmstate);
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
						result.str = CreateString(dest,vmstate);
						result.v = M_STRING;
						*VMSTATESP(vmstate)=result;
						delete[] dest;
					}

					if(gettype==2){
						if(index>=strlen(stt->str->string)  || index<0){
							MError::CreateInstance()->PrintRunTimeError("Array out of bounds",vmstate);
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
						result.str = CreateString(dest,vmstate);
						result.v = M_STRING;
						*VMSTATESP(vmstate)=result;
						delete[] dest;
					}

					if(gettype==3){
						if(index<0 || index2<0){
								MError::CreateInstance()->PrintRunTimeError("index value cannot be less than zero",vmstate);
								return 1;
						}else
						{
							if(index>=strlen(stt->str->string)){
								MError::CreateInstance()->PrintRunTimeError("Array out of bounds",vmstate);
								return 1;
							}
							if(index2>=strlen(stt->str->string)){
								MError::CreateInstance()->PrintRunTimeError("Array out of bounds",vmstate);
								return 1;
							}

							if(index>index2){
								MError::CreateInstance()->PrintRunTimeError("Array out of bounds",vmstate);
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
						result.str = CreateString(dest,vmstate);
						result.v = M_STRING;
						*VMSTATESP(vmstate)=result;
						delete[] dest;
					}
					
				}else{

					VECOTRSTACKSTATEPOINTER _arr = (VECOTRSTACKSTATEPOINTER)stt->parray->array;
					if(gettype==0){
						if(index>_arr->size()-1 || index<0){
							MError::CreateInstance()->PrintRunTimeError("Array out of bounds",vmstate);
							return 1;
						}else{
							*VMSTATESP(vmstate)=_arr->at(index);
						}
					}
					if(gettype==1)
					{
						StackState  result;
						result.v = M_ARRAY;
						pArray arr = CreateArray(vmstate);
						VECOTRSTACKSTATEPOINTER _t = arr->array;

						if(index>=_arr->size() || index<0)
						{
							MError::CreateInstance()->PrintRunTimeError("Array out of bounds",vmstate);
						}
						for (int i=index;i<_arr->size();i++){			
							_t->push_back(_arr->at(i));
						}
						result.parray = arr;
						*VMSTATESP(vmstate) = result;
					}
					if(gettype==2)
					{
						StackState  result;
						result.v = M_ARRAY;
						pArray arr = CreateArray(vmstate);
						VECOTRSTACKSTATEPOINTER _t = arr->array;
						if(index>=_arr->size() || index<0)
						{
							MError::CreateInstance()->PrintRunTimeError("Array out of bounds",vmstate);
						}
						for (int i=0;i<=index;i++){			
							_t->push_back(_arr->at(i));
						}
						result.parray = arr;
						*VMSTATESP(vmstate) = result;
					}
					if(gettype==3)
					{
						StackState  result;
						result.v = M_ARRAY;
						pArray arr = CreateArray(vmstate);
						VECOTRSTACKSTATEPOINTER _t =  arr->array;
						int s = _arr->size();
						if(index>=s || index<0 || index2>=s || index2<0 || index>index2)
						{
							MError::CreateInstance()->PrintRunTimeError("Array out of bounds",vmstate);
						}

						for (int i=index;i<=index2;i++){			
							_t->push_back(_arr->at(i));
						}
						result.parray = arr;
						*VMSTATESP(vmstate) = result;
					}
				}
				VMSTATESP(vmstate)++;
			SWITCHCASEEND

			SWITCHCASESTART(OP_CREATEDICT)
				StackState  result;
				result.v = M_DICT;
				result.pdict = CreateDict(vmstate);	
				*VMSTATESP(vmstate)++ = result;
			SWITCHCASEEND

			SWITCHCASESTART(OP_SETDICT)
				int c =*VMSTATECODELIST(vmstate)++;				
				map<hashValue,StackState>* _ss = (map<hashValue,StackState>*)(VMSTATESP(vmstate)-(c*2)-1)->pdict->dict;	
				VMSTATESP(vmstate) = VMSTATESP(vmstate)-(2*c);
				for (int i = 0; i < c; i++)
				{
					StackState value =*(VMSTATESP(vmstate)+(i*2));
					
					StackState key =*(VMSTATESP(vmstate)+(i*2+1));					
					_ss->insert(pair<hashValue,StackState>(key.hash,value));
				}
			SWITCHCASEEND

			SWITCHCASESTART(OP_GETDICTELEMENT)
				hashValue key = *VMSTATECODELIST(vmstate)++;			
				STACKSTATEPOINTER p = --VMSTATESP(vmstate);
				if(p->v!=M_DICT){
					MError::CreateInstance()->PrintRunTimeError("It is not a dictionary",vmstate);
					return 1;
				}
				map<hashValue,StackState>* _ss = (map<hashValue,StackState>*)p->pdict->dict;	
				map<hashValue,StackState>::iterator it = _ss->find(key);
				if (it == _ss->end()){
					StackState _st;
					_st.v = M_NULL;
					*VMSTATESP(vmstate)=_st;
				}else
				{
					*VMSTATESP(vmstate)=it->second;
				}			
				VMSTATESP(vmstate)++;
			SWITCHCASEEND

			SWITCHCASESTART(OP_SETDICTELEMENT)
				 hashValue key = *VMSTATECODELIST(vmstate)++;			
				  STACKSTATEPOINTER pa = (--VMSTATESP(vmstate));
				  if(pa->v!=M_DICT){
					MError::CreateInstance()->PrintRunTimeError("It is not a dictionary",vmstate);
					return 1;
				  }
				  map<hashValue,StackState>* _ss = (map<hashValue,StackState>*)pa->pdict->dict;	
				  StackState value =*(--VMSTATESP(vmstate));
				  if (_ss->find(key) == _ss->end()){
					 _ss->insert(pair<hashValue,StackState>(key,value));
				  }else
				  {
					  _ss->find(key)->second = value;
				  }
				  VMSTATESP(vmstate)++;
			SWITCHCASEEND

			SWITCHCASESTART(OP_JMP)
				/*STACKSTATEPOINTER b = sp-1;*/

				StackState b = MLogic::ConvertToBool(VMSTATESP(vmstate)-1);
				/*
				if(b->v!=M_BOOL)
				{
					b->v = M_BOOL;
					b->b = b->d;
				}*/
				if(b.b){ //如果为true顺序执行代码即可
					*VMSTATECODELIST(vmstate)++;
				}else
				{
					Instruction _ip = *VMSTATECODELIST(vmstate);
					VMSTATECODELIST(vmstate) +=_ip;
				}
				VMSTATESP(vmstate)--;
			SWITCHCASEEND

			SWITCHCASESTART(OP_UJMPS)
			 	Instruction _ip = *VMSTATECODELIST(vmstate);//为什么没有做*codelist++，因为如果如果在++，则代码现在指向的是要跳跃数字的下一个代码，则下面减的时候需要多减掉1，减去刚才被++的那个代码
				VMSTATECODELIST(vmstate) -=_ip;
			SWITCHCASEEND

			SWITCHCASESTART(OP_UJMP)
			 	Instruction _ip = *VMSTATECODELIST(vmstate);
				VMSTATECODELIST(vmstate) +=_ip;
			SWITCHCASEEND

			SWITCHCASESTART(OP_HALT)
				return 1;
			SWITCHCASEEND

			SWITCHCASESTART(OP_OR)
					STACKSTATEPOINTER value1 =VMSTATESP(vmstate)-2;
					STACKSTATEPOINTER value2 =VMSTATESP(vmstate)-1;
					if(!MLogic::Or(value1,value2))
					{
						return 0;
					}
					VMSTATESP(vmstate)--;
			SWITCHCASEEND

			SWITCHCASESTART(OP_AND)
				STACKSTATEPOINTER value1 =VMSTATESP(vmstate)-2;
					STACKSTATEPOINTER value2 =VMSTATESP(vmstate)-1;
					if(!MLogic::And(value1,value2))
					{
						return 0;
					}
					VMSTATESP(vmstate)--;
			SWITCHCASEEND

			SWITCHCASESTART(OP_BIT_OR)
				STACKSTATEPOINTER value1 =VMSTATESP(vmstate)-2;
				STACKSTATEPOINTER value2 =VMSTATESP(vmstate)-1;
				if(!MBitwise::BitOr(value1,value2))
				{
					return 0;
				}
				VMSTATESP(vmstate)--;
			SWITCHCASEEND

			SWITCHCASESTART(OP_BIT_AND)
					STACKSTATEPOINTER value1 =VMSTATESP(vmstate)-2;
					STACKSTATEPOINTER value2 =VMSTATESP(vmstate)-1;
					if(!MBitwise::BitAnd(value1,value2))
					{
						return 0;
					}
					VMSTATESP(vmstate)--;
			SWITCHCASEEND
		
			SWITCHCASESTART(OP_ADJUSTSP)
				STACKSTATEPOINTER newsp = VMSTATEBP(vmstate)+(*VMSTATECODELIST(vmstate)++)+1;		
				VMSTATESP(vmstate)= newsp;
			SWITCHCASEEND

			SWITCHCASESTART(OP_ADJUSTBP)
				STACKSTATEPOINTER b = VMSTATESP(vmstate)-1;
				while (b->v != M_BPMARK) b--;
				VMSTATEBP(vmstate) = b;	
			SWITCHCASEEND

			SWITCHCASESTART(OP_PUSHRS)
				StackState value;					
				value.v= M_NULL;
				value.d = 0;
				/*CodeNumber _code;
				_code.m.c1 = *codelist++; _code.m.c2 = *codelist++;;_code.m.c3 = *codelist++;; _code.m.c4 = *codelist++;*/
				*VMSTATESP(vmstate)++ = value;
			SWITCHCASEEND

			SWITCHCASESTART(OP_GETSEQ) //for in 的集合专用，in 后面的集合无法判断出是数组还是字典，所以要用专们的指令取出
				int pcount = *VMSTATECODELIST(vmstate)++;
				int key = (VMSTATESP(vmstate)-1)->d;	
				STACKSTATEPOINTER seq=VMSTATESP(vmstate)-pcount-2;
				
				if(seq->v!=M_ARRAY && seq->v!=M_DICT && seq->v!=M_STRING)
				{
					MError::CreateInstance()->PrintRunTimeError("It is not an Collection",vmstate);
					return 1;
				}

				if(seq->v==M_STRING){
					if(key>=strlen(seq->str->string)){
							VMSTATECODELIST(vmstate) +=*VMSTATECODELIST(vmstate);
					}else
					{
						VMSTATECODELIST(vmstate)++;					
						/*
						StackState* _t = bp+*codelist++;
						char str[2] = {(seq->str->string)[key],'\0'};					
						_t->str = CreateString(str);
						_t->v = M_STRING;*/
						char str[2] = {(seq->str->string)[key],'\0'};	
						(seq+1)->v = M_STRING;
						(seq+1)->str = CreateString(str,vmstate);
					}
				}

				if(seq->v==M_ARRAY){
					VECOTRSTACKSTATEPOINTER _arr = (VECOTRSTACKSTATEPOINTER)seq->parray->array;
					if(key>=_arr->size()){
							VMSTATECODELIST(vmstate) +=*VMSTATECODELIST(vmstate);
					}else
					{
						VMSTATECODELIST(vmstate)++;	

						*(seq+1) = _arr->at(key);

						//*(bp+*codelist++) = _arr->at(key);
					}
				}
				if(seq->v==M_DICT){
					map<hashValue,StackState>* _ss = (map<hashValue,StackState>*)seq->pdict->dict;
					//vector<StackState>* _arr = new vector<StackState>();
				
					if(key>=_ss->size())
					{
						VMSTATECODELIST(vmstate) +=*VMSTATECODELIST(vmstate);
					}else
					{
							int index = 0;
							VMSTATECODELIST(vmstate)++;
							//StackState* _t = bp+*codelist++;
							STACKSTATEPOINTER _t = seq+1;
							STACKSTATEPOINTER _t2 = seq+2;
							for(map <hashValue, StackState>::iterator m1_Iter = _ss->begin( ); m1_Iter != _ss->end( ); m1_Iter++)
							{
								if(index==key){	
									
									_t->str = CreateDictKeyString((*m1_Iter).first,vmstate);
									_t->v = M_STRING;
									*_t2 =(*m1_Iter).second; 
									SWITCHBREAK;
								}
								index++;
							}	
					}
					//delete _arr;
					//此处可能需要删除原来的字典

				}	
				(VMSTATESP(vmstate)-1)->d++;
			SWITCHCASEEND

			SWITCHCASESTART(OP_PUSHMODULE)
				(*VMSTATESP(vmstate)).v = M_MODULE;
				(*VMSTATESP(vmstate)++).ms = GetModuleAttr(*VMSTATECODELIST(vmstate)++,vmstate);
			SWITCHCASEEND

			SWITCHCASESTART(OP_PUSHMODULEFUNC)
				STACKSTATEPOINTER b = VMSTATESP(vmstate)-1;
				if (b->v != M_MODULE){
					MError::CreateInstance()->PrintRunTimeError("expression is not module",vmstate);
					return 1;
				}
				ModuleState* pa =b->ms;
				b->v = M_PFUN;
				b->hash = *VMSTATECODELIST(vmstate)++; //function's hash value
				b->p = pa->rts;

				if(GetRunTimeFunctionAtter(b->hash,pa->rts).name=="")
				{
					MError::CreateInstance()->PrintRunTimeError(GetStringConstantsByHash(b->hash,VMSTATECURRENTRUNTIMESTATE(vmstate))+string(" is not defined"),vmstate);
					return 1;
				}
			SWITCHCASEEND

			SWITCHCASESTART(OP_GETMODULEATTER)
					STACKSTATEPOINTER b = VMSTATESP(vmstate)-1;
					if (b->v != M_MODULE){
						MError::CreateInstance()->PrintRunTimeError("expression is not module",vmstate);
						return 1;
					}
					ModuleState* pa = b->ms;
					RunTimeState* _rts = VMSTATECURRENTRUNTIMESTATE(vmstate);
					VMSTATECURRENTRUNTIMESTATE(vmstate) = pa->rts;

					*b = FindGlobalMemory(*VMSTATECODELIST(vmstate)++,VMSTATECURRENTRUNTIMESTATE(vmstate),_rts,vmstate);
					VMSTATECURRENTRUNTIMESTATE(vmstate) = _rts;
			SWITCHCASEEND

			SWITCHCASESTART(OP_SETMODULEATTER)
					STACKSTATEPOINTER attr  = --VMSTATESP(vmstate);
					if (attr->v != M_MODULE){
						MError::CreateInstance()->PrintRunTimeError("expression is not module",vmstate);
						return 1;
					}
					STACKSTATEPOINTER value = VMSTATESP(vmstate)-1;
					ModuleState* pa = attr->ms;
					RunTimeState* _rts = VMSTATECURRENTRUNTIMESTATE(vmstate);
					VMSTATECURRENTRUNTIMESTATE(vmstate) = pa->rts;
					*attr = *value;
					attr->namehash = *VMSTATECODELIST(vmstate)++;
					attr->constvalue =  FindGlobalMemory(attr->namehash,VMSTATECURRENTRUNTIMESTATE(vmstate),_rts,vmstate).constvalue;
			
					RestoreGlobalMemory(*attr,vmstate);
					VMSTATECURRENTRUNTIMESTATE(vmstate) = _rts;
			SWITCHCASEEND

			SWITCHCASESTART(OP_MINUS)
					STACKSTATEPOINTER v = VMSTATESP(vmstate)-1;
					if(v->v==M_NUMBER){
						v->d = -1*v->d;
					}
			SWITCHCASEEND

			SWITCHCASESTART(OP_POP)
					VMSTATESP(vmstate)--;
			SWITCHCASEEND

			SWITCHCASESTART(OP_TJMP)
					StackState b = MLogic::ConvertToBool(--VMSTATESP(vmstate));
					if(b.b)
					{  
						*VMSTATECODELIST(vmstate)++;
					}else
					{
						Instruction _ip = *VMSTATECODELIST(vmstate);
						VMSTATECODELIST(vmstate) +=_ip;
					}
			SWITCHCASEEND

			SWITCHCASESTART(OP_INVERTER)
					STACKSTATEPOINTER v = VMSTATESP(vmstate)-1;
					if(!MLogic::Inv(v))
					{
						return 0;
					}
			SWITCHCASEEND

			SWITCHCASESTART(OP_TYPEOF)
					STACKSTATEPOINTER v = VMSTATESP(vmstate)-1;			
					v->str = CreateString(mtypes[v->v],vmstate);
					v->v=M_STRING;
			SWITCHCASEEND

			default:
				return 0;
				SWITCHBREAK;
		}
	}
	return 1;
}





StackState GetParam(int x,VmState* vmstate)
{
	//注释掉，原代码意思不明
	/*StackState _v;
	_v.v = M_UNKONWN;
	StackState v =  *(bp);
	if(x>v.m.paramercount){
		return _v;
	}*/


	return  *(VMSTATEBP(vmstate)+x);
}

void AdjustStack(VmState* vmstate)
{
	*(VMSTATEBP(vmstate)-1) = *(--VMSTATESP(vmstate));
	VMSTATECODELIST(vmstate) = (VMSTATEBP(vmstate))->m.address;
	STACKSTATEPOINTER newsp = (VMSTATEBP(vmstate));
    VMSTATESP(vmstate) = newsp;
	VMSTATEBP(vmstate) = ((VMSTATEBP(vmstate))->m.bp);
}
}