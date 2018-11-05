#include "stdafx.h"
#include "MError.h"
#include "Vm.h"
MError* MError::_inst = 0;
MError::MError(void):_PrintCompileErrorFunc(0),_PrintRunTimeErrorFunc(0)
{
	if(!_inst){
		_inst =this;
	}
}


MError::~MError(void)
{
	_inst = 0;
}

void MError::SetCompilePrintErrorFunc(PrintErrorFunc func)
{
	_PrintCompileErrorFunc = func;
}

void MError::SetRunTimePrintErrorFunc(PrintErrorFunc func)
{
	_PrintRunTimeErrorFunc = func;
}

void MError::PrintError(string s,int _lineno)
{
	if(_lineno!=-1)
		lineno = _lineno;

	yyerrorcount++;

	if(_PrintCompileErrorFunc)
	_PrintCompileErrorFunc(CONSTCAST(char)(s.c_str()),currentyyfile,lineno);
}

void MError::PrintRunTimeError(string s)
{

	int line = -1;
	string filename("");
	vector<MentholDebug> * list = Vm::GetDebugList();
	if(list){
		int c = list->size();
		Instruction* st = Vm::GetCodeListStart();
		if(!st)
		{
			if(_PrintRunTimeErrorFunc)
				_PrintRunTimeErrorFunc(CONSTCAST(char)(s.c_str()),0,-1);

			exit(1);
			return;
		}
		int x = Vm::GetCurrentCodeList()-st;
		MentholDebug dinfo;
		VECTORFORSTART(MentholDebug,list,it)
			if((*it).instno==x)
			{
					dinfo = (*it);
					break;
			}	
		VECTORFOREND
		if(c!=0){
			line = dinfo.lineno;
			filename = list->at(0).filename;
		}
	}



	if(_PrintRunTimeErrorFunc)
		_PrintRunTimeErrorFunc(CONSTCAST(char)(s.c_str()),CONSTCAST(char)(filename.c_str()),line);

	exit(1);
	return;
}

MError* MError::CreateInstance()
{
	return _inst;
}
void MError::DataTypeOpertatError(StackState* value1,StackState* value2,char* str)
{
	char* v1string;
	STACKSTATESTRING(value1,v1string)
	char* v2string;
	STACKSTATESTRING(value2,v2string)
	PrintRunTimeError(string(v1string)+ " and " + v2string + ","+ str);
}