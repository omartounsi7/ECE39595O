#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>
#include "parser.h"
#include "SymbolTable.h"


void twoOperandsClub(std::vector<std::string> assemblystmt, std::string& output){

// declarr

if(assemblystmt[0] == "declarr") {
    // do things
} else{
    // error!
}
}

void oneOperandsClub(std::vector<std::string> assemblystmt, std::string& output){
// declscal
// label
// gosublabel
// jump
// jumpzero
// jumpnzero
// gosub
// pushscal
// pusharr
// pushi
// popscal
// poparr

if(assemblystmt[0] == "declscal") {
    // do things
} else if (assemblystmt[0] == "label"){
    output += "Label " + assemblystmt[1] + "\n";
} else if (assemblystmt[0] == "gosublabel"){
    output += "GoSubLabel " + assemblystmt[1] + "\n";
} else if (assemblystmt[0] == "jump"){
    output += "Jump, " + assemblystmt[1] + "\n";
} else if (assemblystmt[0] == "jumpzero"){
    output += "JumpZero, " + assemblystmt[1] + "\n";
} else if (assemblystmt[0] == "jumpnzero"){
    output += "JumpNZero, " + assemblystmt[1] + "\n";
} else if (assemblystmt[0] == "gosub"){
    output += "GoSub" + assemblystmt[1] + "\n";
} else if (assemblystmt[0] == "pushscal"){
    output += "PushScalar " + assemblystmt[1] + ", \n";
} else if (assemblystmt[0] == "pusharr"){
    output += "PushArray " + assemblystmt[1] + "\n";
} else if (assemblystmt[0] == "pushi"){
    output += "PushI  (" + assemblystmt[1] + ")\n";
} else if (assemblystmt[0] == "popscal"){
    output += "PopScalar " + assemblystmt[1] + ", \n";
} else if (assemblystmt[0] == "poparr"){
    output += "PopArray " + assemblystmt[1] + "\n";
} else {
    // error
}

}

void zeroOperandsClub(std::vector<std::string> assemblystmt, std::string& output){
// start
// end
// exit
// return
// pop
// dup
// swap
// add
// negate
// mul
// div
// printtos
// prints

if(assemblystmt[0] == "start") {
    output += "Start 0\n";
} else if (assemblystmt[0] == "end"){
    // end the program
} else if (assemblystmt[0] == "exit"){
    output += "Exit";
} else if (assemblystmt[0] == "return"){
    output += "Return\n";
} else if (assemblystmt[0] == "pop"){
    output += "Pop\n";
} else if (assemblystmt[0] == "dup"){
    output += "Dup\n";
} else if (assemblystmt[0] == "swap"){
    output += "Swap\n";
} else if (assemblystmt[0] == "add"){
    output += "Add\n";
} else if (assemblystmt[0] == "negate"){
    output += "Negate\n";
} else if (assemblystmt[0] == "mul"){
    output += "Mul\n";
} else if (assemblystmt[0] == "div"){
    output += "Div\n";
} else if (assemblystmt[0] == "printtos"){
    output += "PrintTOS\n";
} else if (assemblystmt[0] == "prints"){
    output += "Prints\n";
} else {
    // error
}
}

int doSomethingwithStmt(std::vector<std::string> assemblystmt, std::string& output){
    if(assemblystmt.size() == 3){
        twoOperandsClub(assemblystmt, output);
        return(1);
    } else if(assemblystmt.size() == 2){
        oneOperandsClub(assemblystmt, output);
        return(1);
    } else if(assemblystmt.size() == 1){
        zeroOperandsClub(assemblystmt, output);
        return(1);
    } else if(assemblystmt.size() == 0){
        return(0);
    }
    return (0);
}

std::vector<std::string> tokenizeStatement(std::string oneline) {
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
    linecount -= 1;

    // std::vector<std::string> teststmt;
    // teststmt.push_back("whats");
    // teststmt.push_back("up");
    // teststmt.push_back("bro");
    // teststmt.push_back("!");
    
    // std::vector<std::vector<std::string>>::iterator p; 
    // p = assemblyprog.begin(); 
    // *p = teststmt;
    // *(p + 1) = teststmt;
    // *(p + 2) = teststmt;

    std::string output;
    int pc = 0;

    while(pc < linecount){
        if(!doSomethingwithStmt(assemblyprog[pc], output)){
            std::cerr << "Error: Could not read an instruction!" << '\n';
            return EXIT_FAILURE;
        }
        pc++;
    }    

    // WRITE OUTPUT TO OUTPUT FILE
    // WRITE ERRORS TO ERROR FILE
    std::cout << output << std::endl;

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