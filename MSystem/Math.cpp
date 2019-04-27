#include "stdafx.h"
#include "Math.h"

namespace Math
{
	StackState  Abs(VmState* vmstate)
	{
		StackState st;
		StackState value =GetParam(1,vmstate);
		st.d = abs(value.d);
		st.v=M_NUMBER;
		return st;
	}

	StackState  Acos(VmState* vmstate)
	{
		StackState value =GetParam(1,vmstate);
		StackState st;
		st.d = acos(value.d);
		st.v=M_NUMBER;
		return st;
	}

	StackState  Asin(VmState* vmstate)
	{
		StackState value =GetParam(1,vmstate);
		StackState st;
		st.d = asin(value.d);
		st.v=M_NUMBER;
		return st;
	}


	StackState  Atan(VmState* vmstate)
	{
		StackState value =GetParam(1,vmstate);
		StackState st;
		st.d = atan(value.d);
		st.v=M_NUMBER;
		return st;
	}


	StackState  Atan2(VmState* vmstate)
	{
		StackState value1 =GetParam(1,vmstate);
		StackState value2 =GetParam(2,vmstate);
		StackState st;
		st.d = atan2(value1.d,value2.d);
		st.v=M_NUMBER;
		return st;
	}

	StackState  Ceil(VmState* vmstate)
	{
		StackState value =GetParam(1,vmstate);
		StackState st;
		st.d = ceil(value.d);
		st.v=M_NUMBER;
		return st;
	}


	StackState  Cos(VmState* vmstate)
	{
		StackState value =GetParam(1,vmstate);
		StackState st;
		st.d = cos(value.d);
		st.v=M_NUMBER;
		return st;
	}

	StackState  Cosh(VmState* vmstate)
	{
		StackState value =GetParam(1,vmstate);
		StackState st;
		st.d = cosh(value.d);
		st.v=M_NUMBER;
		return st;
	}


	StackState  Exp(VmState* vmstate)
	{
		StackState value =GetParam(1,vmstate);
		StackState st;
		st.d = exp(value.d);
		st.v=M_NUMBER;
		return st;
	}

	StackState Fabs(VmState* vmstate)
	{
		StackState value =GetParam(1,vmstate);
		StackState st;
		st.d = fabs(value.d);
		st.v=M_NUMBER;
		return st;
	}

	StackState Floor(VmState* vmstate)
	{
		StackState value =GetParam(1,vmstate);
		StackState st;
		st.d = floor(value.d);
		st.v=M_NUMBER;
		return st;
	}

	StackState Fmod(VmState* vmstate)
	{
		StackState value1 =GetParam(1,vmstate);
		StackState value2 =GetParam(2,vmstate);
		StackState st;
		st.d = fmod(value1.d,value2.d);
		st.v=M_NUMBER;
		return st;
	}
	StackState Log(VmState* vmstate)
	{
		StackState value =GetParam(1,vmstate);
		StackState st;
		st.d = log(value.d);
		st.v=M_NUMBER;
		return st;
	}
	StackState Log10(VmState* vmstate)
	{
		StackState value =GetParam(1,vmstate);
		StackState st;
		st.d = log10(value.d);
		st.v=M_NUMBER;
		return st;
	}

	StackState Pow(VmState* vmstate)
	{
		StackState value1 =GetParam(1,vmstate);
		StackState value2 =GetParam(2,vmstate);
		StackState st;
		st.d = pow(value1.d,value2.d);
		st.v=M_NUMBER;
		return st;
	}

	StackState Sin(VmState* vmstate)
	{
		StackState value =GetParam(1,vmstate);
		StackState st;
		st.d = sin(value.d);
		st.v=M_NUMBER;
		return st;
	}

	StackState Sinh(VmState* vmstate)
	{
		StackState value =GetParam(1,vmstate);
		StackState st;
		st.d = sinh(value.d);
		st.v=M_NUMBER;
		return st;
	}

	StackState Sqrt(VmState* vmstate)
	{
		StackState value =GetParam(1,vmstate);
		StackState st;
		st.d = sqrt(value.d);
		st.v=M_NUMBER;
		return st;
	}

	StackState Tan(VmState* vmstate)
	{
		StackState value =GetParam(1,vmstate);
		StackState st;
		st.d = tan(value.d);
		st.v=M_NUMBER;
		return st;
	}

	StackState Tanh(VmState* vmstate)
	{
		StackState value =GetParam(1,vmstate);
		StackState st;
		st.d = tanh(value.d);
		st.v=M_NUMBER;
		return st;
	}
 
	StackState Random(VmState* vmstate)
	{
		StackState st;
		srand(time(0));
		st.d=rand()%100/(double)101;
		st.v=M_NUMBER;
		return st;
	}

	StackState Cbrt(VmState* vmstate)
	{
		StackState value = GetParam(1,vmstate);
		StackState st;
	/*	st.d = cbrt(value.d);*/
		st.v = M_NUMBER;
		return st;
	}
}