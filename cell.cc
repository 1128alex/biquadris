#include "cell.h"

Cell::Cell(char val, int id, int level) : val{val}, id{id}, level{level} {};

bool Cell::isEmpty()
{
	return val == ' ';
}

char Cell::getVal()
{
	return val;
}

void Cell::setVal(char newVal)
{
	val = newVal;
}

int Cell::getID()
{
	return id;
}

void Cell::setID(int id)
{
	this->id = id;
}

int Cell::getLevel()
{
	return level;
}

void Cell::setLevel(int level)
{
	this->level = level;
}
