#ifndef GRAPHIC_RENDER_H
#define GRAPHIC_RENDER_H

#include <vector>

#include "window.h"

using namespace std;

// Handles graphical rendering for a Biquadris game board.
class GraphicsRender
{
public:
	GraphicsRender(int screenWidth, int screenHeight);

	void render(vector<vector<string>> result);

private:
	const int width;
	const int height;

	vector<vector<string>> prev;
	Xwindow xwindow;

	int charToColour(char color);
};

#endif
