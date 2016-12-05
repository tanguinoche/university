#include "AST.h"

ASTDiv::ASTDiv(ASTExpr *expr1, ASTExpr *expr2) {
    this->expr1 = expr1;
    this->expr2 = expr2;
}
std::string ASTDiv::toString() {
    return std::string("app(div,[") + std::string(expr1->toString()) + std::string(",") + std::string(expr2->toString()) + std::string("])");
}
