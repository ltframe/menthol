#pragma once
#ifndef STATEMENTLIST
#define STATEMENTLIST
#include "header.h"
#include "Parser.h"
#include "MError.h"
#include "MCommon.h"


#pragma comment(lib, "libfl.a")
#pragma comment(lib, "liby.a")

#define MENTHOLPACKAGEEXTENSION ".mep"
#define MENTHOLPACKAGEDLLEXTENSION ".med"

#define MENTHOLEXTENSION ".me"
#define MENTHOLEXECUTEEXTENSION ".mee"

struct LocalVarAttr
{
   string name;
   int index;
};
struct GlobalVarAttr
{
   string name;
   hashValue hash;
};

#define ipiadd ipi = ipi+1;



class StatementList 
{
public:
	StatementList();
	void SetCompileStructTable(Statement* b);
	void AddCode(Instruction x);
	void SetCode(Instruction x,int ipp);  
	void AddCharCode(char x);
	int GetIpi();
	bool AddGlobalMemory(string _name);
	GlobalVarAttr FindGlobalMemory(string str);
	void AddStringConstant(string str);
	void AddDictKeyConstant(string s);
	void AddDoubleConstant(double d);
	static StatementList* GetInstance();
	bool AddLocalMemory(string _name);
	LocalVarAttr FindLocalMemory(string _name);
	void ClearLocalMemory();
	void CreateCode(vector<Statement*>* _CompileStructTable);
	int  FindInCompileStructTable(string b);
	bool IsGlobalVar(string name);
	LocalVarAttr FindLastLocalMemory();
	void ResetIpi();
	int IsHasPackAgeName(string name);
	void AddPackAgeList(string name);
	void ResetInitPackageList();
	int FindDoubleConstant(double s);
	int FindStringConstant(string d);
	int FindDictKeyConstant(string d);
	int FindFunction(string s);
	void AddFunction(string s);
	int GetLocalCountValue();
	void SetLocalCountValue(int x);
	vector <double>* GetDoubleConstants();
	vector<string>* GetImprotFiles();
	vector<PackageAttr>* GetPackAgeList();
	vector<string>* GetFunctionList();	
	vector <string>* GetStringConstants();
	vector <string>* GetDictKeyConstants();
	vector<GlobalVarAttr>* GetGlobalMemory();
	vector<LocalVarAttr>* GetLocalMemory();
public:
	vector<Instruction> *CodeList;
	vector <Statement*> *CompileStructTable;
	int StackID;
	string currentpackagename;
private:
	int ipi;
	static StatementList* _StatementList;
	int localcount;
	vector <double> *doubleconstants;
	vector<string> *ImprotFiles;
	vector<PackageAttr> *PackAgeList;
	vector<string> *functionlist;	
	vector <string> *stringconstants;
	vector <string> *dictkeyconstants;	
	vector<GlobalVarAttr>* GlobalMemory;
	vector<LocalVarAttr>* LocalMemory;
};
#endif