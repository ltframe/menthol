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
private:
	static MCommon* _inst;
};
#endif

