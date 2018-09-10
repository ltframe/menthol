// MNumber.cpp : 定义 DLL 应用程序的导出函数。
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

MentholPackMethod void MNumber_Init()
{
	RegisterPackAgeFunciton("ToString",ToString,1);	

}