 #include <map>
 #include <string>
 #include <vector>
 #include "SymbolTable.h"
 #include "Table.h"
 


 SymbolTable::SymbolTable() {
 	definedMap = new std::map<std::string, std::vector<double>>();
 	idx = 0;
 }
 std::map<std::string, std::vector<double>> SymbolTable::makeSymbolTable() {
 	if (!mapDefined) {
 		mapDefined = std::map<std::string, std::vector<double>>();
 	}
 	return mapDefined;
 }
 int SymbolTable::getData(std::string key) {
     if (!mapDefined) {
         return -1;
         for (auto const& e : *definedMap) {
             if (e.first == key) {
                 return x.second;
             }
         }
     }
 }
 
