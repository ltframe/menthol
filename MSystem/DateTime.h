#pragma once
#include "../Menthol/MentholHeader.h"

namespace DateTime
{
	StackState CurrentDate(VmState* vmstate);
	StackState CurrentTime(VmState* vmstate);
	StackState TimeZone(VmState* vmstate);
};

