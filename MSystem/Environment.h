#pragma once
#include "Menthol.h"
namespace Environment
{
	StackState Version();
	StackState Sleep();
	StackState SystemInfo();
	StackState CpuInfo();
	StackState SystemMemory();
	StackState OsInfo();
	StackState Getpid();
	StackState Exit();
	StackState System();
	StackState MachineName();
	StackState UserName();
	StackState TickCount();
	StackState NewGuid();
};