#pragma once
#ifndef MGC
#define MGC

#include <map>
#include "MError.h"

#define MAXGARBAGE 10000
#define MAXGARBAGEMEMORYSIZE 50971520
namespace MGc
{
	void InitWGc();
	void MarkArray(VECOTRSTACKSTATEPOINTER arr);
	void CopyToGlobalGarBage(Garbage* g);
	void MarkGlobalGarBage();
	void ClearGarbage();
	Garbage* CollectGarbage_String(char* p,ValueType mark = M_STRING);
	Garbage* CreateString(char* str);
	Garbage* CreateNullString(size_t len);
	Garbage* CreateArray();
	void SetAllGarbages(int mark);
	void MarkAllGarbages();
	Garbage* CreateDict();
	void MarkArray(VECOTRSTACKSTATEPOINTER arr);
	void MarkDict(map<hashValue,StackState>* arr);
	long GetGarBageMemorySize();
	vector<Garbage*> *GetGarbageCollect();
};
#endif

