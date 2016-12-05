%option yylineno
%{
#include <cstdio>
#include <iostream>
#include <cstring>

extern "C" int yylex();

void yyerror(const char* msg);
using namespace std;
int lineno = 1;
int charno = 1;

#include "analyzer.tab.h"  // to get the token types that we return

%}
%%

^#.*$ {}
("true"|"false")  {yylval.boolean=strdup(yytext); charno+=strlen(yytext); return BOOL;}
("void"|"bool"|"int")  {yylval.type=strdup(yytext); charno+=strlen(yytext); return TYPE;}

"VAR" {charno+=strlen(yytext); return VAR;}
"CONST" {charno+=strlen(yytext); return CONST;}
"SET" {charno+=strlen(yytext); return SET;}
"IF" {charno+=strlen(yytext); return IF;}
"WHILE" { charno+=strlen(yytext); return WHILE;}
"ECHO" { charno+=strlen(yytext); return MY_ECHO;}
"PROC" {charno+=strlen(yytext); return PROC;}
"CALL" {charno+=strlen(yytext); return CALL;}
"FUN" {charno+=strlen(yytext); return FUN;}
"RETURN" {charno+=strlen(yytext); return RETURN;}
"REC" {charno+=strlen(yytext); return REC;}

"add" {charno+=strlen(yytext); return ADD;}
"sub" {charno+=strlen(yytext); return SUB;}
"div" {charno+=strlen(yytext); return DIV;}
"mul" {charno+=strlen(yytext); return MUL;}
"lt" {charno+=strlen(yytext); return LT;}
"eq" {charno+=strlen(yytext); return EQ;}
"not" {charno+=strlen(yytext); return NOT;}
"and" {charno+=strlen(yytext); return AND;}
"or" {charno+=strlen(yytext); return OR;}

(-?)[0-9]+  {yylval.num = atoi(yytext); charno+=strlen(yytext); return NUM;}
([a-zA-Z])([a-zA-Z0-9])* {yylval.ident=strdup(yytext); charno+=strlen(yytext); return IDENT;}

[ \t] {charno+=strlen(yytext); }
[\r\n\v\f]  {lineno++; charno=1; }
";" {charno+=strlen(yytext); return SEMICOLON;}
"[" {charno+=strlen(yytext); return LBRACKET;}
"]" {charno+=strlen(yytext); return RBRACKET;}
"(" {charno+=strlen(yytext); return LPAR;}
")" {charno+=strlen(yytext); return RPAR;}
":" { charno+=strlen(yytext); return COLON;}
"," {charno+=strlen(yytext); return COMA;}
"->" {charno+=strlen(yytext); return ARROW;}
.  {std::string buffer = std::string("at line:char ") + std::to_string(lineno) +""+std::to_string(charno)+ " undefined symbol : " + yytext ;
	char *outErr = new char[buffer.length() + 1];
	std::strcpy(outErr, buffer.c_str());
	 yyerror(outErr);}
%%

