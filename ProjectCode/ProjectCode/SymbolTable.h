#ifndef SYMBOLTABLE_H_
#define SYMBOLTABLE_H_

#include <map>
#include <string>

class SymbolTable {
	public:
		SymbolTable();

	private:
		int idx;
		void *definedMap;

};
#endif
