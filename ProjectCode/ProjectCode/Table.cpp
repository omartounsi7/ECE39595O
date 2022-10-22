#include "Table.h"
#include <vector>
#include "SymbolTable.h"

TableEntry::TableEntry(double location, double length) {
	std::vector<double> entry;
	entry.push_back(location);
	entry.push_back(length);
}