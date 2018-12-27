#include "stdafx.h"
#include "Number.h"
namespace Number
{
	StackState ToString()
	{
		StackState value =GetParam(1);
		StackState st;
		st.v = M_STRING;
		char a[32];
		sprintf(a,"%f",value.d);
		st = String_CreateString(a);
		return st;
	}

	StackState ToNumber()
	{
		StackState value =GetParam(1);
		StackState st;
		st.v = M_NUMBER;
		st.d = atoi(value.str->string);
		return st;
	}
};