#pragma once
#ifndef MLOGIC
#define MLOGIC
#include "Vm.h"
#include "MGc.h"


namespace MLogic
{


inline bool Xor(STACKSTATEPOINTER value1,STACKSTATEPOINTER value2)
{	
	
	value1->v = M_BOOL;
	if((IsNumber(value1) || IsBool(value1)) && (IsNumber(value2) || IsBool(value2))){
			value1->b=(bool)((int)(value1->d)^(int)(value2->d));
			return true;
	}
	value1->b = false;
	return false;
}

inline bool EqEq(STACKSTATEPOINTER value1,STACKSTATEPOINTER value2)
{

	if((IsNumber(value1) || IsBool(value1)) && (IsNumber(value1) || IsBool(value1))){
			value1->v = M_BOOL;
			value1->b=(value1->d==value2->d);
			return true;
	}
	if(IsString(value1) && IsString(value2))
	{
		value1->v = M_BOOL;
		value1->b=(strcmp(value1->str->string,value2->str->string)==0?true:false);
		return true;
	}
	if(IsNULL(value1) && IsNULL(value2))
	{
		value1->v = M_BOOL;
		value1->b=true;
		return true;
	}
	return false;
}

//Ğ¡ÓÚ
inline bool Lt(STACKSTATEPOINTER value1,STACKSTATEPOINTER value2)
{

	if((IsNumber(value1) || IsBool(value1)) && (IsNumber(value1) || IsBool(value1))){
			value1->v = M_BOOL;
			value1->b=(value1->d<value2->d);
			return true;
	}
	if(IsString(value1) && IsString(value2))
	{
		value1->v = M_BOOL;
		int k=strcmp(value1->str->string,value2->str->string);
		value1->b=(k<0)?true:false;
		return true;
	}
	return false;
}

inline bool Le(STACKSTATEPOINTER value1,STACKSTATEPOINTER value2)
{

	if((IsNumber(value1) || IsBool(value1)) && (IsNumber(value1) || IsBool(value1))){
			value1->v = M_BOOL;
			value1->b=(value1->d>value2->d);
			return true;
	}
	if(IsString(value1) && IsString(value2))
	{
		value1->v = M_BOOL;
		int k=strcmp(value1->str->string,value2->str->string);
		value1->b=(k>0)?true:false;
		return true;
	}
	return false;
}

inline bool Geeq(STACKSTATEPOINTER value1,STACKSTATEPOINTER value2)
{

	if((IsNumber(value1) || IsBool(value1)) && (IsNumber(value1) || IsBool(value1))){
			value1->v = M_BOOL;
			value1->b=(value1->d>=value2->d);
			return true;
	}
	if(IsString(value1) && IsString(value2))
	{
		value1->v = M_BOOL;
		int k=strcmp(value1->str->string,value2->str->string);
		value1->b=(k>=0)?true:false;
		return true;
	}
	return false;
}

inline bool Leeq(STACKSTATEPOINTER value1,STACKSTATEPOINTER value2)
{

	if((IsNumber(value1) || IsBool(value1)) && (IsNumber(value1) || IsBool(value1))){
			value1->v = M_BOOL;
			value1->b=(value1->d<=value2->d);
			return true;
	}
	if(IsString(value1) && IsString(value2))
	{
		value1->v = M_BOOL;
		int k=strcmp(value1->str->string,value2->str->string);
		value1->b=(k<=0)?true:false;
		return true;
	}
	return false;
}
inline bool Neq(STACKSTATEPOINTER value1,STACKSTATEPOINTER value2)
{	
	if((IsNumber(value1) || IsBool(value1)) && (IsNumber(value1) || IsBool(value1))){
			value1->v = M_BOOL;
			value1->b=(value1->d!=value2->d);
			return true;
	}
	if(IsString(value1) && IsString(value2))
	{
		int k=strcmp(value1->str->string,value2->str->string);
		value1->v = M_BOOL;
		value1->b=(k!=0)?true:false;
		return true;
	}
	if(IsNULL(value1) && IsNULL(value2))
	{
		value1->v = M_BOOL;
		value1->b=false;
		return true;
	}
	return false;
}

inline bool Or(STACKSTATEPOINTER value1,STACKSTATEPOINTER value2)
{
	CONVERTVALUETYPE(value1,value2)
	value1->v = M_BOOL;
	value1->b=value1->b || value2->b;
	return true;
}

inline bool And(STACKSTATEPOINTER value1,STACKSTATEPOINTER value2)
{
	CONVERTVALUETYPE(value1,value2)
	value1->v = M_BOOL;
	value1->b=value1->b && value2->b;;
	return true;
}
};
#endif
