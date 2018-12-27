%{
#include "header.h"
#include "menthol-bison.tab.h"
extern int lineno = 1;
extern int yyerrorcount=0;
extern char* currentyyfile;
#include <io.h>
static void comment_block();
static void comment_line();
static void convert(char *a);
extern int yyerror(char*);
%}

%%
"/*"			                          { comment_block(); }
"//"                                      { comment_line(); }
0[0-7]+                                   {yylval.vINTEGER =(strtol(yytext, NULL, 8));  return NUMBER; }
[0-9]+	                                  {yylval.vINTEGER =atoi(yytext);  return NUMBER; }
[0-9]+[Ee][+-]?([0-9]+)?	              {yylval.vINTEGER =atoi(yytext);  return NUMBER; }
[0-9]+"."[0-9]+	                          {yylval.vDOUBLE =atof(yytext); return DOUBLE; }
[0-9]+"."[0-9]+[Ee][+-]?([0-9]+)?	      {yylval.vDOUBLE =atof(yytext); return DOUBLE; }

0[xX][0-9a-fA-F]+         {yylval.vINTEGER =(strtol(yytext, NULL, 16));  return NUMBER; }

"if"   			{return IF;}
"else" 			{return ELSE;}
"for"  			{return FOR;}
"break"    		{return BREAK;}
"true"     		{return TRUE_KEYWORD;}
"false"    		{return FALSE_KEYWORD;}
"try"       	{return TRY;}
"except"     	{return EXCEPT;}
"throw"    		{return THROW;}
"continue"   	{return CONTINUE;}
"return"     	{return RETURN;}
"while"      	{return WHILE;}
"null"      	{return NULL_KEYWORD;}
"import"        {return IMPORT;}
"_mmain"		{return WMAIN;}
"def"			{return DEF;}
"var"			{return VAR;}
"in"            {return IN;} 
"typeof"        {return TYPEOF;}
"+" 			{return('+');}

"-" 			{return('-');}
"*" 			{return('*');}
"/"  			{return('/');}
"{"     		{return('{');}
"}"    			{return '}';}
"("    			{return '(';}
")"    			{return ')';}
";"				{return(';');}
"|"	    		{return('|');}
"&"				{return('&');}
","				{return(',');}
"?"				{return('?');}
"."				{return('.');}
"["				{return('[');}
"]"				{return(']');}
"!"				{return('!');}
"%"				{return('%');}
"^"				{return('^');}
":"				{return(':');}
"::"			{return DICT_OP;}
".."            {return ARRAYSECTION;}
"="             {yylval.vSTRING=string(yytext);return ASSIGN_ASSIGN;}
"<"             {return('<'); }
">"             {return('>'); }
("!="|"<>")  	{return NEQ_OP;}
"||"			{return OR_OP;}
"&&"			{return AND_OP;}
">="    		{return GE_OP;}
"<="			{return LE_OP;}
"=="    		{return EQ_OP;}
"+="    		{yylval.vSTRING=string(yytext);return ADD_ASSIGN;}
"-="			{yylval.vSTRING=string(yytext);return SUB_ASSIGN;}
"/="			{yylval.vSTRING=string(yytext);return DIV_ASSIGN;}
"*="			{yylval.vSTRING=string(yytext);return MUL_ASSIGN;}
"%="    		{yylval.vSTRING=string(yytext);return MOD_ASSIGN;}
"&="			{yylval.vSTRING=string(yytext);return AND_ASSIGN;}
"|="			{yylval.vSTRING=string(yytext);return OR_ASSIGN;}
"^="			{yylval.vSTRING=string(yytext);return XOR_ASSIGN;}
"<<"			{return SHIFT_LEFT_OP;}
">>"			{return SHIFT_RIGHT_OP;}
"**"			{return POWER_OP;}
"module"        {return MODULE;}
"use"           {return USE;}

"$"[a-zA-Z_][a-zA-Z_0-9]*	{
							
							yylval.vSTRING=string(yytext);return VARIDENTIFIER;
							
						}

"@"[a-zA-Z_][a-zA-Z_0-9]*	{
							yylval.vSTRING=string(yytext);return GLOBALVARIDENTIFIER;
						}

[a-zA-Z_][a-zA-Z_0-9]* {
							yylval.vSTRING=string(yytext);return IDENTIFIER;
						}

[ \t]+			/* ignore white space */
.							return yytext[0];

\n                    { lineno++; }
     
\"([^\\"]|\\.)*\"  { 
								
								convert(yytext);
				
								yylval.vSTRING = string(yytext).substr(1,string(yytext).length()-2);
								
								return STRING;

								 }
%%


static void convert(char *a)
{
    int i, j;
    for(i = j = 0; a[i]; i ++)
        if(a[i] == '\\' && a[i+1] == 'n')
        {
            a[j++] = '\n';
            i++;
        }
		else if(a[i] == '\\' && a[i+1] == 'r')
        {
            a[j++] = '\r';
            i++;
        }else if(a[i] == '\\' && a[i+1] == 'b')
        {
            a[j++] = '\b';
            i++;
        }else if(a[i] == '\\' && a[i+1] == '"')
        {
            a[j++] = '\"';
            i++;
        }
        else a[j++] = a[i];
 
    a[j] = 0;
}

static void comment_block()
{
    int c1, c2;

    c1 = yyinput();
    c2 = yyinput();

    while (c2 != EOF && !(c2 == '/')) {
        if (c1 == '\n')
            lineno++;
        c1 = c2;
        c2 = yyinput();
    }
}

static void comment_line(void)
{
    int c;

    while ((c = yyinput()) != EOF && c != '\n')
        ;
    lineno++;
}

int yywrap()
{
	return 1;
}
