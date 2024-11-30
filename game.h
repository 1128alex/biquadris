#ifndef GAME_H
#define GAME_H

#include <vector>
#include <iostream>

#include "board.h"
#include "grid.h"

using namespace std;

class Game : public Grid
{
public:
	Game(vector<string> files, ostream &output, int level, bool textOnly);

	void move(Coord &direction);
	void rotate(int change);
	void drop(int change = 1);

	int lost(Board *loser);
	bool effect(char effect, char type = ' ');
	bool force(char type);

	void changeLevel(int change);

	void render();

	~Game();

private:
	const int level;
	const bool textMode;

	bool effectCheck;

	ostream &out;

	vector<Board *> boards;
	vector<Board *>::iterator currentBoard;

	GraphicsRender *graphicsRender;

	void nextPlayer();
	int currentPlayer();
};

#endif
