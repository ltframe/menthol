// MMath.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"

#include "Menthol.h"
#include <string>
#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <fstream>
#include  <direct.h>  
#include <list>
#include <stdarg.h>
#include <sstream>
#include <time.h>
#include <functional>
#include <math.h>
using namespace std;



StackState  Abs()
{
	StackState st;
	StackState value =GetParam(1);
	if(value.v!=M_NUMBER){
		st.v = M_NULL;
		return st;
	}
	st.d = abs(value.d);
	st.v=M_NUMBER;
	return st;
}

StackState  Acos()
{
	StackState value =GetParam(1);
	StackState st;
	if(value.v!=M_NUMBER){
		st.v = M_NULL;
		return st;
	}
	st.d = acos(value.d);
	st.v=M_NUMBER;
	return st;
}

StackState  Asin()
{
	StackState value =GetParam(1);
	StackState st;
	if(value.v!=M_NUMBER){
		st.v = M_NULL;
		return st;
	}
	st.d = asin(value.d);
	st.v=M_NUMBER;
	return st;
}


StackState  Atan()
{
	StackState value =GetParam(1);
	StackState st;
	if(value.v!=M_NUMBER){
		st.v = M_NULL;
		return st;
	}
	st.d = atan(value.d);
	st.v=M_NUMBER;
	return st;
}


StackState  Atan2()
{
	StackState value1 =GetParam(1);
	StackState value2 =GetParam(2);
	StackState st;
	if(value1.v!=M_NUMBER || value2.v!=M_NUMBER){
		st.v = M_NULL;
		return st;
	}
	st.d = atan2(value1.d,value2.d);
	st.v=M_NUMBER;
	return st;
}

StackState  Ceil()
{
	StackState value =GetParam(1);
	StackState st;
	if(value.v!=M_NUMBER){
		st.v = M_NULL;
		return st;
	}
	st.d = ceil(value.d);
	st.v=M_NUMBER;
	return st;
}


StackState  Cos()
{
	StackState value =GetParam(1);
	StackState st;
	if(value.v!=M_NUMBER){
		st.v = M_NULL;
		return st;
	}
	st.d = cos(value.d);
	st.v=M_NUMBER;
	return st;
}

StackState  Cosh()
{
	StackState value =GetParam(1);
	StackState st;
	if(value.v!=M_NUMBER){
		st.v = M_NULL;
		return st;
	}
	st.d = cosh(value.d);
	st.v=M_NUMBER;
	return st;
}


StackState  Exp()
{
	StackState value =GetParam(1);
	StackState st;
	if(value.v!=M_NUMBER){
		st.v = M_NULL;
		return st;
	}
	st.d = exp(value.d);
	st.v=M_NUMBER;
	return st;
}

StackState Fabs()
{
	StackState value =GetParam(1);
	StackState st;
	if(value.v!=M_NUMBER){
		st.v = M_NULL;
		return st;
	}
	st.d = fabs(value.d);
	st.v=M_NUMBER;
	return st;
}

StackState Floor()
{
	StackState value =GetParam(1);
	StackState st;
	if(value.v!=M_NUMBER){
		st.v = M_NULL;
		return st;
	}
	st.d = floor(value.d);
	st.v=M_NUMBER;
	return st;
}

StackState Fmod()
{
	StackState value1 =GetParam(1);
	StackState value2 =GetParam(2);
	StackState st;
	if(value1.v!=M_NUMBER || value2.v!=M_NUMBER){
		st.v = M_NULL;
		return st;
	}
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
	if(value.v!=M_NUMBER){
		st.v = M_NULL;
		return st;
	}
	st.d = log10(value.d);
	st.v=M_NUMBER;
	return st;
}

StackState Pow()
{
	StackState value1 =GetParam(1);
	StackState value2 =GetParam(2);
	StackState st;
	if(value1.v!=M_NUMBER || value2.v!=M_NUMBER){
		st.v = M_NULL;
		return st;
	}
	st.d = pow(value1.d,value2.d);
	st.v=M_NUMBER;
	return st;
}

StackState Sin()
{
	StackState value =GetParam(1);
	StackState st;
	if(value.v!=M_NUMBER){
		st.v = M_NULL;
		return st;
	}
	st.d = sin(value.d);
	st.v=M_NUMBER;
	return st;
}

StackState Sinh()
{
	StackState value =GetParam(1);
	StackState st;
	if(value.v!=M_NUMBER){
		st.v = M_NULL;
		return st;
	}
	st.d = sinh(value.d);
	st.v=M_NUMBER;
	return st;
}

StackState Sqrt()
{
	StackState value =GetParam(1);
	StackState st;
	if(value.v!=M_NUMBER){
		st.v = M_NULL;
		return st;
	}
	st.d = sqrt(value.d);
	st.v=M_NUMBER;
	return st;
}

StackState Tan()
{
	StackState value =GetParam(1);
	StackState st;
	if(value.v!=M_NUMBER){
		st.v = M_NULL;
		return st;
	}
	st.d = tan(value.d);
	st.v=M_NUMBER;
	return st;
}

StackState Tanh()
{
	StackState value =GetParam(1);
	StackState st;
	if(value.v!=M_NUMBER){
		st.v = M_NULL;
		return st;
	}
	st.d = tanh(value.d);
	st.v=M_NUMBER;
	return st;
}
 
StackState Random()
{
	StackState value =GetParam(1);
	StackState st;
	if(value.v!=M_NUMBER){
		st.v = M_NULL;
		return st;
	}
	srand(time(0));
	st.d=rand()%100/(double)101;
	st.v=M_NUMBER;
	return st;
}

MentholPackMethod void MMath_Init()
{
	RegisterPackAgeFunciton("Abs",Abs,1);	
	RegisterPackAgeFunciton("Acos",Acos,1);	
	RegisterPackAgeFunciton("Asin",Asin,1);	
	RegisterPackAgeFunciton("Atan",Atan,1);	
	RegisterPackAgeFunciton("Atan2",Atan2,2);
	RegisterPackAgeFunciton("Ceil",Ceil,1);	
	RegisterPackAgeFunciton("Cos",Cos,1);
	RegisterPackAgeFunciton("Cosh",Cosh,1);
	RegisterPackAgeFunciton("Exp",Exp,1);
	RegisterPackAgeFunciton("Fabs",Fabs,1);
	RegisterPackAgeFunciton("Floor",Floor,1);
	RegisterPackAgeFunciton("Fmod",Fmod,2);
	RegisterPackAgeFunciton("Log",Log,1);
	RegisterPackAgeFunciton("Log10",Log10,1);
	RegisterPackAgeFunciton("Pow",Pow,2);
	RegisterPackAgeFunciton("Sin",Sin,1);
	RegisterPackAgeFunciton("Sinh",Sinh,1);
	RegisterPackAgeFunciton("Sqrt",Sqrt,1);
	RegisterPackAgeFunciton("Tan",Tan,1);
	RegisterPackAgeFunciton("Tanh",Tanh,1);
	RegisterPackAgeFunciton("Random",Tanh,1);
}