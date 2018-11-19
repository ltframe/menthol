// MString.cpp : 定义 DLL 应用程序的导出函数。
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


StackState StoN()
{
	StackState value =GetParam(1);
	StackState st;
	st.d = atof(value.str->string);
	st.v=M_NUMBER;
	return st;
}

StackState IndexOf()
{
	StackState value1 =GetParam(1);
	StackState value2 =GetParam(2);
	string s1(value1.str->string);
	string::size_type pos = s1.find(value2.str->string);
	int index = -1;
    if(pos != string::npos)
	{
		index = pos;
	}
	StackState st;
	st.d =index;
	st.v  = M_NUMBER;	
	return st;
}

std::string replace(const std::string& inStr, const char* pSrc, const char* pReplace )
{
    std::string str = inStr;
    std::string::size_type stStart = 0;
    std::string::iterator iter = str.begin();
    while( iter != str.end() )
    {
        // 从指定位置 查找下一个要替换的字符串的起始位置。
        std::string::size_type st = str.find( pSrc, stStart );
        if ( st == str.npos )
        {
            break;
        }
        iter = iter + st - stStart;
        // 将目标字符串全部替换。
        str.replace( iter, iter + strlen( pSrc ), pReplace );
        iter = iter + strlen( pReplace );
        // 替换的字符串下一个字符的位置
        stStart = st + strlen( pReplace );
    }
    return str;
}

StackState Replace()
{
	StackState st;
	StackState value1 =GetParam(1);
	StackState value2 =GetParam(2);
	StackState value3 =GetParam(3);
	st = String_CreateString(const_cast<char*>(replace(string(value1.str->string),value2.str->string,value3.str->string).c_str()));
	return st;
}





StackState Toupper()
{
	StackState st;
	StackState value =GetParam(1);
	int len = strlen(value.str->string);
	int i;
	char*dest = (char*)malloc(len + 1);
	for (i = 0; i < len; ++i)
	{
		dest[i] = toupper(value.str->string[i]);
	}
		dest[len] = 0;

	st = String_CreateString(dest);
	free(dest);
	return st;
}

StackState Tolower()
{
	StackState st;
	StackState value =GetParam(1);
	int len = strlen(value.str->string);
	int i;
	char*dest = (char*)malloc(len + 1);
	for (i = 0; i < len; ++i)
	{
		dest[i] = tolower(value.str->string[i]);
	}
	dest[len] = 0;
	st = String_CreateString(dest);
	free(dest);
	return st;
}

StackState Length()
{
	StackState value =GetParam(1);
	StackState st;
	st.d = strlen(value.str->string);
	st.v  = M_NUMBER;	
	return st;
}

StackState Isdigit()
{
	StackState value = GetParam(1);	
	StackState st;
	st.v = M_BOOL;
	if (value.v == M_NUMBER)
	{
		st.b = true;
		return st;
	}
	if (value.v != M_STRING)
	{
		st.b = false;
		return st;
	}
	char * str = value.str->string;
	while (*str != '\0'){
		bool b = isdigit(*str);
		if (!b){
			st.b = false;
			return st;
		}
		str++;
	}
	st.b = true;
	return st;
}
 
StackState Isalpha()
{
	StackState value = GetParam(1);
	StackState st;
	st.v = M_BOOL;
	if (value.v == M_NUMBER)
	{
		st.b = false;
		return st;
	}
	if (value.v != M_STRING)
	{
		st.b = false;
		return st;
	}
	char * str = value.str->string;
	while (*str != '\0'){
		bool b = isalpha(*str);
		if (!b){
			st.b = false;
			return st;
		}
		str++;
	}
	st.b = true;
	return st;
}

MentholPackMethod void MString_Init()
{
	RegisterPackAgeFunciton("StoN",StoN,1);	
	RegisterPackAgeFunciton("Length",Length,1);	
	RegisterPackAgeFunciton("IndexOf",IndexOf,2);
	RegisterPackAgeFunciton("Replace",Replace,3);
	RegisterPackAgeFunciton("Toupper",Toupper,1);
	RegisterPackAgeFunciton("Tolower",Tolower,1);
	RegisterPackAgeFunciton("Isdigit", Isdigit, 1);
	RegisterPackAgeFunciton("Isalpha", Isalpha, 1);
}