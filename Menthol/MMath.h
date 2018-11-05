#pragma once
#ifndef MMATH
#define MMATH
#include "Vm.h"
#include "MGc.h"

namespace MMath
{
	inline bool Add(STACKSTATEPOINTER value1,STACKSTATEPOINTER value2)
{

	if(IsNumber(value1) && IsNumber(value2)){
		value1->v = M_NUMBER;
		value1->d+=value2->d;
		return true;
	}


	if(IsBool(value1) && IsBool(value2)){
		value1->v = M_NUMBER;
		value1->d+=value2->d;
		return true;
	}

	 if(IsNumber(value1) &&  IsBool(value2)){
		value1->v = M_NUMBER;
		value1->d+=value2->d;
		return true;
	}

	if((IsNumber(value1) || IsBool(value1)) && (IsNumber(value2) || IsBool(value2))){
		value1->v = M_NUMBER;
		value1->d+=value2->d;
		return true;
	}
	else if(IsBool(value1) && IsString(value2)){

		int c = strlen(value2->str->string)+10;
		char *dest = new char[c];
		sprintf(dest,"%s%s",value1->b?"true":"false",value2->str->string);
		value1->str= Vm::CreateString(dest);	
		value1->v = M_STRING;
		delete [] dest;
		return true;
	}
	else if(IsString(value1) && IsBool(value2)){
		////MGc::SetGarBageRef(value1->str,-1);
		int c = strlen(value1->str->string)+10;
		char *dest = new char[c];
		sprintf(dest,"%s%s",value1->str->string,value2->b?"true":"false");		
		value1->str= Vm::CreateString(dest);
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
		value1->str= Vm::CreateString(dest);	
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
		value1->str= Vm::CreateString(dest);
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
		value1->str= Vm::CreateString(dest);
		value1->v = M_STRING;
		delete [] dest;
		return true;
	}
	else if(IsArray(value1) && (IsNumber(value2) || IsBool(value2)))
	{
		VECOTRSTACKSTATEPOINTER _ss = (VECOTRSTACKSTATEPOINTER)(value1->parray);
		_ss->push_back(*value2);
		return true;
	}
	if((IsNumber(value1) || IsBool(value1)) && IsArray(value2))
	{
		//MGc::SetGarBageRef(value2->parray,-1);
		VECOTRSTACKSTATEPOINTER _ss = (VECOTRSTACKSTATEPOINTER)(value2->parray);
		_ss->push_back(*value1);
		*value1 = *value2;
		return true;
	}
	else if(IsArray(value1) && IsDict(value2))
	{
		//MGc::SetGarBageRef(value2->pdict,-1);
		VECOTRSTACKSTATEPOINTER _ss = (VECOTRSTACKSTATEPOINTER)(value1->parray);
		_ss->push_back(*value2);
		return true;
	}
	else if(IsDict(value1) && IsArray(value2))
	{
		//MGc::SetGarBageRef(value1->pdict,-1);
		VECOTRSTACKSTATEPOINTER _ss = (VECOTRSTACKSTATEPOINTER)(value2->parray);
		_ss->push_back(*value2);
		*value1=*value2;
		return true;
	}	
	else if(IsNULL(value1) && IsString(value2))
	{
		int c = strlen(value2->str->string)+1;
		char *dest = new char[c];
		memset(dest,0,c);
		sprintf(dest,"%s",value2->str->string);		
		value1->str= Vm::CreateString(dest);
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
		value1->str= Vm::CreateString(dest);
		value1->v = M_STRING;
		delete [] dest;
		return true;
	}
	else if(IsNumber(value1) && IsNULL(value2))
	{
		return true;
	}
	else if(IsNULL(value1) && IsNumber(value2))
	{
		value1->v = M_NUMBER;
		value1->d = value2->d;
		return true;
	}

	MError::CreateInstance()->DataTypeOpertatError(value1,value2,"Can't add");
	return false;

	
}
inline bool Power(STACKSTATEPOINTER value1,STACKSTATEPOINTER value2)
{
	if((IsNumber(value1) || IsBool(value1)) && (IsNumber(value2) || IsBool(value2))){
		value1->v = M_NUMBER;
		value1->d=pow(value1->d,value2->d);
		return true;
	}
	MError::CreateInstance()->DataTypeOpertatError(value1,value2," Can't exponent");
	return false;
}
inline bool Sub(STACKSTATEPOINTER value1,STACKSTATEPOINTER value2)
{
	if((IsNumber(value1) || IsBool(value1)) && (IsNumber(value2) || IsBool(value2))){
			value1->v = M_NUMBER;
			value1->d-=value2->d;
			return true;
	}
	MError::CreateInstance()->DataTypeOpertatError(value1,value2," Can't subtraction");
	return false;
	
}
inline bool Mul(STACKSTATEPOINTER value1,STACKSTATEPOINTER value2)
{
	if((IsNumber(value1) || IsBool(value1)) && (IsNumber(value2) || IsBool(value2))){
			value1->v = M_NUMBER;
			value1->d*=value2->d;
			return true;
	}
	MError::CreateInstance()->DataTypeOpertatError(value1,value2," Can't multiply");
	return false;
}

inline bool Div(STACKSTATEPOINTER value1,STACKSTATEPOINTER value2)
{
	if(value2->d==0)
	{
		MError::CreateInstance()->PrintRunTimeError("Divisor must not be zero!");
		return false;
	}
	if((IsNumber(value1) || IsBool(value1)) && (IsNumber(value2) || IsBool(value2))){
			value1->v = M_NUMBER;
			value1->d*=value2->d;
			return true;
	}
	MError::CreateInstance()->DataTypeOpertatError(value1,value2," Can't  Division");
	return false;
}


inline bool Mod(STACKSTATEPOINTER value1,STACKSTATEPOINTER value2)
{
	if(value2->d==0)
	{
		MError::CreateInstance()->PrintRunTimeError("do not divide by zero !");
		return false;
	}
	if((IsNumber(value1) || IsBool(value1)) && (IsNumber(value2) || IsBool(value2))){
			value1->v = M_NUMBER;
			value1->d=(int)(value1->d)%(int)(value2->d);
			return true;
	}
	MError::CreateInstance()->DataTypeOpertatError(value1,value2," Can't Modulo");
	return false;
}
};
#endif
