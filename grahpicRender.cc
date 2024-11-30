#include <stdexcept>

#include "grahpicRender.h"

using namespace std;

GraphicsRender::GraphicsRender(int width, int height) : width{width}, height{height}, xwindow{width, height} {}

void GraphicsRender::render(vector<vector<string>> result)
{
	// Calculate the width of each board and the size of each cell.
	const int boardWidth = width / result.size();
	const int pixelWidth = boardWidth / result[0][0].size();
	const int pixelHeight = height / result[0].size();

	// board
	for (int i = 0; i < result.size(); i++)
	{
		// row
		for (int j = 0; j < result[i].size(); j++)
		{
			// pixel
			for (int k = 0; k < result[i][j].size(); k++)
			{
				try
				{ // Skip rendering if the cell has not changed.
					if (result[i][j][k] == prev.at(i).at(j).at(k))
					{
						continue;
					}
				}
				catch (out_of_range)
				{
				}

				xwindow.fillRectangle(i * boardWidth + pixelWidth * k, (result[i].size() - j - 1) * pixelWidth, pixelWidth, pixelHeight, charToColour(result[i][j][k]));
			}
		}
	}

	// Save the current render state for comparison in the next render call.
	prev = result;
}

int GraphicsRender::charToColour(char color)
{
	switch (color)
	{
	case ' ':
		return 0;
	case 'I':
		return 1;
	case 'L':
		return 2;
	case 'J':
		return 3;
	case 'O':
		return 4;
	case 'S':
		return 5;
	case 'T':
		return 6;
	case 'Z':
		return 7;
	case '*':
		return 8;
	case '?':
		return 9;
	default:
		return 0;
	}

	//  0 = "white"
	//  1 = "red"
	//  2 = "green"
	//  3 = "blue"
	//  4 = "cyan"
	//  5 = "yellow"
	//  6 = "darkgreen"
	//  7 = "orange"
	//  8 = "brown"
	//  9 = "black"
};
