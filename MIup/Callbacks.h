#pragma once
#include "header.h"
namespace Callbacks
{
	StackState MainLoop(VmState* vmstate);
	StackState MainLoopLevel(VmState* vmstate);
	StackState LoopStep(VmState* vmstate);
	StackState ExitLoop(VmState* vmstate);
	StackState Flush(VmState* vmstate);
	StackState SetCallback(VmState* vmstate);
};

