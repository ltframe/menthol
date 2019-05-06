#include "Attributes.h"
namespace Attributes
{
	StackState SetAttribute(VmState* vmstate)
	{
		IupSetAttribute(static_cast<Ihandle*>(GetParam(1,vmstate).p),GetParam(2,vmstate).str->string,GetParam(3,vmstate).str->string);
		return Null_CreateNull();
	}

	StackState SetAttributes(VmState* vmstate)
	{
		return Object_CreateObject(IupSetAttributes(static_cast<Ihandle*>(GetParam(1, vmstate).p), GetParam(2, vmstate).str->string));
	}

	StackState SetAttributeHandle(VmState* vmstate)
	{
		IupSetAttributeHandle(static_cast<Ihandle*>(GetParam(1,vmstate).p),GetParam(2,vmstate).str->string,static_cast<Ihandle*>(GetParam(3,vmstate).p));
		return Null_CreateNull();
	}

	StackState ResetAttribute(VmState* vmstate)
	{
		IupResetAttribute(static_cast<Ihandle*>(GetParam(1,vmstate).p),GetParam(2,vmstate).str->string);
		return Null_CreateNull();
	}


	StackState GetAttribute(VmState* vmstate)
	{
		char* ret = IupGetAttribute(static_cast<Ihandle*>(GetParam(1,vmstate).p),GetParam(2,vmstate).str->string);
		if(ret)
		{
			return String_CreateString(ret,vmstate);
		}
		return Null_CreateNull();
	}

	StackState GetAttributeData(VmState* vmstate)
	{
		return Object_CreateObject(IupGetAttribute(static_cast<Ihandle*>(GetParam(1,vmstate).p),GetParam(2,vmstate).str->string));
	}

	StackState GetAllAttributes(VmState* vmstate)
	{
		return Null_CreateNull();
	}

	StackState GetAttributes(VmState* vmstate)
	{
		return String_CreateString(IupGetAttributes(static_cast<Ihandle*>(GetParam(1,vmstate).p)),vmstate);
	}

	StackState CopyAttributes(VmState* vmstate)
	{
		IupCopyAttributes(static_cast<Ihandle*>(GetParam(1,vmstate).p),static_cast<Ihandle*>(GetParam(2,vmstate).p));
		return Null_CreateNull();
	}

	StackState GetAttributeHandle(VmState* vmstate)
	{
		return Object_CreateObject(IupGetAttributeHandle(static_cast<Ihandle*>(GetParam(1,vmstate).p),GetParam(2,vmstate).str->string));
	}

	StackState SetGlobal(VmState* vmstate)
	{
		IupSetGlobal(GetParam(1,vmstate).str->string,GetParam(2,vmstate).str->string);
		return Null_CreateNull();
	}

	StackState GetGlobal(VmState* vmstate)
	{
		return String_CreateString(IupGetGlobal(GetParam(1,vmstate).str->string),vmstate);
	}
};

