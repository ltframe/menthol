#pragma once
#ifndef MBITWISE
#define MBITWISE
#include "Vm.h"
#include "MGc.h"

namespace MBitwise
{

inline bool SHIFTL(STACKSTATEPOINTER value1,STACKSTATEPOINTER value2)
{
	if((IsNumber(value1) || IsBool(value1)) && (IsNumber(value2) || IsBool(value2))){
			value1->v = M_NUMBER;
			value1->d=(int)(value1->d)<<(int)(value2->d);
			return true;
	}
	MError::CreateInstance()->DataTypeOpertatError(value1,value2," can't bitwise");
	return false;
}

inline bool SHIFTR(STACKSTATEPOINTER value1,STACKSTATEPOINTER value2)
{
	if((IsNumber(value1) || IsBool(value1)) && (IsNumber(value2) || IsBool(value2))){
			value1->v = M_NUMBER;
			value1->d=(int)(value1->d)>>(int)(value2->d);
			return true;
	}
	MError::CreateInstance()->DataTypeOpertatError(value1,value2," can't bitwise");
	return false;
}

inline bool BitAnd(STACKSTATEPOINTER value1,STACKSTATEPOINTER value2)
{
	value1->v = M_NUMBER;
	value1->d=((int)(value1->d) & (int)(value2->d));
	return true;
}

inline bool BitOr(STACKSTATEPOINTER value1,STACKSTATEPOINTER value2)
{
	value1->v = M_NUMBER;
	value1->d=((int)(value1->d) | (int)(value2->d));
	return true;
}
};
#endif
