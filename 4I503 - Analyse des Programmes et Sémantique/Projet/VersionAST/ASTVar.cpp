#include "AST.h"

ASTVar::ASTVar(ASTIdent *ident, ASTType *type) {
    this->ident = ident;
    this->type = type;
}
std::string ASTVar::toString() {
    return std::string("VAR(") + std::string(ident->toString()) + std::string(",") + std::string(type->toString()) + std::string(")");
}
