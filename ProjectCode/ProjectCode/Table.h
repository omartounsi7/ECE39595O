#ifndef TABLE_H_
#define TABLE_H_
#include "SymbolTable.h"
#include <vector>

//Table entry of <location, length> double into symbol table
class TableEntry : public SymbolTable {
	public: 
		TableEntry(double location, double length);

};

#endif
