#pragma once
#include "header.h"

#define funcparamter1(action) callbackstruct cbs = GetIcallback(ih,action);\
							  CreateFunctionCall(1,cbs.vmstate);\
							  PushObject(ih,cbs.vmstate);\
							  return (int)CallFunction(cbs.callbackfunc,cbs.vmstate).d;\
 
#define funcparamter2(action,intval) callbackstruct cbs = GetIcallback(ih,action);\
									 CreateFunctionCall(2,cbs.vmstate);\
									 PushObject(ih,cbs.vmstate);\
									 PushNumber(intval,cbs.vmstate);\
									 return (int)CallFunction(cbs.callbackfunc,cbs.vmstate).d;\



extern vector<callbackstruct> *_tvalues;
callbackstruct GetIcallback(Ihandle* ih,char* action)
{
	for (std::vector<callbackstruct>::iterator it = _tvalues->begin() ; it != _tvalues->end(); ++it)
	{		
		if(!strcmp(action,(*it).action) && ih==(*it).handle)
		{
			return (*it);
		}
	}
	return callbackstruct();
}



int callback_MAP_CB(Ihandle *ih)
{
	funcparamter1("MAP_CB");
}
int callback_UNMAP_CB(Ihandle *ih)
{
	funcparamter1("UNMAP_CB");
}
int callback_DESTROY_CB(Ihandle *ih)
{
	funcparamter1("DESTROY_CB");
}
int callback_GETFOCUS_CB(Ihandle *ih)
{
	funcparamter1("GETFOCUS_CB");
}
int callback_KILLFOCUS_CB(Ihandle *ih)
{
	funcparamter1("KILLFOCUS_CB");
}
int callback_ENTERWINDOW_CB(Ihandle *ih)
{
	funcparamter1("ENTERWINDOW_CB");
}
int callback_LEAVEWINDOW_CB(Ihandle *ih)
{
	funcparamter1("LEAVEWINDOW_CB");
}
int callback_K_ANY(Ihandle *ih, int c)
{
	funcparamter2("K_ANY",c)
}
int callback_HELP_CB(Ihandle *ih)
{
	ih = IupGetDialog(ih);
	funcparamter1("HELP_CB");
}



int callback_CLOSE_CB(Ihandle *ih)
{
	funcparamter1("CLOSE_CB");
}


int callback_DROPFILES_CB(Ihandle *ih, const char* filename, int num, int x, int y)
{
	callbackstruct cbs =GetIcallback(ih,"DROPFILES_CB");
	VmState* vmstate = cbs.vmstate;
	CreateFunctionCall(5,vmstate);
	PushObject(ih,vmstate);
	PushString(String_CreateString((char*)filename,vmstate).str,vmstate);
	PushNumber(num,vmstate);
	PushNumber(x,vmstate);
	PushNumber(y,vmstate);
	return (int)CallFunction(cbs.callbackfunc,vmstate).d;
}

int callback_RESIZE_CB(Ihandle *ih, int width, int height)
{
	callbackstruct cbs =GetIcallback(ih,"RESIZE_CB");
	VmState* vmstate = cbs.vmstate;
	CreateFunctionCall(3,vmstate);
	PushObject(ih,vmstate);
	PushNumber(width,vmstate);
	PushNumber(height,vmstate);
	return (int)CallFunction(cbs.callbackfunc,vmstate).d;
	
}


int callback_SHOW_CB(Ihandle *ih, int state)
{
	funcparamter2("SHOW_CB",state)
}

int callback_FILE_CB(Ihandle *ih, const char* file_name, const char* status)
{
	callbackstruct cbs =GetIcallback(ih,"FILE_CB");
	VmState* vmstate = cbs.vmstate;
	CreateFunctionCall(3,vmstate);
	PushObject(ih,vmstate);
	PushString(String_CreateString((char*)file_name,vmstate).str,vmstate);
	PushString(String_CreateString((char*)status,vmstate).str,vmstate);
	return (int)CallFunction(cbs.callbackfunc,vmstate).d;
	
}


int callback_Button_ACTION(Ihandle *ih)
{
	funcparamter1("ACTION");
}


int callback_BUTTON_CB(Ihandle* ih, int button, int pressed, int x, int y, char* status)
{
	callbackstruct cbs =GetIcallback(ih,"BUTTON_CB");
	VmState* vmstate = cbs.vmstate;
	CreateFunctionCall(6,vmstate);
	PushObject(ih,vmstate);
	PushNumber(button,vmstate);
	PushNumber(pressed,vmstate);
	PushNumber(x,vmstate);
	PushNumber(y,vmstate);
	PushString(String_CreateString(status,vmstate).str,vmstate);
	return (int)CallFunction(cbs.callbackfunc,vmstate).d;
	
}



int callback_MOTION_CB(Ihandle *ih, int x, int y, char *status)
{
	callbackstruct cbs =GetIcallback(ih,"MOTION_CB");
	VmState* vmstate = cbs.vmstate;
	CreateFunctionCall(4,vmstate);
	PushObject(ih,vmstate);
	PushNumber(x,vmstate);
	PushNumber(y,vmstate);
	PushString(String_CreateString(status,vmstate).str,vmstate);
	return (int)CallFunction(cbs.callbackfunc,vmstate).d;
	
}


int callback_WHEEL_CB(Ihandle *ih, float delta, int x, int y, char *status)
{
	callbackstruct cbs =GetIcallback(ih,"WHEEL_CB");
	VmState* vmstate = cbs.vmstate;
	CreateFunctionCall(5,vmstate);
	PushObject(ih,vmstate);
	PushNumber(delta,vmstate);
	PushNumber(x,vmstate);
	PushNumber(y,vmstate);
	PushString(String_CreateString(status,vmstate).str,vmstate);
	return (int)CallFunction(cbs.callbackfunc,vmstate).d;
	

}

int callback_COLORUPDATE_CB(Ihandle *ih)
{
	funcparamter1("COLORUPDATE_CB");
}

int callback_CANCEL_CB(Ihandle *ih)
{
	funcparamter1("CANCEL_CB");
}


int callback_EXIT_CB(Ihandle *ih)
{
	funcparamter1("EXIT_CB");
}

int callback_NEWTEXT_CB(Ihandle* ih, char* old_filename, char* new_filename)
{
	callbackstruct cbs =GetIcallback(ih,"NEWTEXT_CB");
	VmState* vmstate = cbs.vmstate;
	CreateFunctionCall(3,vmstate);
	PushObject(ih,vmstate);
	PushString(String_CreateString(old_filename,vmstate).str,vmstate);
	PushString(String_CreateString(new_filename,vmstate).str,vmstate);
	return (int)CallFunction(cbs.callbackfunc,vmstate).d;
	
}


int callback_CLOSETEXT_CB(Ihandle* ih, Ihandle* multitext)
{
	callbackstruct cbs =GetIcallback(ih,"CLOSETEXT_CB");
	VmState* vmstate = cbs.vmstate;
	CreateFunctionCall(2,vmstate);
	PushObject(ih,vmstate);
	PushObject(multitext,vmstate);
	return (int)CallFunction(cbs.callbackfunc,vmstate).d;
	
}


int callback_NEWFILENAME_CB(Ihandle* ih, Ihandle* multitext)
{
	callbackstruct cbs =GetIcallback(ih,"NEWFILENAME_CB");
	VmState* vmstate = cbs.vmstate;
	CreateFunctionCall(2,vmstate);
	PushObject(ih,vmstate);
	PushObject(multitext,vmstate);
	return (int)CallFunction(cbs.callbackfunc,vmstate).d;
	
}

int callback_MARKERCHANGED_CB(Ihandle* ih, Ihandle* multitext, int lin, int margin)
{
	callbackstruct cbs =GetIcallback(ih,"MARKERCHANGED_CB");
	VmState* vmstate = cbs.vmstate;
	CreateFunctionCall(2,vmstate);
	PushObject(ih,vmstate);
	PushObject(multitext,vmstate);
	PushNumber(lin,vmstate);
	PushNumber(margin,vmstate);
	return (int)CallFunction(cbs.callbackfunc,vmstate).d;
	

}


int callback_RESTOREMARKERS_CB(Ihandle* ih, Ihandle* multitext)
{
	callbackstruct cbs =GetIcallback(ih,"RESTOREMARKERS_CB");
	VmState* vmstate = cbs.vmstate;
	CreateFunctionCall(2,vmstate);
	PushObject(ih,vmstate);
	PushObject(multitext,vmstate);
	return (int)CallFunction(cbs.callbackfunc,vmstate).d;
	
}

int callback_SAVEMARKERS_CB(Ihandle* ih, Ihandle* multitext)
{
	callbackstruct cbs =GetIcallback(ih,"SAVEMARKERS_CB");
	VmState* vmstate = cbs.vmstate;
	CreateFunctionCall(2,vmstate);
	PushObject(ih,vmstate);
	PushObject(multitext,vmstate);
	return (int)CallFunction(cbs.callbackfunc,vmstate).d;
	
}

int callback_CONFIGLOAD_CB(Ihandle* ih, Ihandle* multitext)
{
	callbackstruct cbs =GetIcallback(ih,"CONFIGLOAD_CB");
	VmState* vmstate = cbs.vmstate;
	CreateFunctionCall(2,vmstate);
	PushObject(ih,vmstate);
	PushObject(multitext,vmstate);
	return (int)CallFunction(cbs.callbackfunc,vmstate).d;
	
}

int callback_CONFIGSAVE_CB(Ihandle* ih, Ihandle* multitext)
{
	callbackstruct cbs =GetIcallback(ih,"CONFIGSAVE_CB");
	VmState* vmstate = cbs.vmstate;
	CreateFunctionCall(2,vmstate);
	PushObject(ih,vmstate);
	PushObject(multitext,vmstate);
	return (int)CallFunction(cbs.callbackfunc,vmstate).d;
	
}


int callback_DropButton_FLAT_ACTION(Ihandle *ih)
{
	funcparamter1("FLAT_ACTION");
}


int callback_VALUECHANGED_CB(Ihandle *ih)
{
	funcparamter1("VALUECHANGED_CB");
}


int callback_DROPDOWN_CB(Ihandle *ih, int state)
{
	funcparamter2("DROPDOWN_CB",state);
}

int callback_DROPSHOW_CB(Ihandle *ih, int state)
{
	funcparamter2("DROPSHOW_CB",state);
}


int callback_KEYPRESS_CB(Ihandle *ih, int c, int press)
{
	callbackstruct cbs =GetIcallback(ih,"KEYPRESS_CB");
	VmState* vmstate = cbs.vmstate;
	CreateFunctionCall(3,vmstate);
	PushObject(ih,vmstate);
	PushNumber(c,vmstate);
	PushNumber(press,vmstate);
	return (int)CallFunction(cbs.callbackfunc,vmstate).d;
	
}


int callback_SCROLL_CB(Ihandle *ih, int op, float posx, float posy)
{
	callbackstruct cbs =GetIcallback(ih,"SCROLL_CB");
	VmState* vmstate = cbs.vmstate;
	CreateFunctionCall(4,vmstate);
	PushObject(ih,vmstate);
	PushNumber(op,vmstate);
	PushNumber(posx,vmstate);
	PushNumber(posy,vmstate);
	return (int)CallFunction(cbs.callbackfunc,vmstate).d;
	
}


int callback_WOM_CB(Ihandle *ih, int state)
{
	funcparamter2("WOM_CB",state);
}


int callback_CELL_CB(Ihandle* ih, int cell)
{
	funcparamter2("CELL_CB",cell);
}

int callback_EXTENDED_CB(Ihandle* ih, int cell)
{
	funcparamter2("EXTENDED_CB",cell);
}


int callback_SELECT_CB(Ihandle* ih, int cell, int type)
{
	callbackstruct cbs =GetIcallback(ih,"SELECT_CB");
	VmState* vmstate = cbs.vmstate;
	CreateFunctionCall(3,vmstate);
	PushObject(ih,vmstate);
	PushNumber(cell,vmstate);
	PushNumber(type,vmstate);
	return (int)CallFunction(cbs.callbackfunc,vmstate).d;
	
}

int callback_SWITCH_CB(Ihandle* ih, int prim_cell, int sec_cell)
{
	callbackstruct cbs =GetIcallback(ih,"SWITCH_CB");
	VmState* vmstate = cbs.vmstate;
	CreateFunctionCall(3,vmstate);
	PushObject(ih,vmstate);
	PushNumber(prim_cell,vmstate);
	PushNumber(sec_cell,vmstate);
	return (int)CallFunction(cbs.callbackfunc,vmstate).d;
	
}


int callback_CHANGE_CB(Ihandle *ih, unsigned char r, unsigned char g, unsigned char b)
{
	callbackstruct cbs =GetIcallback(ih,"CHANGE_CB");
	VmState* vmstate = cbs.vmstate;
	CreateFunctionCall(4,vmstate);
	PushObject(ih,vmstate);
	PushNumber(r,vmstate);
	PushNumber(g,vmstate);
	PushNumber(b,vmstate);
	return (int)CallFunction(cbs.callbackfunc,vmstate).d;
	
}

int callback_DRAG_CB(Ihandle *ih, unsigned char r, unsigned char g, unsigned char b)
{
	callbackstruct cbs =GetIcallback(ih,"DRAG_CB");
	VmState* vmstate = cbs.vmstate;
	CreateFunctionCall(4,vmstate);
	PushObject(ih,vmstate);
	PushNumber(r,vmstate);
	PushNumber(g,vmstate);
	PushNumber(b,vmstate);
	return (int)CallFunction(cbs.callbackfunc,vmstate).d;
	
}


int callback_BUTTON_PRESS_CB(Ihandle* ih, int angle)
{
	funcparamter2("BUTTON_PRESS_CB",angle);
}

int callback_BUTTON_RELEASE_CB(Ihandle* ih, int angle)
{
	funcparamter2("BUTTON_RELEASE_CB",angle);
}

int callback_MOUSEMOVE_CB(Ihandle* ih, int angle)
{
	funcparamter2("MOUSEMOVE_CB",angle);
}


int callback_Link_ACTION(Ihandle* ih, char *url)
{
	callbackstruct cbs =GetIcallback(ih,"ACTION");
	VmState* vmstate = cbs.vmstate;
	CreateFunctionCall(2,vmstate);
	PushObject(ih,vmstate);
	PushString(String_CreateString(url,vmstate).str,vmstate);
	return (int)CallFunction(cbs.callbackfunc,vmstate).d;
	
}

int callback_List_ACTION(Ihandle *ih, char *text, int item, int state)
{
	callbackstruct cbs =GetIcallback(ih,"ACTION");
	VmState* vmstate = cbs.vmstate;
	CreateFunctionCall(4,vmstate);
	PushObject(ih,vmstate);
	PushString(String_CreateString(text,vmstate).str,vmstate);
	PushNumber(item,vmstate);
	PushNumber(state,vmstate);
	return (int)CallFunction(cbs.callbackfunc,vmstate).d;
	
}


int callback_ACTION_Common(Ihandle *ih)
{
	funcparamter1("ACTION");
}

int callback_CARET_CB(Ihandle *ih, int lin, int col, int pos)
{
	callbackstruct cbs =GetIcallback(ih,"CARET_CB");
	VmState* vmstate = cbs.vmstate;
	CreateFunctionCall(4,vmstate);
	PushObject(ih,vmstate);
	PushNumber(lin,vmstate);
	PushNumber(col,vmstate);
	PushNumber(pos,vmstate);
	return (int)CallFunction(cbs.callbackfunc,vmstate).d;
	
}

int callback_DBLCLICK_CB(Ihandle *ih, int item, char *text)
{
	callbackstruct cbs =GetIcallback(ih,"DBLCLICK_CB");
	VmState* vmstate = cbs.vmstate;
	CreateFunctionCall(3,vmstate);
	PushObject(ih,vmstate);
	PushNumber(item,vmstate);
	PushString(String_CreateString(text,vmstate).str,vmstate);
	return (int)CallFunction(cbs.callbackfunc,vmstate).d;
	
}


int callback_DRAGDROP_CB(Ihandle *ih, int drag_id, int drop_id, int isshift, int iscontrol)
{
	callbackstruct cbs =GetIcallback(ih,"DRAGDROP_CB");
	VmState* vmstate = cbs.vmstate;
	CreateFunctionCall(5,vmstate);
	PushObject(ih,vmstate);
	PushNumber(drag_id,vmstate);
	PushNumber(drop_id,vmstate);
	PushNumber(isshift,vmstate);
	PushNumber(iscontrol,vmstate);
	return (int)CallFunction(cbs.callbackfunc,vmstate).d;
	

}


int callback_EDIT_CB(Ihandle *ih, int c, char *new_value)
{
	callbackstruct cbs =GetIcallback(ih,"EDIT_CB");
	VmState* vmstate = cbs.vmstate;
	CreateFunctionCall(3,vmstate);
	PushObject(ih,vmstate);
	PushNumber(c,vmstate);
	PushString(String_CreateString(new_value,vmstate).str,vmstate);
	return (int)CallFunction(cbs.callbackfunc,vmstate).d;
	
}


int callback_MULTISELECT_CB(Ihandle *ih, char *value)
{
	callbackstruct cbs =GetIcallback(ih,"MULTISELECT_CB");
	VmState* vmstate = cbs.vmstate;
	CreateFunctionCall(3,vmstate);
	PushObject(ih,vmstate);
	PushString(String_CreateString(value,vmstate).str,vmstate);
	return (int)CallFunction(cbs.callbackfunc,vmstate).d;
	
}


int callback_SPIN_CB(Ihandle* ih, int inc)
{
	funcparamter2("SPIN_CB",inc);
}


int callback_Text_ACTION(Ihandle *ih, int c, char *new_value)
{
	callbackstruct cbs =GetIcallback(ih,"ACTION");
	VmState* vmstate = cbs.vmstate;
	CreateFunctionCall(3,vmstate);
	PushObject(ih,vmstate);
	PushNumber(c,vmstate);
	PushString(String_CreateString(new_value,vmstate).str,vmstate);
	return (int)CallFunction(cbs.callbackfunc,vmstate).d;
	
}

int callback_Toggle_ACTION(Ihandle* ih, int state)
{
	callbackstruct cbs =GetIcallback(ih,"ACTION");
	VmState* vmstate = cbs.vmstate;
	CreateFunctionCall(2,vmstate);
	PushObject(ih,vmstate);
	PushNumber(state,vmstate);
	return (int)CallFunction(cbs.callbackfunc,vmstate).d;
	
}


int callback_FlatToggle_FLAT_ACTION(Ihandle* ih, int state)
{
	funcparamter2("FLAT_ACTION",state);
}



int callback_SELECTION_CB(Ihandle *ih, int id, int status)
{
	callbackstruct cbs =GetIcallback(ih,"SELECTION_CB");
	VmState* vmstate = cbs.vmstate;
	CreateFunctionCall(3,vmstate);
	PushObject(ih,vmstate);
	PushNumber(id,vmstate);
	PushNumber(status,vmstate);
	return (int)CallFunction(cbs.callbackfunc,vmstate).d;	
}

int callback_HIGHLIGHT_CB(Ihandle *ih)
{
	funcparamter1("HIGHLIGHT_CB");
}

int callback_OPEN_CB(Ihandle *ih)
{
	funcparamter1("OPEN_CB");
}

int callback_MENUCLOSE_CB(Ihandle *ih)
{
	funcparamter1("MENUCLOSE_CB");
}

int callback_ACTION_CB(Ihandle *ih)
{
	funcparamter1("ACTION_CB");
}





















