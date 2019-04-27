#pragma once
#include "Menthol.h"
namespace Environment
{
	StackState Version(VmState* vmstate);
	StackState Sleep(VmState* vmstate);
	StackState SystemInfo(VmState* vmstate);
	StackState CpuInfo(VmState* vmstate);
	StackState SystemMemory(VmState* vmstate);
	StackState OsInfo(VmState* vmstate);
	StackState Getpid(VmState* vmstate);
	StackState Exit(VmState* vmstate);
	StackState System(VmState* vmstate);
	StackState MachineName(VmState* vmstate);
	StackState UserName(VmState* vmstate);
	StackState TickCount(VmState* vmstate);
	StackState NewGuid(VmState* vmstate);
};