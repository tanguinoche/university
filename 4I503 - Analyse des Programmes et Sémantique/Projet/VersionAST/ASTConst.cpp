#include "AST.h"

ASTConst::ASTConst(ASTIdent *ident, ASTType *type, ASTExpr *expr){
    this->ident = ident;
    this->type = type;
    this->expr = expr;
}
std::string ASTConst::toString() {
    return std::string("SET(") + std::string(ident->toString()) + std::string(",") + std::string(expr->toString()) + std::string(")");
}
