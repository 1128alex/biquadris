#include <stdexcept>

#include "grid.h"

using namespace std;

Grid::Grid() : blockGrid{vector<vector<Cell>>()} {}

Grid::Grid(Grid &grid)
{
	blockGrid.clear();
	for (int i = 0; i < grid.blockGrid.size(); i++)
	{
		blockGrid.push_back(grid.blockGrid[i]);
	}
}

bool Grid::collide(Grid &grid)
{
	if (grid.gridPosition.x < gridPosition.x || grid.gridPosition.y < gridPosition.y || grid.gridPosition.y + grid.blockGrid.size() > gridPosition.y + blockGrid.size() || grid.gridPosition.x + grid.blockGrid[0].size() > gridPosition.x + blockGrid[0].size())
	{
		return true;
	}

	Grid *smallerGrid;
	Grid *largerGrid;

	if (blockGrid.size() * blockGrid[0].size() > grid.blockGrid.size() * grid.blockGrid[0].size())
	{
		smallerGrid = &grid;
		largerGrid = this;
	}
	else
	{
		largerGrid = &grid;
		smallerGrid = this;
	}

	for (int i = 0; i < smallerGrid->blockGrid.size(); i++)
	{
		for (int j = 0; j < smallerGrid->blockGrid[i].size(); j++)
		{
			try
			{
				if (!smallerGrid->blockGrid.at(i).at(j).isEmpty() && !largerGrid->blockGrid.at(i + smallerGrid->gridPosition.y - largerGrid->gridPosition.y).at(j + smallerGrid->gridPosition.x - largerGrid->gridPosition.x).isEmpty())
				{
					return true;
				}
			}
			catch (out_of_range)
			{
			}
		}
	}
	return false;
}

void Grid::dropBlock(Grid &grid)
{

	for (int i = 0; i < grid.blockGrid.size(); i++)
	{
		for (int j = 0; j < grid.blockGrid[i].size(); j++)
		{
			// Skip empty cells.
			if (grid.blockGrid[i][j].isEmpty())
			{
				continue;
			}
			blockGrid[i + grid.gridPosition.y - gridPosition.y][j + grid.gridPosition.x - gridPosition.y] = grid.blockGrid[i][j];
		}
	}
}

Cell &Grid::operator[](Coord &coord)
{
	return blockGrid[(coord - gridPosition).y][(coord - gridPosition).x];
}

vector<Cell> &Grid::operator[](int idx)
{
	return blockGrid[idx];
}

vector<Cell> &Grid::at(int idx)
{
	return blockGrid.at(idx);
}

Grid::~Grid() {}
