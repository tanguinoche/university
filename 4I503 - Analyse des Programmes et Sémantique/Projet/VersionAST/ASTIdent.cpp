#include "AST.h"

ASTIdent::ASTIdent(std::string ident) {
    this->ident = ident;
}
std::string ASTIdent::toString() {
    return this->ident;
}
