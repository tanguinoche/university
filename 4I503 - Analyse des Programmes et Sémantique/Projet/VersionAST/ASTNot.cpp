#include "AST.h"

ASTNot::ASTNot(ASTExpr *expr) {
    this->expr = expr;
}
std::string ASTNot::toString() {
    return std::string("app(not,[") + std::string(expr->toString()) + std::string("])");
}
