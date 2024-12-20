#pragma once
#ifndef STATEMENTLIST
#define STATEMENTLIST
#include "header.h"
#include "Parser.h"
#include "MError.h"
#include "MCommon.h"



//包的源扩展名
#define MENTHOLPACKAGEEXTENSION ".mep"
//包编译后的扩展名
#define MENTHOLPACKAGEDLLEXTENSION ".med"

//可执行文件的源扩展名
#define MENTHOLEXTENSION ".me"
//可执行文件编译后的扩展名
#define MENTHOLEXECUTEEXTENSION ".mee"

//用来和编译后的文件中的类型比较使用
#define MENTHOLPACKAGEDLLEXTENSION2 "MED"
#define MENTHOLEXECUTEEXTENSION2 "MEE"

//mmain默认name
#define MAINMODULENAME "53A25398-E89C-439d-9F93-011EA71D6872"
#define MAINMODULENAMEHASH 4022255038



typedef void (*initfuncallback)(VmState*);

struct LocalVarAttr
{
   string name;
   int index;
   bool isconst;
};
struct GlobalVarAttr
{
   string name;
   hashValue hash;
   bool isconst;
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
	void SetCompileStructTable(Statement* b);//把一个解析后的表达式加入CompileStructTable中
	void AddCode(Instruction x,int lineno=0);//生成只从代码
	void SetCode(Instruction x,int ipp);  //设置某个位置的制定
	void AddCharCode(char x);//生成一个char类型的执行
	int GetIpi();//获取当前代码的位置
	bool AddGlobalMemory(string _name,bool _isconst=false);//增加模块里全局变量
	GlobalVarAttr FindGlobalMemory(string str);//找到模块中的全局变量属性
	void AddStringConstant(string str);//增加一般字符串列表
	void AddDictKeyConstant(string s);//增加字典的键字符串
	void AddDoubleConstant(double d);//增加double类型列表
	static StatementList* GetInstance();//后去势力
	bool AddLocalMemory(string _name,int _lineno,bool _isconst=false);//增加局部变量
	LocalVarAttr FindLocalMemory(string _name);//训啊找局部变量
	void ClearLocalMemory();//清空局部变量
	void CreateCode(vector<Statement*>* _CompileStructTable,string extension);//创建代码
	bool IsGlobalVar(string name);//判断变量是否为全局变量
	LocalVarAttr FindLastLocalMemory();
	int IsHasModuleName(string name);//判断是否有这个模块
	void AddModuleList(string name);//增加当前包的模块泪飙
	//void ResetInitPackageList();
	int FindDoubleConstant(double s);//找到double的索引
	int FindStringConstant(string d);//找到string的索引
	int FindDictKeyConstant(string d);//找到字典key的索引
	int FindFunction(string s);//找到调用的函数
	void AddFunction(string s);//把包里的函数增加到函数列表中
	int GetLocalCountValue();
	void SetLocalCountValue(int x);
	vector<GlobalVarAttr>* GetGlobalMemory();//获取全局变量列表
	vector<LocalVarAttr>* GetLocalMemory();//获取局部变量列表
	void AddExternalModuleList(string modulename);//把外部模块增加到模块列表
	void RestDebugIpi();//重置debugipi
	void AddToIncludeFile(string modulename);//加入到整个程序需要包含的包列表中
	void AddMainModuleList(Statement* fd);//把main函数也当作一个模块加入到模块列表中
	void AddUseModuleList(string modulename);//把当前包使用的模块增加到模块列表
	bool FindUseModuleList(string modulename);//判断模块是否已经加入了模块列表中
public:
	vector<Instruction> *CodeList;//一个包最后生成的所有代码
	vector <Statement*> *CompileStructTable;//一个包最后生成的需要编译的结构
	int StackID;//在虚拟机中模拟的ip;
	vector<ImportFileAttr> *includefiles;	//一个包中包含的其他包

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