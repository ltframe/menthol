
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
	//如果在设计计算、比较的操作上，如果两个操作数不符合操作类型，则提示
	void DataTypeOpertatError(STACKSTATEPOINTER value1,STACKSTATEPOINTER value2,char* str,VmState* vmstate);
	void PrintRunTimeError(string s,VmState * vmstate);

	//设置编译错误提示调用的函数，fuc为函数指针，在Compile函数中指定
	void SetCompilePrintErrorFunc(PrintErrorFunc func);
	//设置运行错误提示调用的函数，fuc为函数指针，在Run函数中指定
	void SetRunTimePrintErrorFunc(PrintErrorFunc func);
private:
	static MError* _inst;
	PrintErrorFunc _PrintCompileErrorFunc;
	PrintErrorFunc _PrintRunTimeErrorFunc;
};
#endif
