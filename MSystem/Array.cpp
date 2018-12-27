#include "stdafx.h"
#include "Array.h"
namespace Array
{
	StackState Length()
	{
		StackState st;
		st.v = M_NUMBER;
		StackState value =GetParam(1);
		st.d=Array_Length(value.parray);
		return st;
	}
	StackState Join()
	{
		StackState value1 =GetParam(1);
		StackState value2 =GetParam(2);
		StackState st;
		st.str = Array_Join(value1.parray,static_cast<char*>(value2.str->string));
		st.v = M_STRING;
		return st;
	}

	StackState Reverse()
	{
		StackState value =GetParam(1);
		StackState st;
		st.parray = Array_Reverse(value.parray);
		st.v = M_ARRAY;
		return st;
	}
 

	StackState Push()
	{
		StackState value1 =GetParam(1);
		StackState value2 =GetParam(2);
		Array_Push(value1.parray,value2);
		StackState st;
		st.v = M_NULL;
		return st;
	}
};

