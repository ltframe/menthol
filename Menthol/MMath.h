#pragma once
#ifndef MMATH
#define MMATH
#include "Vm.h"
#include "MGc.h"

namespace MMath
{


StackState ConvertToNumber(STACKSTATEPOINTER value)
{
	StackState ret;
	if(IsBool(value)){
		ret.v = M_NUMBER;
		ret.d = value->b?1:0;
		return ret;
	}

	if(IsNULL(value)){
		ret.v = M_NUMBER;
		ret.d = 0;
		return ret;
	}
	if(IsNumber(value)){
		ret = *value;
		return ret;
	}
	ret.v = M_UNKONWN;
	return ret;
}
inline bool Add(STACKSTATEPOINTER value1,STACKSTATEPOINTER value2,VmState * vmstate)
{
	StackState ctn1 = ConvertToNumber(value1);
	StackState ctn2 = ConvertToNumber(value2);
	if(ctn1.v!=M_UNKONWN && ctn2.v!=M_UNKONWN){	
		value1->v = M_NUMBER;
		value1->d=(ctn1.d+=ctn2.d);
		return true;
	}else if(IsBool(value1) && IsString(value2)){

		int c = strlen(value2->str->string)+10;
		char *dest = new char[c];
		sprintf(dest,"%s%s",value1->b?"true":"false",value2->str->string);
		value1->str= Vm::CreateString(dest,vmstate);	
		value1->v = M_STRING;
		delete [] dest;
		return true;
	}
	else if(IsString(value1) && IsBool(value2)){
		////MGc::SetGarBageRef(value1->str,-1);
		int c = strlen(value1->str->string)+10;
		char *dest = new char[c];
		sprintf(dest,"%s%s",value1->str->string,value2->b?"true":"false");		
		value1->str= Vm::CreateString(dest,vmstate);
		value1->v = M_STRING;
		delete [] dest;
		return true;
	}
	else if(IsNumber(value1) && IsString(value2)){
		char str[256]={0};
		if(value1->d != (int)value1->d){
			sprintf(str, "%.6lf", value1->d);;
		}else
		{
			sprintf(str, "%d", (int)value1->d);;
		}	
		int c = strlen(value2->str->string)+256;
		char *dest = new char[c];
		sprintf(dest,"%s%s",str,value2->str->string);
		value1->str= Vm::CreateString(dest,vmstate);	
		value1->v = M_STRING;
		delete [] dest;
		return true;
	}
	else if(IsString(value1) && IsNumber(value2)){
		////MGc::SetGarBageRef(value1->str,-1);
		value1->v = M_STRING;
		char str[256]={0};
		if(value2->d != (int)value2->d){
			sprintf(str, "%.6lf", value2->d);;
		}else
		{
			sprintf(str, "%d", (int)value2->d);;
		}		
		int c = strlen(value1->str->string)+256;
		char *dest = new char[c];
		sprintf(dest,"%s%s",value1->str->string,str);		
		value1->str= Vm::CreateString(dest,vmstate);
		delete [] dest;
		return true;
	}
	else if(IsString(value1) && IsString(value2)){
		////MGc::SetGarBageRef(value1->str,-1);
		////MGc::SetGarBageRef(value2->str,-1);
		int c = strlen(value1->str->string)+strlen(value2->str->string)+1;
		char *dest = new char[c];
		memset(dest,0,c);
		sprintf(dest,"%s%s",value1->str->string,value2->str->string);		
		value1->str= Vm::CreateString(dest,vmstate);
		value1->v = M_STRING;
		delete [] dest;
		return true;
	}
	else if(IsArray(value1))
	{
		VECOTRSTACKSTATEPOINTER _ss = (VECOTRSTACKSTATEPOINTER)(value1->parray->array);
		_ss->push_back(*value2);
		return true;
	}
	else if(IsArray(value2))
	{
		//MGc::SetGarBageRef(value2->parray,-1);
		VECOTRSTACKSTATEPOINTER _ss = (VECOTRSTACKSTATEPOINTER)(value2->parray->array);
		_ss->push_back(*value1);
		*value1 = *value2;
		return true;
	}
	else if(IsNULL(value1) && IsString(value2))
	{
		int c = strlen(value2->str->string)+1;
		char *dest = new char[c];
		memset(dest,0,c);
		sprintf(dest,"%s",value2->str->string);		
		value1->str= Vm::CreateString(dest,vmstate);
		value1->v = M_STRING;
		delete [] dest;
		return true;
	}
	else if(IsString(value1) && IsNULL(value2))
	{
		int c = strlen(value1->str->string)+1;
		char *dest = new char[c];
		memset(dest,0,c);
		sprintf(dest,"%s",value1->str->string);		
		value1->str= Vm::CreateString(dest,vmstate);
		value1->v = M_STRING;
		delete [] dest;
		return true;
	}
	MError::CreateInstance()->DataTypeOpertatError(value1,value2,"Can't add",vmstate);
	return false;

	
}
inline bool Power(STACKSTATEPOINTER value1,STACKSTATEPOINTER value2,VmState * vmstate)
{
	StackState ctn1 = ConvertToNumber(value1);
	StackState ctn2 = ConvertToNumber(value2);
	if(ctn1.v!=M_UNKONWN && ctn2.v!=M_UNKONWN){			
		value1->v = M_NUMBER;
		value1->d=pow(ctn1.d,ctn2.d);
		return true;
	}
	MError::CreateInstance()->DataTypeOpertatError(value1,value2," Can't exponent",vmstate);
	return false;
}
inline bool Sub(STACKSTATEPOINTER value1,STACKSTATEPOINTER value2,VmState * vmstate)
{
	StackState ctn1 = ConvertToNumber(value1);
	StackState ctn2 = ConvertToNumber(value2);
	if(ctn1.v!=M_UNKONWN && ctn2.v!=M_UNKONWN){			
		value1->v = M_NUMBER;
		value1->d=(ctn1.d-=ctn2.d);
		return true;
	}
	MError::CreateInstance()->DataTypeOpertatError(value1,value2," Can't subtraction",vmstate);
	return false;
	
}
inline bool Mul(STACKSTATEPOINTER value1,STACKSTATEPOINTER value2,VmState * vmstate)
{
	StackState ctn1 = ConvertToNumber(value1);
	StackState ctn2 = ConvertToNumber(value2);
	if(ctn1.v!=M_UNKONWN && ctn2.v!=M_UNKONWN){			
			value1->v = M_NUMBER;
			value1->d=(ctn1.d*=ctn2.d);
			return true;
	}
	MError::CreateInstance()->DataTypeOpertatError(value1,value2," Can't multiply",vmstate);
	return false;
}

inline bool Div(STACKSTATEPOINTER value1,STACKSTATEPOINTER value2,VmState * vmstate)
{
	if(value2->d==0)
	{
		MError::CreateInstance()->PrintRunTimeError("Divisor must not be zero!",vmstate);
		return false;
	}
	StackState ctn1 = ConvertToNumber(value1);
	StackState ctn2 = ConvertToNumber(value2);
	if(ctn1.v!=M_UNKONWN && ctn2.v!=M_UNKONWN){			
			value1->v = M_NUMBER;
			value1->d=(ctn1.d/=ctn2.d);
			return true;
	}
	MError::CreateInstance()->DataTypeOpertatError(value1,value2," Can't  Division",vmstate);
	return false;
}


inline bool Mod(STACKSTATEPOINTER value1,STACKSTATEPOINTER value2,VmState * vmstate)
{
	if(value2->d==0)
	{
		MError::CreateInstance()->PrintRunTimeError("do not divide by zero !",vmstate);
		return false;
	}
	StackState ctn1 = ConvertToNumber(value1);
	StackState ctn2 = ConvertToNumber(value2);
	if(ctn1.v!=M_UNKONWN && ctn2.v!=M_UNKONWN){	
			int a = ctn1.d;
			int b = ctn2.d;
			int c = a%b;
			value1->v = M_NUMBER;
			value1->d=c;
			return true;
	}
	MError::CreateInstance()->DataTypeOpertatError(value1,value2," Can't Modulo",vmstate);
	return false;
}
};
#endif
