#include "AST.h"

ASTBool::ASTBool(bool boolean) {
    this->boolean = boolean;
}
std::string ASTBool::toString() {
    return this->boolean ? "true" : "false";
}
