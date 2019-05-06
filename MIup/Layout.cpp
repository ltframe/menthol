#include "Layout.h"
namespace Layout
{
	StackState Append(VmState* vmstate)
	{
		return Object_CreateObject(IupAppend(static_cast<Ihandle*>(GetParam(1,vmstate).p),static_cast<Ihandle*>(GetParam(2,vmstate).p)));
	}

	StackState Detach(VmState* vmstate)
	{
		IupDetach(static_cast<Ihandle*>(GetParam(1,vmstate).p));
		return Null_CreateNull();
	}

	StackState Insert(VmState* vmstate)
	{
		return Object_CreateObject(IupInsert(static_cast<Ihandle*>(GetParam(1,vmstate).p),static_cast<Ihandle*>(GetParam(2,vmstate).p),static_cast<Ihandle*>(GetParam(3,vmstate).p)));
	}


	StackState Reparent(VmState* vmstate)
	{
		return Number_CreateNumber(IupReparent(static_cast<Ihandle*>(GetParam(1,vmstate).p),static_cast<Ihandle*>(GetParam(2,vmstate).p),static_cast<Ihandle*>(GetParam(3,vmstate).p)));
	}

	StackState GetParent(VmState* vmstate)
	{
		return Object_CreateObject(IupGetParent(static_cast<Ihandle*>(GetParam(1,vmstate).p)));
	}


	StackState GetChild(VmState* vmstate)
	{
		return Object_CreateObject(IupGetChild(static_cast<Ihandle*>(GetParam(1,vmstate).p),GetParam(2,vmstate).d));
	}

	StackState GetChildPos(VmState* vmstate)
	{
		return Number_CreateNumber(IupGetChildPos(static_cast<Ihandle*>(GetParam(1,vmstate).p),static_cast<Ihandle*>(GetParam(2,vmstate).p)));
	}

	StackState GetChildCount(VmState* vmstate)
	{
		return Number_CreateNumber(IupGetChildCount(static_cast<Ihandle*>(GetParam(1,vmstate).p)));
	}

	StackState GetNextChild(VmState* vmstate)
	{
		return Object_CreateObject(IupGetNextChild(static_cast<Ihandle*>(GetParam(1,vmstate).p),static_cast<Ihandle*>(GetParam(2,vmstate).p)));
	}

	StackState GetBrother(VmState* vmstate)
	{
		return Object_CreateObject(IupGetBrother(static_cast<Ihandle*>(GetParam(1,vmstate).p)));
	}

	StackState GetDialog(VmState* vmstate)
	{
		return Object_CreateObject(IupGetDialog(static_cast<Ihandle*>(GetParam(1,vmstate).p)));
	}

	StackState GetDialogChild(VmState* vmstate)
	{
		return Object_CreateObject(IupGetDialogChild(static_cast<Ihandle*>(GetParam(1,vmstate).p),GetParam(2,vmstate).str->string));
	}

	StackState Refresh(VmState* vmstate)
	{
		IupRefresh(static_cast<Ihandle*>(GetParam(1,vmstate).p));
		return Null_CreateNull();
	}

	StackState RefreshChildren(VmState* vmstate)
	{
		IupRefreshChildren(static_cast<Ihandle*>(GetParam(1,vmstate).p));
		return Null_CreateNull();
	}
};