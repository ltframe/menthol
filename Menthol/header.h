#ifndef MENTHOLHEADER
#define MENTHOLHEADER

#include "Menthol.h"
extern int yyparse(void * param);
extern int yylex();
extern int yylineno;
extern void yyrestart(FILE* F);
extern FILE* yyin;
extern int yyerror(char* str);
extern int lineno;
extern int yyerrorcount;
extern char* currentyyfile;
class StatementList;
class Statement;


#define IsNumber(o) (o->v == M_NUMBER)
#define IsString(o) (o->v==M_STRING)
#define IsArray(o) (o->v==M_ARRAY)
#define IsDict(o) (o->v==M_DICT)
#define IsBool(o) (o->v==M_BOOL)
#define IsNULL(o) (o->v==M_NULL)

#define STACKSTATESTRING(o,s)\
	if(IsNumber(o)){s = "number";}\
	if(IsString(o)){s = "string";}\
	if(IsArray(o)){s = "array";}\
	if(IsDict(o)){s = "dict";}\
	if(IsBool(o)){s = "bool";}\
	if(IsNULL(o)){s = "Null";}\


#define VECTORFORSTART(t,v,it) for (std::vector<t>::iterator it = v->begin() ; it != v->end(); ++it){


#define VECTORFOREND }


typedef union
{
 struct {char c1; char c2;char c3; char c4;char c5; char c6;char c7; char c8;} m;
 double d;
}CodeDouble;

typedef union
{
 struct {char c1; char c2;char c3; char c4;} m;
 int i;
 unsigned int h;
}CodeInt;


typedef union
{
 struct {char c1; char c2;} m;
 unsigned short s;
}CodeCode,CodeShort;


typedef union
{
  struct {char c1; char c2;char c3; char c4;} m;
  Instruction i;
}CodeInst;



struct StringValue
{
	string str;
	hashValue hash;
};



enum NodeType{
	MNT_FunctionParameter,
	MNT_TryParameter,
	MNT_VarIdentIfier,
	MNT_FunctionParameterStatement,
	MNT_ExpressionStatement,
	MNT_ExpressionList,
	MNT_AssignmentDefinition,
	MNT_InitializationDefinition,
	MNT_AssignmentList,
	MNT_InitializationExpression,
	MNT_InitializationList,
	MNT_BuiltinTypeDeclare,
	MNT_ArithmeticExpressionDefinition,
	MNT_IfStatement,
	MNT_WhileStatement,
	MNT_ForStatement,
	MNT_ArrayDeclare,
	MNT_DictDeclare,
	MNT_ArrayElement,
	MNT_DictElement,
	MNT_ContinueExpression,
	MNT_BreakExpression,
	MNT_FunctionDefinition,
	MNT_ReturnExpression,
	MNT_TryStatement,
	MNT_ThrowExpression,
	MNT_CodeBlockStatement,
	MNT_ImportFileExpression,
	MNT_PackAgeExpresson,
	MNT_PackAgeFunCall,
	MNT_TernaryExpression,
	MNT_DictExpression,
	MNT_FunctionCall,
	MNT_FunctionArguments,
	MNT_LogiceEpressionDefintion,
	MNT_MinusExpression,
	MNT_PlusExpression,
	MNT_Release,
	MNT_InverterExpression
};


enum OperateCode{
	OP_PUSHNUMBER =0,
	OP_PUSHDOUBLE,
	OP_PUSHSTRING,
	OP_PUSHMARK,
	OP_CALLFUNC,
	OP_ADD,
	OP_STOREM,
	OP_LOADM,
	OP_NOP,
	OP_HALT,
	OP_RET,
	OP_JMP,
	OP_UJMPS,
	OP_UJMP,
	OP_TEST,
	OP_CMP,
	OP_SUB,
	OP_MUL,
	OP_DIV,
	OP_LT,//<
	OP_LE,//>
	OP_CREATEARRAY,
	OP_SETARRAYELEMENT,
	OP_GETARRAYELEMENT,
	OP_SETARRAY,
	OP_GEEQ,
	OP_LEEQ,
	OP_EQEQ,
	OP_NEQ,
	OP_OR, // ||
	OP_AND,// &&
	OP_BIT_OR,
	OP_BIT_AND,
	OP_LOADS,
	OP_STORES,
	OP_LOADP,
	OP_SETS,
	OP_LOADG,//载入运行记录,
	OP_ADJUSTBP,
	OP_ADJUSTSP,
	OP_PUSHRS,
	OP_PUSHBOOL,
	OP_MOD,
	OP_XOR,
	OP_SHIFTL,
	OP_SHIFTR,
	OP_PUSHTRYMARK,
	OP_THROWSTART,
	OP_THROWEND,
	OP_CREATEDICT,
	OP_SETDICT,
	OP_GETDICTELEMENT,
	OP_SETDICTELEMENT,
	OP_POWER,
	OP_GETSEQ,
	OP_INITS,
	OP_INITM,
	OP_PUSHFUN,
	OP_PUSHPACKAGE,
	OP_BREAK,
	OP_PUSHPACKAGEFUNC,
	OP_SETPACKAGEATTER,
	OP_GETPACKAGEATTER,
	OP_MINUS,
	OP_PUSHHASH,
	OP_POP,
	OP_TJMP,
	OP_ADD1,
	OP_INVERTER
	};

enum PackAgeType{
	MPA_PACKAGE,
	MPA_DLL,
	MPA_SPACKAGE,
	MPA_SDLL,
	/*MPA_SO,*/
	MPA_UNKONWN
};

struct PackageAttr{
	char pname[_MAX_PATH];//pacakage name
	char fname[_MAX_PATH];//file name
	PackAgeType ptype;
	//void* packagepointer;
};


enum DataType{
	DATA,
	LOADDATA
};








//记录函数的状态
struct FunctionAtter
{
	string name;
	Instruction* postion; //所在的二进制位置 //如果是内置函数则本属性无用
	hashValue hash; //如果是内置函数则本属性无用
	int paramcount;
	int lenght;
};





enum Scope{
	GLOBAL,
	LOCAL
};



struct CompileStruct
{
	int addressline;
	string name;
	NodeType type;
	vector <CompileStruct*> *childer;
};
struct RunTimeState;

struct PackageState{
	hashValue hash;
	RunTimeState* rts;
};

struct RunTimeState
{
	string pname;
	hashValue hash;
	vector<string> *strings;
	vector<double>* doubles;
	vector<FunctionAtter>* functionlist;
	vector<PackageState*>* includepackages;
	vector<StackState>* globalvalues;
	PackAgeType ptype;

};





typedef struct _PathStruct{
	string drive;
	string dir;
	string name;
	string extension;
	string filename;
}PathInfo;

typedef struct YYSTYPE
{
	string vSTRING;
	int  vINTEGER;
	double vDOUBLE;
	struct StackState*  vStackState;
	struct CompileStruct* vCompileStruct;
	Statement* vStatement;
} YYSTYPE;

#endif