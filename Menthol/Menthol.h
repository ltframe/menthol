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

#define  MentholModuleMethod  extern "C"  __declspec(dllexport)


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
	M_MODULE,
	M_HASH,
	M_UNKONWN,
	M_OBJECT
};

struct StackState;
struct StackMark;
struct ModuleState;
struct RunTimeState;
typedef unsigned int hashValue,Instruction,M_UInt;
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
struct StackState;
#define STACKSTATEPOINTER StackState*

typedef struct StackMark
{
	StackState* bp;
	Instruction* address;
	M_UInt paramercount;//参数的个数
	RunTimeState* rts;
	int calltype;

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
		ModuleState* ms;
	};
	pInst p;
	char* name;
	hashValue namehash;//name 的hash值
	ValueType v;
};


struct GcState
{
	long garbagememorysize;
	vector<Garbage*> *garbagecollect;
};
#define VECOTRSTACKSTATE  vector<StackState>
static struct VmState
{
	Instruction* codelist;
	RunTimeState* currentruntimestate;
	STACKSTATEPOINTER sp;
	STACKSTATEPOINTER bp;
	STACKSTATEPOINTER stackbase;
	VECOTRSTACKSTATE stacklist;
	int garbagescount;
	GcState* gc;
};


typedef StackState (*funcallback)(VmState*);
struct UserFunctionAtter
{
	char* name;
	funcallback postion; 
	int paramcount;
};
typedef int (*PrintErrorFunc)(char* str,char* cf,int line);
//global:
MentholModuleMethod void SetPrintCompileErrorFunc(PrintErrorFunc _pef);
MentholModuleMethod void SetPrintRunTimeErrorFunc(PrintErrorFunc _pef);
MentholModuleMethod int Compile(char* cfile);
MentholModuleMethod int Run(char* files,char* arg1,char* arg2);
MentholModuleMethod void RegisterModuleFunciton(RunTimeState* moduleinst,UserFunctionAtter* functionlist);			  
MentholModuleMethod StackState GetParam(int index,VmState*);
MentholModuleMethod RunTimeState* CreateModuleRunTime(char* modulename,VmState*);

 //array
MentholModuleMethod StackState Array_CreateArray(VmState*);
MentholModuleMethod StackState Array_Get(pArray sk1,int index);
MentholModuleMethod void Array_Set(pArray sk1,StackState sk2,int index);
MentholModuleMethod int Array_Length(pArray p);
MentholModuleMethod void Array_Push(pArray sk1,StackState sk2);
MentholModuleMethod pString Array_Join(pArray a1,char* link,VmState*);
MentholModuleMethod pArray Array_Reverse(pArray a1);
 //dict
MentholModuleMethod StackState Dict_CreateDict(VmState*);
MentholModuleMethod void Dict_Push(char* key,pDict sk1,StackState sk2);
MentholModuleMethod int Dict_Length(pDict);
MentholModuleMethod StackState Dict_Get(pDict sk1,hashValue key);
MentholModuleMethod void Dict_Set(char* key,pDict sk1,StackState sk2);
MentholModuleMethod pString Dict_Key(pDict pdict,hashValue sk2,VmState*);
 //string
MentholModuleMethod StackState String_CreateString(char* str,VmState*);


//function
MentholModuleMethod void CreateFunctionCall(int pc,VmState*);
MentholModuleMethod void PushNumber(double d,VmState*);
MentholModuleMethod void PushString(pString str,VmState*);
MentholModuleMethod void PushArray(pArray arr,VmState*);
MentholModuleMethod void PushDict(pDict arr,VmState*);
MentholModuleMethod void PushBool(bool arr,VmState*);
MentholModuleMethod void PushObject(pInst arr,VmState*);
MentholModuleMethod StackState CallFunction(StackState fu,VmState*);

//number
MentholModuleMethod StackState Number_CreateNumber(double d);

//null
MentholModuleMethod StackState Null_CreateNull();

//bool
MentholModuleMethod StackState Bool_CreateBool(bool b);


MentholModuleMethod StackState Object_CreateObject(pInst p);

MentholModuleMethod  VmState* NewVmState();
MentholModuleMethod  void NewVm(VmState* vmstate);
MentholModuleMethod  void ClearVmState(VmState* vmstate);
#endif

