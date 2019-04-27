#include "Handle.h"
#define MAX_SIZE   10000
namespace Handle
{
	StackState SetHandle(VmState* vmstate)
	{
		char* aa = GetParam(1,vmstate).str->string;
		Ihandle* bbb = static_cast<Ihandle*>(GetParam(2,vmstate).p);
		return Object_CreateObject(IupSetHandle(GetParam(1,vmstate).str->string,static_cast<Ihandle*>(GetParam(2,vmstate).p)));
	}
	StackState GetHandle(VmState* vmstate)
	{
		return Object_CreateObject(IupGetHandle(GetParam(1,vmstate).str->string));
	}
	StackState GetName(VmState* vmstate)
	{
		return String_CreateString(IupGetName(static_cast<Ihandle*>(GetParam(1,vmstate).p)),vmstate);
	}
	StackState GetAllNames(VmState* vmstate)
	{
		char* names[MAX_SIZE];
		int c = GetParam(1,vmstate).d;
		if(c>MAX_SIZE){
			c= MAX_SIZE;
		}
		int k = IupGetAllNames(names,c);
		StackState ret = Array_CreateArray(vmstate);
		for (int i=0; i < k; i++)
		{
			Array_Push(ret.parray,String_CreateString(names[i],vmstate));
		}
		return ret;
	}
	StackState GetAllDialogs(VmState* vmstate)
	{
		char* names[MAX_SIZE];
		int c = GetParam(1,vmstate).d;
		if(c>MAX_SIZE){
			c= MAX_SIZE;
		}
		int k = IupGetAllDialogs(names,c);
		StackState ret = Array_CreateArray(vmstate);
		for (int i=0; i < k; i++)
		{
			Array_Push(ret.parray,String_CreateString(names[i],vmstate));
		}
		return ret;
	}
};

