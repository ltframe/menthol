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
#define IsObject(o) (o->v==M_OBJECT)
#define IsModule(o)(o->v==M_MODULE)
#define IsFUN(o)(o->v==M_FUN)	
#define IsPFUN(o)(o->v==M_PFUN)	
#define IsMMRT(o)(o->v==M_MMRT)	


//是不是menthol写成的包
#define IsPackage(o)(o==MPA_USER_PACKAGE || o==MPA_SYS_PACKAGE)	

//是不是DLL写成的包
#define IsEXTPackage(o)(o==MPA_USER_EXTPACKAGE || o==MPA_SYS_EXTPACKAGE)	


//是不是系统自带的包
#define IsSYSPackage(o)(o==MPA_SYS_PACKAGE || o==MPA_SYS_EXTPACKAGE)	


//通过类型，返回类型名的的字符串
#define STACKSTATESTRING(o,s)\
	if(IsNumber(o)){s = "number";}\
	if(IsString(o)){s = "string";}\
	if(IsArray(o)){s = "array";}\
	if(IsDict(o)){s = "dict";}\
	if(IsBool(o)){s = "bool";}\
	if(IsNULL(o)){s = "Null";}\
	if(IsObject(o)){s = "object";}\
	if(IsModule(o)){s = "module";}\
	if(IsFUN(o)){s = "function";}\
	if(IsPFUN(o)){s = "module function";}\
	if(IsMMRT(o)){s = "mmrt";}\

//循环vector的宏，t为vector的泛型类型，v传入的vector,it为循环中的临时变量
#define VECTORFORSTART(t,v,it) for (std::vector<t>::iterator it = v->begin() ; it != v->end(); ++it){
#define VECTORFOREND }





#define VECOTRSTACKSTATEPOINTER  VECOTRSTACKSTATE*
#define STATICCAST(T,P) static_cast<T*>(P)
#define CONSTCAST(T)  const_cast<T*>
#define STATICCASTPARRAY(P) STATICCAST(VECOTRSTACKSTATE,P->array)


#define SWITCHBREAK break

#define SWITCHCASESTART(op) case op:{ \

#define SWITCHCASEEND SWITCHBREAK; \
						  } \

typedef union
{
 struct {char c1; char c2;char c3; char c4;char c5; char c6;char c7; char c8;} m;
 double d;
}CodeDouble;

typedef union
{
 struct {char c1; char c2;char c3; char c4;} m;
 int i;
 M_UInt h;
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


//mentho node type 
enum NodeType{
	MNT_FunctionParameter,
	MNT_FunctionParameterWithDefault,
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
	MNT_ImportPackageExpression,
	MNT_ModuleExpresson,
	MNT_ModuleFunCall,
	MNT_ModuleFunctionDefinition,
	MNT_TernaryExpression,
	MNT_DictExpression,
	MNT_FunctionCall,
	MNT_FunctionArguments,
	MNT_LogiceEpressionDefintion,
	MNT_MinusExpression,
	MNT_PlusExpression,
	MNT_Release,
	MNT_InverterExpression,
	MNT_TypeOfExpression,
	MNT_ModuleStatementList,
	MNT_ModuleDefine,
	MNT_MainFunction,
	MNT_InstanceExpression
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
	OP_JMP, //11
	OP_UJMPS,
	OP_UJMP,
	OP_TEST,
	OP_CMP,
	OP_SUB,
	OP_MUL,
	OP_DIV,
	OP_LT,//<  19
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
	OP_LOADS, //33
	OP_STORES,
	OP_LOADP,
	OP_SETS,
	//OP_LOADG,//载入运行记录,
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
	OP_PUSHMODULE,
	OP_BREAK,
	OP_PUSHMODULEFUNC,
	OP_SETMODULEATTER,
	OP_GETMODULEATTER,
	OP_MINUS,
	OP_PUSHHASH,
	OP_POP,
	OP_TJMP,
	OP_ADD1,
	OP_INVERTER,
	OP_TYPEOF,
	OP_CONST,
	OP_MMRT,
	};

enum PackAgeType{
	MPA_UNKNOW,
	MPA_USER_PACKAGE, //用户自定义开发的包，不在lib中的那些
	MPA_SYS_PACKAGE,//系统自带的包，在lib中的那些
	MPA_USER_EXTPACKAGE,//用户自定义开发的包，不在lib中的那些,由C/C++写成的dll
	MPA_SYS_EXTPACKAGE //系统自带的包，在lib中的那些,由C/C++写成的dll
};

struct ImportFileAttr
{
	string filename;
	PackAgeType ptype;
};


struct PackageAttr{
	char pname[_MAX_PATH];//pacakage name
	char fname[_MAX_PATH];//pacakage name
	PackAgeType ptype;

};


enum DataType{
	DATA,
	LOADDATA
};





struct BuiltinTypeValue
{
	double d;
	int i;
	hashValue hash;
	string str;
	pInst p;
	bool b;
	ValueType v;
};


//记录函数的状态
struct FunctionAtter
{
	string name;
	Instruction* postion; //所在的二进制位置 //如果是内置函数则本属性无用
	hashValue hash; //如果是内置函数则本属性无用
	int paramcount;
	int lenght;
	vector <int> *defaultvaluelengthlist;
};
//类实例MMRT
struct ModuleInstState {
	VECOTRSTACKSTATEPOINTER inst;
	RunTimeState* rts;//使用的模块指针
	vector<GcState*> *gcstatelist;
};




struct MentholDebug
{
	int instno;
	int lineno;
	int filenamelenght;
	string filename;
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

struct ModuleState{
	hashValue hash;
	RunTimeState* rts;//当前使用的模块指针
};



struct RunTimeState
{
	string modulename;
	hashValue hash;
	vector<string> *strings;
	vector<double>* doubles;
	vector<FunctionAtter>* functionlist;
	vector<ModuleState*>* includemodule;
	//VECOTRSTACKSTATEPOINTER globalvalues;
	vector<MentholDebug> *debuglist;
	PackAgeType ptype;
	int codeoffset;
	vector<vector<Instruction>*>* globalcode;
	pInstance inst;//当前使用的实例
};

struct GlobalCodeRuntimeAtter
{
	vector<Instruction> *globalcodelist;
	RunTimeState* belongtoruntimestate; //属于哪一个RunTimeState
	int lenght;
};


//关于路径驱动器、目录，文件名，扩展名
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
	struct STACKSTATEPOINTER  vStackState;
	struct CompileStruct* vCompileStruct;
	Statement* vStatement;
} YYSTYPE;

#endif