#pragma once
#include "Menthol.h"

namespace Drives
{
	StackState GetDrives(VmState* vmstate);
	StackState AvailableFreeSpace(VmState* vmstate);
	StackState DriveType(VmState* vmstate);
	StackState TotalFreeSpace(VmState* vmstate);
	StackState TotalSize(VmState* vmstate);
};