%option yylineno
%{
#include <cstdio>
#include <iostream>
#include <cstring>

extern "C" int yylex();

void yyerror(const char* msg);
using namespace std;
	

#include "tme1essai2.tab.h"  // to get the token types that we return

%}
%%

("true"|"false")  {cout << "Flex:Found a boolean:" << yytext << endl; yylval.boolean=strdup(yytext); return BOOL;}
("void"|"bool"|"int")  {cout << "Flex:Found a type:" << yytext << endl; yylval.type=strdup(yytext); return TYPE;}

"VAR" {cout << "Flex:Found a var:" << yytext << endl; return VAR;}
"CONST" {cout << "Flex:Found a const:" << yytext << endl; return CONST;}
"SET" {cout << "Flex:Found a set:" << yytext << endl; return SET;}
"IF" {cout << "Flex:Found a if:" << yytext << endl; return IF;}
"WHILE" {cout << "Flex:Found a while:" << yytext << endl; return WHILE;}

"add" {cout << "Flex:Found a add:" << yytext << endl; return ADD;}
"sub" {cout << "Flex:Found a sub:" << yytext << endl; return SUB;}
"div" {cout << "Flex:Found a div:" << yytext << endl; return DIV;}
"mul" {cout << "Flex:Found a mul:" << yytext << endl; return MUL;}

"lt" {cout << "Flex:Found a lt:" << yytext << endl; return LT;}
"eq" {cout << "Flex:Found a eq:" << yytext << endl; return EQ;}

"not" {cout << "Flex:Found a not:" << yytext << endl; return NOT;}
"and" {cout << "Flex:Found a and:" << yytext << endl; return AND;}
"or" {cout << "Flex:Found a or:" << yytext << endl; return OR;}

[0-9]+  {cout << "Flex:Found a number:" << yytext << endl; yylval.num = atoi(yytext); return NUM;}

([A-Z]|[a-z])+ {cout << "Flex:Found a ident:" << yytext << endl; yylval.ident=strdup(yytext);  return IDENT;}


[ \t\r\n\v\f]*  {cout << "Flex:Found a space:" << yytext << endl;}
";" {cout << "Flex:Found a semicolon:" << yytext << endl; return SEMICOLON;}
"[" {cout << "Flex:Found a left bracket:" << yytext << endl; return LBRACKET;}
"]" {cout << "Flex:Found a right bracket:" << yytext << endl; return RBRACKET;}
"(" {cout << "Flex:Found a left parenthesis:" << yytext << endl; return LPAR;}
")" {cout << "Flex:Found a right parenthesis:" << yytext << endl; return RPAR;}
.  {cout << "Flex:Found a uni-symbol:" << yytext[0] << endl;
	std::string buffer = std::string("at line ") + std::to_string(yylineno) + " undefined symbol : " + yytext ;
	char *outErr = new char[buffer.length() + 1];
	std::strcpy(outErr, buffer.c_str());
	 yyerror(outErr);}
%%
