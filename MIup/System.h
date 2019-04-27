#ifndef SYSTEM
#define SYSTEM
#pragma once
#include "header.h"

namespace System
{
	StackState Init(VmState* vmstate);
	StackState Close(VmState* vmstate);
	StackState Version(VmState* vmstate);
	StackState Clipboard(VmState* vmstate);
	StackState Timer(VmState* vmstate);
	StackState User(VmState* vmstate);
	StackState Config(VmState* vmstate);
	StackState Destroy(VmState* vmstate);
	StackState Create(VmState* vmstate);
	StackState ClassName(VmState* vmstate);
	StackState Update(VmState* vmstate);
	StackState Redraw(VmState* vmstate);

};
#endif