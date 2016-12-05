#include "AST.h"

ASTBlock::ASTBlock(std::list<ASTCmds> *cmds) {
    this->cmds = cmds;
}

std::string ASTBlock::toString() {
    std::string str ="";
    for (std::list<ASTCmds>::const_iterator iterator = cmds->begin(), end = cmds->end(); iterator != end; ++iterator) {
        str += iterator->toString();
    }
    return str;
}
