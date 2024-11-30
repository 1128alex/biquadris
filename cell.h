#ifndef CELL_H
#define CELL_H

// Represents a single cell with associated value, ID, and level
class Cell
{
public:
	Cell(char newVal = ' ', int id = -1, int level = -1);

	bool isEmpty();

	char getVal();
	void setVal(char newVal);

	int getID();
	void setID(int id);

	int getLevel();
	void setLevel(int level);

private:
	char val;
	int id;
	int level;
};

#endif
