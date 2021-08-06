#include "StdAfx.h"
#include "StatementList.h"
#include "MFile.h"
#include "MBinary.h"
#include <Windows.h>
#include <algorithm>
void StatementList::SetCompileStructTable(Statement* b)
{
   CompileStructTable->push_back(b);
}

void StatementList::AddCode(Instruction x,int line){	

	if(line!=0){
		if (!currentmodule.debuglist->size())
		{
			MentholDebug info = {debugipi++,line,strlen(currentyyfile),currentyyfile};
			currentmodule.debuglist->push_back(info);
		}else
		{
			MentholDebug info = {debugipi++,line,0,""};
			currentmodule.debuglist->push_back(info);
		}
	}
	CodeList->push_back(x);ipiadd;
}

void StatementList::SetCode(Instruction x,int ipp){	    
	CodeList->at(ipp) =x;
}

void StatementList::AddCharCode(char x){	    
	CodeList->push_back(x);ipiadd;
}




int StatementList::GetIpi()
{
	return ipi;
}



StatementList* StatementList::_StatementList = 0;

StatementList::StatementList():CompileStructTable(new vector <Statement*>())
	,CodeList(new vector<Instruction>()),
   localcount(0),ipi(0),StackID(0),LocalMemory(new vector<LocalVarAttr>()),
   ModuleList(new vector<ModuleAndConstant>()), debugipi(0), includefiles(new vector<ImportFileAttr>()), UseModuleList(new vector<ModuleAndConstant>()),
   ImportFileAllModuleList(new vector<ModuleAndConstant>())

{
	_StatementList =this;
	debugipi = 0;
	doublelist = new vector<double>();
	stringlist = new vector<string>();
	functionlist = new vector<string>();	
	dictkeyconstants= new vector<string>();	
	GlobalMemory = new vector<GlobalVarAttr>();
}

StatementList::~StatementList(void)
{
	delete CompileStructTable;
	delete CodeList;

	delete GlobalMemory;
	delete LocalMemory;
	delete doublelist;
	delete functionlist;
	delete stringlist;	
	VECTORFORSTART(ModuleAndConstant, UseModuleList, it)
		delete (*it).doublelist;
		delete (*it).stringlist;
		delete (*it).functionlist;
		delete (*it).debuglist;
		delete (*it).globalmemory;
	VECTORFOREND
	delete ModuleList;
	delete includefiles;
	delete dictkeyconstants;
	delete UseModuleList;
	delete ImportFileAllModuleList;
	StatementList::_StatementList = 0;
}




bool StatementList::AddLocalMemory(string _name,int _lineno,bool _isconst){

	if(IsGlobalVar(_name)){
		MError::CreateInstance()->PrintError("Do not allow global variables to be declared inside a function "+_name,_lineno);	

	}

	for (int i = 0;i<localcount;i++){
		
		if(LocalMemory->at(i).name ==_name)
		{
			return	false;
		}
	}


	LocalVarAttr lv;
	lv.name = _name;
	lv.index = StackID;
	lv.isconst = _isconst;
	LocalMemory->push_back(lv);
	localcount++;
	return true;

}

void StatementList::ClearLocalMemory()
{
	LocalMemory->clear();
	localcount = 0;
}


LocalVarAttr StatementList::FindLastLocalMemory()
{
	LocalVarAttr lva = *(LocalMemory->end()-1);
	return lva;
}

int StatementList::IsHasModuleName(string name)
{

	VECTORFORSTART(ModuleAndConstant, UseModuleList, it)
		if(name==(*it).modulename){
			return it - UseModuleList->begin();
		}
	VECTORFOREND
	return -1;
}


bool StatementList::IsAddedImportFileAllPackAgeList(string modulename)
{
	VECTORFORSTART(ModuleAndConstant, ImportFileAllModuleList, it)
		if (modulename == (*it).modulename){
			return true;
		}
	VECTORFOREND
	return false;
}

void StatementList::AddExternalModuleList(string modulename)
{
	if (IsAddedImportFileAllPackAgeList(modulename)){
		return;
	}
	ModuleAndConstant pac = { modulename, MCommon::CreateInstance()->ELFHash(string(modulename)), 0, 0, 0, 0, 0 };
	ImportFileAllModuleList->push_back(pac);
}

void StatementList::AddToIncludeFile(string filename)
{
	
	VECTORFORSTART(ImportFileAttr,includefiles,it)
		transform(filename.begin(), filename.end(), filename.begin(),::tolower);
		transform((*it).filename.begin(), (*it).filename.end(), (*it).filename.begin(),::tolower);
		if(MCommon::CreateInstance()->StringPathSplit((*it).filename).name==filename)
		{
			return;
		}
	VECTORFOREND

	ImportFileAttr ifa={"",MPA_UNKNOW};
	ifa.filename = filename + MENTHOLPACKAGEDLLEXTENSION;	

	string physicalpath = ifa.filename;

	if(MFile::CreateInstance()->IsFileExist(physicalpath))
	{
		if(MBinary::CreateInstance()->ReadPackageFormat(physicalpath)==MENTHOLPACKAGEDLLEXTENSION2)
		{
			ifa.ptype = MPA_USER_PACKAGE;	
		}else
		{
			ifa.ptype = MPA_USER_EXTPACKAGE;	
		}	
		includefiles->push_back(ifa);
	}else
	{
		string strpath = MCommon::CreateInstance()->GetRunPath()+ "\\lib\\";
		physicalpath =strpath+ifa.filename;
		if(MFile::CreateInstance()->IsFileExist(physicalpath)){				
			if(MBinary::CreateInstance()->ReadPackageFormat(physicalpath)==MENTHOLPACKAGEDLLEXTENSION2)
			{
				ifa.ptype  = MPA_SYS_PACKAGE;
			}else
			{
				ifa.ptype  = MPA_SYS_EXTPACKAGE;
			}
			includefiles->push_back(ifa);
		}
	}


	if(ifa.ptype!=MPA_UNKNOW){
		if(IsPackage(ifa.ptype))
		{
			vector<string> *plist =new vector<string>();
			MBinary::CreateInstance()->ReadMEPPackage(physicalpath,plist);

			VECTORFORSTART(string,plist,it)
				AddExternalModuleList(*it);
			VECTORFOREND
			delete plist;

		}else
		{
			HMODULE h = ::LoadLibrary(physicalpath.c_str());
			initfuncallback ProcAdd = (initfuncallback)GetProcAddress(h, "MP_Init");
			ProcAdd(0);
			FreeLibrary(h);
		}
	}
	else
	{
		MError::CreateInstance()->PrintError(filename + " package not found");
	}
}

void StatementList::AddMainModuleList(Statement* fd)
{
	string s = MCommon::CreateInstance()->CreateGuid();
	ModuleStatementList * _p = new ModuleStatementList();
	_p->AddChilder(fd);
	SetCompileStructTable(new ModuleDefine(MAINMODULENAME, _p));
}

void StatementList::AddModuleList(string s)
{
	if (IsHasModuleName(s) != -1){
		MError::CreateInstance()->PrintError(s+ " module redefinition");	
		return;
	}
	ModuleAndConstant pac = { s, MCommon::CreateInstance()->ELFHash(s), doublelist, stringlist, functionlist, new vector<MentholDebug>(), GlobalMemory };
	ModuleList->push_back(pac);
	ImportFileAllModuleList->push_back(pac);
	UseModuleList->push_back(pac);
	doublelist =new vector<double>();
	stringlist=new vector<string>();
	functionlist=new vector<string>();
	GlobalMemory = new vector<GlobalVarAttr>();		
}
LocalVarAttr StatementList::FindLocalMemory(string _name){

	for (int i = 0;i<localcount;i++){
		
		if(LocalMemory->at(i).name ==_name)
		{
			return	LocalMemory->at(i);
		}
	}
	LocalVarAttr NullVarAttr={"",-1};
	return NullVarAttr;
}

StatementList* StatementList::GetInstance()
{
	return _StatementList;
}

//测试变量开始头是@开头的为全局变量，var开头的为局部变量
bool StatementList::IsGlobalVar(string name)
{
	if(name[0]=='@')return true;
	return false;
}

bool StatementList::AddGlobalMemory(string _name,bool _isconst){
	//for (std::vector<GlobalVarAttr>::iterator it = GlobalMemory->begin() ; it != GlobalMemory->end(); ++it)
	//{
	VECTORFORSTART(GlobalVarAttr, currentmodule.globalmemory, it)
		if(_name==(*it).name){
		 return false;
		}
	VECTORFOREND
	//}
	GlobalVarAttr lv;
	lv.name = _name;
	lv.hash = MCommon::CreateInstance()->ELFHash(_name);
	lv.isconst = _isconst;
	currentmodule.globalmemory->push_back(lv);
	//AddStringConstants(_name);
	return true;
}
GlobalVarAttr StatementList::FindGlobalMemory(string str)
{
	//for (std::vector<GlobalVarAttr>::iterator it = GlobalMemory->begin() ; it != GlobalMemory->end(); ++it)
	//{	
	VECTORFORSTART(GlobalVarAttr, currentmodule.globalmemory, it)
		if(str==(*it).name)
		{
			return	(*it);
		}
	VECTORFOREND
	//}	
	GlobalVarAttr NullVarAttr={"",0}; //global的值是字符串的HASH值，不可能为0
	return NullVarAttr;
}


void StatementList::CreateCode(vector<Statement*>* _CompileStructTable,string extension)
{	

	//写入文件二进制文件的文件表示，字符形式
	if(MCommon::CreateInstance()->StrCmpNoCase(extension,MENTHOLEXTENSION)){
		string fileext = MENTHOLEXECUTEEXTENSION2;
		for(int i=0;i<fileext.length();i++){
			AddCharCode(fileext[i]);
		}
	}
	if(MCommon::CreateInstance()->StrCmpNoCase(extension,MENTHOLPACKAGEEXTENSION)){
		string fileext = MENTHOLPACKAGEDLLEXTENSION2;
		for(int i=0;i<fileext.length();i++){
			AddCharCode(fileext[i]);
		}
	}


	//需要使用的包的入口，此地址保存了文件所使用的包的文件地址
	int importentry = GetIpi();
	AddCode(0); //import files entry point

	//是了模块列表的地址
	int moduleentry = GetIpi();
	AddCode(0); //package entry point


	int includemoduleentry = GetIpi();
	AddCode(0);

	int globalentry = GetIpi();
	AddCode(0);//global codes  entry point
	int functionentry = GetIpi();
	AddCode(0);//function list entry
	int stringentry = GetIpi();
	AddCode(0);//string lsit  entry
	int doubleentry = GetIpi();
	AddCode(0);//double lsit  entry
	int dictkeyentry = GetIpi();
	AddCode(0);//dict key lsit  entry
	int montholdebugentry = GetIpi();
	AddCode(0);//debug lsit  entry



	SetCode(GetIpi(),importentry);
	int allimportstart = GetIpi();
	AddCode(0); ////set strings length



	//导入使用的包文件
	VECTORFORSTART(ImportFileAttr,includefiles,it)
		AddCode((*it).ptype);
		int filepathpostion = GetIpi(); //filepath  postion;	
		AddCode(0);
		int slen = (*it).filename.length();
		for(int i = 0;i<slen;i++){
			AddCode((*it).filename[i]);
		}
		SetCode(slen,filepathpostion);
	VECTORFOREND
	SetCode(GetIpi()-allimportstart,allimportstart);


	




	//////////////////////////////////package start
	SetCode(GetIpi(),moduleentry);
	int allmoduleentrystart =GetIpi();
	AddCode(0); ////set functions length
	VECTORFORSTART(ModuleAndConstant, ModuleList, it)
			AddCode((*it).hash);
			int namepostion = GetIpi(); //name  postion;	
			AddCode(0);	
			int slen = (*it).modulename.length();
			for(int i = 0;i<slen;i++){
				AddCode((*it).modulename[i]);
			}
			SetCode(slen,namepostion);
	VECTORFOREND
	SetCode(GetIpi()-allmoduleentrystart,allmoduleentrystart);
	//////////////////////////////////package end


	//////////////////////////////////use package start
	SetCode(GetIpi(),includemoduleentry);
	int allincludemoduleentrystart =GetIpi();
	AddCode(0); ////set functions length
	VECTORFORSTART(ModuleAndConstant, UseModuleList, it)
		AddCode((*it).hash);
		int namepostion = GetIpi(); //name  postion;	
		AddCode(0);	
		int slen = (*it).modulename.length();
		for(int i = 0;i<slen;i++){
			AddCode((*it).modulename[i]);
		}
		SetCode(slen,namepostion);
	VECTORFOREND
	SetCode(GetIpi()-allincludemoduleentrystart,allincludemoduleentrystart);
	//////////////////////////////////use package end



	///////////////////////////////////global start	
	SetCode(GetIpi(),globalentry);
	int allglobalstart =GetIpi();
	AddCode(0); ////set functions length
	/*for (std::vector<Statement*>::iterator it = _CompileStructTable->begin() ; it != _CompileStructTable->end(); ++it)
	{*/
	VECTORFORSTART(Statement*,_CompileStructTable,moduleelement)
		if((*moduleelement)->NType==MNT_ModuleDefine){
			debugipi = 0;
			ModuleDefine* _moduledefine = STATICCAST(ModuleDefine,*moduleelement);
			currentmodule = FindModuleByName(_moduledefine->modulename);
			ModuleStatementList* _moduleStatementList = STATICCAST(ModuleStatementList,_moduledefine->modulestatementlist);
			VECTORFORSTART(Statement*,_moduleStatementList->Member,it)
				if((*it)->NType==MNT_ExpressionList ||  (*it)->NType==MNT_InitializationList){
					AddCode(MCommon::CreateInstance()->ELFHash(_moduledefine->modulename));
					int codelengthpostion = GetIpi();
					AddCode(0); ////set strings length
					int codestart = GetIpi();
					(*it)->CreateCode();
					AddCode(OP_HALT);//每一个条全局变量执行后，要返回
					SetCode(GetIpi()-codestart,codelengthpostion);
				}
			/*}*/
			VECTORFOREND
		}
	VECTORFOREND
	SetCode(GetIpi()-allglobalstart,allglobalstart);





	////////////////////////////////////funciton start

	int allfunctionstart =GetIpi();
	SetCode(allfunctionstart,functionentry);
	AddCode(0); ////set functions length

	VECTORFORSTART(Statement*,_CompileStructTable,moduleelement)
		if((*moduleelement)->NType==MNT_ModuleDefine){
				debugipi = 0;
				ModuleDefine* _moduledefine = STATICCAST(ModuleDefine,*moduleelement);
				currentmodule = FindModuleByName(_moduledefine->modulename);
				ModuleStatementList* _ModuleStatementList = STATICCAST(ModuleStatementList,_moduledefine->modulestatementlist);
				VECTORFORSTART(Statement*,_ModuleStatementList->Member,it)
					if((*it)->NType==MNT_FunctionDefinition || (*it)->NType==MNT_MainFunction){
						AddCode(MCommon::CreateInstance()->ELFHash(_moduledefine->modulename));
						FunctionDefinition* fd = STATICCAST(FunctionDefinition,*it);
						int functionnamelengthpostion = GetIpi();
						AddCode(0);
						int functionnamestart = GetIpi();
						for(int i=0;i<(*it)->name.length();i++){
							AddCharCode((*it)->name[i]);
						}
						SetCode(GetIpi()-functionnamestart,functionnamelengthpostion);
						AddCode(0);
						AddCode(MCommon::CreateInstance()->ELFHash((*it)->name));
						AddCode(fd->GetParamerCount());
						int codelengthpostion = GetIpi();
						AddCode(0); ////set strings length
						int codestart = GetIpi();
						(*it)->CreateCode();
						SetCode(GetIpi()-codestart,codelengthpostion);			
						fd->GetDefaultValueList();
					}
				VECTORFOREND
		}
	VECTORFOREND
	SetCode(GetIpi()-allfunctionstart,allfunctionstart);


	///////////////////////////////////string start
	int allstringstart  = GetIpi();
	SetCode(allstringstart,stringentry);
	AddCode(0); ////set strings length

	VECTORFORSTART(ModuleAndConstant, ModuleList, _modulelist)
			VECTORFORSTART(string, (*_modulelist).stringlist, it)
				AddCode((*_modulelist).hash);
				int singlestringpostion = GetIpi();
				AddCode(0);
				int singlestringstart = GetIpi();
				for(int i=0;i<(*it).length();i++){
					AddCharCode((*it)[i]);
				}
				SetCode(GetIpi()-singlestringstart,singlestringpostion);
			VECTORFOREND
	VECTORFOREND
	SetCode(GetIpi()-allstringstart,allstringstart);

	///////////////////////////////////double start
	int alldoublestart  = GetIpi();
	SetCode(alldoublestart,doubleentry);
	AddCode(0); ////set strings length

	VECTORFORSTART(ModuleAndConstant, ModuleList, _modulelist)
		VECTORFORSTART(double, (*_modulelist).doublelist, it)
				AddCode((*_modulelist).hash);
				CodeDouble cd;
				cd.d = (*it);
				CodeInst ci;
				ci.m.c1 = cd.m.c1;
				ci.m.c2 = cd.m.c2;
				ci.m.c3 = cd.m.c3;
				ci.m.c4 = cd.m.c4;
				AddCode(ci.i);
				ci.m.c1 = cd.m.c5;
				ci.m.c2 = cd.m.c6;
				ci.m.c3 = cd.m.c7;
				ci.m.c4 = cd.m.c8;
				AddCode(ci.i);
			VECTORFOREND
	VECTORFOREND
	SetCode(GetIpi()-alldoublestart,alldoublestart);



	///////////////////////////////////dict key start
	int alldictkeystart  = GetIpi();
	SetCode(alldictkeystart,dictkeyentry);
	AddCode(0); ////set strings length
	/*for (std::vector<string>::iterator it = dictkeyconstants->begin() ; it != dictkeyconstants->end(); ++it)
	{	*/
	VECTORFORSTART(string,dictkeyconstants,it)
		int singlestringpostion = GetIpi();
		AddCode(0);
		int singlestringstart = GetIpi();
		for(int i=0;i<(*it).length();i++){
			AddCharCode((*it)[i]);
		}
		SetCode(GetIpi()-singlestringstart,singlestringpostion);
		AddCode(MCommon::CreateInstance()->ELFHash((*it)));
	/*}*/
	VECTORFOREND
	SetCode(GetIpi()-alldictkeystart,alldictkeystart);



	/////////////////////////////////debug start
	int montholdebugstart  = GetIpi();
	SetCode(montholdebugstart,montholdebugentry);
	AddCode(0); ////set strings length
	VECTORFORSTART(ModuleAndConstant, ModuleList, _modulelist)
		VECTORFORSTART(MentholDebug, (*_modulelist).debuglist, it)
					AddCode((*_modulelist).hash);
					AddCode((*it).instno);
					AddCode((*it).lineno);
					AddCode((*it).filenamelenght);
					for(int i=0;i<(*it).filenamelenght;i++){
						AddCharCode((*it).filename[i]);
					}
			VECTORFOREND
	VECTORFOREND
	SetCode(GetIpi()-montholdebugstart,montholdebugstart);
}






void StatementList::AddStringConstant(string s)
{
	VECTORFORSTART(string,stringlist,it)
	if((*it)==s){
		return;
	}
	VECTORFOREND
	stringlist->push_back(s);
}

void StatementList::AddDictKeyConstant(string s)
{
	if(FindDictKeyConstant(s)==-1){
		dictkeyconstants->push_back(s);
	}
}



void StatementList::AddDoubleConstant(double d)
{
	VECTORFORSTART(double,doublelist,it)
		if((*it)==d){
			return;
		}
	VECTORFOREND
	doublelist->push_back(d);

}

int StatementList::FindStringConstant(string d)
{
	VECTORFORSTART(string, currentmodule.stringlist, it)
		if((*it)==d){
			return it - currentmodule.stringlist->begin();
		}
	VECTORFOREND
	return -1;
}

int StatementList::FindDictKeyConstant(string d)
{
	//for (std::vector<string>::iterator it = dictkeyconstants->begin() ; it != dictkeyconstants->end(); ++it)
	//{	
	VECTORFORSTART(string,dictkeyconstants,it)
		if((*it)==d){
			return it-dictkeyconstants->begin();
		}
	//}
	VECTORFOREND
	return -1;
}

int StatementList::FindDoubleConstant(double d)
{
	//for (std::vector<double>::iterator it = doubleconstants->begin() ; it != doubleconstants->end(); ++it)
	//{	
	VECTORFORSTART(double, currentmodule.doublelist, it)
		if((*it)==d){
			return it - currentmodule.doublelist->begin();
		}
	//}
	VECTORFOREND
	return -1;
}

int StatementList::FindFunction(string s)
{
	//for (std::vector<string>::iterator it = functionlist->begin() ; it != functionlist->end(); ++it)
	//{	
	VECTORFORSTART(string, currentmodule.functionlist, it)
		if (s == (*it))return it - currentmodule.functionlist->begin();
	//}
	VECTORFOREND
	return -1;
}

void StatementList::AddFunction(string s)
{
	VECTORFORSTART(string,functionlist,it)
		if(s==(*it)){
			 MError::CreateInstance()->PrintError("The function name cannot be the same as the module");
			 return;
		}
	VECTORFOREND
	functionlist->push_back(s);
}

int StatementList::GetLocalCountValue()
{
	return localcount;
}
void StatementList::SetLocalCountValue(int x)
{
	localcount = x;
}

ModuleAndConstant StatementList::FindModuleByName(string name)
{
	VECTORFORSTART(ModuleAndConstant, ModuleList, it)
		if (name == (*it).modulename)
			return (*it);
	VECTORFOREND
	ModuleAndConstant ret = {};
	return ret;
}


vector<GlobalVarAttr>* StatementList::GetGlobalMemory()
{
	return GlobalMemory;
}
vector<LocalVarAttr>* StatementList::GetLocalMemory()
{
	return LocalMemory;
}

void StatementList::RestDebugIpi()
{
	debugipi = 0;
}
//从UseModuleList中查找是否存在
bool StatementList::FindUseModuleList(string modulename)
{
	VECTORFORSTART(ModuleAndConstant, UseModuleList, it)
		if (modulename == (*it).modulename)
			return true;
	VECTORFOREND
	return false;
}
//往UseModuleList中加入使用的模块
void StatementList::AddUseModuleList(string modulename)
{
	if (FindUseModuleList(modulename))
	{
		return;
	}
	if (!IsAddedImportFileAllPackAgeList(modulename)){
		MError::CreateInstance()->PrintError(modulename + " module not found");
		return;
	}
	ModuleAndConstant pac = { modulename, MCommon::CreateInstance()->ELFHash(string(modulename)), 0, 0, 0, 0, 0 };
	UseModuleList->push_back(pac);
}



