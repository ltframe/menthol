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
	void PrintError(string s);
	static MError* CreateInstance();
	int ErrorCount();
	void DataTypeOpertatError(StackState* value1,StackState* value2,char* str);
	void PrintRunTimeError(string s);
public:
	
private:
	static MError* _inst;
};
#endif
