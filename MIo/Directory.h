#pragma once
#include "Menthol.h"
namespace Directory
{
	StackState Getcwd();
	StackState Chdir();
	StackState Getenv();
	StackState Remove();
	StackState Rmdir();
	StackState Mkdir();
	StackState Rename();
	StackState Exists();
}