#pragma once
#ifndef MPACKAGE
#define MPACKAGE
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
#include "header.h"
#include <stack>
using namespace std;
class MPackAge
{
public:
	MPackAge(void);
	~MPackAge(void);
	static  MPackAge* CreateInstance();	
	PackAgeType GetPackAgeType(char*);
private:	
	static MPackAge* _inst;
};
#endif
