%{
#include <cstdio>
#include <iostream>

#include <cstring>
using namespace std;
/*
To compile :
bison -d tme1essai2.y 
flex tme1essai2.l 
g++ -std=c++11 tme1essai2.tab.c lex.yy.c -lfl -o tme1essai2
*/

// stuff from flex that bison needs to know about:
extern "C" int yylex();
extern "C" int yyparse();
extern "C" FILE *yyin;
 
void yyerror(const char *s);
std::string buffer;
%}

// Bison fundamentally works by asking flex to get the next token, which it
// returns as an object of type "yystype".  But tokens could be of any
// arbitrary data type!  So we deal with that in Bison by defining a C union
// holding each of the types of tokens that Flex could return, and have Bison
// use that union instead of "int" for the definition of "yystype":
%union {
	int num;
	char* boolean;
	char* ident;
	char* type;
	char* smthg;
}

// define the "terminal symbol" token types I'm going to use (in CAPS
// by convention), and associate each with a field of the union:




%token <num> NUM
%token <boolean> BOOL
%token <ident> IDENT
%token <type> TYPE
%token <smthg> VAR
%token <smthg> CONST
%token <smthg> SET
%token <smthg> ADD
%token <smthg> SUB
%token <smthg> DIV
%token <smthg> MUL
%token <smthg> LT
%token <smthg> EQ
%token <smthg> NOT
%token <smthg> AND
%token <smthg> OR
%token <smthg> IF
%token <smthg> WHILE
%token <smthg> MY_ECHO
%token <smthg> REC
%token <smthg> FUN
%token <smthg> PROC
%token <smthg> CALL
%token <smthg> RETURN

%token <smthg> LBRACKET
%token <smthg> RBRACKET
%token <smthg> SEMICOLON
%token <smthg> LPAR
%token <smthg> RPAR
%token <smthg> COLON
%token <smthg> COMA
%token <smthg> ARROW

%type <smthg> prog
%type <smthg> cmds
%type <smthg> dec
%type <smthg> stat
%type <smthg> expr
%type <smthg> block
%type <type> type

%start	prog
%%
// this is the actual grammar that bison will parse, but for right now it's just
// something silly to echo to the screen what bison gets from flex.  We'll
// make a real one shortly:

//PROGRAM
prog : block
{
	//Construction string prolog
	buffer = "prog" + string($1);
	$$ = strdup(buffer.c_str());
	//Construction AST
	//program = new ASTProg($1);
	//Debug
	cout << $$ << endl; 
}
;
//END OF PROGRAM

//BLOCK
block : LBRACKET cmds RBRACKET
{
	//Construction string prolog
	buffer = "[" + string($2) + "]"; 
	$$ = strdup(buffer.c_str());
	//Construction AST
	//Debug
}
| LBRACKET error RBRACKET
{
	yyerrok; yyerror("error in block");
}
;
//END OF BLOCK

//COMMANDS
cmds : stat
{
	//Construction string prolog
	//Construction AST
	//Debug
	$$=$1; 
}
| dec SEMICOLON cmds
{
	//Construction string prolog
	//Construction AST
	//Debug
	buffer = string($1) + string(",") + string($3); 
	$$ = strdup(buffer.c_str()); 
}
| stat SEMICOLON cmds
{
	buffer = string($1) + string(",") + string($3); 
	$$ = strdup(buffer.c_str()); 
}
;
//END OF COMMANDS

//DECLARATION
dec : VAR IDENT type
{
	buffer = string("VAR(") + string($2) + string(",") + string($3) + string(")");
	$$ = strdup(buffer.c_str()); 
}
| CONST IDENT type expr
{
	buffer = string("SET(") + string($2) + string(",") + string($4) + string(")"); 
	$$ = strdup(buffer.c_str()); 
}
| PROC IDENT block
{

}
| PROC IDENT LBRACKET args RBRACKET block 
{

}
| FUN IDENT type LBRACKET args RBRACKET block 
{

}
| FUN REC IDENT type LBRACKET args RBRACKET expr 
{

}
| FUN REC IDENT type LBRACKET args RBRACKET block 
{

}
| PROC REC IDENT block 
{

}
| PROC REC IDENT LBRACKET args RBRACKET block 
{

}
;
//END OF DECLARATION

//STATEMENT
stat : SET IDENT expr
{ 
	buffer = string("SET(") + string($2) + string(",") + string($3) + string(")"); 
	$$ = strdup(buffer.c_str());
}
| IF expr block block
{
	buffer = string("IF(") + string($2) + string("),[") + string($3) + string("],[") + string($4) + string("]"); 
	$$ = strdup(buffer.c_str()); 
}
| WHILE expr block
{ 
	buffer = string("WHILE(") + string($2) + string(",") + string($3) + string(")"); 
	$$ = strdup(buffer.c_str()); 
}
| MY_ECHO expr 
{
	buffer = string("aps_echo(") + string($2) + string(")");
	$$ = strdup(buffer.c_str());
}
| CALL IDENT 
{

}
| CALL IDENT exprs 
{

}
| RETURN expr 
{

}
;
//END OF STATEMENT

//EXPRESSION
expr : BOOL
{ 
	$$=$1;
}
| NUM
{ 
	buffer = std::to_string($1); 
	$$ = strdup(buffer.c_str());
}
| IDENT
{ 
	$$=$1;
}
| LPAR NOT expr RPAR
{ 
	buffer = string("app(not,[") + string($3) + string("])"); 
	$$ = strdup(buffer.c_str()); 
}
| LPAR AND expr expr RPAR
{ 
	buffer = string("app(and,[") + string($3) + string(",") + string($4) + string("])"); 
	$$ = strdup(buffer.c_str()); 
}
| LPAR OR expr expr RPAR
{ 
	buffer = string("app(or,[") + string($3) + string(",") + string($4) + string("])"); 
	$$ = strdup(buffer.c_str()); 
}
| LPAR EQ expr expr RPAR
{ 
	buffer = string("app(eq,[") + string($3) + string(",") + string($4) + string("])");  
	$$ = strdup(buffer.c_str()); 
}
| LPAR LT expr expr RPAR
{ 
	buffer = string("app(lt,[") + string($3) + string(",") + string($4) + string("])"); 
	$$ = strdup(buffer.c_str()); 
}
| LPAR ADD expr expr RPAR
{ 
	buffer = string("app(add,[") + string($3) + string(",") + string($4) + string("])"); 
	$$ = strdup(buffer.c_str()); 
}
| LPAR SUB expr expr RPAR
{ 
	buffer = string("app(sub,[") + string($3) + string(",") + string($4) + string("])"); 
	$$ = strdup(buffer.c_str()); 
}
| LPAR DIV expr expr RPAR
{ 
	buffer = string("app(div,[") + string($3) + string(",") + string($4) + string("])"); 
	$$ = strdup(buffer.c_str()); 
}
| LPAR MUL expr expr RPAR
{ 
	buffer = string("app(mul,[") + string($3) + string(",") + string($4) + string("])"); 
	$$ = strdup(buffer.c_str()); 
}
| LBRACKET args RBRACKET expr 
{

}
| LPAR exprs RPAR 
{

}
;
//END OF EXPRESSION

//EXPRESSIONS
exprs : expr 
{

}
| expr exprs 
{

}
;
//END OF EXPRESSIONS

//ARGUMENTS
args : arg 
{

}
| arg COMA args 
{

}
;
//END OF ARGUMENTS

//ARGUMENT
arg : IDENT COLON type 
{

}
;
//END OF ARGUMENT

//TYPE
type : TYPE 
{  
	buffer = string($1); 
	$$ = strdup(buffer.c_str());  
}
| TYPE ARROW TYPE 
{

}
| LPAR TYPE RPAR 
{

}
;
//END OF TYPE
%%

int main(int, char** argv) {
	// open a file handle to a particular file:
	FILE *myfile = fopen(argv[1], "r");
	// make sure it is valid:
	if (!myfile) {
		cout << "I can't open the file!" << endl;
		return -1;
	}
	// set flex to read from it instead of defaulting to STDIN:
	yyin = myfile;
	
	// parse through the input until there is no more:
	do {
		yyparse();
	} while (!feof(yyin));
	
}

void yyerror(const char *s) {
	cout << "EEK, parse error!  Message: " << s << endl;
	// might as well halt now:
	exit(-1);
}
