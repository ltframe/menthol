// MArray.cpp : 定义 DLL 应用程序的导出函数。
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
using namespace std;



StackState Length()
{
	StackState st;
	st.v = M_NUMBER;
	StackState value =GetParam(1);
	if (value.v!=M_ARRAY)
	{
		st.d=-1;
	}else
	{
		st.d=Array_Length(value.parray);
	}
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
 

MentholPackMethod void MP_Init()
{
	RegisterPackAgeFunciton("Length",Length,1);	
	RegisterPackAgeFunciton("Join",Join,2);	
	RegisterPackAgeFunciton("Reverse",Reverse,1);	
	RegisterPackAgeFunciton("Push",Push,2);	
}