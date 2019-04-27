#pragma once
#include "Menthol.h"
namespace File
{
	StackState Open(VmState* vmstate);
	StackState Readfile(VmState* vmstate);
	StackState Close(VmState* vmstate);
	StackState Writefile(VmState* vmstate);
	StackState Copy(VmState* vmstate);
	StackState Create(VmState* vmstate);
	StackState Delete(VmState* vmstate);
	StackState Exists(VmState* vmstate);
	StackState Move(VmState* vmstate);
	StackState GetCreationTime(VmState* vmstate);
	StackState GetLastAccessTime(VmState* vmstate);
	StackState GetLastWriteTime(VmState* vmstate);
	StackState IsFile(VmState* vmstate);
	StackState GetFileList(VmState* vmstate);
}