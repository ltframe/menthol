#include "stdafx.h"
#include "Menus.h"
namespace Menus
{
	StackState Item(VmState* vmstate)
	{
		return Object_CreateObject(IupItem(GetParam(1,vmstate).str->string, GetParam(2,vmstate).str->string));
	}
	StackState Item2(VmState* vmstate)
	{
		return Object_CreateObject(IupItem(GetParam(1,vmstate).str->string, 0));
	}
	StackState Menu(VmState* vmstate)
	{
		return Object_CreateObject(IupMenu(0));
	}
	StackState Separator(VmState* vmstate)
	{
		return Object_CreateObject(IupSeparator());
	}
	StackState Submenu(VmState* vmstate)
	{
		return Object_CreateObject(IupSubmenu(GetParam(1,vmstate).str->string, static_cast<Ihandle*>(GetParam(2,vmstate).p)));
	}
};
