%{
#include <cstdio>
#include <iostream>

#include <cstring>
using namespace std;


// stuff from flex that bison needs to know about:
extern "C" int yylex();
extern "C" int yyparse();
extern "C" FILE *yyin;
 
void yyerror(const char *s);
std::string buffer;
%}


%union {
	int num;
	char* boolean;
	char* ident;
	char* type;
	char* smthg;
}





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

%token <smthg> LBRACKET
%token <smthg> RBRACKET
%token <smthg> SEMICOLON
%token <smthg> LPAR
%token <smthg> RPAR

%type <smthg> prog
%type <smthg> cmds
%type <smthg> dec
%type <smthg> stat
%type <smthg> expr
%type <smthg> block
%type <type> type

%start	prog
%%


prog : block { buffer = "prog" + string($1); $$ = strdup(buffer.c_str()); cout<<"Yacc:(prog)->"<<$$<<endl; cout << $$ << endl; }
	;

block : LBRACKET cmds RBRACKET								  { buffer = "[" + string($2) + "]"; 
																$$ = strdup(buffer.c_str());
																cout<<"Yacc:(block)->"<<$$<<endl;}
	| LBRACKET error RBRACKET										  { yyerrok; yyerror("error in block");  }
	;

cmds : stat                                                   { $$=$1; 
																cout<<"Yacc:(cmds:stat)->"<<$$<<endl;}
	| dec SEMICOLON cmds                                      { buffer = string($1) + string(",") + string($3); 
																$$ = strdup(buffer.c_str()); 
																cout<<"Yacc:(cmds:dec;cmds)->"<<$$<<endl;}
	| stat SEMICOLON cmds                                     { buffer = string($1) + string(",") + string($3); 
																$$ = strdup(buffer.c_str()); 
																cout<<"Yacc:(cmds:stat;cmds)->"<<$$<<endl;}
	;

dec : VAR IDENT type                                          { /*DO NOTHING*/ 
																cout<<"Yacc:(dec:var_ident_type)->"<<$$<<endl;}
	| CONST IDENT type expr                                   { buffer = string("set(") + string($2) + string(",") + string($4) + string(")"); 
																$$ = strdup(buffer.c_str()); 
																cout<<"Yacc:(dec:const_ident_type_expr)->"<<$$<<endl;}
	;

stat : SET IDENT expr                                         { buffer = string("set(") + string($2) + string(",") + string($3) + string(")"); 
																$$ = strdup(buffer.c_str());
																cout<<"Yacc:(stat:set_ident_expr)->"<<$$<<endl;}
	| IF expr block block                                       { buffer = string("if(") + string($2) + string("),[") + string($3) + string("],[") + string($4) + string("]"); 
																$$ = strdup(buffer.c_str()); 
																cout<<"Yacc:(stat:if:set_ident_expr)->"<<$$<<endl;}
	| WHILE expr block                                         { buffer = string("while(") + string($2) + string(",") + string($3) + string(")"); 
																$$ = strdup(buffer.c_str()); 
																cout<<"Yacc:(stat:while_expr_prog)->"<<$$<<endl;}

	;

expr : BOOL                                                   { $$=$1;
																cout<<"Yacc:(expr:bool)->"<<$$<<endl;}
	| NUM                                                     { buffer = std::to_string($1); $$ = strdup(buffer.c_str());
																cout<<"Yacc:(expr:num)->"<<$$<<endl;}
	| IDENT                                                   { $$=$1;
																cout<<"Yacc:(expr:ident)->"<<$$<<endl; }
	| LPAR NOT expr RPAR                                      { buffer = string("app(not,[") + string($3) + string("])"); $$ = strdup(buffer.c_str()); 
																cout<<"Yacc:(expr:not)->"<<$$<<endl; }
	| LPAR AND expr expr RPAR                                 { buffer = string("app(and,[") + string($3) + string(",") + string($4) + string("])"); $$ = strdup(buffer.c_str()); 
																cout<<"Yacc:(expr:and)->"<<$$<<endl; }
	| LPAR OR expr expr RPAR                                  { buffer = string("app(or,[") + string($3) + string(",") + string($4) + string("])"); $$ = strdup(buffer.c_str()); 
																cout<<"Yacc:(expr:or)->"<<$$<<endl; }
	| LPAR EQ expr expr RPAR                                  { buffer = string("app(eq,[") + string($3) + string(",") + string($4) + string("])");  $$ = strdup(buffer.c_str()); 
																cout<<"Yacc:(expr:eq)->"<<$$<<endl; }
	| LPAR LT expr expr RPAR                                  { buffer = string("app(lt,[") + string($3) + string(",") + string($4) + string("])"); $$ = strdup(buffer.c_str()); 
																cout<<"Yacc:(expr:lt)->"<<$$<<endl; }
	| LPAR ADD expr expr RPAR                                 { buffer = string("app(add,[") + string($3) + string(",") + string($4) + string("])"); $$ = strdup(buffer.c_str()); 
																cout<<"Yacc:(expr:add)->"<<$$<<endl; }
	| LPAR SUB expr expr RPAR                                 { buffer = string("app(sub,[") + string($3) + string(",") + string($4) + string("])"); $$ = strdup(buffer.c_str()); 
																cout<<"Yacc:(expr:sub)->"<<$$<<endl; }
	| LPAR DIV expr expr RPAR                                 { buffer = string("app(div,[") + string($3) + string(",") + string($4) + string("])"); $$ = strdup(buffer.c_str()); 
																cout<<"Yacc:(expr:div)->"<<$$<<endl; }
	| LPAR MUL expr expr RPAR                                 { buffer = string("app(mul,[") + string($3) + string(",") + string($4) + string("])"); $$ = strdup(buffer.c_str()); 
																cout<<"Yacc:(expr:mul)->"<<$$<<endl; }
	;
	
type : TYPE { /*DO NOTHING*/  
			cout<<"Yacc:(prog)->"<<"type"<<endl; }
	;
%%

int main(int, char**) {

	FILE *myfile = fopen("tme1.txt", "r");

	if (!myfile) {
		cout << "I can't open the file!" << endl;
		return -1;
	}

	yyin = myfile;
	

	do {
		yyparse();
	} while (!feof(yyin));
	
}

void yyerror(const char *s) {
	cout << "EEK, parse error!  Message: " << s << endl;
	exit(-1);
}
