#include "AST.h"

ASTNum::ASTNum(int number) {
    this->number = number;
}
std::string ASTNum::toString() {
    std::string str = this->number+"";
    return str;
}
