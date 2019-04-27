#pragma once
#include "Menthol.h"
namespace Console
{
	StackState Out(VmState* vmstate);
	StackState Oute(VmState* vmstate);
	StackState In(VmState* vmstate);
	StackState Clear(VmState* vmstate);
}