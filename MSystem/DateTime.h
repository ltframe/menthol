#pragma once
#include "../Menthol/MentholHeader.h"

namespace DateTime
{
	StackState CurrentDate(VmState* vmstate);
	StackState CurrentTime(VmState* vmstate);
	StackState TimeZone(VmState* vmstate);
	StackState AddDays(VmState* vmstate);
	StackState AddHours(VmState* vmstate);
	StackState AddMinutes(VmState* vmstate);
	StackState AddSeconds(VmState* vmstate);
	StackState AddYears(VmState* vmstate);
};

