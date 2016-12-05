:- [typeur].

eval(_,'vrai','vrai').
eval(_,'faux','faux').
eval(_,X,X) :- integer(X), !.

%% Expression logique
eval(G,app('and',[X,Y]),'vrai') :- eval(G,X,'vrai'), eval(G,Y,'vrai').
eval(G,app('and',[X,Y]),'vrai') :- eval(G,X,'faux'), eval(G,Y,'faux').
eval(G,app('and',[X,Y]),'faux') :- eval(G,X,'vrai'), eval(G,Y,'faux').
eval(G,app('and',[X,Y]),'faux') :- eval(G,X,'faux'), eval(G,Y,'vrai').

eval(G,app('or',[X,Y]),'vrai') :- eval(G,X,'vrai'), eval(G,Y,'vrai').
eval(G,app('or',[X,Y]),'faux') :- eval(G,X,'faux'), eval(G,Y,'faux').
eval(G,app('or',[X,Y]),'vrai') :- eval(G,X,'vrai'), eval(G,Y,'faux').
eval(G,app('or',[X,Y]),'vrai') :- eval(G,X,'faux'), eval(G,Y,'vrai').

eval(_,app('not',['vrai']),'faux').
eval(_,app('not',['faux']),'vrai').
eval(G,app('not',[X]),'vrai') :- eval(G,X,'faux').
eval(G,app('not',[X]),'faux') :- eval(G,X,'vrai').


eval(_,app('eq',[X,X]),'vrai').
eval(G,app('eq',[X,Y]),'vrai') :- eval(G,X,VAL), eval(G,Y,VAL).
eval(G,app('eq',[X,Y]),'faux') :- eval(G,X,VAL1), eval(G,Y,VAL2), VAL1\==VAL2.

eval(G,app('lt',[X,Y]),'vrai') :- eval(G,X,VAL1), eval(G,Y,VAL2), VAL1<VAL2.
eval(G,app('lt',[X,Y]),'faux') :- eval(G,X,VAL1), eval(G,Y,VAL2), VAL1>=VAL2.

%% Expression algebrique
eval(G,app('add',[X,Y]),V) :- eval(G,X,VAL1), eval(G,Y,VAL2), V is VAL1+VAL2.
eval(G,app('sub',[X,Y]),V) :- eval(G,X,VAL1), eval(G,Y,VAL2), V is VAL1-VAL2.
eval(G,app('mul',[X,Y]),V) :- eval(G,X,VAL1), eval(G,Y,VAL2), V is VAL1*VAL2.
eval(G,app('div',[X,Y]),V) :- eval(G,X,VAL1), eval(G,Y,VAL2), V is div(VAL1,VAL2).

%% eval(G,'or'(X,Y), 'vrai') :- find_type(G, X, T_X), find_type



/* Recherche d'une variable dans un environnement */
eval(G,[],'void',G).
eval(G,VAR,EXPR,newG) :- find_val(_,G,VAR,_,EXPR).

%% Declaration
eval(G,[aps_var(VAR,TYPE)|SUITE],'void',newG) :- eval(G,SUITE,'void',(_,VAR,TYPE,'null')).
eval(G,[aps_const(VAR,TYPE,EXPR)|SUITE],EXPR,newG) :- \+find_val(FINAL,G,VAR,TYPE,EXPR), eval(G,SUITE,'void',[(CONST,VAR,TYPE,EXPR)|G]).

%% Instruction
eval(G,[aps_set(VAR,EXPR)|SUITE],'void',newG) :- eval(G,EXPR,TYPE), replace_val(G,(_,VAR,TYPE,OLDEXPR),(_,VAR,TYPE,EXPR),[(_,VAR,TYPE,EXPR)|G]), eval(newG,SUITE,'void',newG).
eval(G,[aps_if(CONDITION),CORPS,_|SUITE],'void',newG) :- eval(G,CONDITION,'vrai',G), eval(G,CORPS,'void',G), eval(G,SUITE,'void',newG).
eval(G,[aps_if(CONDITION),_,ALTERNANT|SUITE],'void',newG) :- eval(G,CONDITION,'faux',G), eval(G,ALTERNANT,'void',G), eval(G,SUITE,'void',newG).
eval(G,[aps_while(CONDITION,CORPS)|SUITE],'void',newG) :- eval(G,CONDITION,'vrai',G), eval(G,CORPS,'void',G), eval(G,SUITE,'void',G).
eval(G,[aps_while(CONDITION,CORPS)|SUITE],'void',newG) :- eval(G,CONDITION,'faux',G), eval(G,CORPS,'void',G), eval(G,SUITE,'void',G).
eval(G,[aps_echo(_)|SUITE],'void',newG) :- eval(G,SUITE,'void',G).



find_val(_,[(_,VAR,TYPE,EXPR)|_],VAR,TYPE,EXPR).
find_val(_,[(_,VAR_G,TYPE,EXPR)|_],VAR,TYPE,_) :- VAR == VAR_G.
find_val(FINAL,[(FINAL,VAR1,_T1,_EXPR1)|L],VAR,TYPE,EXPR) :- VAR \== VAR1, find_val(FINAL,L,VAR,TYPE,EXPR).

replace_val([],_,_,[]).
replace_val([(_,OLDVAR,TYPE,OLDEXPR)|L1],(_,OLDVAR,TYPE,OLDEXPR),(_,NEWVAR,TYPE,NEWEXPR),[(_,NEWVAR,TYPE,NEWEXPR)|L2]) :- replace_val(L1,(_,OLDVAR,TYPE,OLDEXPR),(_,NEWVAR,TYPE,NEWEXPR),L2).
replace_val([(_,VAR1,TYPE1,EXPR1)|L1],(_,OLDVAR,TYPE,OLDEXPR),(_,NEWVAR,TYPE,NEWEXPR),[(_,VAR2,TYPE2,EXPR2)|L2]) :- VAR1 \= OLDVAR, replace_val(L1,(_,OLDVAR,TYPE,OLDEXPR),(_,NEWVAR,TYPE,NEWEXPR),L2).



eval(G,prog(PROG)) :- eval(G,PROG,'void',G).



