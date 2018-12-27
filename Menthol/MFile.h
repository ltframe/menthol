#pragma once
#ifndef MFILE
#define MFILE
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
#include "MCommon.h"
using namespace std;

struct StringAtter
{
	string str;
	hashValue hash;
};
class MFile
{
public:
	MFile(void);
	~MFile(void);
	static  MFile* CreateInstance();	
	void GenerateFileData(vector<Instruction>* codelist,vector<StringAtter>* stringlist,vector <FunctionAtter> * funcitonlist,vector <const char*> * importfiles,string extension,string name);
	bool IsFileExist(string csFile);
private:	
	string MFile::currentDateTime();
	static MFile* _inst;
};
#endif
