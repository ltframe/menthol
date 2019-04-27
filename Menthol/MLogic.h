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

inline bool EqEq(STACKSTATEPOINTER value1,STACKSTATEPOINTER value2,VmState* vmstate)
{

	if(value1->v!=value2->v)
	{
		value1->v = M_BOOL;
		value1->b = false;
		return true;
	}

	if(IsString(value1) && IsString(value2))
	{
		value1->v = M_BOOL;
		value1->b=(strcmp(value1->str->string,value2->str->string)==0?true:false);
		return true;
	}
	if(IsArray(value1) && IsArray(value2))
	{
		value1->v = M_BOOL;
		value1->b=value1->parray==value2->parray;
		return true;
	}
	if(IsDict(value1) && IsDict(value2))
	{
		value1->v = M_BOOL;
		value1->b=value1->pdict==value2->pdict;
		return true;
	}


	if (IsModule(value1) && IsModule(value2))
	{
		value1->v = M_BOOL;
		value1->b=value1->ms==value2->ms;
		return true;
	}
	
	if(IsObject(value1) && IsObject(value2))
	{
		value1->v = M_BOOL;
		value1->b=value1->p==value2->p;
		return true;
	}


	if(IsFUN(value1) && IsFUN(value2))
	{
		value1->v = M_BOOL;
		value1->b=((value1->p==value2->p) && (value1->i==value2->i));
		return true;
	}

	if(IsPFUN(value1) && IsPFUN(value2))
	{
		value1->v = M_BOOL;
		value1->b=((value1->p==value2->p) && (value1->hash==value2->hash));
		return true;
	} 

	StackState ctn1 = MMath::ConvertToNumber(value1);
	StackState ctn2 = MMath::ConvertToNumber(value2);
	if (ctn1.v != M_UNKONWN && ctn2.v != M_UNKONWN){
		value1->v = M_BOOL;
		value1->b = (ctn1.d==ctn2.d);
		return true;
	}
	if(ctn1.v!=ctn2.v)
	{
		value1->v = M_BOOL;
		value1->b = false;
		return true;
	}

	MError::CreateInstance()->DataTypeOpertatError(value1, value2, " Can't compare",vmstate);
	return false;
	
}

//С��
inline bool Lt(STACKSTATEPOINTER value1,STACKSTATEPOINTER value2,VmState* vmstate)
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
	MError::CreateInstance()->DataTypeOpertatError(value1,value2," Can't compare",vmstate);
	return false;
}

inline bool Le(STACKSTATEPOINTER value1,STACKSTATEPOINTER value2,VmState* vmstate)
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
	MError::CreateInstance()->DataTypeOpertatError(value1,value2," Can't compare",vmstate);
	return false;
}

inline bool Geeq(STACKSTATEPOINTER value1,STACKSTATEPOINTER value2,VmState* vmstate)
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
	MError::CreateInstance()->DataTypeOpertatError(value1,value2," Can't compare",vmstate);
	return false;
}

inline bool Leeq(STACKSTATEPOINTER value1,STACKSTATEPOINTER value2,VmState* vmstate)
{
	if(IsString(value1) && IsString(value2))
	{
		value1->v = M_BOOL;
		int k=strcmp(value1->str->string,value2->str->string);
		value1->b=(k<=0)?true:false;
		return true;
	}
	StackState ctn1 = MMath::ConvertToNumber(value1);
	StackState ctn2 = MMath::ConvertToNumber(value2);
	if(ctn1.v!=M_UNKONWN && ctn2.v!=M_UNKONWN){	
			value1->v = M_BOOL;
			value1->b=(ctn1.d<=ctn2.d);
			return true;
	}

	MError::CreateInstance()->DataTypeOpertatError(value1,value2," Can't compare",vmstate);
	return false;
}
inline bool Neq(STACKSTATEPOINTER value1,STACKSTATEPOINTER value2,VmState* vmstate)
{	


	if(value1->v!=value2->v)
	{
		value1->v = M_BOOL;
		value1->b = true;
		return true;
	}

	if(IsString(value1) && IsString(value2))
	{
		int k=strcmp(value1->str->string,value2->str->string);
		value1->v = M_BOOL;
		value1->b=(k!=0)?true:false;
		return true;
	}
	if(IsArray(value1) && IsArray(value2))
	{
		value1->v = M_BOOL;
		value1->b=value1->parray!=value2->parray;
		return true;
	}
	if(IsDict(value1) && IsDict(value2))
	{
		value1->v = M_BOOL;
		value1->b=value1->pdict!=value2->pdict;
		return true;
	}
	if (IsModule(value1) && IsModule(value2))
	{
		value1->v = M_BOOL;
		value1->b=value1->ms!=value2->ms;
		return true;
	}

	if(IsObject(value1) && IsObject(value2))
	{
		value1->v = M_BOOL;
		value1->b=value1->p!=value2->p;
		return true;
	}


	if(IsFUN(value1) && IsFUN(value2))
	{
		value1->v = M_BOOL;
		value1->b=((value1->p!=value2->p) || (value1->i!=value2->i));
		return true;
	}

	if(IsPFUN(value1) && IsPFUN(value2))
	{
		value1->v = M_BOOL;
		value1->b=((value1->p!=value2->p) || (value1->hash!=value2->hash));
		return true;
	} 

	StackState ctn1 = MMath::ConvertToNumber(value1);
	StackState ctn2 = MMath::ConvertToNumber(value2);
	if(ctn1.v!=M_UNKONWN && ctn2.v!=M_UNKONWN){	
			value1->v = M_BOOL;
			value1->b=(ctn1.d!=ctn2.d);
			return true;
	}

	if(ctn1.v!=ctn2.v)
	{
		value1->v = M_BOOL;
		value1->b = true;
		return true;
	}

	MError::CreateInstance()->DataTypeOpertatError(value1,value2," Can't compare",vmstate);
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
