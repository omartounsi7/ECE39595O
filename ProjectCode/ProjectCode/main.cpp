#include <iostream>

#include "parser.h"
#include "SymbolTable.h"

int main(int argc, char* argv[]) {


}

/* Omar: We need to do the following:
1) Open up the file containing the instructions
2) Read the instructions one by one.
    An instruction is of form: opcode [operand [operand]].
    We must read line by line.
    We need to read the opcode first. Read until we reach a space basically.
    Determine how many operands the opcode takes.
    Read them.
3) Execute the instructions one by one.
*/