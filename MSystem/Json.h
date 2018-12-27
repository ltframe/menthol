#pragma once
#include "Menthol.h"
#include "cJSON\cJSON.h"
namespace Json
{
	StackState GetArrayItem();
	StackState GetArraySize();
	StackState JsonParse();
	StackState GetObjectItem();
	StackState Delete();
	StackState Type();
};

