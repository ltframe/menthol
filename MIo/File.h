#pragma once
#include "Menthol.h"
namespace File
{
	StackState Readfile();
	StackState Writefile();
	StackState Copy();
	StackState Create();
	StackState Delete();
	StackState Exists();
	StackState Move();
	StackState GetCreationTime();
	StackState GetLastAccessTime();
	StackState GetLastWriteTime();
}