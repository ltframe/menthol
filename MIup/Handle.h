#pragma once
#include "header.h"
namespace Handle
{
	StackState SetHandle(VmState* vmstate);
	StackState GetHandle(VmState* vmstate);
	StackState GetName(VmState* vmstate);
	StackState GetAllNames(VmState* vmstate);
	StackState GetAllDialogs(VmState* vmstate);
};

