#pragma once
#include "../Menthol/MentholHeader.h"

namespace Dict
{
	StackState Length(VmState* vmstate);
	StackState Push(VmState* vmstate);
	StackState SetValue(VmState* vmstate);
	StackState GetKey(VmState* vmstate);
	StackState GetValue(VmState* vmstate);
};

