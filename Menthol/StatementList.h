#pragma once
#ifndef STATEMENTLIST
#define STATEMENTLIST
#include "header.h"
#include "Parser.h"
#include "MError.h"
#include "MCommon.h"



//����Դ��չ��
#define MENTHOLPACKAGEEXTENSION ".mep"
//����������չ��
#define MENTHOLPACKAGEDLLEXTENSION ".med"

//��ִ���ļ���Դ��չ��
#define MENTHOLEXTENSION ".me"
//��ִ���ļ���������չ��
#define MENTHOLEXECUTEEXTENSION ".mee"

//�����ͱ������ļ��е����ͱȽ�ʹ��
#define MENTHOLPACKAGEDLLEXTENSION2 "MED"
#define MENTHOLEXECUTEEXTENSION2 "MEE"

//mmainĬ��name
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
	void SetCompileStructTable(Statement* b);//��һ��������ı��ʽ����CompileStructTable��
	void AddCode(Instruction x,int lineno=0);//����ֻ�Ӵ���
	void SetCode(Instruction x,int ipp);  //����ĳ��λ�õ��ƶ�
	void AddCharCode(char x);//����һ��char���͵�ִ��
	int GetIpi();//��ȡ��ǰ�����λ��
	bool AddGlobalMemory(string _name,bool _isconst=false);//����ģ����ȫ�ֱ���
	GlobalVarAttr FindGlobalMemory(string str);//�ҵ�ģ���е�ȫ�ֱ�������
	void AddStringConstant(string str);//����һ���ַ����б�
	void AddDictKeyConstant(string s);//�����ֵ�ļ��ַ���
	void AddDoubleConstant(double d);//����double�����б�
	static StatementList* GetInstance();//��ȥ����
	bool AddLocalMemory(string _name,int _lineno,bool _isconst=false);//���Ӿֲ�����
	LocalVarAttr FindLocalMemory(string _name);//ѵ���Ҿֲ�����
	void ClearLocalMemory();//��վֲ�����
	void CreateCode(vector<Statement*>* _CompileStructTable,string extension);//��������
	bool IsGlobalVar(string name);//�жϱ����Ƿ�Ϊȫ�ֱ���
	LocalVarAttr FindLastLocalMemory();
	int IsHasModuleName(string name);//�ж��Ƿ������ģ��
	void AddModuleList(string name);//���ӵ�ǰ����ģ�����
	//void ResetInitPackageList();
	int FindDoubleConstant(double s);//�ҵ�double������
	int FindStringConstant(string d);//�ҵ�string������
	int FindDictKeyConstant(string d);//�ҵ��ֵ�key������
	int FindFunction(string s);//�ҵ����õĺ���
	void AddFunction(string s);//�Ѱ���ĺ������ӵ������б���
	int GetLocalCountValue();
	void SetLocalCountValue(int x);
	vector<GlobalVarAttr>* GetGlobalMemory();//��ȡȫ�ֱ����б�
	vector<LocalVarAttr>* GetLocalMemory();//��ȡ�ֲ������б�
	void AddExternalModuleList(string modulename);//���ⲿģ�����ӵ�ģ���б�
	void RestDebugIpi();//����debugipi
	void AddToIncludeFile(string modulename);//���뵽����������Ҫ�����İ��б���
	void AddMainModuleList(Statement* fd);//��main����Ҳ����һ��ģ����뵽ģ���б���
	void AddUseModuleList(string modulename);//�ѵ�ǰ��ʹ�õ�ģ�����ӵ�ģ���б�
	bool FindUseModuleList(string modulename);//�ж�ģ���Ƿ��Ѿ�������ģ���б���
public:
	vector<Instruction> *CodeList;//һ����������ɵ����д���
	vector <Statement*> *CompileStructTable;//һ����������ɵ���Ҫ����Ľṹ
	int StackID;//���������ģ���ip;
	vector<ImportFileAttr> *includefiles;	//һ�����а�����������

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