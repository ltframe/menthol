#include "stdafx.h"
#include "MError.h"

MError* MError::_inst = 0;
MError::MError(void)
{
	if(!_inst){
		_inst =this;
	}
}


MError::~MError(void)
{
}

void MError::PrintError(string s)
{
	yyerror(const_cast<char*>(s.c_str()));
}

void MError::PrintRunTimeError(string s)
{
	printf("\r\n");
	cout<<"runtime error: "+s<<endl;
	printf("\r\n");
	abort();
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