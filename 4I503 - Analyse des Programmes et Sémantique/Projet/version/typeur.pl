%% Type terminaux
type(_,'true','bool').
type(_,'false','bool').
type(_,'void','void').
type(_,X,'int') :- integer(X).


%% Expression logique
type(G,app('and',[X,Y]),'bool') :- type(G,X,'bool'), type(G,Y,'bool').
type(G,app('and',[X,Y]),'bool') :- find_type(_,G,X,'bool'), type(G,Y,'bool').
type(G,app('and',[X,Y]),'bool') :- type(G,X,'bool'), find_type(_,G,Y,'bool').
type(G,app('and',[X,Y]),'bool') :- find_type(_,G,X,'bool'), find_type(_,G,Y,'bool').


type(G,app('or',[X,Y]),'bool')  :- type(G,X,'bool'), type(G,Y,'bool').
type(G,app('or',[X,Y]),'bool')  :- find_type(_,G,X,'bool'), type(G,Y,'bool').
type(G,app('or',[X,Y]),'bool')  :- type(G,X,'bool'), find_type(_,G,Y,'bool').
type(G,app('or',[X,Y]),'bool')  :- find_type(_,G,X,'bool'), find_type(_,G,Y,'bool').

type(G,app('not',[X]),'bool')   :- type(G,X,'bool').
type(G,app('not',[X]),'bool')   :- find_type(_,G,X,'bool').

type(G,app('eq',[X,Y]),'bool')  :- type(G,X,T), type(G,Y,T).
type(G,app('eq',[X,Y]),'bool')  :- find_type(_,G,X,T), type(G,Y,T).
type(G,app('eq',[X,Y]),'bool')  :- type(G,X,T), find_type(_,G,Y,T).
type(G,app('eq',[X,Y]),'bool')  :- find_type(_,G,X,T), find_type(_,G,Y,T).

type(G,app('lt',[X,Y]),'bool')  :- type(G,X,T), type(G,Y,T).
type(G,app('lt',[X,Y]),'bool')  :- find_type(_,G,X,T), type(G,Y,T).
type(G,app('lt',[X,Y]),'bool')  :- type(G,X,T), find_type(_,G,Y,T).
type(G,app('lt',[X,Y]),'bool')  :- find_type(_,G,X,T), find_type(_,G,Y,T).

%% Expression algebrique
type(G,app('add',[X,Y]),'int') :- type(G,X,'int'), type(G,Y,'int').
type(G,app('add',[X,Y]),'int') :- type(G,X,'int'), find_type(_,G,Y,'int').
type(G,app('add',[X,Y]),'int') :- find_type(_,G,X,'int'), type(G,Y,'int').
type(G,app('add',[X,Y]),'int') :- find_type(_,G,X,'int'), find_type(_,G,Y,'int').

type(G,app('sub',[X,Y]),'int') :- type(G,X,'int'), type(G,Y,'int').
type(G,app('sub',[X,Y]),'int') :- find_type(_,G,X,'int'), type(G,Y,'int').
type(G,app('sub',[X,Y]),'int') :- type(G,X,'int'), find_type(_,G,Y,'int').
type(G,app('sub',[X,Y]),'int') :- find_type(_,G,X,'int'), find_type(_,G,Y,'int').

type(G,app('mul',[X,Y]),'int') :- type(G,X,'int'), type(G,Y,'int').
type(G,app('mul',[X,Y]),'int') :- find_type(_,G,X,'int'), type(G,Y,'int').
type(G,app('mul',[X,Y]),'int') :- type(G,X,'int'), find_type(_,G,Y,'int').
type(G,app('mul',[X,Y]),'int') :- find_type(_,G,X,'int'), find_type(_,G,Y,'int').

type(G,app('div',[X,Y]),'int') :- type(G,X,'int'), type(G,Y,'int').
type(G,app('div',[X,Y]),'int') :- find_type(_,G,X,'int'), type(G,Y,'int').
type(G,app('div',[X,Y]),'int') :- type(G,X,'int'), find_type(_,G,Y,'int').
type(G,app('div',[X,Y]),'int') :- find_type(_,G,X,'int'), find_type(_,G,Y,'int').

%% stockage des types
%% add_type(_, VAR, TYPE, [(VAR, TYPE) | _] ).
%% add_type( G, VAR, TYPE, G2) :- G2 = [ (VAR, TYPE) | G ]. %%

%type(G, VAR, TYPE) :- find_type(_, [], VAR, TYPE).

/* recherche de type d'une variable dans un environnement */
find_type(FINAL,[(FINAL,VAR,TYPE)|_],VAR,TYPE).
find_type(_,[(_,VAR_G,TYPE)|_],VAR,TYPE) :- VAR == VAR_G.
find_type(FINAL,[(FINAL,VAR1,_T1)|L],VAR,TYPE) :- VAR \== VAR1, find_type(FINAL,L,VAR,TYPE).


%% Analyse du Programme
%%analyze_type(prog(PROG), T) :- analyze_type([], PROG,'void').
is_well_typed(prog(PROG)) :- analyze_type([],PROG,'void').

%% Déclarations
analyze_type(G,[aps_var(VAR,TYPE)|SUITE],'void') :- analyze_type([(_,VAR,TYPE)|G],SUITE,'void').
analyze_type(G,[aps_const(VAR,TYPE,EXPR)|SUITE],'void') :- type(G,EXPR,TYPE),analyze_type([(_,VAR,TYPE)|G],SUITE,'void').

%% Instruction
analyze_type(_,[],_).
analyze_type([],[aps_set(_,EXPR)|SUITE],'void') :- analyze_type([(_,EXPR,_)],SUITE,'void').
analyze_type(G,[aps_set(VAR,EXPR)|SUITE],'void') :- find_type(_,G,VAR,_),type(G,EXPR,TYPE),analyze_type([(_,EXPR,TYPE)|G],SUITE,'void').
analyze_type(G,[aps_if(CONDITION),CORPS,ALTERNANT|SUITE],'void') :- type(G,CONDITION,'bool'),analyze_type(G,CORPS,'void'),analyze_type(G,ALTERNANT,'void'),analyze_type(G,SUITE,'void').
analyze_type(G,[aps_while(CONDITION,CORPS)|SUITE],'void') :- type(G,CONDITION,'bool'),analyze_type(G,CORPS,'void'),analyze_type(G,SUITE,'void').
analyze_type(G,[aps_echo(_)|SUITE],'void') :- analyze_type(G,SUITE,'void').






