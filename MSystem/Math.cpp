#include "stdafx.h"
#include "Math.h"

namespace Math
{
	StackState  Abs()
	{
		StackState st;
		StackState value =GetParam(1);
		st.d = abs(value.d);
		st.v=M_NUMBER;
		return st;
	}

	StackState  Acos()
	{
		StackState value =GetParam(1);
		StackState st;
		st.d = acos(value.d);
		st.v=M_NUMBER;
		return st;
	}

	StackState  Asin()
	{
		StackState value =GetParam(1);
		StackState st;
		st.d = asin(value.d);
		st.v=M_NUMBER;
		return st;
	}


	StackState  Atan()
	{
		StackState value =GetParam(1);
		StackState st;
		st.d = atan(value.d);
		st.v=M_NUMBER;
		return st;
	}


	StackState  Atan2()
	{
		StackState value1 =GetParam(1);
		StackState value2 =GetParam(2);
		StackState st;
		st.d = atan2(value1.d,value2.d);
		st.v=M_NUMBER;
		return st;
	}

	StackState  Ceil()
	{
		StackState value =GetParam(1);
		StackState st;
		st.d = ceil(value.d);
		st.v=M_NUMBER;
		return st;
	}


	StackState  Cos()
	{
		StackState value =GetParam(1);
		StackState st;
		st.d = cos(value.d);
		st.v=M_NUMBER;
		return st;
	}

	StackState  Cosh()
	{
		StackState value =GetParam(1);
		StackState st;
		st.d = cosh(value.d);
		st.v=M_NUMBER;
		return st;
	}


	StackState  Exp()
	{
		StackState value =GetParam(1);
		StackState st;
		st.d = exp(value.d);
		st.v=M_NUMBER;
		return st;
	}

	StackState Fabs()
	{
		StackState value =GetParam(1);
		StackState st;
		st.d = fabs(value.d);
		st.v=M_NUMBER;
		return st;
	}

	StackState Floor()
	{
		StackState value =GetParam(1);
		StackState st;
		st.d = floor(value.d);
		st.v=M_NUMBER;
		return st;
	}

	StackState Fmod()
	{
		StackState value1 =GetParam(1);
		StackState value2 =GetParam(2);
		StackState st;
		st.d = fmod(value1.d,value2.d);
		st.v=M_NUMBER;
		return st;
	}
	StackState Log()
	{
		StackState value =GetParam(1);
		StackState st;
		st.d = log(value.d);
		st.v=M_NUMBER;
		return st;
	}
	StackState Log10()
	{
		StackState value =GetParam(1);
		StackState st;
		st.d = log10(value.d);
		st.v=M_NUMBER;
		return st;
	}

	StackState Pow()
	{
		StackState value1 =GetParam(1);
		StackState value2 =GetParam(2);
		StackState st;
		st.d = pow(value1.d,value2.d);
		st.v=M_NUMBER;
		return st;
	}

	StackState Sin()
	{
		StackState value =GetParam(1);
		StackState st;
		st.d = sin(value.d);
		st.v=M_NUMBER;
		return st;
	}

	StackState Sinh()
	{
		StackState value =GetParam(1);
		StackState st;
		st.d = sinh(value.d);
		st.v=M_NUMBER;
		return st;
	}

	StackState Sqrt()
	{
		StackState value =GetParam(1);
		StackState st;
		st.d = sqrt(value.d);
		st.v=M_NUMBER;
		return st;
	}

	StackState Tan()
	{
		StackState value =GetParam(1);
		StackState st;
		st.d = tan(value.d);
		st.v=M_NUMBER;
		return st;
	}

	StackState Tanh()
	{
		StackState value =GetParam(1);
		StackState st;
		st.d = tanh(value.d);
		st.v=M_NUMBER;
		return st;
	}
 
	StackState Random()
	{
		StackState value =GetParam(1);
		StackState st;
		srand(time(0));
		st.d=rand()%100/(double)101;
		st.v=M_NUMBER;
		return st;
	}

	StackState Cbrt()
	{
		StackState value = GetParam(1);
		StackState st;
	/*	st.d = cbrt(value.d);*/
		st.v = M_NUMBER;
		return st;
	}


	StackState Truncate()
	{
		StackState value = GetParam(1);
		return Number_CreateNumber((int)value.d);
	}
}