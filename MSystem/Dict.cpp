#include "stdafx.h"
#include "Dict.h"

namespace Dict
{
	StackState Length(VmState* vmstate)
	{
		StackState value =GetParam(1,vmstate);
		StackState st;	
		st.d = Dict_Length(value.pdict);
		st.v = M_NUMBER;
		return st;
	}
	StackState Push(VmState* vmstate)
	{
		StackState value1 =GetParam(1,vmstate);
		StackState value2 =GetParam(2,vmstate);
		StackState value3 =GetParam(3,vmstate);
		Dict_Push(value1.str->string,value2.pdict,value3);
		StackState st;
		st.v=M_NULL;
		return st;
	}
	StackState GetValue(VmState* vmstate)
	{
		StackState value1 =GetParam(1,vmstate);
		StackState value2 =GetParam(2,vmstate);
		return Dict_Get(value1.pdict,value2.hash);
	}

	StackState SetValue(VmState* vmstate)
	{
		StackState value1 =GetParam(1,vmstate);
		StackState value2 =GetParam(2,vmstate);
		StackState value3 =GetParam(3,vmstate);
		Dict_Set(value1.str->string,value2.pdict,value3);
		StackState st;
		st.v=M_NULL;
		return st;
	}


	StackState GetKey(VmState* vmstate)
	{
		StackState value1 =GetParam(1,vmstate);
		StackState value2 =GetParam(2,vmstate);
		StackState st;
		st.str = Dict_Key(value1.pdict,value2.hash,vmstate);
		st.v = M_STRING;
		return st;
	}
};


