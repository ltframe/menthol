#pragma once
#include "../Menthol/MentholHeader.h"
#include <regex>
namespace Regex
{
	StackState Exec(VmState* vmstate);
	StackState Test(VmState* vmstate);
	StackState Replace(VmState* vmstate);
};

