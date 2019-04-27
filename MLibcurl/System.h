#pragma once
#include "header.h"
namespace System
{	
	StackState init(VmState* vmstate);
	StackState cleanup(VmState* vmstate);
	StackState perform(VmState* vmstate);
	StackState version(VmState* vmstate);
	StackState unescape(VmState* vmstate);
	StackState escape(VmState* vmstate);
};

