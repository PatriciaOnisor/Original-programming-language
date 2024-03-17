%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "limbaj.tab.h"
%}
%option noyywrap
%%
"int"|"float"|"char"|"string"|"bool" {yylval.string = strdup(yytext); return TYPE;}
"class " {yylval.string = strdup(yytext); return CLASA;}
"true"|"false" {yylval.string = strdup(yytext); return BOOL;}
"begin_progr" {return BGIN;}
"end_progr" {return END;}
"###globalVars" {return BGIN_G;}
"###types" {return BGIN_C;}
"###globalFunctions" {return BGIN_F;}
"const" {yylval.string = strdup(yytext); return CONST;}
"TypeOf" {yylval.string = strdup(yytext); return TYPEOF;}
"Eval" {yylval.string = strdup(yytext); return EVAL;}
"Methods: " { return Methods;}
"Data: " {return Data;}
"if" {return IF;}
"for" {return FOR;}
"while" {return WHILE;}
[0-9]+"."[0-9]+ {yylval.string = strdup(yytext);  return NR;}
[0-9]+ {yylval.string = strdup(yytext);  return NR;}
[a-z][a-z0-9]* {yylval.string = strdup(yytext); return ID;}
"/"[a-zA-Z0-9]+"/" {yylval.string = strdup(yytext); return CHAR;}
"/"[a-zA-Z0-9]+[a-zA-Z0-9_.,?!; ]*"/" {yylval.string = strdup(yytext); return CHAR;}
"["[0-9]+"]" {yylval.string = strdup(yytext); return ARRAY;}
"=" {return ASSIGN;}
[*/+-] {yylval.string = strdup(yytext); return OP_AR;}
"==" {yylval.string = strdup(yytext); return OP_B;}
"!=" {yylval.string = strdup(yytext); return OP_B;}
"<=" {yylval.string = strdup(yytext); return OP_B;}
">=" {yylval.string = strdup(yytext); return OP_B;}
"<" {yylval.string = strdup(yytext); return OP_B;}
">" {yylval.string = strdup(yytext); return OP_B;}
"||" {yylval.string = strdup(yytext); return OP_B;}
"&&" {yylval.string = strdup(yytext); return OP_B;}
[ \t] ;
\n {yylineno++;}
. {return yytext[0];}
