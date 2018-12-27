#pragma once
#include "Menthol.h"

namespace Drives
{
	StackState GetDrives();
	StackState AvailableFreeSpace();
	StackState DriveType();
	StackState TotalFreeSpace();
	StackState TotalSize();
};