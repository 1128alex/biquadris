#ifndef BOARD_H
#define BOARD_H

#include "coord.h"
#include "block.h"
#include "level.h"
#include "textRender.h"
#include "grahpicRender.h"

using namespace std;

// Represents the Biquadris game board
class Board : public Grid
{
public:
	Board(string peiceFile, int defaultLevel);

	int getScore();

	bool getTurn();
	void setTurn(bool turn);

	void move(Coord &direction);
	void rotate(int amount);
	void drop(bool otherCase = false);

	bool force(char blockType);
	void changeHeavy(int q);
	void blindOn();

	void changeLevel(int change);
	void aftercare();

	vector<vector<string>> render(bool isTurn);

	~Board();

private:
	int downsCount;
	int score;
	int weight;
	int moveCnt;
	bool turn;
	bool isBlind;
	bool ecf;

	Block *currentBlock;
	Block *nextBlock;
	Level *levelController;
	TextRender *textRender;

	bool isRowEmpty(int row);
	bool isRowFull(int row);
	bool cellExist(int id);
};

#endif
