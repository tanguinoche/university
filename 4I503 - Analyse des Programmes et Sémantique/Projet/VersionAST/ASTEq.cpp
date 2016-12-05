#include "AST.h"

ASTEq::ASTEq(ASTExpr *expr1, ASTExpr *expr2) {
    this->expr1 = expr1;
    this->expr2 = expr2;
}
std::string ASTEq::toString() {
    return std::string("app(eq,[") + std::string(expr1->toString()) + std::string(",") + std::string(expr2->toString()) + std::string("])");;
}
