#pragma once
#include "header.h"
namespace Menus
{
	StackState Item(VmState* vmstate);
	StackState Item2(VmState* vmstate);
	StackState Menu(VmState* vmstate);
	StackState Separator(VmState* vmstate);
	StackState Submenu(VmState* vmstate);
};

