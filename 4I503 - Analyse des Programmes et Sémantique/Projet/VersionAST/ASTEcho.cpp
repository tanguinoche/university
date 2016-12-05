#include "AST.h"

ASTEcho::ASTEcho(ASTExpr *expr) {
    this->expr = expr;
}
std::string ASTEcho::toString() {
    return std::string("ECHO(") + std::string(expr->toString()) + std::string(")");
}
