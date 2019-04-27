#pragma once
#include "header.h"
namespace Keyboard
{
	StackState NextField(VmState* vmstate);
	StackState PreviousField(VmState* vmstate);
	StackState GetFocus(VmState* vmstate);
	StackState SetFocus(VmState* vmstate);
	StackState GetKeyCodeString(VmState* vmstate);
};

