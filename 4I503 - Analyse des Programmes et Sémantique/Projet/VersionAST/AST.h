#include <iostream>
#include <list>
#include <memory>

class ASTNode;
class ASTProg;
class ASTBlock;
class ASTCmds;
class ASTDec;
class ASTStat;
class ASTConst;
class ASTVar;
class ASTRec;
class ASTFun;
class ASTProc;
class ASTSet;
class ASTIf;
class ASTWhile;
class ASTEcho;
class ASTCall;
class ASTReturn;
class ASTExpr;
class ASTBool;
class ASTNum;
class ASTIdent;
class ASTOp;
class ASTUnaryOp;
class ASTBinaryOp;
class ASTAdd;
class ASTSub;
class ASTMul;
class ASTDiv;
class ASTLt;
class ASTEq;
class ASTAnd;
class ASTOr;
class ASTNot;
class ASTType;
class TYPEVoid;
class TYPEInt;
class TYPEBool;
class ASTArgs;
class ASTArg;
class ASTExprs;


class ASTNode
{ 
	public: 
		virtual std::string toString(){return "node";}
};

//AST NODES
//AST 0
class ASTProg : public ASTNode 
{ 
	public: 
		ASTBlock *block; 
		ASTProg(ASTBlock *block); 
		std::string toString();
};
class ASTBlock : public ASTNode 
{ 
	public: 
		std::list<ASTCmds> *cmds; 
		ASTBlock(std::list<ASTCmds> *cmds); 
		std::string toString();
};
class ASTCmds : public ASTNode 
{ 
	public: 
		virtual std::string toString() const{return "cmds";}
}; //Abstract : soit un DEC, soit un STAT. Si plusieurs cmds, devrait finir par stat...


//AST COMMANDES
class ASTDec : public ASTCmds 
{ 
	public: 
		virtual std::string toString(){return "dec";}
}; //Abstract : soit VAR, soit CONST
class ASTStat : public ASTCmds 
{ 
	public: 
		virtual std::string toString(){return "stat";}
}; //Abstract : SET, IF, WHILE, ECHO

//AST DECLARATIONS
//AST 0
class ASTConst : public ASTDec 
{ 
	public: 
		ASTIdent *ident; 
		ASTType *type; 
		ASTExpr *expr; 
		ASTConst(ASTIdent *ident, ASTType *type, ASTExpr *expr); 
		std::string toString();
};
class ASTVar : public ASTDec 
{ 
	public: 
		ASTIdent *ident; 
		ASTType *type; 
		ASTVar(ASTIdent *ident, ASTType *type); 
		std::string toString(); 	
};
class ASTRec : public ASTDec 
{ 
	public: 
		std::string toString(){return "rec";}
};
class ASTFun : public ASTDec 
{ 
	public: 
		std::string toString(){return "fun";}
};
class ASTProc : public ASTDec 
{ 
	public:  
		std::string toString(){return "proc";}
};

//AST STATEMENTS
//AST 0
class ASTSet : public ASTStat 
{ 
	public: 
		ASTIdent *ident; 
		ASTExpr *expr; 
		ASTSet(ASTIdent *ident, ASTExpr *expr); 
		std::string toString();
};
class ASTIf : public ASTStat 
{ 
	public: 
		ASTExpr *expr; 
		ASTBlock *block1; 
		ASTBlock *block2; 
		ASTIf(ASTExpr *expr, ASTBlock *block1, ASTBlock *block2); 
		std::string toString();
};
class ASTWhile : public ASTStat 
{ 
	public: 
		ASTExpr *expr; 
		ASTBlock *block; 
		ASTWhile(ASTExpr *expr, ASTBlock *block); 
		std::string toString();
};
class ASTEcho : public ASTStat 
{ 
	public: 
		ASTExpr *expr; 
		ASTEcho(ASTExpr *expr); 
		std::string toString();
};
class ASTCall : public ASTStat 
{ 
	public: 
		std::string toString(){return "call";}
};
class ASTReturn : public ASTStat 
{ 
	public: 
		std::string toString(){return "return";}
};

//AST EXPRESSIONS
//AST 0
class ASTExpr : public ASTNode 
{
	public: 
		virtual std::string toString(){return "expr";}
};
class ASTBool : public ASTExpr 
{ 
	public: 
		bool boolean; 
		ASTBool(bool boolean); 
		std::string toString(); 
};
class ASTNum : public ASTExpr 
{ 
	public: 
		int number; 
		ASTNum(int number); 
		std::string toString();
};
class ASTIdent : public ASTExpr 
{ 
	public: 
		std::string ident; 
		ASTIdent(std::string ident); 
		std::string toString(); 
};
class ASTOp : public ASTExpr 
{
	public: 
		virtual std::string toString(){return "op";}
}; //Abstract unary ou binary op
//AST 1

//AST OPERATIONS
//AST 0
class ASTUnaryOp : public ASTOp 
{ 
	public: 
		ASTExpr *expr; 
		virtual std::string toString(){return "unOp";}
}; //abstract
class ASTBinaryOp : public ASTOp 
{ 
	public: 
		ASTExpr *expr1; 
		ASTExpr *expr2; 
		virtual std::string toString(){return "binOp";}
}; //abstract

//AST BINARY OPERATIONS
//AST 0
class ASTAdd : public ASTBinaryOp 
{ 
	public: 
		ASTAdd(ASTExpr *expr1, ASTExpr *expr2); 
		std::string toString();
}; 
class ASTSub : public ASTBinaryOp 
{
	public: 
		ASTSub(ASTExpr *expr1, ASTExpr *expr2); 
		std::string toString();
};
class ASTMul : public ASTBinaryOp 
{
	public:
		ASTMul(ASTExpr *expr1, ASTExpr *expr2);
		std::string toString();
};
class ASTDiv : public ASTBinaryOp {
	public:
		ASTDiv(ASTExpr *expr1, ASTExpr *expr2);
		std::string toString();
};
class ASTLt : public ASTBinaryOp {
	public:
		ASTLt(ASTExpr *expr1, ASTExpr *expr2);
		std::string toString();
};
class ASTEq : public ASTBinaryOp {
	public:
		ASTEq(ASTExpr *expr1, ASTExpr *expr2);
		std::string toString();
};
class ASTAnd : public ASTBinaryOp {
	public:
		ASTAnd(ASTExpr *expr1, ASTExpr *expr2);
		std::string toString();
};
class ASTOr : public ASTBinaryOp {
	public:
		ASTOr(ASTExpr *expr1, ASTExpr *expr2);
		std::string toString();
};

//AST UNARY OPERATIONS
//AST 0
class ASTNot : public ASTUnaryOp {
	public:
		ASTNot(ASTExpr *expr);
		std::string toString();
};

//AST TYPES
//AST 0
class ASTType : public ASTNode {
	public:
		std::string toString(){return "type";}
		
}; //Abstract : void, bool ou int
class TYPEVoid : public ASTType {
	public:
		std::string toString(){return "void type";}
		
};
class TYPEBool : public ASTType {
	public:
		std::string toString(){return "bool type";}
		
};
class TYPEInt : public ASTType {
	public:
		std::string toString(){return "int type";}
		
};