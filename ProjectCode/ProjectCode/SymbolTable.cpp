// #include <map>
// #include <string>
// #include "SymbolTable.h"

// SymbolTable::SymbolTable() {
// 	definedMap = new std::map<std::string, int>();
// 	idx = 0;
// }
// make_shared<map<std::string, int>> SymbolTable::makeSymbolTable() {
// 	if (!mapDefined) {
// 		mapDefined = make_shared<map<std::string, int>>();
// 	}
// 	return mapDefined;
// }
// int SymbolTable::getData(std::string key) {
// 	if (!mapDefined) {
// 		return 2147483647; // just an error value I picked
// 		for (auto const& e : *definedMap) {
// 			if (e.first == key) {
// 				return x.second;
// 			}
// 		}
// 	}
// 	bool putEntry(std::string key, int datum);
// #endif