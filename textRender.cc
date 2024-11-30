#include <string>
#include <vector>
#include <stdexcept>

#include "textRender.h"
#include "block.h"

using namespace std;

// Header Rendering
vector<string> TextRender::header(int score, int level, Coord box, bool isTurn)
{
	vector<string> output;

	output.push_back(string(box.x, '-'));

	if (score < 10)
	{
		output.push_back("Score:    " + to_string(score));
	}
	else if (score < 100)
	{
		output.push_back("Score:   " + to_string(score));
	}
	else if (score < 1000)
	{
		output.push_back("Score:  " + to_string(score));
	}
	else if (score < 10000)
	{
		output.push_back("Score: " + to_string(score));
	}
	else
	{
		output.push_back("Score:" + to_string(score));
	}

	output.push_back("Level:    " + to_string(level));

	if (isTurn)
	{
		output.push_back(string(box.x, '*'));
	}
	else
	{
		output.push_back(string(box.x, '-'));
	}

	return output;
}

// Body Rendering
vector<string> TextRender::body(vector<Grid *> grids, Coord box)
{
	vector<string> output(box.y, string(box.x, ' '));

	for (Grid *object : grids)
	{
		for (int i = 0; i < object->blockGrid.size(); i++)
		{
			for (int j = 0; j < object->blockGrid[0].size(); j++)
			{
				try
				{
					// Skip empty cells
					if ((*object)[i][j].isEmpty())
					{
						continue;
					}
					// Place the grid value into the output board
					output.at(i + object->gridPosition.y).at(j + object->gridPosition.x) = (*object)[i][j].getVal();
				}
				catch (out_of_range)
				{
				}
			}
		}
	}

	return output;
}

// Footer Rendering
vector<string> TextRender::footer(Block *next, Coord box)
{
	vector<string> output;

	output.insert(output.begin(), string(box.x, '-'));
	output.insert(output.begin(), "Next:      ");
	output.insert(output.begin(), string(box.x, ' '));
	output.insert(output.begin(), string(box.x, ' '));

	for (int i = 0; i < next->getRow(); i++)
	{
		for (int j = 0; j < next->getColumn(); j++)
		{
			output[i][j] = (*next)[i][j].getVal();
		}
	}

	return output;
}
