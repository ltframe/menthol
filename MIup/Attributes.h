#pragma once
#include "header.h"
namespace Attributes
{
	StackState SetAttribute(VmState* vmstate);
	StackState SetAttributes(VmState* vmstate);
	StackState ResetAttribute(VmState* vmstate);
	StackState GetAttribute(VmState* vmstate);
	StackState GetAllAttributes(VmState* vmstate);
	StackState SetAttributeHandle(VmState* vmstate);
	StackState GetAttributes(VmState* vmstate);
	StackState CopyAttributes(VmState* vmstate);
	StackState GetAttributeHandle(VmState* vmstate);
	StackState SetGlobal(VmState* vmstate);
	StackState GetGlobal(VmState* vmstate);
	StackState GetAttributeData(VmState* vmstate);
};