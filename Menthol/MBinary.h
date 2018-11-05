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
	void ReadBinary(string filename,vector <FunctionAtter>* FunctionRecoredList,vector<string>* stringconstants,vector<Instruction> *codelist,
		vector<Instruction> &globalcodelist,vector<double>* doubleconstants,vector<PackageState*>* packagelist,vector<RunTimeState*> *vrts,vector<StringValue>* dictkeyconstants,vector<MentholDebug>* debuglist);
	void MReadImportFiles(const char* fp,vector<PackageAttr> *filetree,char* modidr,char* workdir);
	bool IsInInclude(vector<PackageState*>* packagelist,hashValue hash);
};
#endif

