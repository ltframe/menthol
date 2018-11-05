#include "StdAfx.h"
#include "StatementList.h"
#include "MFile.h"


void StatementList::SetCompileStructTable(Statement* b)
{
   if(b->NType==MNT_FunctionDefinition && FindInCompileStructTable(b->name)!=-1)
   {
		MError::CreateInstance()->PrintError("function " + b->name + " already has a body");
   }
   CompileStructTable->push_back(b);
}

int StatementList::FindInCompileStructTable(string b)
{
	//for (std::vector<Statement*>::iterator it =CompileStructTable->begin() ; it != CompileStructTable->end(); ++it)
	//{	
	VECTORFORSTART(Statement*,CompileStructTable,it)
		if((*it)->NType==MNT_FunctionDefinition && (*it)->name==b){
			return (*it)->wfileaddressline;
		}
	VECTORFOREND
	//}
	return -1;
}


void StatementList::AddCode(Instruction x,int line){	

	if(line!=0){
		if(!MentholDebugList->size())
		{
			MentholDebug info = {debugipi++,line,strlen(currentyyfile),currentyyfile};
			MentholDebugList->push_back(info);
		}else
		{
			MentholDebug info = {debugipi++,line,0,""};
			MentholDebugList->push_back(info);
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


void StatementList::ResetIpi(){
	ipi = 0;
}

int StatementList::GetIpi()
{
	return ipi;
}



StatementList* StatementList::_StatementList = 0;

StatementList::StatementList():CompileStructTable(new vector <Statement*>())
	,CodeList(new vector<Instruction>()),functionlist(new vector<string>()),
   localcount(0),stringconstants(new vector <string>()),dictkeyconstants(new vector <string>()),GlobalMemory(new vector <GlobalVarAttr>()),ipi(0),StackID(0),LocalMemory(new vector<LocalVarAttr>()),
   PackAgeList(new vector<PackageAttr>()),doubleconstants(new vector <double>()),debugipi(0)

{
	_StatementList =this;
	debugipi = 0;
	MentholDebugList = new vector<MentholDebug>();
	
}

StatementList::~StatementList(void)
{
	delete CompileStructTable;
	delete CodeList;
	delete functionlist;
	delete stringconstants;
	delete dictkeyconstants;
	delete GlobalMemory;
	delete LocalMemory;
	delete PackAgeList;
	delete doubleconstants;
	delete MentholDebugList;
}




bool StatementList::AddLocalMemory(string _name,int _lineno){

	/*string classname = "";
	if(_name.substr(0,2) =="$0"){
		classname = _name.substr(3);
		_name = "$0";
	}*/
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

int StatementList::IsHasPackAgeName(string name)
{
	//for (std::vector<PackageAttr>::iterator it = PackAgeList->begin() ; it != PackAgeList->end(); ++it)
	//{	
	VECTORFORSTART(PackageAttr,PackAgeList,it)
		if(name==(*it).pname){
			return it-PackAgeList->begin();
		}
	VECTORFOREND
	//}
	return -1;
}
void StatementList::AddPackAgeList(string s)
{

	if(IsHasPackAgeName(s)!=-1)return;

	string pname = MCommon::CreateInstance()->StringPathSplit(s).name;
	PackageAttr pa;
	pa.ptype = MPA_UNKONWN;
	string _pname = pname;
	strcpy(pa.pname, _pname.c_str());
	if(MFile::CreateInstance()->IsFileExist(s + ".dll"))
	{
		string str = s + ".dll";
		strcpy(pa.fname,str.c_str());
		pa.ptype = MPA_DLL;
		PackAgeList->push_back(pa);
		return;
	}
	if(MFile::CreateInstance()->IsFileExist(s + MENTHOLPACKAGEDLLEXTENSION)){
		string str = s + MENTHOLPACKAGEDLLEXTENSION;
		strcpy(pa.fname,str.c_str());
		pa.ptype = MPA_PACKAGE;
		PackAgeList->push_back(pa);
		return;
	}
	string strpath = MCommon::CreateInstance()->GetRunPath()+ "\\lib\\";

	if(MFile::CreateInstance()->IsFileExist(strpath+s + ".dll")){
		string str = s + ".dll";
		strcpy(pa.fname,str.c_str());
		pa.ptype = MPA_SDLL;
		PackAgeList->push_back(pa);
		return;
	}
	if(MFile::CreateInstance()->IsFileExist(strpath+s + MENTHOLPACKAGEDLLEXTENSION)){
		string str = s + MENTHOLPACKAGEDLLEXTENSION;
		strcpy(pa.fname,str.c_str());
		pa.ptype = MPA_SPACKAGE;
		PackAgeList->push_back(pa);
		return;
	}
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

bool StatementList::IsGlobalVar(string name)
{
	if(name[0]=='@')return true;
	return false;
}

bool StatementList::AddGlobalMemory(string _name){
	//for (std::vector<GlobalVarAttr>::iterator it = GlobalMemory->begin() ; it != GlobalMemory->end(); ++it)
	//{
	VECTORFORSTART(GlobalVarAttr,GlobalMemory,it)
		if(_name==(*it).name){
			return false;
		}
	VECTORFOREND
	//}
	GlobalVarAttr lv;
	lv.name = _name;
	lv.hash = MCommon::CreateInstance()->ELFHash(_name);
    GlobalMemory->push_back(lv);
	//AddStringConstants(_name);
	return true;
}
GlobalVarAttr StatementList::FindGlobalMemory(string str)
{
	//for (std::vector<GlobalVarAttr>::iterator it = GlobalMemory->begin() ; it != GlobalMemory->end(); ++it)
	//{	
	VECTORFORSTART(GlobalVarAttr,GlobalMemory,it)
		if(str==(*it).name)
		{
			return	(*it);
		}
	VECTORFOREND
	//}	
	GlobalVarAttr NullVarAttr={"",0}; //global的值是字符串的HASH值，不可能为0
	return NullVarAttr;
}


void StatementList::ResetInitPackageList()
{
	AddPackAgeList("MSystem");
	AddPackAgeList("MIo");
}
void StatementList::CreateCode(vector<Statement*>* _CompileStructTable,string extension,bool isdebug)
{	

	if(extension==MENTHOLEXTENSION){
		string fileext = MENTHOLEXECUTEEXTENSION2;
		for(int i=0;i<fileext.length();i++){
			AddCharCode(fileext[i]);
		}
	}
	if(extension==MENTHOLPACKAGEEXTENSION){
		string fileext = MENTHOLPACKAGEDLLEXTENSION2;
		for(int i=0;i<fileext.length();i++){
			AddCharCode(fileext[i]);
		}
	}

	int importentry = GetIpi();
	AddCode(0); //import files entry point
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
/*	for (std::vector<PackageAttr>::iterator it = PackAgeList->begin() ; it != PackAgeList->end(); ++it)
	{*/	
	VECTORFORSTART(PackageAttr,PackAgeList,it)
		AddCode((*it).ptype);	
		int namepostion = GetIpi(); //name  postion;	
		AddCode(0);
		int slen = strlen((*it).pname);
		for(int i = 0;i<strlen((*it).pname);i++){
			AddCode((*it).pname[i]);
		}
		SetCode(slen,namepostion);


		int filepathpostion = GetIpi(); //filepath  postion;	
		AddCode(0);
		slen = strlen((*it).fname);
		for(int i = 0;i<slen;i++){
			AddCode((*it).fname[i]);
		}
		SetCode(slen,filepathpostion);
	/*}	*/
	VECTORFOREND
	SetCode(GetIpi()-allimportstart,allimportstart);


	///////////////////////////////////global start
	
	SetCode(GetIpi(),globalentry);
	int allglobalstart =GetIpi();
	AddCode(0); ////set functions length
	/*for (std::vector<Statement*>::iterator it = _CompileStructTable->begin() ; it != _CompileStructTable->end(); ++it)
	{*/
	VECTORFORSTART(Statement*,_CompileStructTable,it)
		if((*it)->NType==MNT_ExpressionList ||  (*it)->NType==MNT_InitializationList){			
			int codelengthpostion = GetIpi();
			AddCode(0); ////set strings length
			int codestart = GetIpi();
			(*it)->CreateCode();
			SetCode(GetIpi()-codestart,codelengthpostion);
		}
	/*}*/
	VECTORFOREND
	SetCode(GetIpi()-allglobalstart,allglobalstart);


		////////////////////////////////////funciton start

	int allfunctionstart =GetIpi();
	SetCode(allfunctionstart,functionentry);
	AddCode(0); ////set functions length
	/*for (std::vector<Statement*>::iterator it =_CompileStructTable->begin() ; it != _CompileStructTable->end(); ++it)
	{	*/	
	VECTORFORSTART(Statement*,_CompileStructTable,it)
		if((*it)->NType==MNT_FunctionDefinition){

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
	//}
	VECTORFOREND
	SetCode(GetIpi()-allfunctionstart,allfunctionstart);


	///////////////////////////////////string start
	int allstringstart  = GetIpi();
	SetCode(allstringstart,stringentry);
	AddCode(0); ////set strings length
	/*for (std::vector<string>::iterator it = stringconstants->begin() ; it != stringconstants->end(); ++it)
	{	*/
	VECTORFORSTART(string,stringconstants,it)
		int singlestringpostion = GetIpi();
		AddCode(0);
		int singlestringstart = GetIpi();
		for(int i=0;i<(*it).length();i++){
			AddCharCode((*it)[i]);
		}
		SetCode(GetIpi()-singlestringstart,singlestringpostion);
		//AddCode(MCommon::CreateInstance()->ELFHash((*it)));
	//}
	VECTORFOREND
	SetCode(GetIpi()-allstringstart,allstringstart);

	///////////////////////////////////double start
	int alldoublestart  = GetIpi();
	SetCode(alldoublestart,doubleentry);
	AddCode(0); ////set strings length
	/*for (std::vector<double>::iterator it = doubleconstants->begin() ; it != doubleconstants->end(); ++it)
	{*/	
	VECTORFORSTART(double,doubleconstants,it)
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
	/*}*/
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
	if(isdebug){
		VECTORFORSTART(MentholDebug,MentholDebugList,it)
				AddCode((*it).instno);
				AddCode((*it).lineno);
				AddCode((*it).filenamelenght);
				for(int i=0;i<(*it).filenamelenght;i++){
					AddCharCode((*it).filename[i]);
				}
		VECTORFOREND
	}
	SetCode(GetIpi()-montholdebugstart,montholdebugstart);
}






void StatementList::AddStringConstant(string s)
{
	if(FindStringConstant(s)==-1){
		stringconstants->push_back(s);
	}
}

void StatementList::AddDictKeyConstant(string s)
{
	if(FindDictKeyConstant(s)==-1){
		dictkeyconstants->push_back(s);
	}
}



void StatementList::AddDoubleConstant(double d)
{
	if(FindDoubleConstant(d)==-1){
		doubleconstants->push_back(d);
	}
}

int StatementList::FindStringConstant(string d)
{
	//for (std::vector<string>::iterator it = stringconstants->begin() ; it != stringconstants->end(); ++it)
	//{
	VECTORFORSTART(string,stringconstants,it)
		if((*it)==d){
			return it-stringconstants->begin();
		}
	//}
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
	VECTORFORSTART(double,doubleconstants,it)
		if((*it)==d){
			return it-doubleconstants->begin();
		}
	//}
	VECTORFOREND
	return -1;
}

int StatementList::FindFunction(string s)
{
	//for (std::vector<string>::iterator it = functionlist->begin() ; it != functionlist->end(); ++it)
	//{	
	VECTORFORSTART(string,functionlist,it)
		if(s==(*it))return it-functionlist->begin();
	//}
	VECTORFOREND
	return -1;
}

void StatementList::AddFunction(string s)
{
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


vector<double>* StatementList::GetDoubleConstants()
{
	return doubleconstants;
}
vector<string>* StatementList::GetImprotFiles()
{
	return ImprotFiles;
}
vector<PackageAttr>* StatementList::GetPackAgeList()
{
	return PackAgeList;
}
vector<string>* StatementList::GetFunctionList()
{
	return functionlist;
}
vector <string>* StatementList::GetStringConstants()
{
	return stringconstants;
}
vector <string>* StatementList::GetDictKeyConstants()
{
	return dictkeyconstants;
}

vector<GlobalVarAttr>* StatementList::GetGlobalMemory()
{
	return GlobalMemory;
}
vector<LocalVarAttr>* StatementList::GetLocalMemory()
{
	return LocalMemory;
}

vector<MentholDebug>* StatementList::GetMentholDebug()
{
	return MentholDebugList;
}	

void StatementList::RestDebugIpi()
{
	debugipi = 0;
}