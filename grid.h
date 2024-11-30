#ifndef GRID_H
#define GRID_H

#include <vector>

#include "cell.h"
#include "coord.h"

using namespace std;

class TextRender;

class Grid
{
public:
	Grid();
	Grid(Grid &grid);

	virtual bool collide(Grid &grid);
	void dropBlock(Grid &grid);

	Cell &operator[](Coord &coord);

	vector<Cell> &operator[](int idx);

	vector<Cell> &at(int idx);

	friend class TextRender;

	virtual ~Grid();

protected:
	vector<vector<Cell>> blockGrid;

	Coord gridPosition;
};

#endif
