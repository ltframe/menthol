// MString.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include  "String.h"
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

namespace String{
	StackState StoN(VmState* vmstate)
	{
		StackState value =GetParam(1,vmstate);
		StackState st;
		st.d = atof(value.str->string);
		st.v=M_NUMBER;
		return st;
	}

	StackState IndexOf(VmState* vmstate)
	{
		StackState value1 =GetParam(1,vmstate);
		StackState value2 =GetParam(2,vmstate);
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


	std::string replaceformat(std::string str, VmState* vmstate)
	{
		size_t start_pos = 0;
		string from = "%";
		int i = 2;
		while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
			StackState value = GetParam(i, vmstate);
			string to = string(value.str->string);
			str.replace(start_pos, from.length(), to);
			start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
			i++;
		}
		return str;
	}

	StackState ReplaceFormat(VmState* vmstate)
	{
		StackState st;
		StackState value1 = GetParam(1, vmstate);
		st = String_CreateString(const_cast<char*>(replaceformat(string(value1.str->string),vmstate).c_str()), vmstate);
		return st;
	}


	StackState Replace(VmState* vmstate)
	{
		StackState st;
		StackState value1 =GetParam(1,vmstate);
		StackState value2 =GetParam(2,vmstate);
		StackState value3 =GetParam(3,vmstate);
		st = String_CreateString(const_cast<char*>(replace(string(value1.str->string),value2.str->string,value3.str->string).c_str()),vmstate);
		return st;
	}





	StackState Toupper(VmState* vmstate)
	{
		StackState st;
		StackState value =GetParam(1,vmstate);
		int len = strlen(value.str->string);
		int i;
		char*dest = (char*)malloc(len + 1);
		for (i = 0; i < len; ++i)
		{
			dest[i] = toupper(value.str->string[i]);
		}
			dest[len] = 0;

		st = String_CreateString(dest,vmstate);
		free(dest);
		return st;
	}

	StackState Tolower(VmState* vmstate)
	{
		StackState st;
		StackState value =GetParam(1,vmstate);
		int len = strlen(value.str->string);
		int i;
		char*dest = (char*)malloc(len + 1);
		for (i = 0; i < len; ++i)
		{
			dest[i] = tolower(value.str->string[i]);
		}
		dest[len] = 0;
		st = String_CreateString(dest,vmstate);
		free(dest);
		return st;
	}

	StackState Length(VmState* vmstate)
	{
		StackState value =GetParam(1,vmstate);
		StackState st;
		st.d = strlen(value.str->string);
		st.v  = M_NUMBER;	
		return st;
	}

	StackState Isdigit(VmState* vmstate)
	{
		StackState value = GetParam(1,vmstate);	
		StackState st;
		st.v = M_BOOL;
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
 
	StackState Isalpha(VmState* vmstate)
	{
		StackState value = GetParam(1,vmstate);
		StackState st;
		st.v = M_BOOL;
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


	StackState UTF8ToGBK(VmState* vmstate)  
	{  
		char* utf8str = GetParam(1,vmstate).str->string;
		int len = MultiByteToWideChar(CP_UTF8, 0,utf8str , -1, NULL, 0);  
		WCHAR* wszGBK = new WCHAR[len+1];
		memset(wszGBK, 0, len * 2 + 2);  
		MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)(LPCTSTR)utf8str, -1, wszGBK, len);  
 
		len = WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, NULL, 0, NULL, NULL);  
		char *szGBK = new char[len + 1];  
		memset(szGBK, 0, len + 1);  
		WideCharToMultiByte(CP_ACP,0, wszGBK, -1, szGBK, len, NULL, NULL);   
		StackState str = String_CreateString(szGBK,vmstate);  
		delete[]szGBK;  
		delete[]wszGBK;  
		return str;  
	} 
	StackState GBKToUTF8(VmState* vmstate)  
	{  
		char * strGBK = GetParam(1,vmstate).str->string;
		WCHAR * str1;  
		int n = MultiByteToWideChar(CP_ACP, 0, strGBK, -1, NULL, 0);  
		str1 = new WCHAR[n];  
		MultiByteToWideChar(CP_ACP, 0, strGBK, -1, str1, n);  
		n = WideCharToMultiByte(CP_UTF8, 0, str1, -1, NULL, 0, NULL, NULL);  
		char * str2 = new char[n];  
		WideCharToMultiByte(CP_UTF8, 0, str1, -1, str2, n, NULL, NULL);  
		StackState str = String_CreateString(str2,vmstate);  
		delete[]str1;  
		delete[]str2;  
		return str;  
	} 



	StackState Toascii(VmState* vmstate)
	{
		StackState value =GetParam(1,vmstate);
		char str[2]={toascii((int)value.d),'\0'};
		return String_CreateString(str,vmstate);
	}

}