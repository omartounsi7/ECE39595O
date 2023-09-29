#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <cstring>
#include <vector>

//std::multimap<std::string, std::vector<int>> sT;
std::vector<std::vector<std::string>>iB; // instruction buffer: contains program instructions.
std::vector<std::string> sB; // string buffer: contains strings to be printed.
std::vector<int> rS; // runtime stack
std::vector<int> rA; // return address
std::vector<std::vector<std::string>> dM; // data memory
int scopeVars = 0;
std::vector<int>::iterator it;

bool readProg(){
    for(int i = 0 ; i < iB.size() ; i++){
        //std::cout << "hello the pc is " + std::to_string(i) + " and life is good " << std::endl;
        if(iB[i][0] == "OP_JUMP"){
            i = stoi(iB[i][1]) - 1; // Problem here?
        }else if(iB[i][0] == "OP_JUMPZERO"){
            it = rS.begin();
            if(*it == 0){
                i = stoi(iB[i][1]) - 1; // Problem here?
            }
            rS.erase(rS.begin());
        }else if(iB[i][0] == "OP_JUMPNZERO"){

        }else if(iB[i][0] == "OP_GOSUB"){
            rA.push_back(i + 1);
            i = stoi(iB[i][1]) - 1; // Problem here?
        }else if(iB[i][0] == "OP_RETURN"){
            //std::cout << rA.back() - 1 << std::endl;
            i = rA.back() - 1; // Problem here?
            rA.pop_back();
            for(int l = 0 ; l < scopeVars ; l++) {
                dM.pop_back();
            }
            scopeVars = 0;
        }else if(iB[i][0] == "OP_ENTER_SUBROUTINE"){
            scopeVars = stoi(iB[i][1]);
            std::vector<std::string> variable;
            variable.push_back(std::string("PH"));
            variable.push_back(std::string("zero"));
            for(int l = 0 ; l < scopeVars ; l++) {
                dM.push_back(variable);
            }
        }else if(iB[i][0] == "OP_EXIT_SUBROUTINE"){

        }else if(iB[i][0] == "OP_START_PROGRAM"){
            int outerScopeVars = stoi(iB[i][1]);
            std::vector<std::string> variable;
            variable.push_back(std::string("PH"));
            variable.push_back(std::string("zero"));
            for(int l = 0 ; l < outerScopeVars ; l++) {
                dM.push_back(variable);
                //std::cout << "do i execute?\n"; 
            }
        }else if(iB[i][0] == "OP_EXIT_PROGRAM"){

        }else if(iB[i][0] == "OP_PUSHSCALAR"){
            int index = stoi(iB[i][1]);
            if(dM.at(index).at(1) == "zero"){
                continue;
            }
            rS.push_back(stoi(dM.at(index).at(1)));
        }else if(iB[i][0] == "OP_PUSHARRAY"){
            int e = stoi(iB[i][1]);
            e += rS.back();

            if(e >= dM.size()){
                continue;
            }
            if(dM.at(e).at(1) == "zero"){
                continue;
            }
            rS.push_back(stoi(dM.at(e).at(1)));
            

        }else if(iB[i][0] == "OP_PUSHI"){
            int num = stoi(iB[i][1]);
            it = rS.begin();
            it = rS.insert (it, num);
        }else if(iB[i][0] == "OP_POPSCALAR"){
            int scalar = rS.back();
            rS.pop_back();
            for(int c = dM.size() - 1 ; c >= 0 ; c--){
                if (dM.at(c).at(0) == "PH"){
                    //std::cout << "do i execute?\n"; 
                    dM.at(c).at(0) = "B";
                    dM.at(c).at(1) = std::to_string(scalar);
                    break;
                }
            }
        }else if(iB[i][0] == "OP_POPARRAY"){
            int e = stoi(iB[i][1]);
            e += rS.back();
            rS.pop_back();
            int scalar = rS.back();
            rS.pop_back();
            if(e < dM.size() && dM.at(e).at(0) == "PH"){
                dM.at(e).at(0) = "B";
                dM.at(e).at(1) = std::to_string(scalar);
            }
        }else if(iB[i][0] == "OP_POP"){
            rS.erase(rS.begin());
        }else if(iB[i][0] == "OP_DUP"){
            int scalar = rS.back();
            rS.push_back(scalar);
        }else if(iB[i][0] == "OP_SWAP"){
            // if (rS.size() > 1){
            //     int temp = rS[rS.size() - 1];
            //     rS[rS.size() - 1] = rS[rS.size() - 2];
            //     rS[rS.size() - 2] = temp;
            // }
        }else if(iB[i][0] == "OP_ADD"){
            if(rS.size() > 1){
                rS[rS.size() - 2] += rS[rS.size() - 1];
                rS.pop_back();
            }
        }else if(iB[i][0] == "OP_NEGATE"){
            if(rS.size() > 1){
                rS[rS.size() - 2] -= rS[rS.size() - 1];
                rS.pop_back();
            } else{
                rS[rS.size() - 1] = 0 - rS[rS.size() - 1];
            }
        }else if(iB[i][0] == "OP_MUL"){
            rS[rS.size() - 2] *= rS[rS.size() - 1];
            rS.pop_back();
        }else if(iB[i][0] == "OP_DIV"){
            rS[rS.size() - 2] /= rS[rS.size() - 1];
            rS.pop_back();
        }else if(iB[i][0] == "OP_PRINTS"){
            std::cout << sB[stoi(iB[i][1])] << std::endl;
        }else if(iB[i][0] == "OP_PRINTTOS"){
            std::cout << rS[rS.size() - 1] << std::endl;
            rS.pop_back();
        }else{
            return false;
        }
    }
    return true;
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

int main(int argc, char* argv[]){
    if (argc != 2){
        std::cerr << "error: invalid number of input arguments to the vm" << '\n';
        return EXIT_FAILURE;
    }

    std::ifstream inFile(argv[1], std::ios::in | std::ios::binary);

    if (!inFile.is_open()){
        std::cerr << "error: failed to open input file to the vm" << '\n';
        return EXIT_FAILURE;
    }

    std::string oneline;
    std::vector<std::string> assemblystmt;


    while (inFile.good()){
        std::getline(inFile, oneline);
        if(oneline == "Instruction Buffer"){ continue; }
        if(oneline == "String Buffer"){ break; }
        assemblystmt = tokenizeStatement(oneline);
        iB.push_back(assemblystmt);
    }

    while (inFile.good()){
        std::getline(inFile, oneline);
        if(oneline == "String Buffer"){ continue; }
        if(oneline == "EOF"){ break; }
        sB.push_back(oneline);
    }


    if(!readProg()){
        std::cerr << "error: vm failed to read the parsed program" << '\n';
        return EXIT_FAILURE;        
    }

    // std::cout << "Instruction Buffer" << std::endl;
    // for(int i = 0 ; i < iB.size() ; i++){
    //     for(int y = 0 ; y < iB[i].size() ; y++)
    //     {
    //         std::cout << iB[i][y] + " ";
    //     }
    //     std::cout << std::endl;
    // }

    // std::cout << "String Buffer" << std::endl;
    // for(int i = 0 ; i < sB.size() ; i++){
    //     std::cout << sB[i] << std::endl;
    // }

    inFile.close( );
    return EXIT_SUCCESS;
}