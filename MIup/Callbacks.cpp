#include "Callbacks.h"
#include "Callbackfunc.h"
			extern vector<callbackstruct> *_tvalues;

namespace Callbacks
{
	StackState MainLoop(VmState* vmstate)
	{
		return Number_CreateNumber(IupMainLoop());
	}

	StackState MainLoopLevel(VmState* vmstate)
	{
		return Number_CreateNumber(IupMainLoopLevel());
	}

	StackState LoopStep(VmState* vmstate)
	{
		return Number_CreateNumber(IupLoopStep());
	}


	StackState ExitLoop(VmState* vmstate)
	{
		IupExitLoop();
		return Null_CreateNull();
	}

	StackState Flush(VmState* vmstate)
	{
		IupFlush();
		return Null_CreateNull();
	}


	static StackState Addtotvalue(Ihandle* handle,char* action,StackState callbackfunc,Icallback icb,VmState * vmstate)
	{		
		

		
		callbackstruct d = GetIcallback(handle,action);
		callbackstruct _cbs = {handle,action,callbackfunc,vmstate};
		_tvalues->push_back(_cbs);
		IupSetCallback(handle,action,icb);
		return Null_CreateNull();
	}

	StackState SetCallback(VmState* vmstate)
	{
		Ihandle* p =  IupGetParent( static_cast<Ihandle*>(GetParam(1,vmstate).p));
		Ihandle* handle = static_cast<Ihandle*>(GetParam(1,vmstate).p);
		char * action = GetParam(2,vmstate).str->string;

		Icallback icb=0;
		char* controlname = IupGetClassName(handle);
		
		if (!strcmp(controlname, "link"))
		{
			if (!strcmp(action, "ACTION"))
			{
				return Addtotvalue(handle, action, GetParam(3,vmstate), (Icallback)callback_Link_ACTION,vmstate);
			}
		}
		if (!strcmp(controlname, "list"))
		{
			if (!strcmp(action, "ACTION"))
			{
				return Addtotvalue(handle, action, GetParam(3,vmstate), (Icallback)callback_List_ACTION,vmstate);
			}
		}
		if (!strcmp(controlname, "text"))
		{
			if (!strcmp(action, "ACTION"))
			{
				return Addtotvalue(handle, action, GetParam(3,vmstate), (Icallback)callback_Text_ACTION,vmstate);
			}
		}
		if (!strcmp(controlname, "toggle"))
		{
			if (!strcmp(action, "ACTION"))
			{
				return Addtotvalue(handle, action, GetParam(3,vmstate), (Icallback)callback_Toggle_ACTION,vmstate);
			}
		}

		if (!strcmp(action, "ACTION"))
		{
			return Addtotvalue(handle, action, GetParam(3,vmstate), (Icallback)callback_ACTION_Common,vmstate);
		}


		if (!strcmp(controlname, "dropbutton"))
		{
			if (!strcmp(action, "FLAT_ACTION"))
			{
				return Addtotvalue(handle, action, GetParam(3,vmstate), (Icallback)callback_DropButton_FLAT_ACTION,vmstate);
			}
		}

		if (!strcmp(controlname, "flattoggle"))
		{
			if (!strcmp(action, "FLAT_ACTION"))
			{
				return Addtotvalue(handle, action, GetParam(3,vmstate), (Icallback)callback_FlatToggle_FLAT_ACTION,vmstate);
			}
		}

		if (!strcmp(action, "MAP_CB"))
		{
			return Addtotvalue(handle, action, GetParam(3,vmstate), (Icallback)callback_MAP_CB,vmstate);
		}

		if (!strcmp(action, "UNMAP_CB"))
		{
			return Addtotvalue(handle, action, GetParam(3,vmstate), (Icallback)callback_UNMAP_CB,vmstate);
		}

		if (!strcmp(action, "DESTROY_CB"))
		{
			return Addtotvalue(handle, action, GetParam(3,vmstate), (Icallback)callback_DESTROY_CB,vmstate);
		}

		if (!strcmp(action, "GETFOCUS_CB"))
		{
			return Addtotvalue(handle, action, GetParam(3,vmstate), (Icallback)callback_GETFOCUS_CB,vmstate);
		}

		if (!strcmp(action, "KILLFOCUS_CB"))
		{
			return Addtotvalue(handle, action, GetParam(3,vmstate), (Icallback)callback_KILLFOCUS_CB,vmstate);
		}
		

		if (!strcmp(action, "ENTERWINDOW_CB"))
		{
			return Addtotvalue(handle, action, GetParam(3,vmstate), (Icallback)callback_ENTERWINDOW_CB,vmstate);
		}

		if (!strcmp(action, "LEAVEWINDOW_CB"))
		{
			return Addtotvalue(handle, action, GetParam(3,vmstate), (Icallback)callback_LEAVEWINDOW_CB,vmstate);
		}

		if (!strcmp(action, "K_ANY"))
		{
			return Addtotvalue(handle, action, GetParam(3,vmstate), (Icallback)callback_K_ANY,vmstate);
		}

		if (!strcmp(action, "HELP_CB"))
		{
			return Addtotvalue(handle, action, GetParam(3,vmstate), (Icallback)callback_HELP_CB,vmstate);
		}

		if (!strcmp(action, "CLOSE_CB"))
		{
			return Addtotvalue(handle, action, GetParam(3,vmstate), (Icallback)callback_CLOSE_CB,vmstate);
		}

		if (!strcmp(action, "DROPFILES_CB"))
		{
			return Addtotvalue(handle, action, GetParam(3,vmstate), (Icallback)callback_DROPFILES_CB,vmstate);
		}

		if (!strcmp(action, "RESIZE_CB"))
		{
			return Addtotvalue(handle, action, GetParam(3,vmstate), (Icallback)callback_RESIZE_CB,vmstate);
		}
		if (!strcmp(action, "SHOW_CB"))
		{
			return Addtotvalue(handle, action, GetParam(3,vmstate), (Icallback)callback_SHOW_CB,vmstate);
		}

		if (!strcmp(action, "FILE_CB"))
		{
			return Addtotvalue(handle, action, GetParam(3,vmstate), (Icallback)callback_FILE_CB,vmstate);
		}

		if (!strcmp(action, "BUTTON_CB"))
		{
			return Addtotvalue(handle, action, GetParam(3,vmstate), (Icallback)callback_BUTTON_CB,vmstate);
		}
		if (!strcmp(action, "MOTION_CB"))
		{
			return Addtotvalue(handle, action, GetParam(3,vmstate), (Icallback)callback_MOTION_CB,vmstate);
		}

		if (!strcmp(action, "WHEEL_CB"))
		{
			return Addtotvalue(handle, action, GetParam(3,vmstate), (Icallback)callback_WHEEL_CB,vmstate);
		}

		if (!strcmp(action, "COLORUPDATE_CB"))
		{
			return Addtotvalue(handle, action, GetParam(3,vmstate), (Icallback)callback_COLORUPDATE_CB,vmstate);
		}
		if (!strcmp(action, "CANCEL_CB"))
		{
			return Addtotvalue(handle, action, GetParam(3,vmstate), (Icallback)callback_CANCEL_CB,vmstate);
		}
		if (!strcmp(action, "EXIT_CB"))
		{
			return Addtotvalue(handle, action, GetParam(3,vmstate), (Icallback)callback_EXIT_CB,vmstate);
		}

		if (!strcmp(action, "NEWTEXT_CB"))
		{
			return Addtotvalue(handle, action, GetParam(3,vmstate), (Icallback)callback_NEWTEXT_CB,vmstate);
		}
		if (!strcmp(action, "CLOSETEXT_CB"))
		{
			return Addtotvalue(handle, action, GetParam(3,vmstate), (Icallback)callback_CLOSETEXT_CB,vmstate);
		}
		if (!strcmp(action, "NEWFILENAME_CB"))
		{
			return Addtotvalue(handle, action, GetParam(3,vmstate), (Icallback)callback_NEWFILENAME_CB,vmstate);
		}
		if (!strcmp(action, "MARKERCHANGED_CB"))
		{
			return Addtotvalue(handle, action, GetParam(3,vmstate), (Icallback)callback_MARKERCHANGED_CB,vmstate);
		}
		if (!strcmp(action, "RESTOREMARKERS_CB"))
		{
			return Addtotvalue(handle, action, GetParam(3,vmstate), (Icallback)callback_RESTOREMARKERS_CB,vmstate);
		}
		if (!strcmp(action, "SAVEMARKERS_CB"))
		{
			return Addtotvalue(handle, action, GetParam(3,vmstate), (Icallback)callback_SAVEMARKERS_CB,vmstate);
		}
		if (!strcmp(action, "CONFIGLOAD_CB"))
		{
			return Addtotvalue(handle, action, GetParam(3,vmstate), (Icallback)callback_CONFIGLOAD_CB,vmstate);
		}

		if (!strcmp(action, "CONFIGSAVE_CB"))
		{
			return Addtotvalue(handle, action, GetParam(3,vmstate), (Icallback)callback_CONFIGSAVE_CB,vmstate);
		}

		if (!strcmp(action, "VALUECHANGED_CB"))
		{
			return Addtotvalue(handle, action, GetParam(3,vmstate), (Icallback)callback_VALUECHANGED_CB,vmstate);
		}

		if (!strcmp(action, "DROPDOWN_CB"))
		{
			return Addtotvalue(handle, action, GetParam(3,vmstate), (Icallback)callback_DROPDOWN_CB,vmstate);
		}


		if (!strcmp(action, "DROPSHOW_CB"))
		{
			return Addtotvalue(handle, action, GetParam(3,vmstate), (Icallback)callback_DROPSHOW_CB,vmstate);
		}

		if (!strcmp(action, "KEYPRESS_CB"))
		{
			return Addtotvalue(handle, action, GetParam(3,vmstate), (Icallback)callback_KEYPRESS_CB,vmstate);
		}


		if (!strcmp(action, "SCROLL_CB"))
		{
			return Addtotvalue(handle, action, GetParam(3,vmstate), (Icallback)callback_SCROLL_CB,vmstate);
		}


		if (!strcmp(action, "WOM_CB"))
		{
			return Addtotvalue(handle, action, GetParam(3,vmstate), (Icallback)callback_WOM_CB,vmstate);
		}


		if (!strcmp(action, "CELL_CB"))
		{
			return Addtotvalue(handle, action, GetParam(3,vmstate), (Icallback)callback_CELL_CB,vmstate);
		}

		if (!strcmp(action, "EXTENDED_CB"))
		{
			return Addtotvalue(handle, action, GetParam(3,vmstate), (Icallback)callback_EXTENDED_CB,vmstate);
		}

		if (!strcmp(action, "SELECT_CB"))
		{
			return Addtotvalue(handle, action, GetParam(3,vmstate), (Icallback)callback_SELECT_CB,vmstate);
		}

		if (!strcmp(action, "SWITCH_CB"))
		{
			return Addtotvalue(handle, action, GetParam(3,vmstate), (Icallback)callback_SWITCH_CB,vmstate);
		}


		if (!strcmp(action, "CHANGE_CB"))
		{
			return Addtotvalue(handle, action, GetParam(3,vmstate), (Icallback)callback_CHANGE_CB,vmstate);
		}


		if (!strcmp(action, "DRAG_CB"))
		{
			return Addtotvalue(handle, action, GetParam(3,vmstate), (Icallback)callback_DRAG_CB,vmstate);
		}

		if (!strcmp(action, "BUTTON_PRESS_CB"))
		{
			return Addtotvalue(handle, action, GetParam(3,vmstate), (Icallback)callback_BUTTON_PRESS_CB,vmstate);
		}

		if (!strcmp(action, "BUTTON_RELEASE_CB"))
		{
			return Addtotvalue(handle, action, GetParam(3,vmstate), (Icallback)callback_BUTTON_RELEASE_CB,vmstate);
		}

		if (!strcmp(action, "MOUSEMOVE_CB"))
		{
			return Addtotvalue(handle, action, GetParam(3,vmstate), (Icallback)callback_MOUSEMOVE_CB,vmstate);
		}

		if (!strcmp(action, "CARET_CB"))
		{
			return Addtotvalue(handle, action, GetParam(3,vmstate), (Icallback)callback_CARET_CB,vmstate);
		}

		if (!strcmp(action, "DBLCLICK_CB"))
		{
			return Addtotvalue(handle, action, GetParam(3,vmstate), (Icallback)callback_DBLCLICK_CB,vmstate);
		}


		if (!strcmp(action, "DRAGDROP_CB"))
		{
			return Addtotvalue(handle, action, GetParam(3,vmstate), (Icallback)callback_DRAGDROP_CB,vmstate);
		}
		if (!strcmp(action, "EDIT_CB"))
		{
			return Addtotvalue(handle, action, GetParam(3,vmstate), (Icallback)callback_EDIT_CB,vmstate);
		}


		if (!strcmp(action, "MULTISELECT_CB"))
		{
			return Addtotvalue(handle, action, GetParam(3,vmstate), (Icallback)callback_MULTISELECT_CB,vmstate);
		}

		if (!strcmp(action, "SPIN_CB"))
		{
			return Addtotvalue(handle, action, GetParam(3,vmstate), (Icallback)callback_SPIN_CB,vmstate);
		}

		if (!strcmp(action, "SELECTION_CB"))
		{
			return Addtotvalue(handle, action, GetParam(3,vmstate), (Icallback)callback_SELECTION_CB,vmstate);
		}

		if (!strcmp(action, "HIGHLIGHT_CB"))
		{
			return Addtotvalue(handle, action, GetParam(3,vmstate), (Icallback)callback_HIGHLIGHT_CB,vmstate);
		}

		if (!strcmp(action, "OPEN_CB"))
		{
			return Addtotvalue(handle, action, GetParam(3,vmstate), (Icallback)callback_OPEN_CB,vmstate);
		}

		if (!strcmp(action, "MENUCLOSE_CB"))
		{
			return Addtotvalue(handle, action, GetParam(3,vmstate), (Icallback)callback_MENUCLOSE_CB,vmstate);
		}
		
		if (!strcmp(action, "ACTION_CB"))
		{
			return Addtotvalue(handle, action, GetParam(3,vmstate), (Icallback)callback_ACTION_CB,vmstate);
		}
		return Null_CreateNull();
	}
};

