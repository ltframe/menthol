#ifndef HEADER
#define HEADER
#include "stdafx.h"
#include "include\iup.h"
#include "Menthol.h"
#include "include\iup_scintilla.h"
struct callbackstruct
{
	Ihandle* handle;
	char* action;
	StackState callbackfunc;
	VmState * vmstate;
};


#endif