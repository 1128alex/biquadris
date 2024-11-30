#include <math.h>

#include "board.h"
#include "cell.h"
#include "throws.h"

using namespace std;

Board::Board(string peiceFile, int defaultLevel) : score{0}, turn{true}, weight{0}, ecf{false}, moveCnt{0}, isBlind{false}
{
	blockGrid.assign(18, vector<Cell>{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '});
	gridPosition = Coord(0, 0);

	levelController = new Level(peiceFile, defaultLevel);
	currentBlock = levelController->generateBlock();
	nextBlock = levelController->generateBlock();
}

int Board::getScore()
{
	return score;
}

bool Board::getTurn()
{
	return turn;
}

void Board::setTurn(bool turn)
{
	this->turn = turn;
}

void Board::move(Coord &direction)
{
	if (direction.x != 0 && direction.y != 0)
	{
		return;
	}

	while (direction.x != 0 || direction.y != 0)
	{
		Coord temp(0, 0);
		// Determine whether to move vertically or horizontally.
		if (direction.y != 0)
		{
			temp.y = ((direction.y < 0) ? (-1) : 1);
		}
		else
		{
			temp.x = ((direction.x < 0) ? (-1) : 1);
		}

		// Attempt the move. If successful, reduce the remaining distance.
		if (currentBlock->move(temp, *this))
		{
			if (direction.y != 0)
			{
				direction.y += ((direction.y < 0) ? 1 : (-1));
			}
			else
			{
				direction.x += ((direction.x < 0) ? 1 : (-1));
			}
		}
		else
		{
			// If the move fails vertically, drop the block.
			if (direction.x != 0)
			{
				return;
			}

			drop();
		}
	}
}

void Board::rotate(int rotation)
{
	while (rotation != 0)
	{
		if (currentBlock->rotate(((rotation < 0) ? (-1) : 1), *this))
		{
			rotation += ((rotation < 0) ? 1 : (-1));
		}
		else
		{
			return;
		}
	}
}

void Board::drop(bool otherCase)
{
	if (!otherCase)
	{
		isBlind = false;
	}

	Block *toDrop;
	if (otherCase)
	{
		toDrop = new Block('*', -1, -1);
	}
	else
	{
		toDrop = currentBlock;
	}
	Coord temp(0, -1);

	// Move the block downward until it can no longer move.
	while (toDrop->move(temp, *this))
		;

	this->dropBlock(*toDrop);

	delete toDrop;

	if (otherCase)
	{
		return;
	}

	currentBlock = nextBlock;
	nextBlock = levelController->generateBlock();

	int removeCnt = 0;
	vector<Cell> removedCells;

	for (int i = 0; i < 12; i++)
	{
		if (isRowFull(i))
		{
			removedCells.insert(removedCells.begin(), blockGrid[i].begin(), blockGrid[i].end());
			blockGrid.erase(blockGrid.begin() + i--);
			blockGrid.push_back(vector<Cell>{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '});
			removeCnt++;
		}
	}

	if (removeCnt == 0 && !otherCase)
	{
		moveCnt++;
	}
	else
	{
		moveCnt = 0;
	}

	// Drop a special block if enough moves have passed without a clear.
	if (moveCnt >= 5 && levelController->getLevel() >= 4)
	{
		moveCnt = 0;
		drop(true);
	}

	if (removeCnt > 0)
	{
		score += pow(levelController->getLevel() + removeCnt, 2);
	}

	for (int i = 0; i < removedCells.size(); i++)
	{
		if (removedCells[i].getID() < 0)
		{
			removedCells.erase(removedCells.begin() + i);
			i--;
		}
		for (int j = i + 1; j < removedCells.size(); j++)
		{
			if (removedCells[i].getID() == removedCells[j].getID())
			{
				removedCells.erase(removedCells.begin() + j);
				j--;
			}
		}
	}

	// Additional scoring logic for special blocks and IDs.
	for (auto cell : removedCells)
	{
		if (!cellExist(cell.getID()))
		{
			score += pow(cell.getLevel() + 1, 2);
		}
	}

	if (this->collide(*currentBlock))
	{
		throw GameOver{this};
	}

	if (removeCnt > 1)
	{
		throw Effect{this};
	}

	throw BlockDropped();
}

bool Board::force(char blockType)
{
	Block *newP = new Block(blockType, (*currentBlock)[0][0].getID(), (*currentBlock)[0][0].getLevel());

	if (newP->getRow() == 0)
	{
		delete newP;
		return false;
	}

	delete currentBlock;
	currentBlock = newP;

	if (this->collide(*currentBlock))
	{
		throw GameOver{this};
	}

	return true;
}

void Board::changeHeavy(int q)
{
	weight += q;
}

void Board::blindOn()
{
	isBlind = true;
}

void Board::changeLevel(int change)
{
	levelController->setLevel(change);
}

void Board::aftercare()
{
	if (levelController->getLevel() >= 3)
	{
		Coord temp(0, -1);
		move(temp);
	}

	Coord temp(0, -weight);
	move(temp);

	if (!isRowEmpty(15) || !isRowEmpty(16) || !isRowEmpty(17))
	{
		throw GameOver{this};
	}
}

vector<vector<string>> Board::render(bool isTurn)
{
	vector<vector<string>> output;

	vector<Grid *> grids{this, currentBlock};

	Block blindBlock{'b', -1, -1};

	if (isBlind)
	{
		grids.push_back(&blindBlock);
	}

	Coord gridSize(11, 18);

	output.push_back(textRender->footer(nextBlock, gridSize));
	output.push_back(textRender->body(grids, gridSize));
	output.push_back(textRender->header(score, levelController->getLevel(), gridSize, isTurn));

	return output;
}

Board::~Board()
{
	delete currentBlock;
	delete nextBlock;
}

bool Board::isRowEmpty(int row)
{
	for (Cell &cell : blockGrid[row])
	{
		if (!cell.isEmpty())
		{
			return false;
		}
	}

	return true;
}

bool Board::isRowFull(int row)
{
	for (Cell &cell : blockGrid[row])
	{
		if (cell.isEmpty())
		{
			return false;
		}
	}

	return true;
}

bool Board::cellExist(int id)
{
	for (auto row : blockGrid)
	{
		for (auto cell : row)
		{
			if (cell.getID() == id)
			{
				return true;
			}
		}
	}

	return false;
}
