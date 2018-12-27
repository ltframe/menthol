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

MPackAge* MPackAge::CreateInstance()
{
	return _inst;
}