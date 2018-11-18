#pragma once
#ifndef MBITWISE
#define MBITWISE
#include "Vm.h"
#include "MGc.h"

namespace MBitwise
{

StackState ConvertToNumber(STACKSTATEPOINTER value)
{
	StackState ret;
	if(IsBool(value)){
		ret.v = M_NUMBER;
		ret.d = value->b?1:0;
		return ret;
	}

	if(IsNumber(value)){
		ret = *value;
		return ret;
	}
	ret.v = M_NUMBER;
	ret.d = 0;
	return ret;
}

inline bool SHIFTL(STACKSTATEPOINTER value1,STACKSTATEPOINTER value2)
{
	
	value1->d=(int)(ConvertToNumber(value1).d)<<(int)(ConvertToNumber(value2).d);
	value1->v = M_NUMBER;
	return true;
}

inline bool SHIFTR(STACKSTATEPOINTER value1,STACKSTATEPOINTER value2)
{
	
	value1->d=(int)(ConvertToNumber(value1).d)>>(int)(ConvertToNumber(value2).d);
	value1->v = M_NUMBER;
	return true;
}

inline bool BitAnd(STACKSTATEPOINTER value1,STACKSTATEPOINTER value2)
{
	
	value1->d=((int)(ConvertToNumber(value1).d) & (int)(ConvertToNumber(value2).d));
	value1->v = M_NUMBER;
	return true;
}

inline bool BitOr(STACKSTATEPOINTER value1,STACKSTATEPOINTER value2)
{
	
	value1->d=((int)(ConvertToNumber(value1).d) | (int)(ConvertToNumber(value2).d));
	value1->v = M_NUMBER;
	return true;
}
};
#endif
