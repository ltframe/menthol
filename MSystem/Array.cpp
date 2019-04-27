#include "stdafx.h"
#include "Array.h"
namespace Array
{
	StackState Length(VmState* vmstate)
	{
		StackState st;
		st.v = M_NUMBER;
		StackState value =GetParam(1,vmstate);
		st.d=Array_Length(value.parray);
		return st;
	}
	StackState Join(VmState* vmstate)
	{
		StackState value1 =GetParam(1,vmstate);
		StackState value2 =GetParam(2,vmstate);
		StackState st;
		st.str = Array_Join(value1.parray,static_cast<char*>(value2.str->string),vmstate);
		st.v = M_STRING;
		return st;
	}

	StackState Reverse(VmState* vmstate)
	{
		StackState value =GetParam(1,vmstate);
		StackState st;
		st.parray = Array_Reverse(value.parray);
		st.v = M_ARRAY;
		return st;
	}
 

	StackState Push(VmState* vmstate)
	{
		StackState value1 =GetParam(1,vmstate);
		StackState value2 =GetParam(2,vmstate);
		Array_Push(value1.parray,value2);
		StackState st;
		st.v = M_NULL;
		return st;
	}
};

