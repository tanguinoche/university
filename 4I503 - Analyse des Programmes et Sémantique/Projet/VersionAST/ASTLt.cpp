#include "AST.h"

ASTLt::ASTLt(ASTExpr *expr1, ASTExpr *expr2) {
    this->expr1 = expr1;
    this->expr2 = expr2;
}
std::string ASTLt::toString() {
    return std::string("app(lt,[") + std::string(expr1->toString()) + std::string(",") + std::string(expr2->toString()) + std::string("])");
}
