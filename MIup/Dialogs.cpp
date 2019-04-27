#include "Dialogs.h"
namespace Dialogs
{

	StackState Dialog(VmState* vmstate)
	{
		StackState p = GetParam(1,vmstate);
		if(p.v==M_NULL)
		{
			return Object_CreateObject(IupDialog(0));
		}
		return Object_CreateObject(IupDialog(static_cast<Ihandle*>(GetParam(1,vmstate).p)));
	}

	StackState Popup(VmState* vmstate)
	{
		return Number_CreateNumber(IupPopup(static_cast<Ihandle*>(GetParam(1,vmstate).p),GetParam(2,vmstate).d,GetParam(3,vmstate).d));
	}

	StackState Show(VmState* vmstate)
	{
		return Number_CreateNumber(IupShow(static_cast<Ihandle*>(GetParam(1,vmstate).p)));
	}

	StackState ShowXY(VmState* vmstate)
	{
		return Number_CreateNumber(IupShowXY(static_cast<Ihandle*>(GetParam(1,vmstate).p),GetParam(2,vmstate).d,GetParam(3,vmstate).d));
	}


	StackState Hide(VmState* vmstate)
	{
		return Number_CreateNumber(IupHide(static_cast<Ihandle*>(GetParam(1,vmstate).p)));
	}

	StackState FileDlg(VmState* vmstate)
	{
		return Object_CreateObject(IupFileDlg());
	}

	StackState MessageDlg(VmState* vmstate)
	{
		return Object_CreateObject(IupMessageDlg());
	}

	StackState ColorDlg(VmState* vmstate)
	{
		return Object_CreateObject(IupColorDlg());
	}

	StackState FontDlg(VmState* vmstate)
	{
		return Object_CreateObject(IupFontDlg());
	}

	StackState ProgressDlg(VmState* vmstate)
	{
		return Object_CreateObject(IupProgressDlg());
	}

	StackState ScintillaDlg(VmState* vmstate)
	{
		return Object_CreateObject(IupScintillaDlg());
	}

	StackState Alarm(VmState* vmstate)
	{
		return Number_CreateNumber(IupAlarm(GetParam(1,vmstate).str->string,GetParam(2,vmstate).str->string,GetParam(3,vmstate).str->string,GetParam(4,vmstate).str->string,GetParam(5,vmstate).str->string));
	}

	StackState GetFile(VmState* vmstate)
	{
		return Number_CreateNumber(IupGetFile(GetParam(1,vmstate).str->string));
	}

	StackState GetColor(VmState* vmstate)
	{
		return Number_CreateNumber(IupGetColor(GetParam(1,vmstate).d,GetParam(2,vmstate).d,(unsigned char*)GetParam(3,vmstate).str->string,(unsigned char*)GetParam(4,vmstate).str->string,(unsigned char*)GetParam(5,vmstate).str->string));
	}


	StackState GetText(VmState* vmstate)
	{
		return Number_CreateNumber(IupGetText(GetParam(1,vmstate).str->string,GetParam(2,vmstate).str->string,GetParam(3,vmstate).d));
	}

	StackState ListDialog(VmState* vmstate)
	{
		int size = GetParam(3,vmstate).d;
		pArray p = GetParam(4,vmstate).parray;
		char** list = new char*[size];
		for (int i = 0; i < size; i++)
		{
			list[i] = Array_Get(p,i).str->string;
		}
		pArray p2 = GetParam(8,vmstate).parray;
		int* list2 = new int[size];
		for (int i = 0; i < size; i++)
		{
			list2[i] =  Array_Get(p2,i).d;
		}
		int k = IupListDialog(GetParam(1,vmstate).d,GetParam(2,vmstate).str->string,size,(const char**)list,GetParam(5,vmstate).d,GetParam(6,vmstate).d,GetParam(7,vmstate).d,list2);
		
		if(k)
		{

			StackState retarry =Array_CreateArray(vmstate);
			for(int i=0;i<size;i++)
			{
				Array_Push(retarry.parray,Number_CreateNumber(list2[i]));	
			}
			delete[] list;
			delete[] list2;	
			return retarry;	
		}
		delete[] list;
		delete[] list2;
		return Null_CreateNull();
	}

	StackState Message(VmState* vmstate)
	{
		IupMessage(GetParam(1,vmstate).str->string,GetParam(2,vmstate).str->string);
		return Null_CreateNull();
	}

	StackState MessageError(VmState* vmstate)
	{
		IupMessageError(0,GetParam(1,vmstate).str->string);
		return Null_CreateNull();
	}

	StackState MessageAlarm(VmState* vmstate)
	{
		return Number_CreateNumber(IupMessageAlarm(0,GetParam(1,vmstate).str->string,GetParam(2,vmstate).str->string,GetParam(3,vmstate).str->string));
	}


	StackState LayoutDialog(VmState* vmstate)
	{
		return Object_CreateObject(IupLayoutDialog(static_cast<Ihandle*>(GetParam(1,vmstate).p)));
	}


	StackState ElementPropertiesDialog(VmState* vmstate)
	{
		return Object_CreateObject(IupElementPropertiesDialog(static_cast<Ihandle*>(GetParam(1,vmstate).p)));
	}
};
