#include "AST.h"

ASTProg::ASTProg(ASTBlock *block) {
    this->block = block;
}
std::string ASTProg::toString() {
    return block->toString();
}
