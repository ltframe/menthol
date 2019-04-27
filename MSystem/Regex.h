#pragma once
#include "Menthol.h"
#include "deelx/deelx.h"
namespace Regex
{
	StackState Exec(VmState* vmstate);
	StackState Test(VmState* vmstate);
	StackState Replace(VmState* vmstate);
};

