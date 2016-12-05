#include "AST.h"

ASTIf::ASTIf(ASTExpr *expr, ASTBlock *block1, ASTBlock *block2) {
    this->expr = expr;
    this->block1 = block1;
    this->block2 = block2;
}
std::string ASTIf::toString() {
    return std::string("IF(") + std::string(expr->toString()) + std::string("),[") + std::string(block1->toString()) + std::string("],[") + std::string(block2->toString()) + std::string("]");
}
