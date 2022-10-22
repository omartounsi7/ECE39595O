#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>
#include "parser.h"
#include "SymbolTable.h"


std::vector<std::string> tokenizeStatement(std::string oneline)
{
    std::vector<std::string> stmt;
    
    char *token = strtok(const_cast<char*>(oneline.c_str()), " ");
    while (token != nullptr)
    {
        stmt.push_back(std::string(token));
        token = strtok(nullptr, " ");
    }

    return stmt;
}

int main(int argc, char* argv[]) {
    
    if (argc != 2){
        std::cerr << "Error: Invalid number of arguments!" << '\n';
        return EXIT_FAILURE;
    }

    std::ifstream filestream(argv[1]);

    if (!filestream.is_open()){
        std::cerr << "Error: Failed to open input file! " << '\n';
        return EXIT_FAILURE;
    }

    std::vector<std::vector<std::string>> assemblyprog; // Program will be a vector of vectors (statements).
    std::vector<std::string> assemblystmt; // Statements will be vectors of format <opcode,operand1,operand2>

    int linecount = 0; // Number of statements in the program.
    std::string oneline; // One line of code, in string format.
    
    while (filestream.good()){
        std::getline(filestream, oneline);
        assemblystmt = tokenizeStatement(oneline);
        assemblyprog.push_back(assemblystmt);
        linecount += 1;
    }

    // lincount is actually 1 less than its calculated value. The eof is considered a line.
    // Similarly, the last item in assembly prog is eof. It has 0 elements instead of 3 (no operands and no opcode)

    std::vector<std::string> teststmt;
    teststmt.push_back("Whats");
    teststmt.push_back("up");
    teststmt.push_back("bro");
    teststmt.push_back("!");
    
    // std::vector<std::vector<std::string>>::iterator p; 
    // p = assemblyprog.begin(); 
    // *p = teststmt;
    // *(p + 1) = teststmt;
    // *(p + 2) = teststmt;

    int pc = 0;
    int stmtc;

    while(pc < linecount - 1){
        stmtc = 0;
        while(stmtc < assemblyprog[pc].size()){
            std::cout << assemblyprog[pc][stmtc] << " " << std::endl;
            stmtc++;
        }
        pc++;
    }


    return EXIT_SUCCESS;

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