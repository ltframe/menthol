#pragma once
#ifndef PARSER
#define PARSER
#include "header.h"
#include "StatementList.h"



#define DELETETHIS delete this;

#define DESTRUCTORRELEASE  for (std::vector<Statement*>::iterator it = Member->begin() ; it != Member->end(); ++it) {if(*it){(*it)->Release();}}
#define SAVESTACKID     int _tempstackid =sl->StackID;
#define RESTORESTACKID  sl->StackID = _tempstackid;

//上次用for循环递归出错,所以改成宏
/*
Statement* BreakExpression::FindParent(Statement* p)
{
	if(p->ParentNode==0)
	{
		return 0;
	}else
	{
		if(p->ParentNode->NType!=MNT_WhileStatement  && p->ParentNode->NType!=MNT_ForStatement)
		{
			FindParent(p->ParentNode);
		}else
		{
			return p->ParentNode;
		}
	}
	//return 0;
	
}*/
#define FINDPARENT(p) while(true){\
						if(p==0)\
						{\
							break;\
						}\
						if(p->NType!=MNT_WhileStatement  && p->NType!=MNT_ForStatement)\
						{\
							p = p->ParentNode;\
							continue;\
						}else\
						{\
							break;\
						}\
					 }

#define ISTOPLEVLE(p) while(true){\
						if(p==0)\
						{\
							break;\
						}\
						if(p->NType!=MNT_FunctionDefinition)\
						{\
							p = p->ParentNode;\
							continue;\
						}else\
						{\
							break;\
						}\
					 }

class ReturnExpression;

class Statement
{
public:
	virtual void CreateCode()=0;
	virtual void AddChilder(Statement* s){}
	virtual void Release()=0;
	NodeType NType;	
	Statement():ParentNode(0),bytenumber(0),startipi(0),endipi(0),ilength(0){}
	
	Statement* ParentNode;
	int wfileaddressline;
	int bytenumber;
	string name;
	int startipi;
	int endipi;
	int ilength;
};

class BuiltinTypeDeclare:public Statement{
public:
	BuiltinTypeDeclare();
	vector <Statement*> *GetStatements();
	void CreateCode();
	void SetNumber(int number);
	void SetDouble(double number);
	void SetString(string str);
	void SetBool(bool b);
	void SetNull();
	void SetFunctionPointerOrPack(string str,int type);
	void Release();
	BuiltinTypeValue GetBuiltinTypeValue();
private:
	BuiltinTypeValue v;
	string functionname;
};

class FunctionDefinition:public Statement{
public:
	vector <Statement*> *Member;
	FunctionDefinition(string n);
	~FunctionDefinition();
	FunctionDefinition(string n,NodeType t);
	void AddChilder(Statement* s);
	void CreateCode();
	void Release();
	int GetCodeLenght(){
		return codelength;
	};	
	int GetParamerCount();
	void GetDefaultValueList();

private:	
	int codelength;
	ReturnExpression* re;
	BuiltinTypeDeclare* btd;
};

class FunctionParameter:public Statement{
public:
	FunctionParameter(string s);
	FunctionParameter(string s,Statement* _defaultvalue);
	void CreateCode();
	void Release();
	Statement* GetDefalutValue();
	string GetParameterName();
private:
	Statement* defaultvalue;
	string name;

};

class TryParameter:public Statement{
public:
	string name;
	TryParameter(string s);
	void CreateCode();
	void Release();
};


class VarIdentIfier:public Statement{
public:
	VarIdentIfier(string s);
	void CreateCode();
	string GetName();
	void Release();

};

class FunctionParameterStatement:public Statement{
public:	
	vector <Statement*> *Member;
	FunctionParameterStatement();
	~FunctionParameterStatement();
	void AddChilder(Statement* s);
	void CreateCode();
	void InsertChilder(Statement* s);
	int Count();
	void Release();
	vector<int>* GetDefaultValueList();
private:
	vector<int>* defalutvaluelengthlist;
};

class TryParameterStatement:public Statement{
public:	
	vector<Statement*> *Member;
	TryParameterStatement();
	~TryParameterStatement();
	void AddChilder(Statement*  s);
	void CreateCode();
	int Count();
	void Release();
};


class ExpressionStatement:public Statement{
public:
	ExpressionStatement();
	~ExpressionStatement();
	void AddChilder(Statement* s);
	void CreateCode();
	void Release();
private:
	vector <Statement*> *Member;
};

class AssignmentDefinition:public Statement{
public:
	AssignmentDefinition(Statement * _s,string _oper,Statement * _e,bool _t = false);
	~AssignmentDefinition();
	void CreateCode();
	void Release();
private:
	string oper;
	Statement* e;
	Statement* s;
	bool t;

};

class AssignmentList:public Statement{
public:
	AssignmentList();
	void AddChilder(Statement* _s);
	void CreateCode();
	vector <Statement*> *Member;
	void Release();
private:
	Statement* s;
};

class InitializationList:public Statement{
public:
	InitializationList();
	~InitializationList();
	void AddChilder(Statement* _s);
	void CreateCode();
	vector <Statement*> *Member;
	void ModfiyMemberScope(Scope _scope); 
	void Release();
private:
	Statement* s;
};


class ExpressionList:public Statement{
public:
	ExpressionList();
	~ExpressionList();
	void AddChilder(Statement* _s);
	void CreateCode();
	int ExpressionSize();
	void Release();
private:
	Statement* s;
	vector <Statement*> *Member;

};









class InitializationDefinition:public Statement{
public:
	InitializationDefinition(Statement * _name,Statement * _e);
	~InitializationDefinition();
	void CreateCode();
	void ModfiyScope(Scope _scope);
	void Release();
	NodeType GetRightNodeType();
private:
	Scope scope;
	Statement* e;
	Statement* n;
	BuiltinTypeDeclare* btd;
};

class ArithmeticExpressionDefinition:public Statement{
public:
	ArithmeticExpressionDefinition(Statement* _s1,string _op,Statement* _s2);
	~ArithmeticExpressionDefinition();
	void CreateCode();
	void Release();
private:
	Statement* s1;
	string op;
	Statement* s2;
};

class CodeBlockStatement:public Statement{
public:
	CodeBlockStatement();
	~CodeBlockStatement();
	void AddChilder(Statement* s);
	void CreateCode();
	void Release();
private:
	vector <Statement*> *Member;
	int sopcelocalvars;
};




class IfStatement:public Statement{
public:
	IfStatement(int t);
	~IfStatement();
	void AddChilder(Statement* s);
	void CreateCode();
	void Release();
private:
	vector <Statement*> *Member;
	int postion1;
	int postion2;
	int type;// 0 无 else ,1 有else

};

class BreakExpression:public Statement{
public:
	BreakExpression();
	void CreateCode();
	int GetBreakJmpPostion();
	void Release();
private:
	int jmppostion;
};

class ThrowExpression:public Statement{
public:
	ThrowExpression(Statement* _s);
	~ThrowExpression();
	void CreateCode();
	void Release();
private:
	Statement* s;

};

class WhileStatement:public Statement{
public:
	WhileStatement();
	~WhileStatement();
	void AddChilder(Statement* s);
	void CreateCode();
	int GetJmpPostion();
	int GetTemplateid();
	void SetBreakPostion(int b);
	void Release();
private:
	vector <Statement*> *Member;
	int postion1;
	int postion2;
	int templateid;
	vector<int> *breakpostionvector;
};

class ForStatement:public Statement
{
public:
	ForStatement(Statement* assignment,Statement* expression,Statement* userexpression);
	~ForStatement();
	void CreateCode();
	int GetJmpPostion();
		int GetTemplateid();

	void Release();
	void SetBreakPostion(int b);
private:

	Statement* assignment;
	Statement* expression;
	Statement* userexpression;

	int postion1;
	int postion2;
	int sopcelocalvars;
	int templateid;

	vector<int> *breakpostionvector;
};

class ArrayDeclare:public Statement{
public:
	ArrayDeclare(Statement* _s);
	~ArrayDeclare();
	void AddChilder();
	void Release();
	void CreateCode();
private:
	Statement* expressionlist;
};

class ArrayElement:public Statement{
public:
	ArrayElement(Statement* _ar,Statement* index,int gettype);
	ArrayElement(Statement* _ar,Statement* index,Statement* index2);
	~ArrayElement();
	void CreateCode();
	void SetOpt(int i);
	void Release();
private:
	Statement* ar;
	Statement* index;
	Statement* index2;
	int opt; //1 get 2 set
	int gettype;
};

class DictExpression:public Statement{
public:
	DictExpression(string _k,Statement* _v);
	~DictExpression();
	void CreateCode();
	void Release();
private:
	string key;
	Statement* value;
};
class DictStatement:public Statement{
public:
	DictStatement();
	~DictStatement();
	void AddChilder(Statement* s);
	void CreateCode();
	void Release();
private:
	vector <Statement*> *Member;
};


class DictElemenet:public Statement{
public:
	DictElemenet(Statement* _exprssion,string _key);
	~DictElemenet();
	void CreateCode();
	void SetOpt(int i);
	void Release();
private:
	Statement* exprssion;
	string key;
	int opt; //1 get 2 set
};

class TernaryExpression:public Statement{
public:
	TernaryExpression(Statement* _exprssion1,Statement* _exprssion2,Statement* _exprssion3);
	~TernaryExpression();
	void CreateCode();
	void Release();
private:
	Statement* exprssion1;
	Statement* exprssion2;
	Statement* exprssion3;
};

class ContinueExpression:public Statement{
public:
	ContinueExpression();
	void CreateCode();
	void Release();
};


class FunctionArguments:public Statement{
public:
	FunctionArguments();
	~FunctionArguments();
	void AddChilder(Statement* s);
	void CreateCode();
	void Release();
	int FunctionArgumentsCount();
	vector <Statement*> *Member;
	
};


class FunctionCall:public Statement{
public:
	FunctionCall(Statement* _perfix,Statement* s);
	~FunctionCall();
	void CreateCode();
	void Release();
private:
	Statement* ag;
	Statement* perfix;
};


class LogiceEpressionDefintion:public Statement{
public:
	LogiceEpressionDefintion(Statement* _s1,string _op,Statement* _s2);
	~LogiceEpressionDefintion();
	void CreateCode();
	void Release();
private:
   Statement* s1;
   string op;
   Statement* s2;
};




class ReturnExpression:public Statement{
public:
	ReturnExpression();
	~ReturnExpression();
	void Release();
	ReturnExpression(Statement* s);
	void CreateCode();
private:
	Statement* s;
	BuiltinTypeDeclare* btd;
	int type;
};


class TryStatement:public Statement{
public:
	TryStatement(Statement* _s1,Statement* _s2,Statement* _s3);
	~TryStatement();
	void CreateCode();
	void Release();
private:
	Statement* s1;
	Statement* s2;
	Statement* s3;
	int sopcelocalvars;
};

class ImportFileExpression:public Statement{
public:
	ImportFileExpression(string _s);
	void CreateCode(){};
	void Release();
private:
	string s;
	string pname;
};


class PackAgeExpresson:public Statement{
public:
	PackAgeExpresson(Statement* _exprssion,string _key,Statement* _arguments,int _type,int _opt = 1);
	~PackAgeExpresson();
	void CreateCode();
	void SetOpt(int i);
	void SetNType(NodeType i);
	void Release();
private:
	Statement* exprssion;
	string key;
	Statement* arguments;
	int type;
	int opt;
};

class MinusExpression:public Statement{
public:
	MinusExpression(Statement* _exprssion);
	~MinusExpression();
	void Release();
	void CreateCode();
private:
	Statement* exprssion;

};

class PlusExpression:public Statement{
public:
	PlusExpression(Statement* _exprssion);
	~PlusExpression();
	void Release();
	void CreateCode();
private:
	Statement* exprssion;

};



class InverterExpression:public Statement{
public:
	InverterExpression(Statement* _exprssion);
	~InverterExpression();
	void Release();
	void CreateCode();
private:
	Statement* exprssion;

};



class NopExpression:public Statement{
public:
	NopExpression(){wfileaddressline = lineno;}
	~NopExpression(){}
	void Release();
	void CreateCode();

};

class TypeOfExpression:public Statement{
public:
	TypeOfExpression(Statement* _exprssion);
	~TypeOfExpression();
	void Release();
	void CreateCode();
private:
	Statement* exprssion;
};

#endif
