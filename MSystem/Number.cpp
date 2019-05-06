#include "stdafx.h"
#include "Number.h"
namespace Number
{
	StackState ToString(VmState* vmstate)
	{
		StackState value =GetParam(1,vmstate);
		StackState st;
		st.v = M_STRING;
		char a[32];
		sprintf(a,"%f",value.d);
		st = String_CreateString(a,vmstate);
		return st;
	}

	StackState ToNumber(VmState* vmstate)
	{
		StackState value =GetParam(1,vmstate);
		StackState st;
		st.v = M_NUMBER;
		st.d = atoi(value.str->string);
		return st;
	}
};