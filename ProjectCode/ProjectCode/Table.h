#ifndef TABLE_H_
#define TABLE_H_

#include <vector>

//Table entry of <location, length> double into symbol table
class TableEntry {
	public:
		TableEntry(double location, double length);
		
    private:
		double location;
		double length;
};

#endif
