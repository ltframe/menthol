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
                   





#define FINDGARBAGE(T,S)\
	    vector<Garbage*>* list = MGc::GetGarbageCollect();\
		VECTORFORSTART(Garbage*,list,it)\
			if((*it)->v==T && !strcmp((*it)->string,S)){\
				(*it)->mark = 0;\
				return (*it);\
			}\
		VECTORFOREND\


namespace Vm
{
	void Init();
	void Release();
	int Execute();
	StackState GetParam(int x);
	void AdjustStack();	
	void CreateFunctionRecoredList(RunTimeState* packageinst,FunctionAtter fa);
	void CreateStringConstants(char* s);
	Garbage* GetStringConstants(int i);
	void InitStack(StackState v1,StackState  v2);
	int GetRunTimeRecored(string name);
	FunctionAtter GetRunTimeFunctionAtter(hashValue hash,RunTimeState* _currentruntimestate);
	StackState FindGlobalMemory(hashValue hash,RunTimeState* _curentruntimestate,RunTimeState* _callruntimestate);
	void EntryPoint(ImportFileAttr pa,char*);
	void InitCode(Instruction x,int &codep,vector<Instruction>& codealllist);
	void RestoreGlobalMemory(StackState s);
	ModuleState* GetPackageAttr(int i);
	void PintCode(int c);
	Garbage* CreateArray();
	Garbage* CreateDict();
	Garbage* CreateString(char* str);
	Garbage* CreateDictKeyString(hashValue str);
	const char* GetStringConstantsByHash(hashValue hash,RunTimeState* _runtimestate);
	const char* GetDictKeyByHash(hashValue hash);
	void CreateDictKeyString(char* s);
	void CreateFunctionCall(int pc);
	void Push_Number(double d);
	void Push_String(pString str);
	void Push_Array(pArray arr);
	void Push_Dict(pDict arr);
	StackState CallFunction(StackState fu);
	Instruction* GetCurrentCodeList();
	Instruction* GetCodeListStart();
	vector<MentholDebug> *GetDebugList();
	RunTimeState* CreateModuleRunTime(char* modulename);
};
#endif