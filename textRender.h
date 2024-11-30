#ifndef TEXT_RENDER_H
#define TEXT_RENDER_H

#include <vector>
#include <string>

#include "grid.h"

using namespace std;

class Block;

class TextRender
{
public:
	vector<string> header(int score, int level, Coord output_Size, bool curr);
	vector<string> body(vector<Grid *> grids, Coord output_Size);
	vector<string> footer(Block *next, Coord output_Size);
};

#endif
