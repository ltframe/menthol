#pragma once
#ifndef MERROR
#define MERROR
#include <string>
#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <fstream>
#include  <direct.h>  
#include <list>
#include <stdarg.h>
#include "header.h"
extern int yyerror(char* str);

using namespace std;

class MError
{
public:
	MError(void);
	~MError(void);
	void PrintError(string s,int _lineno = -1);
	static MError* CreateInstance();
	int ErrorCount();
	void DataTypeOpertatError(STACKSTATEPOINTER value1,STACKSTATEPOINTER value2,char* str);
	void PrintRunTimeError(string s);
	void SetCompilePrintErrorFunc(PrintErrorFunc func);
	void SetRunTimePrintErrorFunc(PrintErrorFunc func);
private:
	static MError* _inst;
	PrintErrorFunc _PrintCompileErrorFunc;
	PrintErrorFunc _PrintRunTimeErrorFunc;
};
#endif
