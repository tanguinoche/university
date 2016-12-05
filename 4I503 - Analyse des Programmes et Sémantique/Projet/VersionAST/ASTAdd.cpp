#include "AST.h"

ASTAdd::ASTAdd(ASTExpr *expr1, ASTExpr *expr2) {
    this->expr1 = expr1;
    this->expr2 = expr2;
}
std::string ASTAdd::toString() {
    return std::string("app(add,[") + std::string(expr1->toString()) + std::string(",") + std::string(expr2->toString()) + std::string("])");
}
