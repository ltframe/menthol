#include "StdAfx.h"
#include "Parser.h"
#include <algorithm>


FunctionDefinition::FunctionDefinition(string n):btd(0),re(0){

	StatementList* sl = StatementList::GetInstance();
	Member = new vector <Statement*>();
	name = n;

	wfileaddressline = lineno;
	NType = MNT_FunctionDefinition;
}
FunctionDefinition::FunctionDefinition(string n,NodeType t):btd(0),re(0)
{
	StatementList* sl = StatementList::GetInstance();
	Member = new vector <Statement*>();
	name = n;
	wfileaddressline = lineno;
	NType = t;
}
void FunctionDefinition::AddChilder(Statement* s)
{
	if(s)
	{
		s->ParentNode = this;
	}
	Member->push_back(s);
}
void FunctionDefinition::CreateCode()
{

	StatementList* sl = StatementList::GetInstance();
	sl->ClearLocalMemory();
	int codestart = sl->GetIpi();
	sl->StackID = 0;
	bytenumber = sl->GetIpi();
	//for (std::vector<Statement*>::iterator it = Member->begin() ; it != Member->end(); ++it)
	//{		
	VECTORFORSTART(Statement*,Member,it)
		if((*it)){
			(*it)->CreateCode();
		}
	//}	
	VECTORFOREND
	re = new ReturnExpression(btd);
	re->CreateCode();
	sl->ClearLocalMemory();
	codelength = sl->GetIpi()-codestart + 1;
}


int FunctionDefinition::GetParamerCount()
{
	if(Member->at(0)==0)return 0;
	FunctionParameterStatement* _fps =STATICCAST(FunctionParameterStatement,Member->at(0));
	return _fps->Count();
}


void FunctionDefinition::GetDefaultValueList()
{
	StatementList* sl = StatementList::GetInstance();
	FunctionParameterStatement* _fps =STATICCAST(FunctionParameterStatement,Member->at(0));
	if(_fps){
		vector<int>* list =  _fps->GetDefaultValueList();
		VECTORFORSTART(int,list,it)
			sl->AddCode(*it);
		VECTORFOREND
	}
}
FunctionDefinition::~FunctionDefinition()
{
	//for (std::vector<Statement*>::iterator it = Member->begin() ; it != Member->end(); ++it)
	//{	
	VECTORFORSTART(Statement*,Member,it)
		if((*it)){
			(*it)->Release();
		}
	//}
	VECTORFOREND
	if(re)
	re->Release();

	
	delete Member;
}
void FunctionDefinition::Release()
{	
	DELETETHIS
}

FunctionParameter::FunctionParameter(string s){
	wfileaddressline = lineno;
	name = s;
	NType = MNT_FunctionParameter;
	defaultvalue = 0;
}


FunctionParameter::FunctionParameter(string s,Statement* _defaultvalue){
	wfileaddressline = lineno;
	name = s;
	NType = MNT_FunctionParameterWithDefault;
	defaultvalue = _defaultvalue;
	/*if(_defaultvalue->NType==MNT_PlusExpression || _defaultvalue->NType==MNT_MinusExpression)
	{
		ValueType v = static_cast<BuiltinTypeDeclare*>(_defaultvalue)->GetBuiltinTypeValue().v;
		if(v!=M_NUMBER && v!=M_DOUBLE){
			MError::CreateInstance()->PrintError("There are no \"-\" operators that match these operands");
		}
	}*/
}

void FunctionParameter::CreateCode()
{
	StatementList* sl = StatementList::GetInstance();
	if(defaultvalue){
		defaultvalue->CreateCode();
	}else
	{
		sl->StackID++;
	}
	if(!sl->AddLocalMemory(name,wfileaddressline))
	{
		MError::CreateInstance()->PrintError(name+" redefinition",wfileaddressline);
	}

}

Statement* FunctionParameter::GetDefalutValue()
{
	return defaultvalue;
}

string FunctionParameter::GetParameterName()
{
	return name;
}
void FunctionParameter::Release()
{	
	DELETETHIS
}


VarIdentIfier::VarIdentIfier(string s){
	wfileaddressline = lineno;
	name = s;
	NType = MNT_VarIdentIfier;
}
void VarIdentIfier::CreateCode()
{
	StatementList* sl = StatementList::GetInstance();
	bytenumber = sl->GetIpi();

	LocalVarAttr localinfo = sl->FindLocalMemory(name);
	
	if(localinfo.index==-1)
	{
		hashValue index = sl->FindGlobalMemory(name).hash;
		if(index==0)
		{
			MError::CreateInstance()->PrintError(name +string(" undeclared identifier"),wfileaddressline);//未找到	
		}else
		{
			sl->AddCode(OP_LOADM,wfileaddressline);		
		}
		sl->AddCode(index,wfileaddressline);
	}else
	{
		sl->AddCode(OP_LOADS,wfileaddressline);
		sl->AddCode(localinfo.index,wfileaddressline);
	}
	sl->StackID++;
}

void VarIdentIfier::Release()
{
	DELETETHIS
}
string VarIdentIfier::GetName()
{
	return name;
}

FunctionParameterStatement::FunctionParameterStatement(){
	Member=new vector <Statement*>();
	NType = MNT_FunctionParameterStatement;
	wfileaddressline = lineno;
	defalutvaluelengthlist = new vector<int>();
}
void FunctionParameterStatement::AddChilder(Statement* s)
{
	if(s)
	{
		s->ParentNode = this;
	}
	FunctionParameter* _f = (FunctionParameter*)s;
	if(Member->size()!=0 && ((FunctionParameter*)Member->at(Member->size()-1))->GetDefalutValue()!=0 && _f->GetDefalutValue()==0)
	{
		MError::CreateInstance()->PrintError("The default argument is not at the end of the parameter list,"+_f->GetParameterName());	
	}
	Member->push_back(s);
}
void FunctionParameterStatement::CreateCode()
{
	StatementList* sl = StatementList::GetInstance();
	bytenumber = sl->GetIpi();
	//for (std::vector<Statement*>::iterator it = Member->begin() ; it != Member->end(); ++it)
	//{	
	VECTORFORSTART(Statement*,Member,it)
		int length = sl->GetIpi();
		(*it)->CreateCode();
		int _length=sl->GetIpi()-length;
		defalutvaluelengthlist->push_back(_length);
	//}
	VECTORFOREND
}
vector<int>* FunctionParameterStatement::GetDefaultValueList()
{
	return defalutvaluelengthlist;
}
void FunctionParameterStatement::InsertChilder(Statement* s)
{
	Member->insert(Member->begin(),s);
}

int FunctionParameterStatement::Count(){
	return  Member->size();
}
FunctionParameterStatement::~FunctionParameterStatement()
{
	//for (std::vector<Statement*>::iterator it = Member->begin() ; it != Member->end(); ++it)
	//{
	VECTORFORSTART(Statement*,Member,it)
		if(*it){
			(*it)->Release();
		}
	//}
	VECTORFOREND
	delete defalutvaluelengthlist;
	delete Member;
}

void FunctionParameterStatement::Release()
{	
	DELETETHIS
}

ExpressionStatement::ExpressionStatement()
{
	Member=new vector <Statement*>();
	NType = MNT_ExpressionStatement;
	wfileaddressline = lineno;
}
ExpressionStatement::~ExpressionStatement()
{
	//for (std::vector<Statement*>::iterator it = Member->begin() ; it != Member->end(); ++it)
	//{	
	VECTORFORSTART(Statement*,Member,it)
		if(*it){
			(*it)->Release();
		}
	//}
	VECTORFOREND
	delete Member;
}
void ExpressionStatement::Release()
{
	
	DELETETHIS
}
void ExpressionStatement::AddChilder(Statement* s)
{
	if(s)
	{
		s->ParentNode = this;
	}
	Member->push_back(s);
}
void ExpressionStatement::CreateCode()
{
	StatementList* sl = StatementList::GetInstance();
	bytenumber = sl->GetIpi();
	//for (std::vector<Statement*>::iterator it = Member->begin() ; it != Member->end(); ++it)
	//{	
	VECTORFORSTART(Statement*,Member,it)
		(*it)->CreateCode();
	//}
	VECTORFOREND
}


TernaryExpression::TernaryExpression(Statement* _exprssion1,Statement* _exprssion2,Statement* _exprssion3)
{
	
	_exprssion1->ParentNode = this;
	_exprssion2->ParentNode = this;
	_exprssion3->ParentNode = this;
	exprssion1 = _exprssion1;
	exprssion2 = _exprssion2;
	exprssion3 = _exprssion3;
	NType= MNT_TernaryExpression;
	wfileaddressline = lineno;
}
void TernaryExpression::CreateCode()
{
	StatementList* sl = StatementList::GetInstance();

	SAVESTACKID
	exprssion1->CreateCode(); //this is if statment condition
	sl->AddCode(OP_TJMP,wfileaddressline);
	int postion1=sl->GetIpi();
	sl->AddCode(OP_NOP,wfileaddressline);//this is else postion

	//if the condition is true,then code run,in end,jmp
	exprssion2->CreateCode();
	sl->AddCode(OP_UJMP,wfileaddressline);
	int postion2=sl->GetIpi();
	sl->AddCode(OP_NOP,wfileaddressline);

	sl->SetCode(sl->GetIpi()-postion1,postion1); // set else postion
	exprssion3->CreateCode();

	sl->SetCode(sl->GetIpi()-postion2,postion2);
	RESTORESTACKID
	sl->StackID++;
}
TernaryExpression::~TernaryExpression()
{
	if(exprssion1){
		exprssion1->Release();
	}
	if(exprssion2){
		exprssion2->Release();
	}
	if(exprssion3){
		exprssion3->Release();
	}
}
void TernaryExpression::Release()
{
	DELETETHIS
}

CodeBlockStatement::CodeBlockStatement()
{
	Member=new vector <Statement*>();
	NType = MNT_CodeBlockStatement;
	wfileaddressline = lineno;
}
CodeBlockStatement::~CodeBlockStatement()
{
	//for (std::vector<Statement*>::iterator it = Member->begin() ; it != Member->end(); ++it)
	//{	
	VECTORFORSTART(Statement*,Member,it)
		if(*it){
		(*it)->Release();
		}
	//}
	VECTORFOREND
	delete Member;
}
void CodeBlockStatement::Release()
{
	
	DELETETHIS
}
void CodeBlockStatement::AddChilder(Statement* s)
{
	s->ParentNode = this;
	Member->push_back(s);
}
void CodeBlockStatement::CreateCode()
{
	StatementList* sl = StatementList::GetInstance();
	sopcelocalvars = sl->GetLocalCountValue();
	SAVESTACKID
	bytenumber = sl->GetIpi();
	//for (std::vector<Statement*>::iterator it = Member->begin() ; it != Member->end(); ++it)
	//{	
	VECTORFORSTART(Statement*,Member,it)
		(*it)->CreateCode();
	VECTORFOREND
	//}
	RESTORESTACKID
	sl->GetLocalMemory()->resize(sopcelocalvars);
	sl->SetLocalCountValue(sopcelocalvars);
	sl->AddCode(OP_ADJUSTSP,wfileaddressline);
	sl->AddCode(_tempstackid,wfileaddressline);
}

ExpressionList::ExpressionList()
{
	Member = new vector <Statement*>();
	NType =MNT_ExpressionList;
	wfileaddressline = lineno;
}
ExpressionList::~ExpressionList()
{
	DESTRUCTORRELEASE	
	delete Member;
}

void ExpressionList::Release()
{
	
	DELETETHIS
}
void ExpressionList::AddChilder(Statement* _s)
{
	_s->ParentNode = this;
	Member->push_back(_s);
}
void ExpressionList::CreateCode()
{
	//for (std::vector<Statement*>::iterator it = Member->begin() ; it != Member->end(); ++it)
	//{
	VECTORFORSTART(Statement*,Member,it)
		(*it)->CreateCode();
	VECTORFOREND
	//}
}
int ExpressionList::ExpressionSize()
{
	return Member->size();
}


InitializationList::InitializationList()
{
	Member = new vector <Statement*>();
	NType =MNT_InitializationList;
	wfileaddressline = lineno;
}
InitializationList::~InitializationList()
{
	DESTRUCTORRELEASE
	delete Member;
}

void InitializationList::Release()
{
	
	DELETETHIS
}
void InitializationList::AddChilder(Statement* _s)
{
	_s->ParentNode = this;
	Member->push_back(_s);
}
void InitializationList::CreateCode()
{
	//for (std::vector<Statement*>::iterator it = Member->begin() ; it != Member->end(); ++it)
	//{
	VECTORFORSTART(Statement*,Member,it)
		(*it)->CreateCode();
	//}
	VECTORFOREND
}

void InitializationList::ModfiyMemberScope(Scope _scope)
{

	StatementList* sl = StatementList::GetInstance();
	//for (std::vector<Statement*>::iterator it = Member->begin() ; it != Member->end(); ++it)
	//{
	VECTORFORSTART(Statement*,Member,it)		
		InitializationDefinition* initdef = STATICCAST(InitializationDefinition,*it);
		if(!sl->IsGlobalVar(initdef->name)){
			MError::CreateInstance()->PrintError("Local variables are not allowed to be declared externally "+initdef->name);	
		}
		else
		{
			if (initdef->GetRightNodeType() == MNT_FunctionCall || initdef->GetRightNodeType() == MNT_ModuleFunCall){
				MError::CreateInstance()->PrintError("Global variables " + string(name) + " cannot be initialized to functions call");
			}
		}
		initdef->ModfiyScope(_scope);
	//}
	VECTORFOREND
}


AssignmentDefinition::AssignmentDefinition(Statement * _s,string _oper,Statement * _e,bool _t)
{
	StatementList* sl = StatementList::GetInstance();
	if(_s->NType==MNT_MinusExpression ||_s->NType==MNT_PlusExpression||_s->NType==MNT_ArrayDeclare||_s->NType==MNT_DictDeclare||_s->NType==MNT_FunctionCall){
		MError::CreateInstance()->PrintError("Invalid left-hand side in assignment");//被赋值的左值无效	
	} 
	




	if(_s->NType==MNT_ArrayElement){
		ArrayElement* ae = STATICCAST(ArrayElement,_s);
		ae->SetOpt(2);

	}
	if(_s->NType==MNT_DictElement){
		DictElemenet* ae = STATICCAST(DictElemenet,_s);
		ae->SetOpt(2);
	}
	if(_s->NType==MNT_ModuleExpresson){
		ModuleExpresson* ae = STATICCAST(ModuleExpresson,_s);
		ae->SetOpt(2);
	}
	
	e = _e;
	s = _s;
	oper = _oper;
	NType = MNT_AssignmentDefinition;
	wfileaddressline = lineno;
	_e->ParentNode=this;
	_s->ParentNode=this;
	t= _t;
}
AssignmentDefinition::~AssignmentDefinition(){

	if(s && t){
		s->Release();
	}
	if(e){
		e->Release();
	}
}
void AssignmentDefinition:: CreateCode()
{


	StatementList* sl = StatementList::GetInstance();
	/*
	Statement* p = this;
	ISTOPLEVLE(p)

	if ((e->NType == MNT_FunctionCall || e->NType == MNT_PackAgeFunCall) && sl->IsGlobalVar(s->name) && p == 0){
		MError::CreateInstance()->PrintError("Function calls cannot be assigned to global variables " + s->name);
	}*/
	bytenumber = sl->GetIpi();

	if(s->NType==MNT_VarIdentIfier)
	{
		e->CreateCode();
		name =s->name;
		bool isgvar = sl->IsGlobalVar(name);
		if(!isgvar){
			LocalVarAttr lva = sl->FindLocalMemory(name);
			if(lva.index==-1)
			{
 					MError::CreateInstance()->PrintError(name+" undeclared identifier",wfileaddressline);	//未找到
			}else
			{
				sl->AddCode(OP_STORES,wfileaddressline);
				sl->AddCode(lva.index,wfileaddressline);
				//sl->StackID++;
			}
		}else
		{
				if(sl->FindGlobalMemory(name).hash==-1){
					MError::CreateInstance()->PrintError(string(name +string(" undeclared identifier")),wfileaddressline);//未找到	
				}
				sl->AddCode(OP_STOREM,wfileaddressline);
				sl->AddCode(MCommon::CreateInstance()->ELFHash(name),wfileaddressline);

		}
		//sl->StackID++;
	}
	if(s->NType==MNT_ArrayElement){
		SAVESTACKID
		e->CreateCode();
		s->CreateCode();
		RESTORESTACKID
		sl->StackID++;
	}
	if(s->NType==MNT_DictElement)
	{
		SAVESTACKID
		e->CreateCode();
		s->CreateCode();
		RESTORESTACKID	
		sl->StackID++;
	}	
	if(s->NType==MNT_ModuleExpresson)
	{
		SAVESTACKID
		e->CreateCode();
		s->CreateCode();
		RESTORESTACKID	
		sl->StackID++;
	}	
}

void AssignmentDefinition::Release()
{
	
	DELETETHIS
}

InitializationDefinition::InitializationDefinition(Statement * _name,Statement * _e):btd(0)
{
	StatementList* sl = StatementList::GetInstance();
	e = _e;
	if(e==0){
		btd =new BuiltinTypeDeclare();
		btd->SetNull();	
		e = btd;
	}
	n = _name;
	name = _name->name;
	NType = MNT_InitializationExpression;
	wfileaddressline = lineno;
	e->ParentNode=this;
}
InitializationDefinition::~InitializationDefinition(){
	if(e){
		e->Release();
		btd=0;
	}
	if(btd){
		btd->Release();
	}

	n->Release();
}
void InitializationDefinition::CreateCode()
{
		StatementList* sl = StatementList::GetInstance();


		bytenumber = sl->GetIpi();

		SAVESTACKID
		e->CreateCode();

		if(scope==GLOBAL && !sl->AddGlobalMemory(name))
		{
			MError::CreateInstance()->PrintError(name+" redefinition",wfileaddressline);
		}
		
		if(scope==LOCAL)
		{
			if(!sl->AddLocalMemory(name,wfileaddressline))
			{
				MError::CreateInstance()->PrintError(name+" redefinition",wfileaddressline);
			}
		}
		if(scope==GLOBAL)
		{
			
			sl->AddCode(OP_INITM,wfileaddressline);
			sl->AddCode(sl->FindGlobalMemory(name).hash,wfileaddressline);
		}
		RESTORESTACKID	
		if(scope==LOCAL)
		{
			sl->StackID++;
		}
}
void InitializationDefinition::ModfiyScope(Scope _scope)
{
	scope = _scope;
}

void InitializationDefinition::Release()
{
	
	DELETETHIS
}

NodeType InitializationDefinition::GetRightNodeType()
{
	return e->NType;	 
}
BuiltinTypeDeclare::BuiltinTypeDeclare()
{
	NType = MNT_BuiltinTypeDeclare;
	wfileaddressline = lineno;
}


BuiltinTypeValue BuiltinTypeDeclare::GetBuiltinTypeValue()
{
	return v;
}
void BuiltinTypeDeclare::SetNull()
{
	v.v = M_NULL;
	v.i=0;
}

void BuiltinTypeDeclare::SetNumber(int n)
{
	v.v = M_NUMBER;
	v.i = n;
}
void BuiltinTypeDeclare::SetDouble(double d)
{
	v.v = M_DOUBLE;
	v.d = d;
}
void BuiltinTypeDeclare::SetString(string str)
{
	StatementList* sl = StatementList::GetInstance();
	sl->AddStringConstant(str);
	v.v = M_STRING;
	v.str = str;
}

void BuiltinTypeDeclare::SetFunctionPointerOrModule(string str, int type)
{
	StatementList* sl = StatementList::GetInstance();
	if (sl->IsHasModuleName(str) != -1)
	{
		v.v = M_MODULE;
		v.i = sl->IsHasModuleName(str);
	}else{
		v.v = M_FUN;
		functionname =str;
	}

}

void BuiltinTypeDeclare::SetBool(bool b)
{
	v.v = M_BOOL;
	if(b)
		v.i = 1;
	else
		v.i = 0;
}

void BuiltinTypeDeclare::CreateCode()
{
	StatementList* sl = StatementList::GetInstance();
	bytenumber = sl->GetIpi();
	if(v.v==M_NUMBER){
		sl->AddCode(OP_PUSHNUMBER,wfileaddressline);
		sl->AddCode(v.i,wfileaddressline);
	    
	}
	if(v.v==M_DOUBLE){
		sl->AddCode(OP_PUSHDOUBLE,wfileaddressline);
		int doubleindex = sl->FindDoubleConstant(v.d);
		sl->AddCode(doubleindex,wfileaddressline);
	    
	}
	if(v.v==M_STRING){
		sl->AddCode(OP_PUSHSTRING,wfileaddressline);
		int strindex = sl->FindStringConstant(v.str);
		sl->AddCode(strindex,wfileaddressline);
		
	}
	if(v.v==M_BOOL){
		sl->AddCode(OP_PUSHBOOL,wfileaddressline);
		sl->AddCode(v.i,wfileaddressline);
	}
	if(v.v==M_NULL){
		sl->AddCode(OP_PUSHRS,wfileaddressline);

	}
	if(v.v==M_FUN ){
		if((v.i =sl->FindFunction(functionname))==-1){
			MError::CreateInstance()->PrintError(functionname + " is not defined", wfileaddressline);
		}

		sl->AddCode(OP_PUSHFUN,wfileaddressline);
		sl->AddCode(v.i,wfileaddressline);
	}

	if (v.v == M_MODULE){
		sl->AddCode(OP_PUSHMODULE, wfileaddressline);
		sl->AddCode(v.i,wfileaddressline);
	}
	sl->StackID++;
}

void BuiltinTypeDeclare::Release()
{
	
	DELETETHIS
}


ArithmeticExpressionDefinition::ArithmeticExpressionDefinition(Statement* _s1,string _op,Statement* _s2)
{
	s1 = _s1;
	op=_op;
	s2=_s2;
	NType =MNT_ArithmeticExpressionDefinition;
	wfileaddressline = lineno;

	_s1->ParentNode =this;
	_s2->ParentNode =this;
}
ArithmeticExpressionDefinition::~ArithmeticExpressionDefinition()
{
	if(s1){
		s1->Release();
	}
	if(s2){
		s2->Release();
	}
}
void ArithmeticExpressionDefinition::CreateCode()
{
	StatementList* sl = StatementList::GetInstance();
	bytenumber = sl->GetIpi();
	s1->CreateCode();
	s2->CreateCode();
	if(!strcmp(op.c_str(),"+")){
		sl->AddCode(OP_ADD,wfileaddressline);
   }
   if(!strcmp(op.c_str(),"-")){
		sl->AddCode(OP_SUB,wfileaddressline);
   }
   if(!strcmp(op.c_str(),"*")){
		sl->AddCode(OP_MUL,wfileaddressline);
   }
   if(!strcmp(op.c_str(),"/")){
		sl->AddCode(OP_DIV,wfileaddressline);
   }
   if(!strcmp(op.c_str(),"<")){
		sl->AddCode(OP_LT,wfileaddressline);
   }
   if(!strcmp(op.c_str(),">")){
		sl->AddCode(OP_LE,wfileaddressline);
   }
   if(!strcmp(op.c_str(),">=")){
		sl->AddCode(OP_GEEQ,wfileaddressline);
   }  
   if(!strcmp(op.c_str(),"<=")){
		sl->AddCode(OP_LEEQ,wfileaddressline);
   }   		
   if(!strcmp(op.c_str(),"==")){
		sl->AddCode(OP_EQEQ,wfileaddressline);
   }  
   if(!strcmp(op.c_str(),"<>")){
		sl->AddCode(OP_NEQ,wfileaddressline);
   } 
   if(!strcmp(op.c_str(),"%")){
		sl->AddCode(OP_MOD,wfileaddressline);
   } 
   
   if(!strcmp(op.c_str(),"<<")){
		sl->AddCode(OP_SHIFTL,wfileaddressline);
   }
   if(!strcmp(op.c_str(),">>")){
		sl->AddCode(OP_SHIFTR,wfileaddressline);
   }
   if(!strcmp(op.c_str(),"**")){
		sl->AddCode(OP_POWER,wfileaddressline);
   }

   sl->StackID = sl->StackID-1;
	//sl->StackID++;
}

void ArithmeticExpressionDefinition::Release()
{
	
	DELETETHIS
}


IfStatement::IfStatement(int t)
{
	Member = new vector <Statement*>();
	NType =MNT_IfStatement;
	wfileaddressline = lineno;
	type = t;
}
void IfStatement:: AddChilder(Statement* s)
{
	if(s){
		s->ParentNode = this;
		Member->push_back(s);
	}
	
}
IfStatement::~IfStatement()
{
	DESTRUCTORRELEASE
	delete Member;
}

void IfStatement::CreateCode()
{
	StatementList* sl = StatementList::GetInstance();
	bytenumber = sl->GetIpi();
	
	if(type==0){

		int sopcelocalvars = sl->GetLocalCountValue();
		SAVESTACKID
		//for (std::vector<Statement*>::iterator it = Member->begin() ; it != Member->end(); ++it)
		//{	
		VECTORFORSTART(Statement*,Member,it)
			(*it)->CreateCode();

			if(it-Member->begin()==0)
			{
				sl->AddCode(OP_JMP,wfileaddressline);
				postion1=sl->GetIpi();
				sl->AddCode(OP_NOP,wfileaddressline);
				sl->StackID--;
			}
		//}
		VECTORFOREND
		sl->SetCode(sl->GetIpi()-postion1,postion1);
		RESTORESTACKID
		sl->GetLocalMemory()->resize(sopcelocalvars);
		sl->SetLocalCountValue(sopcelocalvars);

	}

	if(type==1){
		
		//for (std::vector<Statement*>::iterator it = Member->begin() ; it != Member->end(); ++it)
		//{	
		VECTORFORSTART(Statement*,Member,it)	
			
			if(it-Member->begin()==0)
			{
				SAVESTACKID
				(*it)->CreateCode(); //this is if statment condition
				sl->AddCode(OP_JMP,wfileaddressline);
				postion1=sl->GetIpi();
				sl->AddCode(OP_NOP,wfileaddressline);//this is else postion
				sl->StackID--;
				RESTORESTACKID
			}			
			if(it-Member->begin()==1){
				//if the condition is true,then code run,in end,jmp
				int sopcelocalvars = sl->GetLocalCountValue();
				SAVESTACKID
				(*it)->CreateCode();
				sl->AddCode(OP_ADJUSTSP,wfileaddressline);
				sl->AddCode(_tempstackid,wfileaddressline);
				sl->AddCode(OP_UJMP,wfileaddressline);
				postion2=sl->GetIpi();
				sl->AddCode(OP_NOP,wfileaddressline);
				RESTORESTACKID
				sl->GetLocalMemory()->resize(sopcelocalvars);
				sl->SetLocalCountValue(sopcelocalvars);

			}

			if(it-Member->begin()==2){
				int sopcelocalvars = sl->GetLocalCountValue();
				SAVESTACKID
				sl->SetCode(sl->GetIpi()-postion1,postion1); // set else postion
				(*it)->CreateCode();
				RESTORESTACKID
				sl->GetLocalMemory()->resize(sopcelocalvars);
				sl->SetLocalCountValue(sopcelocalvars);

			}
		//}
		VECTORFOREND
		sl->SetCode(sl->GetIpi()-postion2,postion2);		
	}

}

void IfStatement::Release()
{
	
	DELETETHIS
}

WhileStatement::WhileStatement()
{
	Member = new vector <Statement*>();
	NType =MNT_WhileStatement;
	wfileaddressline = lineno;
	breakpostionvector =new vector<int>();
}
WhileStatement::~WhileStatement()
{
	DESTRUCTORRELEASE
	delete breakpostionvector;
	delete Member;
}
void WhileStatement:: AddChilder(Statement* s)
{
	if(s)
	{
		s->ParentNode = this;
		Member->push_back(s);
	}
	
}
int WhileStatement::GetTemplateid()
{
	return templateid;
}
void WhileStatement::CreateCode()
{
	StatementList* sl = StatementList::GetInstance();
	bytenumber = sl->GetIpi();
	int sopcelocalvars = sl->GetLocalCountValue();
	SAVESTACKID
	templateid = _tempstackid;
	//for (std::vector<Statement*>::iterator it = Member->begin() ; it != Member->end(); ++it)
	//{
	VECTORFORSTART(Statement*,Member,it)
		if(it-Member->begin()==0)
		{	
			postion1=sl->GetIpi(); //while开始位置，判断部分
			(*it)->CreateCode();	
			sl->AddCode(OP_JMP,wfileaddressline); //如果是FALSE 的跳转位置
			postion2=sl->GetIpi();
			sl->AddCode(OP_NOP,wfileaddressline);
			sl->StackID--;
		}
		if(it-Member->begin()==1){ //while的内容部分
			(*it)->CreateCode();
			sl->AddCode(OP_ADJUSTSP,wfileaddressline);
			sl->AddCode(_tempstackid,wfileaddressline);
			sl->AddCode(OP_UJMPS,wfileaddressline); //无条件跳转回开始位置
			sl->AddCode(sl->GetIpi()-postion1,wfileaddressline);
		}
	//}
	VECTORFOREND
	int endip = sl->GetIpi();
	sl->SetCode(endip-postion2,postion2);
	//for (std::vector<int>::iterator it = breakpostionvector->begin() ; it != breakpostionvector->end(); ++it)
	//{
	VECTORFORSTART(int,breakpostionvector,it)
			sl->SetCode(endip-(*it),(*it));
	//}
	VECTORFOREND
	RESTORESTACKID
	sl->GetLocalMemory()->resize(sopcelocalvars);
	sl->SetLocalCountValue(sopcelocalvars);
	
}

int WhileStatement::GetJmpPostion()
{
	return postion1;
}
void WhileStatement::SetBreakPostion(int b)
{
	breakpostionvector->push_back(b);
}

void WhileStatement::Release()
{
	
	DELETETHIS
}

ForStatement::ForStatement(Statement* _assignment,Statement* _expression,Statement* _userexpression)
{
	NType =MNT_ForStatement;
	wfileaddressline = lineno;
	assignment =_assignment;
	expression =_expression;
	userexpression = _userexpression;
	if(assignment->NType!=MNT_InitializationList){
		MError::CreateInstance()->PrintError("for ",wfileaddressline);
	}
	assignment ->ParentNode = this;
	expression->ParentNode = this;
	userexpression ->ParentNode = this;
	breakpostionvector =new vector<int>();
}
ForStatement::~ForStatement()
{
	if(assignment)
	assignment->Release();

	if(expression)
	expression->Release();

	if(userexpression)
	userexpression->Release();

	delete breakpostionvector;
}
void ForStatement::CreateCode()
{
	StatementList* sl = StatementList::GetInstance();
	
	sopcelocalvars = sl->GetLocalCountValue();
	SAVESTACKID
	templateid = _tempstackid;
	
	//压入集合
	expression->CreateCode();	
	
	//压入临时的复制变量
	assignment->CreateCode();
	//赋值表达式的stackid
	int assigmentindex = sl->StackID;

	//压入一个变量，当作集合的索引
	sl->AddCode(OP_PUSHNUMBER,wfileaddressline);
	sl->AddCode(0,wfileaddressline);
	sl->StackID++;
	int index = sl->StackID;

	postion1 = sl->GetIpi();
	//获取集合内容

	sl->AddCode(OP_GETSEQ,wfileaddressline);
	InitializationList * initializtionlist = STATICCAST(InitializationList,assignment);
	int pcount = initializtionlist->Member->size();
	sl->AddCode(pcount);
	postion2 = sl->GetIpi();
	sl->AddCode(OP_NOP,wfileaddressline); //如果超出索引范围，这跳出循环
	//把内容存入前面的临时变量
	//sl->AddCode(OP_STORES);
	//sl->AddCode(assigmentindex,wfileaddressline);
	//sl->StackID+=pcount;
	//索引增加1


	/*sl->AddCode(OP_ADD1,wfileaddressline);
	sl->AddCode(index,wfileaddressline);*/
	//执行正式代码，以上都是初始化的过程,执行用户代码
	userexpression->CreateCode();

	sl->AddCode(OP_ADJUSTSP,wfileaddressline);
	sl->AddCode(_tempstackid+2+pcount,wfileaddressline);


	sl->AddCode(OP_UJMPS,wfileaddressline);
	sl->AddCode(sl->GetIpi()-postion1,wfileaddressline);



	sl->SetCode(sl->GetIpi()-postion2,postion2);


	sl->AddCode(OP_ADJUSTSP,wfileaddressline);
	sl->AddCode(_tempstackid,wfileaddressline);


	int endip = sl->GetIpi();

	//for (std::vector<int>::iterator it = breakpostionvector->begin() ; it != breakpostionvector->end(); ++it)
	//{
	VECTORFORSTART(int,breakpostionvector,it)
			sl->SetCode(endip-(*it),(*it));
	//}
	VECTORFOREND
	RESTORESTACKID
	sl->GetLocalMemory()->resize(sopcelocalvars);
	sl->SetLocalCountValue(sopcelocalvars);
}

int ForStatement::GetJmpPostion()
{
	
	return postion1;
}

int ForStatement::GetTemplateid()
{
	return templateid+3;
}

void ForStatement::SetBreakPostion(int b)
{
	breakpostionvector->push_back(b);
}
void ForStatement::Release()
{
	
	DELETETHIS
}

ArrayDeclare::ArrayDeclare(Statement* _s)
{
	expressionlist = _s;
	NType =MNT_ArrayDeclare;
	wfileaddressline = lineno;
	_s->ParentNode =this;
}
ArrayDeclare::~ArrayDeclare(){

	if(expressionlist)
	expressionlist->Release();
}
void ArrayDeclare::CreateCode()
{
	StatementList* sl = StatementList::GetInstance();
			
	bytenumber = sl->GetIpi();
	sl->AddCode(OP_CREATEARRAY,wfileaddressline);
	SAVESTACKID
	expressionlist->CreateCode();
	sl->AddCode(OP_SETARRAY,wfileaddressline);
	sl->AddCode(STATICCAST(ExpressionList,expressionlist)->ExpressionSize(),wfileaddressline);
	RESTORESTACKID
	sl->StackID++;
}
void ArrayDeclare::Release()
{
	
	DELETETHIS
}



ArrayElement::ArrayElement(Statement* _ar,Statement* _index,int _gettype):index2(0)
{
	ar=_ar;
	index =_index;
	NType =MNT_ArrayElement;
	gettype=_gettype;
	_ar->ParentNode =this;
	_index->ParentNode =this;
	wfileaddressline = lineno;

}
ArrayElement::ArrayElement(Statement* _ar,Statement* _index,Statement* _index2)
{
	ar=_ar;
	index =_index;
	index2 =_index2;
	NType =MNT_ArrayElement;
	gettype=3;
	_ar->ParentNode =this;
	_index->ParentNode =this;
	_index2->ParentNode =this;
}
ArrayElement::~ArrayElement()
{
	if(ar)
	ar->Release();

	if(index)
	index->Release();

	if(index2)
	index2->Release();
}
void ArrayElement::SetOpt(int i)
{
	opt = i;
}
void ArrayElement::CreateCode()
{
	StatementList* sl = StatementList::GetInstance();
	SAVESTACKID
	ar->CreateCode();
	index->CreateCode();

	if(opt==2){
		sl->AddCode(OP_SETARRAYELEMENT,wfileaddressline);
	}

	if(opt==1){
		if(gettype==3)
		{
			index2->CreateCode();
		}else{
			sl->AddCode(OP_PUSHRS,wfileaddressline);
			sl->StackID++;
		}
		sl->AddCode(OP_PUSHNUMBER,wfileaddressline);
		sl->AddCode(gettype,wfileaddressline);
		sl->StackID++;
	
		sl->AddCode(OP_GETARRAYELEMENT,wfileaddressline);
	}


	RESTORESTACKID
	sl->StackID++;
	

}

void ArrayElement::Release()
{
	
	DELETETHIS
}

DictExpression::DictExpression(string _k,Statement* _v)
{
	key = _k;
	StatementList::GetInstance()->AddStringConstant(key);
	StatementList::GetInstance()->AddDictKeyConstant(key);
	value  = _v;
	_v->ParentNode =this;
	NType = MNT_DictExpression;
	wfileaddressline = lineno;
}
DictExpression::~DictExpression()
{
	if(value)
	value->Release();
}
void DictExpression::CreateCode()
{
	StatementList* sl = StatementList::GetInstance();
	value->CreateCode();
	sl->AddCode(OP_PUSHHASH,wfileaddressline);
	sl->AddCode(MCommon::CreateInstance()->ELFHash(key),wfileaddressline);

}

void DictExpression::Release()
{
	
	DELETETHIS
}



DictStatement::DictStatement()
{
	Member = new vector <Statement*>();
	NType = MNT_DictDeclare;
	wfileaddressline = lineno;
}
void DictStatement::AddChilder(Statement* s)
{
	s->ParentNode = this;
	Member->push_back(s);
}
DictStatement::~DictStatement()
{
	DESTRUCTORRELEASE
	delete Member;
}
void DictStatement::CreateCode()
{
	StatementList* sl = StatementList::GetInstance();
	SAVESTACKID	
	sl->AddCode(OP_CREATEDICT,wfileaddressline);
	//for (std::vector<Statement*>::iterator it = Member->begin() ; it != Member->end(); ++it)
	//{
	VECTORFORSTART(Statement*,Member,it)
		(*it)->CreateCode();
	VECTORFOREND
	//}
	sl->AddCode(OP_SETDICT,wfileaddressline);
	sl->AddCode(Member->size(),wfileaddressline);
	RESTORESTACKID
	sl->StackID++;

}
void DictStatement::Release()
{
	
	DELETETHIS
}




DictElemenet::DictElemenet(Statement* _exprssion,string _key)
{
	exprssion = _exprssion;
	key = _key;
	StatementList::GetInstance()->AddStringConstant(key);
	StatementList::GetInstance()->AddDictKeyConstant(key);
	NType =MNT_DictElement;
	_exprssion->ParentNode =this;
	wfileaddressline = lineno;
}
DictElemenet::~DictElemenet()
{
	if(exprssion)
	exprssion->Release();
}
void DictElemenet::CreateCode()
{
	StatementList* sl = StatementList::GetInstance();
	SAVESTACKID	
	exprssion->CreateCode();
	if(opt==1){
		sl->AddCode(OP_GETDICTELEMENT,wfileaddressline);
		

	}
	if(opt==2){
		sl->AddCode(OP_SETDICTELEMENT,wfileaddressline);
	}
	sl->AddCode(MCommon::CreateInstance()->ELFHash(key),wfileaddressline);

	RESTORESTACKID
	sl->StackID++;
}
void DictElemenet::SetOpt(int i)
{
	opt = i;
}

void DictElemenet::Release()
{
	
	DELETETHIS
}

ContinueExpression::ContinueExpression()
{
	NType =MNT_ContinueExpression;
	wfileaddressline = lineno;
	
}
void ContinueExpression::CreateCode()
{
	StatementList* sl = StatementList::GetInstance();
	bytenumber = sl->GetIpi();
	Statement* p = this;
	FINDPARENT(p)
	if(!p)
	{
		MError::CreateInstance()->PrintError("continue keyword can only be used in the for,while statement",wfileaddressline);
	}
	
	if(p->NType==MNT_WhileStatement)
	{		
		WhileStatement* w =STATICCAST(WhileStatement,p);

		sl->AddCode(OP_ADJUSTSP,wfileaddressline);
		sl->AddCode(w->GetTemplateid(),wfileaddressline);
		sl->AddCode(OP_UJMPS,wfileaddressline);
		sl->AddCode(sl->GetIpi()-w->GetJmpPostion(),wfileaddressline);
	}

	if(p->NType==MNT_ForStatement)
	{
		ForStatement* w =STATICCAST(ForStatement,p);
		sl->AddCode(OP_ADJUSTSP,wfileaddressline);
		sl->AddCode(w->GetTemplateid(),wfileaddressline);
		sl->AddCode(OP_UJMPS,wfileaddressline);
		//int ip = sl->GetIpi();
		//sl->AddCode(OP_NOP);

		sl->AddCode(sl->GetIpi()-w->GetJmpPostion(),wfileaddressline);
	}
}



void ContinueExpression::Release()
{
	
	DELETETHIS
}


BreakExpression::BreakExpression()
{
	NType =MNT_BreakExpression;
	wfileaddressline = lineno;
	
}
void BreakExpression::CreateCode()
{
	StatementList* sl = StatementList::GetInstance();
	bytenumber = sl->GetIpi();
	Statement* p = this;
	FINDPARENT(p)
	if(!p)
	{
		MError::CreateInstance()->PrintError("Break keyword can only be used in the for,while statement",wfileaddressline);
	}
	
	if(p->NType==MNT_WhileStatement)
	{
		WhileStatement* w =STATICCAST(WhileStatement,p);
		sl->AddCode(OP_ADJUSTSP,wfileaddressline);
		sl->AddCode(w->GetTemplateid(),wfileaddressline);
		sl->AddCode(OP_UJMP,wfileaddressline);
		jmppostion = sl->GetIpi();
		sl->AddCode(OP_NOP,wfileaddressline);
		w->SetBreakPostion(jmppostion);
	}
	if(p->NType==MNT_ForStatement)
	{
		ForStatement* w =STATICCAST(ForStatement,p);
		sl->AddCode(OP_ADJUSTSP,wfileaddressline);
		sl->AddCode(w->GetTemplateid(),wfileaddressline);
		sl->AddCode(OP_UJMP,wfileaddressline);
		jmppostion = sl->GetIpi();
		sl->AddCode(OP_NOP,wfileaddressline);
		w->SetBreakPostion(jmppostion);
	}

}

int BreakExpression::GetBreakJmpPostion()
{
	return jmppostion;
}


void BreakExpression::Release()
{
	
	DELETETHIS
}



FunctionCall::FunctionCall(Statement* _perfix,Statement* s)
{
	perfix = _perfix;
	ag = s;
	_perfix->ParentNode =this;
	s->ParentNode =this;
	NType = MNT_FunctionCall;
	wfileaddressline = lineno;
}
FunctionCall::~FunctionCall()
{
	if(perfix)
	perfix->Release();

	if(ag)
	ag->Release();
}
void FunctionCall::CreateCode()
{
	
	StatementList* sl = StatementList::GetInstance();
	

	sl->AddCode(OP_PUSHRS,wfileaddressline);
	sl->StackID++;
	SAVESTACKID
	//sl->AddCode(OP_ADJUSTBP);
	sl->AddCode(OP_PUSHMARK,wfileaddressline);
	FunctionArguments* fas = STATICCAST(FunctionArguments,ag);
	sl->AddCode(fas->FunctionArgumentsCount(),wfileaddressline);
	if(ag){
		ag->CreateCode();
	}

	perfix->CreateCode();
	sl->AddCode(OP_CALLFUNC,wfileaddressline);
	RESTORESTACKID

}
void FunctionCall::Release()
{
	
	DELETETHIS
}


FunctionArguments::FunctionArguments()
{
	Member = new vector <Statement*>();
	NType = MNT_FunctionArguments;
	wfileaddressline = lineno;
}
FunctionArguments::~FunctionArguments()
{
	DESTRUCTORRELEASE
	delete Member;
}
int FunctionArguments::FunctionArgumentsCount()
{
	return Member->size();
}

void FunctionArguments::AddChilder(Statement* s)
{
	s->ParentNode = this;
	Member->push_back(s);
}

void FunctionArguments::CreateCode()
{
	StatementList* sl = StatementList::GetInstance();
	//for (std::vector<Statement*>::iterator it = Member->begin() ; it != Member->end(); ++it)
	//{
	VECTORFORSTART(Statement*,Member,it)
		(*it)->CreateCode();
	VECTORFOREND
	//}
}
void FunctionArguments::Release()
{
	
	DELETETHIS
}



LogiceEpressionDefintion::LogiceEpressionDefintion(Statement* _s1,string _op,Statement* _s2)
{
	s1 =_s1;
	op = _op;
	s2 = _s2;
	_s1->ParentNode=this;
	_s2->ParentNode=this;
	NType = MNT_LogiceEpressionDefintion;
	wfileaddressline = lineno;
}
LogiceEpressionDefintion::~LogiceEpressionDefintion()
{
	if(s1)
	s1->Release();

	if(s2)
	s2->Release();
}
void LogiceEpressionDefintion::CreateCode()
{
	StatementList* sl = StatementList::GetInstance();
	s1->CreateCode();
	
	s2->CreateCode();

	if(op =="|"){
		sl->AddCode(OP_BIT_OR,wfileaddressline);
	}
	if(op =="&"){
		sl->AddCode(OP_BIT_AND,wfileaddressline);
	}
	if(op =="||"){
		sl->AddCode(OP_OR,wfileaddressline);
	}
	if(op =="&&"){
		sl->AddCode(OP_AND,wfileaddressline);
	}
	if(op =="^"){
		sl->AddCode(OP_XOR,wfileaddressline);
    }
	sl->StackID--;
}
void LogiceEpressionDefintion::Release()
{
	DELETETHIS
}




ReturnExpression::ReturnExpression()
{
	NType =MNT_ReturnExpression;
	wfileaddressline = lineno;
	btd =new BuiltinTypeDeclare();
	btd->SetNull();
	s = btd;
	type = 1;
}

ReturnExpression::ReturnExpression(Statement* _s)
{
	NType =MNT_ReturnExpression;
	type=0;
	wfileaddressline = lineno;
	s = _s;  //if return has value the _s nonzero,otherwise _s is 0
	if(_s)
	_s->ParentNode=this;
}
ReturnExpression::~ReturnExpression()
{
	if(type){
		delete btd;
	}else
	{
		if(s){
			s->Release();
		}
	}
}
void ReturnExpression::CreateCode()
{
	StatementList* sl = StatementList::GetInstance();
	if(s){
		s->CreateCode();
	}
		sl->AddCode(OP_RET,wfileaddressline);
}

void ReturnExpression::Release()
{
	DELETETHIS
}


TryStatement::TryStatement(Statement* _s1,Statement* _s2,Statement* _s3){
	s1 =_s1;//try内容
	s2=_s2;//except参数
	s3=_s3;//except内容
	if(_s1)
	{
		_s1->ParentNode = this;
	}
	_s2->ParentNode=this;
	if(_s3)
	{
		_s3->ParentNode = this;
	}
	NType = MNT_TryStatement;
	wfileaddressline = lineno;
}
TryStatement::~TryStatement()
{
	if(s1)
	s1->Release();

	if(s2)
	s2->Release();

	if(s3)
	s3->Release();
}
void TryStatement::CreateCode()
{
	StatementList* sl = StatementList::GetInstance();
	int trymarkid = sl->StackID;
	sl->AddCode(OP_PUSHTRYMARK,wfileaddressline);
	sl->StackID++;
	int i1 = sl->GetIpi(); //记录except的代码地址
	sl->AddCode(OP_NOP,wfileaddressline);//return表示except内的地址，paramercount表示excetp的参数数量
	int i2 = sl->GetIpi(); //记录except的参数的代码地址
	sl->AddCode(OP_NOP,wfileaddressline);//paramercount表示excetp的参数数量 


	sopcelocalvars = sl->GetLocalMemory()->size();
	SAVESTACKID
	s1->CreateCode();//try code
	RESTORESTACKID
	sl->SetLocalCountValue(sopcelocalvars);
	sl->GetLocalMemory()->resize(sopcelocalvars);
	//sl->AddCode(OP_ADJUSTSP,wfileaddressline);
	//sl->AddCode(_tempstackid,wfileaddressline);


	sl->AddCode(OP_UJMP,wfileaddressline);
	int i3 = sl->GetIpi();//记录try except后的第一句的代码地址
	sl->AddCode(OP_NOP,wfileaddressline);

	{
		sopcelocalvars = sl->GetLocalMemory()->size();
		SAVESTACKID
		s2->CreateCode();
		TryParameterStatement* tps =STATICCAST(TryParameterStatement,s2);
		sl->SetCode(tps->Count(),i2);//更新except的参数数量的代码地址

		sl->SetCode(sl->GetIpi()-i1,i1);//更新except的代码地址
		s3->CreateCode();
		RESTORESTACKID
		sl->SetLocalCountValue(sopcelocalvars);
		sl->GetLocalMemory()->resize(sopcelocalvars);
		//sl->AddCode(OP_ADJUSTSP,wfileaddressline);
		//sl->AddCode(_tempstackid,wfileaddressline);
	}
	sl->SetCode(sl->GetIpi()-i3,i3);//更新try except后的第一句的代码地址
	sl->AddCode(OP_ADJUSTSP,wfileaddressline);
	sl->AddCode(trymarkid,wfileaddressline);
	sl->StackID = trymarkid;	
}

void TryStatement::Release()
{
	
	DELETETHIS
}


ThrowExpression::ThrowExpression(Statement* _s)
{
	NType =MNT_ThrowExpression;
	wfileaddressline = lineno;
	s=_s;
	_s->ParentNode=this;
}
ThrowExpression::~ThrowExpression(){
	if(s)
	s->Release();
}
void ThrowExpression::CreateCode()
{
	StatementList* sl = StatementList::GetInstance();
	sl->AddCode(OP_THROWSTART,wfileaddressline);
	s->CreateCode();
	sl->AddCode(OP_THROWEND,wfileaddressline);
}

void ThrowExpression::Release()
{
	
	DELETETHIS
}


TryParameter::TryParameter(string s){
	wfileaddressline = lineno;
	name = s;
	NType = MNT_TryParameter;
	
}
void TryParameter::CreateCode()
{
	StatementList* sl = StatementList::GetInstance();
	sl->StackID++;
	if(!sl->AddLocalMemory(name,wfileaddressline))
	{
		MError::CreateInstance()->PrintError(name+" redefinition",wfileaddressline);
	}
}

void TryParameter::Release()
{
	
	DELETETHIS
}

TryParameterStatement::TryParameterStatement()
{
	Member=new vector<Statement*>();
	NType = MNT_FunctionParameterStatement;
	wfileaddressline = lineno;
}
TryParameterStatement::~TryParameterStatement()
{
	DESTRUCTORRELEASE
	delete Member;
}
void TryParameterStatement::AddChilder(Statement*  s)
{
	s->ParentNode=this;
	Member->push_back(s);
}
void TryParameterStatement::CreateCode()
{

	StatementList* sl = StatementList::GetInstance();
	//for (std::vector<Statement*>::iterator it = Member->begin() ; it != Member->end(); ++it)
	//{	
	VECTORFORSTART(Statement*,Member,it)
		(*it)->CreateCode();
	VECTORFOREND
	//}

}
int TryParameterStatement::Count()
{
	return  Member->size();
}

void TryParameterStatement::Release()
{
	
	DELETETHIS
}




ImportPackageExpression::ImportPackageExpression(string _s)
{
	StatementList* sl = StatementList::GetInstance();
	NType = MNT_ImportPackageExpression;
	wfileaddressline = lineno;
	filename = _s;
	sl->AddToIncludeFile(filename);
}

void ImportPackageExpression::Release()
{
	DELETETHIS
}


ModuleExpresson::ModuleExpresson(Statement* _exprssion,string _key,Statement* _arguments,int _type,int _opt)
{
	wfileaddressline = lineno;
	exprssion = _exprssion;
	key = _key;
    arguments = _arguments;
	type = _type;
	NType =MNT_ModuleExpresson;
	opt = _opt;
	if(_exprssion)
	_exprssion->ParentNode = this;

	if(_arguments)
	_arguments->ParentNode = this;


}
ModuleExpresson::~ModuleExpresson()
{
	if(exprssion)
	exprssion->Release();

	if(arguments)
	arguments->Release();
}

void ModuleExpresson::SetOpt(int i)
{
	opt = i;
}

void ModuleExpresson::SetNType(NodeType i)
{
	NType = i;
}
void ModuleExpresson::CreateCode()
{
	StatementList* sl = StatementList::GetInstance();
	if(type==1){
		sl->AddCode(OP_PUSHRS,wfileaddressline);
		sl->StackID++;
		SAVESTACKID
		//sl->AddCode(OP_ADJUSTBP);
		sl->AddCode(OP_PUSHMARK,wfileaddressline);
		if(arguments){
			FunctionArguments* fas = STATICCAST(FunctionArguments,arguments);
			sl->AddCode(fas->FunctionArgumentsCount(),wfileaddressline);
		}else
		{
			sl->AddCode(0,wfileaddressline);
		}
		if(arguments){
			arguments->CreateCode();
		}
		
		exprssion->CreateCode();
	
		sl->AddCode(OP_PUSHMODULEFUNC, wfileaddressline);
		sl->AddCode(MCommon::CreateInstance()->ELFHash(key),wfileaddressline);
		sl->AddCode(OP_CALLFUNC,wfileaddressline);
		RESTORESTACKID
	}
	if(type==2){
		exprssion->CreateCode();
		if(opt==1){
			sl->AddCode(OP_GETMODULEATTER, wfileaddressline);
			sl->AddCode(MCommon::CreateInstance()->ELFHash(key),wfileaddressline);
		}
		if(opt==2){
			sl->AddCode(OP_SETMODULEATTER, wfileaddressline);
			sl->AddCode(MCommon::CreateInstance()->ELFHash(key),wfileaddressline);
		}
	}
	if(type==3){
		exprssion->CreateCode();
		sl->AddCode(OP_PUSHMODULEFUNC, wfileaddressline);
		sl->AddCode(MCommon::CreateInstance()->ELFHash(key),wfileaddressline);
	}
	

}
void ModuleExpresson::Release()
{	
	DELETETHIS
}


MinusExpression::MinusExpression(Statement* _exprssion):exprssion(0)
{
	wfileaddressline = lineno;
	exprssion = _exprssion;
	_exprssion->ParentNode =this;
	NType = MNT_MinusExpression;
}
MinusExpression::~MinusExpression()
{
	if(exprssion)
	exprssion->Release();

}
void MinusExpression::Release()
{	
	DELETETHIS
}
void MinusExpression::CreateCode()
{
	StatementList* sl = StatementList::GetInstance();
	exprssion->CreateCode();
	sl->AddCode(OP_MINUS,wfileaddressline);
}


PlusExpression::PlusExpression(Statement* _exprssion):exprssion(0)
{
	wfileaddressline = lineno;
	exprssion = _exprssion;
	_exprssion->ParentNode =this;
	NType = MNT_PlusExpression;
}
PlusExpression::~PlusExpression()
{
	if(exprssion)
	exprssion->Release();

}
void PlusExpression::Release()
{	
	DELETETHIS
}
void PlusExpression::CreateCode()
{
	StatementList* sl = StatementList::GetInstance();
	exprssion->CreateCode();
}


InverterExpression::InverterExpression(Statement* _exprssion):exprssion(0)
{
	wfileaddressline = lineno;
	exprssion = _exprssion;
	_exprssion->ParentNode =this;
	NType = MNT_InverterExpression;

}
InverterExpression::~InverterExpression()
{
	if(exprssion)
	exprssion->Release();

}
void InverterExpression::Release()
{	
	DELETETHIS
}
void InverterExpression::CreateCode()
{
	StatementList* sl = StatementList::GetInstance();
	exprssion->CreateCode();
	sl->AddCode(OP_INVERTER,wfileaddressline);
}

void NopExpression::Release()
{
	DELETETHIS
}
void NopExpression::CreateCode()
{
	StatementList* sl = StatementList::GetInstance();
	sl->AddCode(OP_NOP,wfileaddressline);
}


TypeOfExpression::TypeOfExpression(Statement* _exprssion):exprssion(0)
{
	wfileaddressline = lineno;
	exprssion = _exprssion;
	_exprssion->ParentNode =this;
	NType = MNT_TypeOfExpression;
}
TypeOfExpression::~TypeOfExpression()
{
	exprssion->Release();
}
void TypeOfExpression::Release()
{
	DELETETHIS
}
void TypeOfExpression::CreateCode()
{
	StatementList* sl = StatementList::GetInstance();
	exprssion->CreateCode();
	sl->AddCode(OP_TYPEOF,wfileaddressline);
}



ModuleStatementList::ModuleStatementList()
{
	Member = new vector <Statement*>();
	wfileaddressline = lineno;	
	NType = MNT_ModuleStatementList;
}
ModuleStatementList::~ModuleStatementList()
{
	DESTRUCTORRELEASE
	delete Member;
}
void ModuleStatementList::Release()
{
	DELETETHIS
}
void ModuleStatementList::CreateCode()
{
	VECTORFORSTART(Statement*, Member, it)
		(*it)->CreateCode();
	VECTORFOREND
}
void ModuleStatementList::AddChilder(Statement* s)
{
	if (s)
	{
		s->ParentNode = this;
	}
	Member->push_back(s);
}



ModuleDefine::ModuleDefine(string _modulename,Statement* _modulestatementlist)
{
	wfileaddressline = lineno;
	modulestatementlist = _modulestatementlist;
	_modulestatementlist->ParentNode = this;
	modulename = _modulename;
	NType = MNT_ModuleDefine;
	StatementList* sl = StatementList::GetInstance();
	sl->AddModuleList(modulename);
}

ModuleDefine::~ModuleDefine()
{
	modulestatementlist->Release();
}
void ModuleDefine::Release()
{
	DELETETHIS
}
void ModuleDefine::CreateCode()
{
	modulestatementlist->CreateCode();
}