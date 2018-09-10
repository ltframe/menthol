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
                   

#define CONVERTVALUETYPE(value1,value2)\
		if(value1->v!=M_BOOL)\
		{\
			value1->b = value1->d;\
		}\
		if(value2->v!=M_BOOL)\
		{\
			value2->b = value2->d;\
		}\

typedef void (*initfuncallback)();


namespace Vm
{
	void Init();
	void Release();
	int Execute();
	StackState GetParam(int x);
	void AdjustStack();	
	void CreateFunctionRecoredList(FunctionAtter fa);
	void CreateStringConstants(char* s);
	Garbage* GetStringConstants(int i);
	void InitStack(StackState v1,StackState  v2);
	int GetRunTimeRecored(string name);
	FunctionAtter GetRunTimeFunctionAtter(hashValue hash);
	StackState FindGlobalMemory(hashValue hash);
	void EntryPoint(PackageAttr pa,char*);
	void InitCode(Instruction x,int &codep,vector<Instruction>& codealllist);
	void RestoreGlobalMemory(StackState s);
	PackageState* GetPackageAttr(int i);
	void PintCode(int c);
	Garbage* CreateArray();
	Garbage* CreateDict();
	Garbage* CreateString(char* str);
	Garbage* CreateDictKeyString(hashValue str);
	const char* GetStringConstantsByHash(hashValue hash);
	const char* GetDictKeyByHash(hashValue hash);
	void CreateDictKeyString(char* s);
	void CreateFunctionCall(int pc);
	void Push_Number(double d);
	void Push_String(pString str);
	void Push_Array(pArray arr);
	void Push_Dict(pDict arr);
	StackState CallFunction(StackState fu);
};
#endif