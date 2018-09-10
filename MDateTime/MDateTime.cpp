// MDateTime.cpp : 定义 DLL 应用程序的导出函数。
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

StackState CurrentDate()
{
	struct tm *local;  
	time_t t;  
    t=time(NULL);  
    local=localtime(&t);  
	StackState st;
	st =Dict_CreateDict();
	StackState _y;_y.d = local->tm_year+1900;_y.v = M_NUMBER;
	StackState _m;_m.d = local->tm_mon+1;_m.v = M_NUMBER;
	StackState _d;_d.d = local->tm_mday;_d.v = M_NUMBER;
	Dict_Push("y",st.pdict,_y);
	Dict_Push("m",st.pdict,_m);
	Dict_Push("d",st.pdict,_d);
	return st;
}

StackState CurrentTime()
{

	struct tm *local;  
	time_t t;  
    t=time(NULL);  
    local=localtime(&t);  
	StackState st;
	st =Dict_CreateDict();
	StackState _s;_s.d = local->tm_sec;_s.v = M_NUMBER;
	StackState _m;_m.d = local->tm_min;_m.v = M_NUMBER;
	StackState _h; _h.d = local->tm_hour;_h.v = M_NUMBER;
	Dict_Push("s",st.pdict,_s);
	Dict_Push("m",st.pdict,_m);
	Dict_Push("h",st.pdict,_h);
	return st;
}


StackState TimeZone()
{
	StackState st;
	struct tm *local;  
	time_t t;  
    t=time(NULL);  
    local=localtime(&t);  
	st.d = mktime(local);
	st.v = M_NUMBER;
	return st;
}



MentholPackMethod void MDateTime_Init()
{
	RegisterPackAgeFunciton("CurrentDate",CurrentDate,0);	
	RegisterPackAgeFunciton("CurrentTime",CurrentTime,0);	
	RegisterPackAgeFunciton("TimeZone",TimeZone,0);	
}
