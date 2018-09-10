#ifndef MENTHOL
#define MENTHOL

#include "stdafx.h"
#include <string>
#include <iostream>
#include <vector>
#include <stack>
#include <fstream>
#include  <direct.h>  
#include <list>
#include <stdarg.h>
#include <sstream>
#include <time.h>
#include <functional>
#include <map>
using namespace std;

#define  MentholPackMethod  extern "C"  __declspec(dllexport)


enum ValueType{
	M_NUMBER,
	M_LONG,
	M_DOUBLE,
	M_STRING,
	M_SSTRING,//system string,and it's not remove forever
	M_FUN,
	M_PFUN,
	M_BPMARK,
	M_BOOL,
	M_ARRAY,
	M_DICT,
	M_NULL,
	M_TRYMARK,
	M_FORMARK,
	M_PACKAGE,
	M_HASH,
	M_UNKONWN,
	M_POINTER
};

struct StackState;
struct StackMark;
struct RunTimeState;
typedef unsigned int hashValue,Instruction;
struct Garbage{
	Garbage(vector<StackState> * _c){
		array = _c;
		v = M_ARRAY;
		mark = 0;
	}
	Garbage(map<hashValue,StackState>* _c){
		dict = _c;
		v = M_DICT;
		mark = 0;
	}
	Garbage(char * _c,ValueType _v){
		string = _c;
		v = _v;
		mark = 0;
	}
	union {
		vector<StackState> *array;
		map<hashValue,StackState>* dict;	
		char * string;
	};
	ValueType v;
	int mark;
};

typedef Garbage* pArray,*pDict,*pString;

typedef void* pInst;

typedef struct StackMark
{
	StackState* bp;
	Instruction* address;
	unsigned int paramercount;//参数的个数
	RunTimeState* rts;

}TryMark;

struct StackState
{

	union{
		double d;
		int i;
		hashValue hash;//存hash值
		pDict pdict;
		pArray parray;
		pString str;
		StackMark m;
		bool b;
	};
	pInst p;
	char* name;
	hashValue namehash;//name 的hash值
	ValueType v;
};

typedef StackState (*funcallback)();

//global:
MentholPackMethod int Compile(char** files,int c);
MentholPackMethod int Compile2(char* cfile);
MentholPackMethod int Run(char* files,char* arg1,char* arg2);
MentholPackMethod void RegisterPackAgeFunciton(char* name,funcallback fun,int pcount);
MentholPackMethod StackState GetParam(int index);
 
 //array
MentholPackMethod StackState Array_CreateArray();
MentholPackMethod StackState Array_Get(pArray sk1,int index);
MentholPackMethod void Array_Set(pArray sk1,StackState sk2,int index);
MentholPackMethod int Array_Length(pArray p);
MentholPackMethod void Array_Push(pArray sk1,StackState sk2);
MentholPackMethod pString Array_Join(pArray a1,char* link);
MentholPackMethod pArray Array_Reverse(pArray a1);
 //dict
MentholPackMethod StackState Dict_CreateDict();
MentholPackMethod void Dict_Push(char* key,pDict sk1,StackState sk2);
MentholPackMethod int Dict_Length(pDict);
MentholPackMethod StackState Dict_Get(pDict sk1,hashValue key);
MentholPackMethod void Dict_Set(char* key,pDict sk1,StackState sk2);
MentholPackMethod pString Dict_Key(pDict pdict,hashValue sk2);
 //string
MentholPackMethod StackState String_CreateString(char* str);


//function
MentholPackMethod void CreateFunctionCall(int pc);
MentholPackMethod void PushNumber(double d);
MentholPackMethod void PushString(pString str);
MentholPackMethod void PushArray(pArray arr);
MentholPackMethod void PushDict(pDict arr);
MentholPackMethod StackState CallFunction(StackState fu);

#endif