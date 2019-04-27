#pragma once
#include "Menthol.h"
namespace Math
{
	StackState Abs(VmState* vmstate);
	StackState Acos(VmState* vmstate);
	StackState Asin(VmState* vmstate);
	StackState Atan(VmState* vmstate);
	StackState Atan2(VmState* vmstate);
	StackState Ceil(VmState* vmstate);
	StackState Cos(VmState* vmstate);
	StackState Cosh(VmState* vmstate);
	StackState Exp(VmState* vmstate);
	StackState Fabs(VmState* vmstate);
	StackState Floor(VmState* vmstate);
	StackState Fmod(VmState* vmstate);
	StackState Log(VmState* vmstate);
	StackState Log10(VmState* vmstate);
	StackState Pow(VmState* vmstate);
	StackState Sin(VmState* vmstate);
	StackState Sinh(VmState* vmstate);
	StackState Sqrt(VmState* vmstate);
	StackState Tan(VmState* vmstate);
	StackState Tanh(VmState* vmstate);
	StackState Random(VmState* vmstate);
	StackState Cbrt(VmState* vmstate);
	//StackState Truncate(VmState* vmstate);
};

