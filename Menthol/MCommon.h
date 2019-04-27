#pragma once
#ifndef	MCOMMON
#define MCOMMON
#include <string>
#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <fstream>
#include <direct.h>  
#include <list>
#include <stdarg.h>
#include "Parser.h"
using namespace std;

class MCommon
{
public:
	MCommon(void);
	~MCommon(void);
	static MCommon* CreateInstance();
	hashValue ELFHash(string str);
	PathInfo StringPathSplit(string _path);
	string GetRunPath(); 
	bool StrCmpNoCase(string str1,string str2);
	string CreateGuid();
	wchar_t* AnsiToWideChar(const char* str);
private:
	static MCommon* _inst;
	string runpath;
};
#endif

