#include "stdafx.h"
#include "String.h"


namespace String
{
	StackState SetLanguage(VmState* vmstate)
	{
		IupSetLanguage(GetParam(1,vmstate).str->string);
		return Null_CreateNull();
	}
	StackState GetLanguage(VmState* vmstate)
	{
		return String_CreateString(IupGetLanguage(),vmstate);
	}
	StackState SetLanguageString(VmState* vmstate)
	{
		IupSetLanguageString(GetParam(1,vmstate).str->string,GetParam(2,vmstate).str->string);
		return Null_CreateNull();
	}
	StackState GetLanguageString(VmState* vmstate)
	{
		return String_CreateString(IupGetLanguageString(GetParam(1,vmstate).str->string),vmstate);
	}
};
