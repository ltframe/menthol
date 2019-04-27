// MSystem.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "Menthol.h"
#include <string>
#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <fstream>
#include  <direct.h>  
#include <list>
#include <stdarg.h>
#include <sstream>
#include <time.h>
#include <functional>
#include <windows.h>
#include <Objbase.h>
#include <process.h>
#include "Environment.h"
#include "Number.h"
#include "String.h"
#include "Math.h"
#include "DateTime.h"
#include "Array.h"
#include "Dict.h"
#include "Regex.h"
#include "Json.h"
using namespace std;


UserFunctionAtter Numberlist[] = {
	{"ToString",Number::ToString,1},
	{"ToNumber",Number::ToNumber,1},
	{NULL,NULL,0}
}; 


UserFunctionAtter Environmentlist[] = {
	{"Version",Environment::Version,0},
	{"Sleep",Environment::Sleep,1},
	{"SystemInfo",Environment::SystemInfo,0},
	{"CpuInfo",Environment::CpuInfo,0},
	{"SystemMemory",Environment::SystemMemory,0},
	{"OsInfo",Environment::OsInfo,0},
	{"Getpid",Environment::Getpid,0},
	{"Exit",Environment::Exit,1},
	{"System",Environment::System,1},
	{"MachineName",Environment::MachineName,0},
	{"UserName",Environment::UserName,0},
	{"TickCount",Environment::TickCount,0},
	{"NewGuid",Environment::NewGuid,0},
	{NULL,NULL,0}
}; 

UserFunctionAtter Stringlist[] = {
		{"StoN",String::StoN,1},	
		{"Length",String::Length,1},	
		{"IndexOf",String::IndexOf,2},
		{"Replace",String::Replace,3},
		{"Toupper",String::Toupper,1},
		{"Tolower",String::Tolower,1},
		{"Isdigit", String::Isdigit, 1},
		{"Isalpha", String::Isalpha, 1},
		{"Toascii", String::Toascii, 1},
		{"UTF8ToGBK", String::UTF8ToGBK, 1},
		{"GBKToUTF8", String::GBKToUTF8, 1},
		{NULL,NULL,0}
}; 


UserFunctionAtter Mathlist[] = {
		{"Abs",Math::Abs,1},	
		{"Acos",Math::Acos,1},	
		{"Asin",Math::Asin,1},	
		{"Atan",Math::Atan,1},	
		{"Atan2",Math::Atan2,2},
		{"Ceil",Math::Ceil,1},	
		{"Cos",Math::Cos,1},
		{"Cosh",Math::Cosh,1},
		{"Exp",Math::Exp,1},
		{"Fabs",Math::Fabs,1},
		{"Floor",Math::Floor,1},
		{"Fmod",Math::Fmod,2},
		{"Log",Math::Log,1},
		{"Log10",Math::Log10,1},
		{"Pow",Math::Pow,2},
		{"Sin",Math::Sin,1},
		{"Sinh",Math::Sinh,1},
		{"Sqrt",Math::Sqrt,1},
		{"Tan",Math::Tan,1},
		{"Tanh",Math::Tanh,1},
		{"Random",Math::Random,0},
		{"Cbrt",Math::Cbrt, 1},
		{NULL,NULL,0}
}; 

UserFunctionAtter DateTimelist[] = {
	{"CurrentDate",DateTime::CurrentDate,0},	
	{"CurrentTime",DateTime::CurrentTime,0},	
	{"TimeZone",DateTime::TimeZone,0},
	{NULL,NULL,0}
};

UserFunctionAtter Arraylist[] = {
	{"Length",Array::Length,1},	
	{"Join",Array::Join,2},	
	{"Reverse",Array::Reverse,1},	
	{"Push",Array::Push,2},
	{NULL,NULL,0}
};

UserFunctionAtter Dictlist[] = {
	{"Length",Dict::Length,1},	
	{"Push",Dict::Push,3},	
	{"SetValue",Dict::SetValue,3},	
	{"GetKey",Dict::GetKey,2},	
	{"GetValue",Dict::GetValue,2},
	{NULL,NULL,0}
};

UserFunctionAtter RegexList[]= {
	{ "Exec", Regex::Exec,3 },
	{ "Test", Regex::Test,3 },
	{ "Replace", Regex::Replace,4 },
	{NULL,NULL,0}
};


UserFunctionAtter JsonList[] = {
	{ "JsonParse", Json::JsonParse, 1 },
	{ "GetObjectItem", Json::GetObjectItem, 2 },
	{ "GetArrayItem", Json::GetArrayItem, 2 },
	{ "GetArraySize", Json::GetArraySize, 1 },
	{ "Delete", Json::Delete, 1 },
	{ "Type", Json::Type, 1 },
	{NULL,NULL,0}
};

MentholModuleMethod void MP_Init(VmState* vmstate)
{
	RunTimeState* Numberprt = CreateModuleRunTime("CNumber",vmstate);
	RegisterModuleFunciton(Numberprt,Numberlist);

	RunTimeState* Environmentprt = CreateModuleRunTime("CEnvironment",vmstate);
	RegisterModuleFunciton(Environmentprt,Environmentlist);

	RunTimeState* Stringprt = CreateModuleRunTime("CString",vmstate);
	RegisterModuleFunciton(Stringprt,Stringlist);

	RunTimeState* Mathprt = CreateModuleRunTime("CMath",vmstate);
	RegisterModuleFunciton(Mathprt,Mathlist);

	RunTimeState* DateTimeprt = CreateModuleRunTime("CDateTime",vmstate);
	RegisterModuleFunciton(DateTimeprt,DateTimelist);

	RunTimeState* Arrayprt = CreateModuleRunTime("CArray",vmstate);
	RegisterModuleFunciton(Arrayprt,Arraylist);

	RunTimeState* Dictprt = CreateModuleRunTime("CDict",vmstate);
	RegisterModuleFunciton(Dictprt,Dictlist);

	RunTimeState* Regexprt = CreateModuleRunTime("CRegex",vmstate);
	RegisterModuleFunciton(Regexprt, RegexList);

	RunTimeState* Jsonprt = CreateModuleRunTime("CJson",vmstate);
	RegisterModuleFunciton(Jsonprt, JsonList);
}