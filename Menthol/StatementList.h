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

//文件头使用
#define MENTHOLPACKAGEDLLEXTENSION2 "MED"
#define MENTHOLEXECUTEEXTENSION2 "MEE"

#define MAINMODULENAME "53A25398-E89C-439d-9F93-011EA71D6872"
#define MAINMODULENAMEHASH 4022255038



typedef void (*initfuncallback)();

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




struct ModuleAndConstant
{	
	string modulename;
	hashValue hash;
	vector<double> *doublelist;
	vector<string> *stringlist;
	vector<string> *functionlist;	
	vector<MentholDebug> *debuglist;
	vector<GlobalVarAttr>* globalmemory;
};




#define ipiadd ipi = ipi+1;



class StatementList 
{
public:
	StatementList();
	~StatementList(void);
	void SetCompileStructTable(Statement* b);
	void AddCode(Instruction x,int lineno=0);
	void SetCode(Instruction x,int ipp);  
	void AddCharCode(char x);
	int GetIpi();
	bool AddGlobalMemory(string _name);
	GlobalVarAttr FindGlobalMemory(string str);
	void AddStringConstant(string str);
	void AddDictKeyConstant(string s);
	void AddDoubleConstant(double d);
	static StatementList* GetInstance();
	bool AddLocalMemory(string _name,int _lineno);
	LocalVarAttr FindLocalMemory(string _name);
	void ClearLocalMemory();
	void CreateCode(vector<Statement*>* _CompileStructTable,string extension);
	bool IsGlobalVar(string name);
	LocalVarAttr FindLastLocalMemory();
	int IsHasModuleName(string name);
	void AddModuleList(string name);
	//void ResetInitPackageList();
	int FindDoubleConstant(double s);
	int FindStringConstant(string d);
	int FindDictKeyConstant(string d);
	int FindFunction(string s);
	void AddFunction(string s);
	int GetLocalCountValue();
	void SetLocalCountValue(int x);
	vector<GlobalVarAttr>* GetGlobalMemory();
	vector<LocalVarAttr>* GetLocalMemory();
	void AddExternalModuleList(string modulename);
	void RestDebugIpi();
	void AddToIncludeFile(string modulename);
	void AddMainModuleList(Statement* fd);
	void AddUseModuleList(string modulename);
	bool FindUseModuleList(string modulename);
public:
	vector<Instruction> *CodeList;
	vector <Statement*> *CompileStructTable;
	int StackID;
	vector<ImportFileAttr> *includefiles;	

private:
	int ipi;
	int debugipi;
	static StatementList* _StatementList;
	int localcount;
	vector<string> *dictkeyconstants;
	vector<double> *doublelist;
	vector<string> *stringlist;
	vector<string> *functionlist;	
	ModuleAndConstant currentmodule;
	vector<ModuleAndConstant> *ModuleList;
	vector<ModuleAndConstant> *UseModuleList;
	vector<ModuleAndConstant> *ImportFileAllModuleList;
	vector<GlobalVarAttr>* GlobalMemory;
	vector<LocalVarAttr>* LocalMemory;
	ModuleAndConstant FindModuleByName(string);
private:
	bool IsAddedImportFileAllPackAgeList(string packagename);
};
#endif