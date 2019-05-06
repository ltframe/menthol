#pragma once
#include "header.h"
namespace Layout
{
	StackState Append(VmState* vmstate);
	StackState Detach(VmState* vmstate);
	StackState Insert(VmState* vmstate);
	StackState Reparent(VmState* vmstate);
	StackState GetParent(VmState* vmstate);
	StackState GetChild(VmState* vmstate);
	StackState GetChildPos(VmState* vmstate);
	StackState GetChildCount(VmState* vmstate);
	StackState GetNextChild(VmState* vmstate);
	StackState GetBrother(VmState* vmstate);
	StackState GetDialog(VmState* vmstate);
	StackState GetDialogChild(VmState* vmstate);
	StackState Refresh(VmState* vmstate);
	StackState RefreshChildren(VmState* vmstate);
};

