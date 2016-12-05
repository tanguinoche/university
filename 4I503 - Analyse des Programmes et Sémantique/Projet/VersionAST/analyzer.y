%code requires { #include "AST.h" }
%{
#include <cstdio>
#include <iostream>
#include <memory>
#include <cstring>
//#include "AST.h"
using namespace std;

// stuff from flex that bison needs to know about:
extern "C" int yylex();
extern "C" int yyparse();
extern "C" FILE *yyin;
 
void yyerror(const char *s);

//program;
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
	list<ASTCmds> *u_list;
	ASTIdent *u_ident;
	ASTCmds *u_cmd;
	ASTProg *u_prog;
	ASTBlock *u_block;
	ASTType *u_type;
	//ASTArgs *u_args;
	//ASTArg *u_arg;
	//ASTExprs *u_exprs;
	ASTExpr *u_expr;
}

// define the "terminal symbol" token types I'm going to use (in CAPS
// by convention), and associate each with a field of the union:




%token <num> NUM
%token <boolean> BOOL
%token <smthg> IDENT
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

%type <u_prog> prog
%type <u_list> cmds
%type <u_cmd> dec
%type <u_cmd> stat
%type <u_block> block
%type <u_type> type
%type <smthg> args
%type <smthg> arg
%type <smthg> exprs
%type <u_expr> expr
%type <u_ident> ident

%start prog
%%
//TODO : A rajouter :
/*
%type <u_args> args
%type <u_arg> arg
%type <u_exprs> exprs
*/

//PROGRAM
prog : block
{
	ASTProg *program = new ASTProg($1);
	$$ = program;
	cout<<"Yacc:(prog) "<<$$->toString()<<endl; 
}
;
//END OF PROGRAM

//BLOCK
block : LBRACKET cmds RBRACKET
{
	$$ = new ASTBlock($2);
	cout<<"Yacc:(block) "<<$$->toString()<<endl;
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
	$$ = new list<ASTCmds>();
	$$->push_back(*$1);
	cout<<"Yacc:(cmds:stat) "<< "list de cmds" << endl; //$$->toString()<<endl;
}
| dec SEMICOLON cmds
{
	$$ = new list<ASTCmds>();
	$$->push_back(*$1);
	$$->insert($$->end(), $3->begin(), $3->end());
	cout<<"Yacc:(cmds:dec;cmds) "<<"dec + list de cmds" << endl;//$$->toString()<<endl;
}
| stat SEMICOLON cmds
{
	$$ = new list<ASTCmds>();
	$$->push_back(*$1);
	$$->insert($$->end(), $3->begin(), $3->end()); 
	cout<<"Yacc:(cmds:stat;cmds) "<<"stat + list de cmds" << endl;//$$->toString()<<endl;
}
;
//END OF COMMANDS

//DECLARATION
dec : VAR ident type
{
	$$ = new ASTVar($2, $3);
	cout<<"Yacc:(dec:var_ident_type) "<<$$->toString()<<endl;
}
| CONST ident type expr
{
	$$ = new ASTConst($2, $3, $4);
	cout<<"Yacc:(dec:const_ident_type_expr) "<<$$->toString()<<endl;
}
| PROC ident block
{
	//$$ = new ASTProc($2, $3);
}
| PROC ident LBRACKET args RBRACKET block 
{
	//$$ = new ASTProc($4, $6);
}
| FUN ident type LBRACKET args RBRACKET block 
{
	//$$ = new ASTFun($3, $4, $6);
}
| FUN REC ident type LBRACKET args RBRACKET expr 
{

}
| FUN REC ident type LBRACKET args RBRACKET block 
{

}
| PROC REC ident block 
{

}
| PROC REC ident LBRACKET args RBRACKET block 
{

}
;
//END OF DECLARATION

//STATEMENT
stat : SET ident expr
{ 
	$$ = new ASTSet($2, $3);
	cout<<"Yacc:(stat:set_ident_expr) "<<$$->toString()<<endl;
}
| IF expr block block
{
	$$ = new ASTIf($2, $3, $4);
	cout<<"Yacc:(stat:if:set_ident_expr) "<<$$->toString()<<endl;
}
| WHILE expr block
{ 
	$$ = new ASTWhile($2, $3);
	cout<<"Yacc:(stat:while_expr_prog) "<<$$->toString()<<endl;
}
| MY_ECHO expr 
{
	$$ = new ASTEcho($2);
}
| CALL ident 
{
	//$$ = new ASTCall($2);
}
| CALL ident exprs 
{
	//$$ = new ASTCall($2, $3);
}
| RETURN expr 
{
	//$$ = new ASTReturn($2);
}
;
//END OF STATEMENT

//EXPRESSION
expr : BOOL
{ 
	$$ = new ASTBool($1);
	cout<<"Yacc:(expr:bool) "<<$$->toString()<<endl;
}
| NUM
{ 
	$$ = new ASTNum($1);
	cout<<"Yacc:(expr:num) "<<$$->toString()<<endl;
}
| ident
{ 
	$$ = $1;
	cout<<"Yacc:(expr:ident) "<<$$->toString()<<endl; 
}
| LPAR NOT expr RPAR
{ 
	$$ = new ASTNot($3);
	cout<<"Yacc:(expr:not) "<<$$->toString()<<endl; 
}
| LPAR AND expr expr RPAR
{ 
	$$ = new ASTAnd($3, $4);
	cout<<"Yacc:(expr:and) "<<$$->toString()<<endl; 
}
| LPAR OR expr expr RPAR
{ 
	$$ = new ASTOr($3, $4);
	cout<<"Yacc:(expr:or) "<<$$->toString()<<endl; 
}
| LPAR EQ expr expr RPAR
{ 
	$$ = new ASTEq($3, $4);
	cout<<"Yacc:(expr:eq) "<<$$->toString()<<endl; 
}
| LPAR LT expr expr RPAR
{ 
	$$ = new ASTLt($3, $4);
	cout<<"Yacc:(expr:lt) "<<$$->toString()<<endl; 
}
| LPAR ADD expr expr RPAR
{ 
	$$ = new ASTAdd($3, $4);
	cout<<"Yacc:(expr:add) "<<$$->toString()<<endl; 
}
| LPAR SUB expr expr RPAR
{ 
	$$ = new ASTSub($3, $4);
	cout<<"Yacc:(expr:sub) "<<$$->toString()<<endl; 
}
| LPAR DIV expr expr RPAR
{ 
	$$ = new ASTDiv($3, $4);
	cout<<"Yacc:(expr:div) "<<$$->toString()<<endl; 
}
| LPAR MUL expr expr RPAR
{ 
	$$ = new ASTMul($3, $4);
	cout<<"Yacc:(expr:mul) "<<$$->toString()<<endl; 
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
arg : ident COLON type 
{

}
;
//END OF ARGUMENT

//TYPE
type : TYPE 
{  
	if(strcmp("int",$1)==0) {
		$$ = new TYPEInt();
	} else if(strcmp("bool",$1)==0) {
		$$ = new TYPEBool();
	} else if(strcmp("void",$1)==0) {
		$$ = new TYPEVoid();
	} else {
		yyerrok; yyerror("unknown type");
	}
	cout<<"Yacc:(prog) "<<$$->toString()<<endl; 
}
| TYPE ARROW TYPE 
{

}
| LPAR TYPE RPAR 
{

}
;
//END OF TYPE

//IDENT
ident: IDENT 
{ 
	$$ = new ASTIdent($1); 
	cout << "created ASTident from " << $1 <<endl;
}
//END OF IDENT
%%

int main(int, char** argv) {
	// open a file handle to a particular file:
	FILE *myfile = fopen(fopen(argv[1], "r");, "r");
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
