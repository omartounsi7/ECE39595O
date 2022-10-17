#include <iostream>
#include <fstream>
#include <string>
using namespace std;
#include "parser.h"
#include "SymbolTable.h"

void read_infile(const char* input)
{
    std::ifstream file(input);
    if (file) {
        std::cout << file.rdbuf();
    }
    else {
        std::cerr << "Failed to open file" << '\n';
    }
}

int main(int argc, char* argv[]) {
    
    if (argc == 2) {
        read_infile(argv[1]);
    }
    else {
        return;
    }

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