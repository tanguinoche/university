#include "AST.h"

ASTWhile::ASTWhile(ASTExpr *expr, ASTBlock *block) {
    this->expr = expr;
    this->block = block;
}
std::string ASTWhile::toString() {
    return std::string("WHILE(") + std::string(expr->toString()) + std::string(",") + std::string(block->toString()) + std::string(")");
}
