#pragma once
#ifndef MBINARY
#define MBINARY
#include <string>
#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <fstream>
#include <direct.h>  
#include <list>
#include <stdarg.h>
#include <sstream>
#include <time.h>
#include "header.h"
#include <stack>
#include "MPackAge.h"
using namespace std;

#define READHEAD(attr)\
	{char buffer[4];\
	buffer[0] = bufferf[i++];\
	buffer[1] = bufferf[i++];\
	buffer[2] = bufferf[i++];\
	buffer[3] = bufferf[i++];\
	attr = *(int*)buffer;}


class MBinary
{
public:
	MBinary(void);
	~MBinary(void);
	Instruction ReadCode(char* bufferf,int &i);
	void ReadCode(string filename);	
	void ReadBinary(ImportFileAttr fileattr, vector<Instruction> *codelist,
	vector<RunTimeState*> *vrts, vector<StringValue>* dictkeyconstants, void(*_AddRunTimeStateList)(RunTimeState*)
	,vector<GlobalCodeRuntimeAtter>* globallist);
	void MReadImportFiles(const char* fp,vector<ImportFileAttr> *filetree,char* modidr,char* workdir);
	void ReadMEPPackage(string filename,vector<string>* list);
	static MBinary* CreateInstance();
	string ReadPackageFormat(string filename);
private:
	static MBinary* _inst;
};
#endif

