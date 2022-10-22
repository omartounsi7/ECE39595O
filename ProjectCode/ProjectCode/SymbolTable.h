 #ifndef SYMBOLTABLE_H_
 #define SYMBOLTABLE_H_

 #include <map>
 #include <string>
 
//SymbolTable maps from a varible/label key to a table entry
//Implemented as Singleton
 class SymbolTable {
 	public:		
        static std::map<std::string, std::vector<double>> makeSymbolTable();
        static int getData(std::string key);
        //bool putEntry(std::string key, int datum);
 	private:
 		int idx;
 		void *definedMap;
        SymbolTable();
 };

 
 
 #endif