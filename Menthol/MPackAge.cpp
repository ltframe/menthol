#include "stdafx.h"
#include "MPackAge.h"
#include "StatementList.h"
#include <algorithm>

MPackAge* MPackAge::_inst = 0;
MPackAge::MPackAge(void)
{
	if(!_inst){
		_inst =this;
	}
}
MPackAge::~MPackAge(void)
{
		_inst=0;

}

PackAgeType MPackAge::GetPackAgeType(char* f)
{
	string ex = strrchr(f, '.')+1;
	transform(ex.begin(), ex.end(), ex.begin(),::tolower);
	if(ex==MENTHOLPACKAGEDLLEXTENSION){
		return MPA_PACKAGE;
	}
	if(ex=="dll"){
		return MPA_DLL;
	}
	return MPA_UNKONWN;
}
MPackAge* MPackAge::CreateInstance()
{
	return _inst;
}