#pragma once
#include "header.h"
namespace Dialogs
{
	StackState Dialog(VmState* vmstate);
	StackState Popup(VmState* vmstate);
	StackState Show(VmState* vmstate);
	StackState ShowXY(VmState* vmstate);
	StackState Hide(VmState* vmstate);
	StackState FileDlg(VmState* vmstate);
	StackState MessageDlg(VmState* vmstate);
	StackState ColorDlg(VmState* vmstate);
	StackState FontDlg(VmState* vmstate);
	StackState ProgressDlg(VmState* vmstate);
	StackState ScintillaDlg(VmState* vmstate);
	StackState Alarm(VmState* vmstate);
	StackState GetFile(VmState* vmstate);
	StackState GetColor(VmState* vmstate);
	StackState GetText(VmState* vmstate);
	StackState ListDialog(VmState* vmstate);
	StackState Message(VmState* vmstate);
	StackState MessageError(VmState* vmstate);
	StackState MessageAlarm(VmState* vmstate);
	StackState LayoutDialog(VmState* vmstate);
	StackState ElementPropertiesDialog(VmState* vmstate);
	StackState Append(VmState* vmstate);
	StackState Detach(VmState* vmstate);
	StackState Insert(VmState* vmstate);
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

