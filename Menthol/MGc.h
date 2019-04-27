#pragma once
#ifndef MGC
#define MGC

#include <map>
#include "MError.h"

#define MAXGARBAGE 10000
#define MAXGARBAGEMEMORYSIZE 50971520


#define GCSSTATEGARBAGEMEMORYSIZE(GCS) GCS->garbagememorysize
#define GCSSTATEGARBAGECOLLECT(GCS) GCS->garbagecollect

namespace MGc
{	
	GcState* NewWGc();
	void InitWGc();
	void MarkArray(VECOTRSTACKSTATEPOINTER arr);
	void CopyToGlobalGarBage(Garbage* g);
	void MarkGlobalGarBage();
	void ClearGarbage(GcState* gc);
	Garbage* CollectGarbage_String(char* p,GcState* gc,ValueType mark = M_STRING);
	Garbage* CreateString(char* str,VmState* vmstate);
	Garbage* CreateNullString(size_t len,GcState* gc);
	Garbage* CreateArray(GcState* gc);
	void SetAllGarbages(int mark);
	void MarkAllGarbages(GcState* gc);
	Garbage* CreateDict(GcState* gc);
	void MarkArray(VECOTRSTACKSTATEPOINTER arr);
	void MarkDict(map<hashValue,StackState>* arr);
	long GetGarBageMemorySize(GcState* gc);
	vector<Garbage*> *GetGarbageCollect(GcState* gc);
};
#endif

