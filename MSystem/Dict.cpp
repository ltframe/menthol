#include "stdafx.h"
#include "Dict.h"

namespace Dict
{
	StackState Length()
	{
		StackState value =GetParam(1);
		StackState st;	
		st.d = Dict_Length(value.pdict);
		st.v = M_NUMBER;
		return st;
	}
	StackState Push()
	{
		StackState value1 =GetParam(1);
		StackState value2 =GetParam(2);
		StackState value3 =GetParam(3);
		Dict_Push(value1.str->string,value2.pdict,value3);
		StackState st;
		st.v=M_NULL;
		return st;
	}
	StackState GetValue()
	{
		StackState value1 =GetParam(1);
		StackState value2 =GetParam(2);
		return Dict_Get(value1.pdict,value2.hash);
	}

	StackState SetValue()
	{
		StackState value1 =GetParam(1);
		StackState value2 =GetParam(2);
		StackState value3 =GetParam(3);
		Dict_Set(value1.str->string,value2.pdict,value3);
		StackState st;
		st.v=M_NULL;
		return st;
	}


	StackState GetKey()
	{
		StackState value1 =GetParam(1);
		StackState value2 =GetParam(2);
		StackState st;
		st.str = Dict_Key(value1.pdict,value2.hash);
		st.v = M_STRING;
		return st;
	}
};


