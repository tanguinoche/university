#include "AST.h"

ASTSet::ASTSet(ASTIdent *ident, ASTExpr *expr) {
    this->ident = ident;
    this->expr = expr;
}
std::string ASTSet::toString() {
    return std::string("SET(") + std::string(ident->toString()) + std::string(",") + std::string(expr->toString()) + std::string(")");
}
