#pragma once
#include "header.h"

namespace String
{
	StackState SetLanguage(VmState* vmstate);
	StackState GetLanguage(VmState* vmstate);
	StackState SetLanguageString(VmState* vmstate);
	StackState GetLanguageString(VmState* vmstate);
};

