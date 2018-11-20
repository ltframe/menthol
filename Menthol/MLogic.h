#pragma once
#ifndef MLOGIC
#define MLOGIC
#include "Vm.h"
#include "MGc.h"
#include "MMath.h"

namespace MLogic
{

StackState ConvertToBool(STACKSTATEPOINTER value)
{
	StackState ret;
	if(IsNULL(value)){
		ret.v = M_BOOL;
		ret.b = false;
		return ret;
	}

	if(IsNumber(value)){
		ret.v = M_BOOL;
		ret.b = value->d!=0?1:0;
		return ret;
	}

	if(IsBool(value))
	{
		ret = *value;
		return ret;
	}

	if(IsString(value) && !strcmp(value->str->string,"")){
		ret.v = M_BOOL;
		ret.b = false;
		return ret;
	}

	ret.v = M_BOOL;
	ret.b = true;
	return ret;
}

inline bool Xor(STACKSTATEPOINTER value1,STACKSTATEPOINTER value2)
{		
	value1->b=(ConvertToBool(value1).b)^(ConvertToBool(value2).b);
	value1->v = M_BOOL;
	return true;
}

inline bool EqEq(STACKSTATEPOINTER value1,STACKSTATEPOINTER value2)
{


	if(IsString(value1) && IsString(value2))
	{
		value1->v = M_BOOL;
		value1->b=(strcmp(value1->str->string,value2->str->string)==0?true:false);
		return true;
	}
	StackState ctn1 = MMath::ConvertToNumber(value1);
	StackState ctn2 = MMath::ConvertToNumber(value2);
	if (ctn1.v != M_UNKONWN && ctn2.v != M_UNKONWN){
		value1->v = M_BOOL;
		value1->b = (ctn1.d==ctn2.d);
		return true;
	}
	MError::CreateInstance()->DataTypeOpertatError(value1, value2, " Can't compare");
	return false;
	
}

//ะกำฺ
inline bool Lt(STACKSTATEPOINTER value1,STACKSTATEPOINTER value2)
{

	StackState ctn1 = MMath::ConvertToNumber(value1);
	StackState ctn2 = MMath::ConvertToNumber(value2);
	if(ctn1.v!=M_UNKONWN && ctn2.v!=M_UNKONWN){	
			value1->v = M_BOOL;
			value1->b=(ctn1.d<ctn2.d);
			return true;
	}
	if(IsString(value1) && IsString(value2))
	{
		value1->v = M_BOOL;
		int k=strcmp(value1->str->string,value2->str->string);
		value1->b=(k<0)?true:false;
		return true;
	}
	MError::CreateInstance()->DataTypeOpertatError(value1,value2," Can't compare");
	return false;
}

inline bool Le(STACKSTATEPOINTER value1,STACKSTATEPOINTER value2)
{

	StackState ctn1 = MMath::ConvertToNumber(value1);
	StackState ctn2 = MMath::ConvertToNumber(value2);
	if(ctn1.v!=M_UNKONWN && ctn2.v!=M_UNKONWN){	
			value1->v = M_BOOL;
			value1->b=(ctn1.d>ctn2.d);
			return true;
	}
	if(IsString(value1) && IsString(value2))
	{
		value1->v = M_BOOL;
		int k=strcmp(value1->str->string,value2->str->string);
		value1->b=(k>0)?true:false;
		return true;
	}
	MError::CreateInstance()->DataTypeOpertatError(value1,value2," Can't compare");
	return false;
}

inline bool Geeq(STACKSTATEPOINTER value1,STACKSTATEPOINTER value2)
{

	StackState ctn1 = MMath::ConvertToNumber(value1);
	StackState ctn2 = MMath::ConvertToNumber(value2);
	if(ctn1.v!=M_UNKONWN && ctn2.v!=M_UNKONWN){	
			value1->v = M_BOOL;
			value1->b=(ctn1.d>=ctn2.d);
			return true;
	}
	if(IsString(value1) && IsString(value2))
	{
		value1->v = M_BOOL;
		int k=strcmp(value1->str->string,value2->str->string);
		value1->b=(k>=0)?true:false;
		return true;
	}
	MError::CreateInstance()->DataTypeOpertatError(value1,value2," Can't compare");
	return false;
}

inline bool Leeq(STACKSTATEPOINTER value1,STACKSTATEPOINTER value2)
{

	StackState ctn1 = MMath::ConvertToNumber(value1);
	StackState ctn2 = MMath::ConvertToNumber(value2);
	if(ctn1.v!=M_UNKONWN && ctn2.v!=M_UNKONWN){	
			value1->v = M_BOOL;
			value1->b=(ctn1.d<=ctn2.d);
			return true;
	}
	if(IsString(value1) && IsString(value2))
	{
		value1->v = M_BOOL;
		int k=strcmp(value1->str->string,value2->str->string);
		value1->b=(k<=0)?true:false;
		return true;
	}
	MError::CreateInstance()->DataTypeOpertatError(value1,value2," Can't compare");
	return false;
}
inline bool Neq(STACKSTATEPOINTER value1,STACKSTATEPOINTER value2)
{	
	StackState ctn1 = MMath::ConvertToNumber(value1);
	StackState ctn2 = MMath::ConvertToNumber(value2);
	if(ctn1.v!=M_UNKONWN && ctn2.v!=M_UNKONWN){	
			value1->v = M_BOOL;
			value1->b=(ctn1.d!=ctn2.d);
			return true;
	}
	if(IsString(value1) && IsString(value2))
	{
		int k=strcmp(value1->str->string,value2->str->string);
		value1->v = M_BOOL;
		value1->b=(k!=0)?true:false;
		return true;
	}
	MError::CreateInstance()->DataTypeOpertatError(value1,value2," Can't compare");
	return false;
}

inline bool Or(STACKSTATEPOINTER value1,STACKSTATEPOINTER value2)
{
	
	value1->b=(ConvertToBool(value1).b) || (ConvertToBool(value2).b);
	value1->v = M_BOOL;
	return true;
}

inline bool And(STACKSTATEPOINTER value1,STACKSTATEPOINTER value2)
{
	
	value1->b=(ConvertToBool(value1).b) && (ConvertToBool(value2).b);
	value1->v = M_BOOL;
	return true;
}

inline bool Inv(STACKSTATEPOINTER value)
{
	
	value->b=!ConvertToBool(value).b;
	value->v = M_BOOL;
	return true;
}

};
#endif
