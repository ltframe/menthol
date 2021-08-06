 %{
#include "StatementList.h"
extern int yylex();
extern int lineno;
extern int yyerrorcount;
extern char* currentyyfile;
int lineaddress=0;
#define YYDEBUG 1
#define YYPARSE_PARAM parm
int linenum=0;
int yyerror(char* str)
{
	/*
	yyerrorcount++;
	printf("\r\n");
	printf("compile error: %s, in %s,at line %d",str,currentyyfile,lineno);
	printf("\r\n");*/
	MError::CreateInstance()->PrintError(str);
	return(1);
}
enum Scope;
struct StackState;

%}


%token <vSTRING>VARIDENTIFIER 
%token <vSTRING> IDENTIFIER 
%token <vSTRING> GLOBALVARIDENTIFIER

%token <vINTEGER>NUMBER
%token <vSTRING>STRING
%token <vDOUBLE>DOUBLE
%token <vINTEGER>TRUE_KEYWORD
%token <vINTEGER>FALSE_KEYWORD
%token IF ELSE FOR BREAK  TRY EXCEPT THROW IMPORT MODULE USE
%token CONTINUE RETURN  WHILE   NULL_KEYWORD
%token POWER_OP NEQ_OP OR_OP AND_OP GE_OP LE_OP EQ_OP
%token ADD_ASSIGN SUB_ASSIGN DIV_ASSIGN MUL_ASSIGN ASSIGN_ASSIGN
%token MOD_ASSIGN AND_ASSIGN OR_ASSIGN XOR_ASSIGN 
%token SHIFT_LEFT_OP SHIFT_RIGHT_OP WMAIN  DEF  VAR  IN ARRAYSECTION DICT_OP TYPEOF CONST MMRT
 



%type <vStatement> function_parameter
%type <vSTRING> assignment_operator
%type <vStatement> expression_definition
%type <vStatement> built-intype_declare
%type <vStatement> funciton_codeblock_statement
%type <vStatement> assignment_expression_definition
%type <vStatement> if_statement
%type <vStatement> while_statement
%type <vStatement> array_declare
%type <vStatement> jump_statement
%type <vStatement> wmain_definition
%type <vStatement> function_arguments
%type <vStatement> functiondefinition
%type <vStatement> initialization_expression

%type <vStatement> try_statement
%type <vStatement> try_parameter
%type <vStatement> dict_statement
%type <vStatement> dict_declare
%type <vStatement> dict_expression
%type <vStatement> statement_list
%type <vStatement> conditional_expression
%type <vStatement> selection_statement
%type <vStatement> statement
%type <vStatement> iteration_statement
%type <vStatement> expression_statement
%type <vStatement> primary_expression
%type <vStatement> for_statement
%type <vStatement> indentifier_expression
%type <vStatement> Initialization_Definition
%type <vStatement> initialization_list
%type <vStatement> list_element

%type <vStatement> multiplicative_expression
%type <vStatement> additive_expression
%type <vStatement> shift_expression
%type <vStatement> relational_expression
%type <vStatement> equality_expression
%type <vStatement> and_expression
%type <vStatement> exclusive_or_expression
%type <vStatement> inclusive_or_expression
%type <vStatement> logical_and_expression
%type <vStatement> logical_or_expression
%type <vStatement> shift_left_expression
%type <vStatement> subtraction_expression
%type <vStatement> power_expression
%type <vStatement> prefix_expression

%type <vStatement> function_parameter_list
%type <vStatement> try_parameter_list
%type <vStatement> modulestatementlist
%type <vStatement> modulestatement
%type <vStatement> global_initialization
%type <vStatement> import_expression_list
%left '='
%left '-' '+'
%left '*' '/'
%start start
%%
/*************global define start********************/
start:run_statement	
	  |start run_statement
	  ;
	  
/*能被处理的语法只有一下四种：导入表达式、使用模块表达式，main入口函数，定义模块*/
run_statement:import_expresson
			 |moduledefine
			 |USE use_expression_list ';'	
			 |wmain_definition
     		 ;



wmain_definition:WMAIN ':'function_parameter funciton_codeblock_statement	
				{
					StatementList *ls = (StatementList*)parm;
         			FunctionDefinition* fd= new FunctionDefinition("_mmain",MNT_MainFunction);
					fd->AddChilder($3);
					fd->AddChilder($4);
					ls->AddFunction("_mmain");
					ls->AddMainModuleList(fd);
				} 			
			    ;

/*一种函数带参数，一种没参数*/
functiondefinition:DEF IDENTIFIER ':' function_parameter funciton_codeblock_statement
				  {
						StatementList *ls = (StatementList*)parm;		
						ls->AddStringConstant(string($2));		
						$$= new FunctionDefinition($2,MNT_FunctionDefinition);
						$$->AddChilder($4);
						$$->AddChilder($5);
						ls->AddFunction($2);
				  }
				  |DEF IDENTIFIER ':'  funciton_codeblock_statement
				  {
						StatementList *ls = (StatementList*)parm;		
						ls->AddStringConstant(string($2));		
						$$= new FunctionDefinition($2,MNT_FunctionDefinition);
						$$->AddChilder(0);
						$$->AddChilder($4);
						ls->AddFunction($2);
				  }
				  ;


/*模块中的全局变量可以是声明表达式，也是可以赋值表达式*/
global_initialization:initialization_expression ';'
					 { 
						/*在程序内把变量作用域改为GLOBAL*/
						InitializationList* list = static_cast<InitializationList*>($1);
						list->ModfiyMemberScope(GLOBAL);
				     }
				     |expression_definition';'{
							$$ = $1;
				     }
				     ;

function_parameter_list:VARIDENTIFIER{ $$ = new FunctionParameter($1,false);}
					   |VARIDENTIFIER ASSIGN_ASSIGN assignment_expression_definition
					   {
							$$ = new FunctionParameter($1,$3,false);
					   }
					   |
					    CONST VARIDENTIFIER{ $$ = new FunctionParameter($2,true);}
					   |CONST VARIDENTIFIER ASSIGN_ASSIGN assignment_expression_definition
					   {
							$$ = new FunctionParameter($2,$4,true);
					   }
					   ; 


function_parameter:function_parameter_list
				   {
				   		$$ = new FunctionParameterStatement();
				   		$$->AddChilder($1);
				   }
				   |function_parameter ','  function_parameter_list 
				   {
						$1->AddChilder($3);
				   }
				   ;	

funciton_codeblock_statement: '{' statement_list '}'{								
									$$ = new CodeBlockStatement();
									$$->AddChilder($2);
								}
							|'{'  '}'{
								$$ = new NopExpression();
							}
							;
		  

			  
function_arguments:assignment_expression_definition
				  {
						$$ =new FunctionArguments();
						if($1!=0){
							$$->AddChilder($1);
						}
				  }
				  |function_arguments ',' assignment_expression_definition
				  {
						if($3!=0){
							$1->AddChilder($3);
						}
				  }
				  ;




primary_expression:dict_declare{
					$$ = $1;
				   }
				   |array_declare{
					$$ = $1;
				   }
				   |built-intype_declare {$$ = $1;}	
				   |indentifier_expression{
					$$=$1;
				   }
				   |'(' assignment_expression_definition ')'{$$ = $2;}
				   | TYPEOF '(' assignment_expression_definition ')'{
						$$ = new TypeOfExpression($3);
				   }
				   |MMRT '(' assignment_expression_definition ')'{
						$$ = new MmrtExpression($3);
				   }
				   ;



list_element:	primary_expression{$$ = $1;}
				|list_element'[' assignment_expression_definition ']'
				{
						ArrayElement* ad = new ArrayElement($1,$3,0);
						ad->SetOpt(1);
						$$ = ad;
				}						
				|list_element'[' assignment_expression_definition  ARRAYSECTION']'
				{
						ArrayElement* ad = new ArrayElement($1,$3,1);
						ad->SetOpt(1);
						$$ = ad;
				}
				|list_element'[' ARRAYSECTION assignment_expression_definition ']'
				{
						ArrayElement* ad = new ArrayElement($1,$4,2);
						ad->SetOpt(1);
						$$ = ad;
				}
				|list_element'[' assignment_expression_definition  ARRAYSECTION   assignment_expression_definition']'
				{
					ArrayElement* ad = new ArrayElement($1,$3,$5);
					ad->SetOpt(1);
					$$ = ad;

				}
				|list_element  DICT_OP IDENTIFIER
				{
					DictElemenet* ad = new DictElemenet($1,$3);
					ad->SetOpt(1);
					$$ = ad;
				}
				
				|list_element '.' IDENTIFIER '(' function_arguments ')'
				{
				ModuleExpresson* pae =new ModuleExpresson($1,$3,$5,1);
				StatementList *ls = (StatementList*)parm;		
				ls->AddStringConstant(string($3));	
				$$ = pae;
				}
				|list_element '.' IDENTIFIER '(' ')'
				{
				ModuleExpresson* pae =new ModuleExpresson($1,$3,0,1);
				StatementList *ls = (StatementList*)parm;		
				ls->AddStringConstant(string($3));	
				pae->SetNType(MNT_ModuleFunCall);
				$$ = pae;
				}
				|list_element '(' function_arguments ')'
				{
					StatementList *ls = (StatementList*)parm;
					$$ = new FunctionCall($1,$3);
					$$->AddChilder($3);
				}
				|list_element '(' ')'
				{
					StatementList *ls = (StatementList*)parm;
					$$ = new FunctionCall($1,new FunctionArguments());
				} 
				|list_element '.' GLOBALVARIDENTIFIER
				{
					ModuleExpresson* pae =new ModuleExpresson($1,$3,0,2);
					StatementList *ls = (StatementList*)parm;		
					ls->AddStringConstant(string($3));	
					$$ = pae;
				}
				|list_element '.' IDENTIFIER 
				{
					ModuleExpresson* pae =new ModuleExpresson($1,$3,0,3);
					StatementList *ls = (StatementList*)parm;		
					ls->AddStringConstant(string($3));	
					pae->SetNType(MNT_ModuleFunctionDefinition);
					$$ = pae;
				}
				;



statement_list:statement 
			   {
					 $$ =new ExpressionStatement();
					 if($1!=0){
						$$->AddChilder($1);
					  }
			   }
			   |statement_list statement
			   {
				    if($2!=0){
						$$->AddChilder($2);
					}
			   }					
			   ;
			   
/*负数、类似+234的正数、非!*/			   
prefix_expression:list_element {$$ =$1;}
				  |'-' prefix_expression
				  {
						$$ = new MinusExpression($2);
				  }
			      |'+' prefix_expression{
						$$ = new PlusExpression($2);
			      }
				  |'!' prefix_expression{
						$$ = new InverterExpression($2);
			      }
				  ;

power_expression:prefix_expression{$$ =$1;}
				|power_expression POWER_OP prefix_expression
				{
					$$ = new ArithmeticExpressionDefinition($1,"**",$3);
				}
				;


multiplicative_expression: power_expression{$$ =$1;}
						| multiplicative_expression '*' power_expression
						{
							$$ = new ArithmeticExpressionDefinition($1,"*",$3);
						}
						| multiplicative_expression '/' power_expression
						{
							$$ = new ArithmeticExpressionDefinition($1,"/",$3);
						}
						| multiplicative_expression '%' power_expression
						{
							$$ = new ArithmeticExpressionDefinition($1,"%",$3);
						}
						;

subtraction_expression:multiplicative_expression {$$ =$1;}
					  | subtraction_expression '-' multiplicative_expression
					  {
						$$ = new ArithmeticExpressionDefinition($1,"-",$3);
					  }
					  ;

additive_expression: subtraction_expression{$$ =$1;}
					|additive_expression '+' subtraction_expression
					{
						$$ = new ArithmeticExpressionDefinition($1,"+",$3);
					}
				    ;


shift_left_expression:additive_expression{$$ =$1;}
					 | shift_left_expression SHIFT_LEFT_OP additive_expression
					 {
						$$ = new ArithmeticExpressionDefinition($1,"<<",$3);
					 }
					 ;


shift_expression: shift_left_expression{$$ =$1;}				
				| shift_expression SHIFT_RIGHT_OP shift_left_expression
				{
					$$ = new ArithmeticExpressionDefinition($1,">>",$3);
				}
				;

relational_expression: shift_expression{$$ =$1;}
						| relational_expression '<' shift_expression
						{
							$$ = new ArithmeticExpressionDefinition($1,"<",$3);
						}
						| relational_expression '>' shift_expression
						{
							$$ = new ArithmeticExpressionDefinition($1,">",$3);
						}
						| relational_expression LE_OP shift_expression
						{
							$$ = new ArithmeticExpressionDefinition($1,"<=",$3);
						}
						| relational_expression GE_OP shift_expression
						{
							$$ = new ArithmeticExpressionDefinition($1,">=",$3);
						}
						;

equality_expression: relational_expression{$$ =$1;}
					| equality_expression EQ_OP relational_expression
					{
						$$ = new ArithmeticExpressionDefinition($1,"==",$3);
					}
					| equality_expression NEQ_OP relational_expression
					{
						$$ = new ArithmeticExpressionDefinition($1,"<>",$3);
					}
					;

and_expression: equality_expression{$$ =$1;}
				| and_expression '&' equality_expression
				{
					$$ =new LogiceEpressionDefintion($1,"&",$3);
				}
				;

exclusive_or_expression: and_expression{$$ =$1;}
						| exclusive_or_expression '^' and_expression
						{
							$$ =new LogiceEpressionDefintion($1,"^",$3);
						}
						;

inclusive_or_expression: exclusive_or_expression{$$ =$1;}
						| inclusive_or_expression '|' exclusive_or_expression
						{
							$$ =new LogiceEpressionDefintion($1,"|",$3);
						}
						;

logical_and_expression:inclusive_or_expression{$$ =$1;}
						|logical_and_expression AND_OP inclusive_or_expression
						{
							$$ =new LogiceEpressionDefintion($1,"&&",$3);
						}
						;

logical_or_expression:logical_and_expression{$$ =$1;}
					 |logical_or_expression OR_OP logical_and_expression
					 {
						$$ =new LogiceEpressionDefintion($1,"||",$3);
					 }
					 ;

conditional_expression:logical_or_expression{
						$$ = $1;
					   }
					   |logical_or_expression '?' expression_definition ':' conditional_expression
					   {
								$$ = new TernaryExpression($1,$3,$5);
					   }
					  ;


/*只提供变量声明 $a,@b*/
indentifier_expression:VARIDENTIFIER{
							$$ =new VarIdentIfier($1);
					  }
 					  |GLOBALVARIDENTIFIER{
 						StatementList *ls = (StatementList*)parm;
						ls->AddStringConstant(string($1));
 						$$ = new VarIdentIfier((char*)$1.c_str());}
 					  ;




assignment_expression_definition:conditional_expression{$$ = $1;}
								|prefix_expression assignment_operator assignment_expression_definition
								{
									if($2=="+="){
										$$ = new AssignmentDefinition($1,"=",new ArithmeticExpressionDefinition($1,"+",$3));
									}
									if($2=="-="){
										$$ = new AssignmentDefinition($1,"=",new ArithmeticExpressionDefinition($1,"-",$3));
									}
									if($2=="/="){
										$$ = new AssignmentDefinition($1,"=",new ArithmeticExpressionDefinition($1,"/",$3));
									}
									if($2=="*="){
										$$ = new AssignmentDefinition($1,"=",new ArithmeticExpressionDefinition($1,"*",$3));
									}
									if($2=="%="){
										$$ = new AssignmentDefinition($1,"=",new ArithmeticExpressionDefinition($1,"%",$3));
									}
									if($2=="&="){
										$$ = new AssignmentDefinition($1,"=",new LogiceEpressionDefintion($1,"&",$3));
									}
									if($2=="|="){
										$$ = new AssignmentDefinition($1,"=",new LogiceEpressionDefintion($1,"|",$3));
									}
									if($2=="^="){
										$$ = new AssignmentDefinition($1,"=",new LogiceEpressionDefintion($1,"^",$3));
									}
									if($2=="="){
										AssignmentDefinition* ad = new AssignmentDefinition($1,$2,$3,true);
										$$ = ad;
									}								
								}
								
								;
/*赋值表达式可以一行写多个，用逗号隔开*/
expression_definition:assignment_expression_definition {
							$$ =new ExpressionList();
							$$->AddChilder($1);
					   }
					   |expression_definition ',' assignment_expression_definition
					   {
							   $1->AddChilder($3);
					   }
			   ;  

	
			   			   
array_declare:'[' expression_definition ']'
			   {
					$$ = new ArrayDeclare($2);
			   }
			   |'[' ']'
			   {
					$$ = new ArrayDeclare(new ExpressionList());
			   }	   
			   ;

dict_expression:IDENTIFIER DICT_OP assignment_expression_definition
				{
					$$ = new DictExpression($1,$3);
				}
			    ;

dict_statement:dict_expression
			   {
					$$ = new DictStatement();
					$$->AddChilder($1);
			   } 			   
			   | dict_statement ','  dict_expression
			   {
					$1->AddChilder($3);
			   }
			   ;




dict_declare:'(' dict_statement ')'{ $$ = $2;};
			|'(' ')'{
					$$ = new DictStatement();
			}
			;
		    
/*比如 abc=123*/
Initialization_Definition:indentifier_expression {
								 InitializationDefinition* ad = new InitializationDefinition($1,0,false);
								 ad->ModfiyScope(LOCAL);
								 $$ = ad;
							}
							|indentifier_expression ASSIGN_ASSIGN assignment_expression_definition{
									InitializationDefinition* ad = new InitializationDefinition($1,$3,false);
									ad->ModfiyScope(LOCAL);
									$$ = ad;
							}
							|CONST indentifier_expression {
									 InitializationDefinition* ad = new InitializationDefinition($2,0,true);
									 ad->ModfiyScope(LOCAL);
									 $$ = ad;
							}
							|CONST indentifier_expression ASSIGN_ASSIGN assignment_expression_definition{
									InitializationDefinition* ad = new InitializationDefinition($2,$4,true);
									ad->ModfiyScope(LOCAL);
									$$ = ad;
							}
							;


initialization_list:Initialization_Definition{
						$$ = new InitializationList();
						$$->AddChilder($1);
					}
					|initialization_list ',' Initialization_Definition{
						$1->AddChilder($3);
					}
					;
/*生命局部变量必须使用关键字var*/
initialization_expression:VAR initialization_list{						  
							$$ = $2;						  
						  }
						  ;

statement:funciton_codeblock_statement{$$ = $1;}
		 |jump_statement {$$ = $1;}
		 |selection_statement{$$ = $1;}
		 |iteration_statement{$$ = $1;}
		 |expression_statement{
			$$ = $1;
		 }
		 |initialization_expression';'{
			$$ = $1;
		 }
		 ;


expression_statement:';'{
						$$ = 0;
					}
					| expression_definition ';' {
						$$ = $1;
					}
					;


selection_statement:if_statement {$$ = $1;}
				   |try_statement{$$ = $1;}
				   ;

iteration_statement:for_statement {$$ = $1;}
				   |while_statement{$$ = $1;}
				   ;


built-intype_declare:NUMBER 
                     {   					 
						BuiltinTypeDeclare* btd =new BuiltinTypeDeclare();
						btd->SetNumber($1);
						$$= btd;
					 }
					 |
					 STRING
					 {
						
						BuiltinTypeDeclare* btd =new BuiltinTypeDeclare();
						btd->SetString($1);	
						$$= btd;
					 }
					 |DOUBLE{
						 StatementList *ls = (StatementList*)parm;
						BuiltinTypeDeclare* btd =new BuiltinTypeDeclare();
						ls->AddDoubleConstant($1);
						btd->SetDouble($1);
						$$= btd;
					 }
					 |TRUE_KEYWORD{
						BuiltinTypeDeclare* btd =new BuiltinTypeDeclare();
						btd->SetBool(true);
						$$= btd;
					 }
					 |FALSE_KEYWORD
					 {
						BuiltinTypeDeclare* btd =new BuiltinTypeDeclare();
						btd->SetBool(false);
						$$= btd;
					 }					 
					 |NULL_KEYWORD{
						BuiltinTypeDeclare* btd =new BuiltinTypeDeclare();
						btd->SetNull();
						$$= btd;				 
					 }
					 |IDENTIFIER {
						StatementList *ls = (StatementList*)parm;
						ls->AddStringConstant(string($1));
						BuiltinTypeDeclare* btd =new BuiltinTypeDeclare();
						btd->SetFunctionPointerOrModule($1,1);
						$$= btd;
					 } 
					 ;

assignment_operator:ASSIGN_ASSIGN
					|MUL_ASSIGN
					|DIV_ASSIGN
					|MOD_ASSIGN
					|ADD_ASSIGN
					|SUB_ASSIGN
					|AND_ASSIGN
					|XOR_ASSIGN
					|OR_ASSIGN
					;

if_statement: IF '(' expression_definition ')' funciton_codeblock_statement 
			  {
				 $$ = new IfStatement(0);
				 $$->AddChilder($3);
				 $$->AddChilder($5);			 
			  }
			  |IF '(' expression_definition ')' funciton_codeblock_statement ELSE funciton_codeblock_statement
			  {
					 $$ = new IfStatement(1);
					 $$->AddChilder($3);
					 $$->AddChilder($5);
					 $$->AddChilder($7);	 
			  }
			  

			  ;
			  
while_statement: WHILE  '(' expression_definition ')' funciton_codeblock_statement
				{
					$$ = new WhileStatement();
					$$->AddChilder($3);
					$$->AddChilder($5);
				}
			    ;
			    
for_statement:FOR '(' initialization_expression  IN  assignment_expression_definition ')' funciton_codeblock_statement
			  {
				  	$$ = new ForStatement($3,$5,$7);
			  }
			  ;

jump_statement:CONTINUE ';' {
					$$ = new ContinueExpression();
			  }
			  |BREAK ';'{
					$$ = new BreakExpression();
			  }
			  |RETURN ';'{
					$$ =new ReturnExpression();
			  }
			  |RETURN expression_definition ';'{$$ =new ReturnExpression($2);}
			  |THROW function_arguments';'{$$ =new ThrowExpression($2);}
			  ;

try_parameter_list :VARIDENTIFIER{ $$ = new TryParameter($1,false);}
					|CONST VARIDENTIFIER{ $$ = new TryParameter($2,true);}
				    ;	
			  
try_parameter:try_parameter_list
			   {
			   		$$ = new TryParameterStatement();
			   		$$->AddChilder($1);
			   }
			   |try_parameter ','  try_parameter_list 
			   {
					$1->AddChilder($3);
			   }
			   ;

try_statement:TRY funciton_codeblock_statement EXCEPT ':' try_parameter  funciton_codeblock_statement
			  {
				 	$$ =new TryStatement($2,$5,$6);
			  }
			  ;

/*导入文件*/
import_expresson:IMPORT import_expression_list ';'
				 {
						StatementList *ls = (StatementList*)parm;	
						ImportPackagePath* ipp =static_cast<ImportPackagePath*>($2);
						ls->SetCompileStructTable(new ImportPackageExpression(ipp->GetPath()));			
				 }
				 ;

import_expression_list:IDENTIFIER
					   {
							$$ =new ImportPackagePath($1);
					   } 
					   |import_expression_list '.' IDENTIFIER
					   {
							ImportPackagePath* ipp =static_cast<ImportPackagePath*>($1);
							ipp->AddPathString($3);
					   }
				       ;


use_expression_list:IDENTIFIER
				   {
						StatementList *ls = (StatementList*)parm;	
						ls->AddUseModuleList($1);
				   } 
				   |use_expression_list ',' IDENTIFIER
				   {
						StatementList *ls = (StatementList*)parm;	
						ls->AddUseModuleList($3);				   
				   }
				   ;

moduledefine:MODULE IDENTIFIER '{' modulestatementlist '}'
			  {
					StatementList *ls = (StatementList*)parm;	
											
					ls->SetCompileStructTable(new ModuleDefine(string($2),$4));		
			  }
			  |MODULE IDENTIFIER '{'  '}'
			  {
					StatementList *ls = (StatementList*)parm;	
					ls->SetCompileStructTable(new ModuleDefine(string($2),new ModuleStatementList()));		
			  }
			 ;

modulestatementlist:modulestatement
					{
						$$ =new ModuleStatementList();
						if($1!=0){
							$$->AddChilder($1);
						}
					}
					|modulestatementlist  modulestatement
					{
						if($2!=0){
							$1->AddChilder($2);
						}
					}
					;

/*模块中只能包含函数定义和全局变量*/
modulestatement:functiondefinition {$$ = $1;}
				|global_initialization{$$ = $1;}
				;
%%
 