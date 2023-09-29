#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <cstring>
#include <vector>

std::multimap<std::string, std::vector<int>> sT; // symbol table: maps token to its table entry <location, size>.
std::vector<std::vector<std::string>>iB; // instruction buffer: contains program instructions.
std::vector<std::string> sB; // string buffer: contains strings to be printed.
typedef std::multimap<std::string, std::vector<int>>::iterator iterator;
int memoryptr = 0;
int routineStack = 0;
int sBindex = 0;
int mainVarCount = 0;
std::string tempString;
int memoryptr_backup = 0;

bool read2opStmt(std::vector<std::string> assemblystmt){
    if(assemblystmt[0] == "declarr") {
        // do stuff
    } else {
        return false;
    }
    return true;
}

bool read1opStmt(std::vector<std::string> assemblystmt){
    if(assemblystmt[0] == "declscal") {
        sT.insert(std::pair<std::string, std::vector<int>>(assemblystmt[1],(std::vector<int>){memoryptr++, 1}));
        if(!routineStack){
            mainVarCount++;
        }
    } else if (assemblystmt[0] == "label"){
        sT.insert(std::pair<std::string, std::vector<int>>(assemblystmt[1],(std::vector<int>){(int)iB.size(), 0}));
    } else if (assemblystmt[0] == "gosublabel"){
        sT.insert(std::pair<std::string, std::vector<int>>(assemblystmt[1],(std::vector<int>){(int)iB.size(), 0}));
        iB.push_back({"OP_ENTER_SUBROUTINE", assemblystmt[1]});
        routineStack++;
        memoryptr_backup = memoryptr - 1;
    } else if (assemblystmt[0] == "jump"){
        iB.push_back({"OP_JUMP", assemblystmt[1]}); 
    } else if (assemblystmt[0] == "jumpzero"){
        iB.push_back({"OP_JUMPZERO", assemblystmt[1]}); 
    } else if (assemblystmt[0] == "jumpnzero"){
        iB.push_back({"OP_JUMPNZERO", assemblystmt[1]}); 
    } else if (assemblystmt[0] == "gosub"){
        iB.push_back({"OP_GOSUB", assemblystmt[1]}); 
    } else if (assemblystmt[0] == "pushscal"){
        for (auto it = sT.begin(); it != sT.end(); ++it){
            if(it->first == assemblystmt[1]){
                tempString = std::to_string(it->second[0]);
            }
        }
        iB.push_back({"OP_PUSHSCALAR", tempString});  
    } else if (assemblystmt[0] == "pusharr"){
        // do stuff
    } else if (assemblystmt[0] == "pushi"){
        iB.push_back({"OP_PUSHI", assemblystmt[1]}); 
    } else if (assemblystmt[0] == "popscal"){
        for (auto it = sT.begin(); it != sT.end(); ++it){
            if(it->first == assemblystmt[1]){
                tempString = std::to_string(it->second[0]);
            }
        }
        iB.push_back({"OP_POPSCALAR", tempString});   
    } else if (assemblystmt[0] == "poparr"){
        // do stuff
    } else if (assemblystmt[0] == "prints"){
        sB.push_back(assemblystmt[1]);
        iB.push_back({"OP_PRINTS", std::to_string(sBindex++)}); 
    } else {
        return false;
    }
    return true;
}

bool read0opStmt(std::vector<std::string> assemblystmt){
    if(assemblystmt[0] == "start") {
        iB.push_back({"OP_START_PROGRAM", "?"}); 
    } else if (assemblystmt[0] == "end"){
        // end the program
    } else if (assemblystmt[0] == "return"){
        iB.push_back({"OP_RETURN"});
        routineStack--;
        std::pair<iterator, iterator> iterpair;
        for (auto it = sT.begin(); it != sT.end(); ++it){
            iterpair = sT.equal_range(it->first);
            if(iterpair.first != iterpair.second)
            {
                for (iterator it = iterpair.first; it != iterpair.second; ++it) {
                    if (it->second[1] == 1 && it->second[0] > memoryptr_backup) { 
                        sT.erase(it);
                        break;
                    }
                }
            }
            else{
                if (it->second[1] == 1 && it->second[0] > memoryptr_backup) { 
                    sT.erase(it);
                    break;
                }                
            }
        }
    } else if (assemblystmt[0] == "exit"){
        iB.push_back({"OP_EXIT_PROGRAM"}); 
    } else if (assemblystmt[0] == "pop"){
        iB.push_back({"OP_POP"}); 
    } else if (assemblystmt[0] == "dup"){
        iB.push_back({"OP_DUP"}); 
    } else if (assemblystmt[0] == "swap"){
        iB.push_back({"OP_SWAP"}); 
    } else if (assemblystmt[0] == "add"){
        iB.push_back({"OP_ADD"}); 
    } else if (assemblystmt[0] == "negate"){
        iB.push_back({"OP_NEGATE"}); 
    } else if (assemblystmt[0] == "mul"){
        iB.push_back({"OP_MUL"}); 
    } else if (assemblystmt[0] == "div"){
        iB.push_back({"OP_DIV"}); 
    } else if (assemblystmt[0] == "printtos"){
        iB.push_back({"OP_PRINTTOS"}); 
    } else {
        return false;
    }
    return true;
}

bool readStmt(std::vector<std::string> assemblystmt){
    if(assemblystmt.size() == 3){
        return read2opStmt(assemblystmt);
    } else if(assemblystmt.size() == 2){
        return read1opStmt(assemblystmt);
    } else if(assemblystmt.size() == 1){
        return read0opStmt(assemblystmt);
    } else if(assemblystmt.size() == 0){
        return true;
    }
    return false;
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

std::string stmt2opcode (std::string stmt){

    if (stmt == "OP_JUMP"){
        return "Jump";
    } else if (stmt == "OP_JUMPZERO"){
        return "JumpZero";
    } else if (stmt == "OP_JUMPNZERO"){
        return "JumpNZero";
    } else if (stmt == "OP_GOSUB"){
        return "GoSub";
    } else if (stmt == "OP_RETURN"){
        return "Return";
    } else if (stmt == "OP_START_PROGRAM"){
        return "Start";
    } else if (stmt == "OP_EXIT_PROGRAM"){
        return "Exit";
    } else if (stmt == "OP_PUSHSCALAR"){
        return "PushScalar";
    } else if (stmt == "OP_PUSHARRAY"){
        return "PushArray";
    } else if (stmt == "OP_PUSHI"){
        return "PushI";
    } else if (stmt == "OP_POP"){
        return "Pop";
    } else if (stmt == "OP_DUP"){
        return "Dup";
    } else if (stmt == "OP_SWAP"){
        return "Swap";
    } else if (stmt == "OP_ADD"){
        return "Add";
    } else if (stmt == "OP_NEGATE"){
        return "Negate";
    } else if (stmt == "OP_MUL"){
        return "Mul";
    } else if (stmt == "OP_DIV"){
        return "Div";
    } else if (stmt == "OP_PRINTS"){
        return "Prints";
    } else if (stmt == "OP_PRINTTOS"){
        return "PrintTOS";
    } else if (stmt == "OP_POPSCALAR"){
        return "PopScalar";
    } else if (stmt == "OP_POPARRAY"){
        return "PopArray";
    } else if (stmt == "OP_ENTER_SUBROUTINE"){
        return "GoSubLabel";
    } else if (stmt == "OP_EXIT_SUBROUTINE"){
        return "?";
    }
    return "error";
}

void patchiB (){
    
    for(int i = 0 ; i < iB.size() ; i++){
        
        if (iB[i][0] == "OP_JUMP"){
            iterator p = sT.find(iB[i][1]);
            iB[i][1] = std::to_string(p->second[0]);
            continue;
        } else if (iB[i][0] == "OP_JUMPZERO"){
            iterator p = sT.find(iB[i][1]);
            iB[i][1] = p->second[0];
            continue;
        } else if (iB[i][0] == "OP_JUMPNZERO"){
            iterator p = sT.find(iB[i][1]);
            iB[i][1] = std::to_string(p->second[0]);
            continue;
        } else if (iB[i][0] == "OP_GOSUB"){
            iterator p = sT.find(iB[i][1]);
            iB[i][1] = std::to_string(p->second[0]);
            continue;
        } else if (iB[i][0] == "OP_START_PROGRAM"){
            iB[i][1] = std::to_string(mainVarCount);
            continue;
        } else if (iB[i][0] == "OP_ENTER_SUBROUTINE"){
            iB[i][1] = std::to_string(memoryptr - memoryptr_backup - 1);
            continue;
        }
    }
}

std::string readiB () {
    std::string output;
    for(int i = 0 ; i < iB.size() ; i++){
        output += stmt2opcode(iB[i][0]);
        for(int y = 1 ; y < iB[i].size() ; y++)
        {
            output += " " + iB[i][y];
        }
        output += "\n";
    }
    return output;
}

int main(int argc, char* argv[])
{
    if (argc != 2){
        std::cerr << "error: invalid number of arguments" << '\n';
        return EXIT_FAILURE;
    }

    std::ifstream inputFile;
    inputFile.open(argv[1]);

    if (!inputFile.is_open()){
        std::cerr << "error: failed to open input file" << '\n';
        return EXIT_FAILURE;
    }

    std::vector<std::vector<std::string>> assemblyprog; // Program will be a vector of vectors (statements).
    std::vector<std::string> assemblystmt; // Statements will be vectors of format <opcode,operand1,operand2>

    int linecount = 0; // Number of statements in the program.
    std::string oneline; // One line of code, in string format.
    
    while (inputFile.good()){
        std::getline(inputFile, oneline);
        assemblystmt = tokenizeStatement(oneline);
        assemblyprog.push_back(assemblystmt);
        linecount += 1;
    }

    linecount -= 1;
    // lincount is actually 1 less than its calculated value. The eof is considered a line.
    // Similarly, the last item in assembly prog is eof. It has 0 elements instead of 3 (no operands and no opcode)

    int pc = 0;
    while(pc < linecount){
        if(!readStmt(assemblyprog[pc])){
            std::cerr << "error: could not read instruction at line " << pc << "\n";
            return EXIT_FAILURE;
        }
        pc++;
    }

    // std::cout << "Symbol Table" << std::endl;
    // for (auto it = sT.begin(); it != sT.end(); ++it){
    //     std::cout << it->first;
    //     std::cout << ", <";
    //     std::cout << it->second[0];
    //     std::cout << ", ";
    //     std::cout <<  it->second[1];
    //     std::cout << ">" << std::endl;
    // }

    // std::cout << "iB" << std::endl;
    // for(int i = 0 ; i < iB.size() ; i++){
    //     for(int y = 0 ; y < iB[i].size() ; y++)
    //     {
    //         std::cout << iB[i][y];
    //     }
    //     std::cout << std::endl;
    // }

    patchiB();
    std::string output;
    std::vector<std::string>::iterator p = sB.begin();

    while (p != sB.end()){
        output += *p++ + "\n";
    }
    output += readiB();

    std::cout << output;

    // std::ofstream outputFile;
    // outputFile.open((std::string)argv[1] + ".pout");
    // outputFile << output;

    // outputFile.close();
    inputFile.close();
    return EXIT_SUCCESS;
}