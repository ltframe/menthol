#pragma once
#ifndef VM
#define VM
#include "header.h"
#include "MFile.h"
#include "StatementList.h"
#include <complex>
#include "MBinary.h"
#include <map>
#include <algorithm>


#define MMAINHASH  2057163645
                   





#define FINDGARBAGE(T,S,GC)\
	    vector<Garbage*>* list = MGc::GetGarbageCollect(GC);\
		VECTORFORSTART(Garbage*,list,it)\
			if((*it)->v==T && !strcmp((*it)->string,S)){\
				(*it)->mark = 0;\
				return (*it);\
			}\
		VECTORFOREND\


#define VMSTATECODELIST(VMS) VMS->codelist
#define VMSTATECURRENTRUNTIMESTATE(VMS) VMS->currentruntimestate
#define VMSTATESP(VMS) VMS->sp
#define VMSTATEBP(VMS) VMS->bp
#define VMSTATESTACKBASE(VMS) VMS->stackbase
#define VMSTATESTACKLIST(VMS) VMS->stacklist
//#define VMSTATECALLBP(VMS) VMS->callbp
#define VMSTATEGARBAGECOUNT(VMS) VMS->garbagescount
//#define VMSTATECALLTYPE(VMS) VMS->calltype
#define VMSTATEGC(VMS) VMS->gc



namespace Vm
{
	void NewVm(VmState* vmstate);
	void _NewVm(VmState* vmstate);
	VmState* NewVmState();
	void ClearVmState(VmState* vmstate);
	void Init();
	void Release();
	int Execute(VmState* vmstate);
	StackState GetParam(int x,VmState* vmstate);
	void AdjustStack(VmState* vmstate);	
	void CreateFunctionRecoredList(RunTimeState* packageinst,FunctionAtter fa);
	void CreateStringConstants(char* s,VmState* vmstate);
	Garbage* GetStringConstants(int i,VmState* vmstate);
	void InitStack(StackState v1,StackState  v2,VmState* vmstate);
	int GetRunTimeRecored(string name,VmState* vmstate);
	FunctionAtter GetRunTimeFunctionAtter(hashValue hash,RunTimeState* _currentruntimestate);
	StackState FindGlobalMemory(hashValue hash,RunTimeState* _curentruntimestate,RunTimeState* _callruntimestate,VmState* vmstate);
	void EntryPoint(ImportFileAttr pa,char*,VmState* vmstate);
	void InitCode(Instruction x,int &codep,vector<Instruction>& codealllist);
	void RestoreGlobalMemory(StackState s,VmState* vmstate);
	//ModuleState* GetPackageAttr(int i);
	void PintCode(int c,VmState* vmstate);
	Garbage* CreateArray(VmState* vmstate);
	Garbage* CreateDict(VmState* vmstate);
	Garbage* CreateString(char* str,VmState* vmstate);
	Garbage* CreateDictKeyString(hashValue str,VmState* vmstate);
	const char* GetStringConstantsByHash(hashValue hash,RunTimeState* _runtimestate);
	const char* GetDictKeyByHash(hashValue hash);
	void CreateDictKeyString(char* s);
	void CreateFunctionCall(int pc,VmState* vmstate);
	void Push_Number(double d,VmState* vmstate);
	void Push_String(pString str,VmState* vmstate);
	void Push_Array(pArray arr,VmState* vmstate);
	void Push_Dict(pDict arr,VmState* vmstate);
	void Push_Bool(bool arr,VmState* vmstate);
	void Push_Object(pInst arr,VmState* vmstate);
	StackState CallFunction(StackState fu,VmState* vmstate);
	Instruction* GetCurrentCodeList(VmState* vmstate);
	Instruction* GetCodeListStart(VmState* vmstate);
	vector<MentholDebug> *GetDebugList(VmState* vmstate);
	RunTimeState* CreateModuleRunTime(char* modulename,VmState* vmstate);
};
#endif