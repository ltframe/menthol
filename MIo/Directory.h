#pragma once
#include "../Menthol/MentholHeader.h"
namespace Directory
{
	StackState Getcwd(VmState* vmstate);
	StackState Chdir(VmState* vmstate);
	StackState Getenv(VmState* vmstate);
	StackState Remove(VmState* vmstate);
	StackState Rmdir(VmState* vmstate);
	StackState Mkdir(VmState* vmstate);
	StackState Rename(VmState* vmstate);
	StackState Exists(VmState* vmstate);
	StackState IsDirectory(VmState* vmstate);
	StackState GetDirectoryList(VmState* vmstate);
}