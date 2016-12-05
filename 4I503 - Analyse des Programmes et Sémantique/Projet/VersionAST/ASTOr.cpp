#include "AST.h"

ASTOr::ASTOr(ASTExpr *expr1, ASTExpr *expr2) {
    this->expr1 = expr1;
    this->expr2 = expr2;
}
std::string ASTOr::toString() {
    return std::string("app(or,[") + std::string(expr1->toString()) + std::string(",") + std::string(expr2->toString()) + std::string("])");
}
