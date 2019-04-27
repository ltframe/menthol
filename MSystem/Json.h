#pragma once
#include "Menthol.h"
#include "cJSON\cJSON.h"
namespace Json
{
	StackState GetArrayItem(VmState* vmstate);
	StackState GetArraySize(VmState* vmstate);
	StackState JsonParse(VmState* vmstate);
	StackState GetObjectItem(VmState* vmstate);
	StackState Delete(VmState* vmstate);
	StackState Type(VmState* vmstate);
};

