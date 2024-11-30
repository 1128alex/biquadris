#include "game.h"
#include "throws.h"

using namespace std;

Game::Game(vector<string> files, ostream &out, int level, bool textMode) : out{out}, level{level}, effectCheck{false}, textMode{textMode}
{
	for (string file : files)
	{
		boards.push_back(new Board(file, level));
	}
	currentBoard = boards.begin();

	if (!textMode)
	{
		graphicsRender = new GraphicsRender(504, 500);
	}

	render();
}

void Game::move(Coord &direction)
{
	if (effectCheck)
	{
		return;
	}

	try
	{
		(*currentBoard)->move(direction);
		(*currentBoard)->aftercare();
	}
	catch (BlockDropped)
	{
		nextPlayer();
	}
	catch (GameOver g)
	{
		lost(g.player);
	}
	catch (Effect)
	{
		effectCheck = true;
		(*currentBoard)->aftercare();
	}

	render();
}

void Game::rotate(int change)
{
	if (effectCheck)
	{
		return;
	}

	try
	{
		(*currentBoard)->rotate(change);
	}
	catch (BlockDropped)
	{
		nextPlayer();
	}
	catch (GameOver g)
	{
		lost(g.player);
	}
	catch (Effect)
	{
		effectCheck = true;
		(*currentBoard)->aftercare();
	}

	render();
}

void Game::drop(int change)
{
	if (effectCheck)
	{
		return;
	}

	try
	{
		while (change > 0)
		{
			change--;
			try
			{
				(*currentBoard)->drop();
			}
			catch (BlockDropped)
			{
				if (change == 0)
				{
					nextPlayer();
				}
			}
		}
	}
	catch (GameOver g)
	{
		lost(g.player);
	}
	catch (Effect)
	{
		effectCheck = true;
	}

	render();
}

int Game::lost(Board *loser)
{
	loser->setTurn(false);

	int last = -1;
	int playerCnt = 0;

	vector<Board *>::iterator boardIt = boards.begin();

	while (boardIt != boards.end())
	{
		if ((*boardIt)->getTurn())
		{
			playerCnt++;
		}
		boardIt++;
	}

	if (playerCnt == 1)
	{
		boardIt = boards.begin();
		int cnt = 0;
		while (boardIt != boards.end() && last == -1)
		{
			if ((*boardIt)->getTurn())
			{
				last = cnt;
			}
			cnt++;
			boardIt++;
		}

		for (int i = 0; i < 30; i++)
		{
			out << endl;
		}

		out << "Congratulations Player, " + to_string(last + 1) + " you lasted the longest! you have a score of: " + to_string(boards[last]->getScore()) << endl;
		out << "Press any key to start a new game...";
		cin.get();
		cin.get();

		throw Restart{this};
	}
}

bool Game::effect(char effect, char type)
{
	vector<Board *>::iterator boardIt = boards.begin();

	while (boardIt != boards.end())
	{
		if (!(*boardIt == *currentBoard))
		{
			switch (effect)
			{
			case 'f':
				if (!(*boardIt)->force(type))
				{
					return false;
				};
				break;
			case 'b':
				(*boardIt)->blindOn();
				break;
			case 'h':
				(*boardIt)->changeHeavy(2);
				break;
			}
		}

		boardIt++;
	}

	effectCheck = false;
	nextPlayer();
	render();

	return true;
}

bool Game::force(char blockType)
{
	if ((*currentBoard)->force(blockType))
	{
		render();
		return true;
	}

	return false;
}

void Game::changeLevel(int change)
{
	(*currentBoard)->changeLevel(change);
	render();
}

void Game::render()
{

	vector<vector<vector<string>>> textBoards;

	int cnt = 0;
	int currentBoard = currentPlayer();

	for (int i = 0; i < 20; i++)
	{
		out << endl;
	}

	for (Board *board : boards)
	{
		textBoards.push_back(board->render(cnt == currentBoard));
		cnt++;
	}

	for (int i = 2; i >= 0; i--)
	{
		for (int j = textBoards[0][i].size() - 1; j >= 0; j--)
		{
			out << "   ";
			for (int k = 0; k < textBoards.size(); k++)
			{
				out << textBoards[k][i][j] << string(8, ' ');
			}
			out << endl;
		}
	}

	if (!textMode)
	{
		vector<vector<string>> result;

		for (auto x : textBoards)
		{
			result.push_back(x[1]);
		}

		graphicsRender->render(result);
	}
}

Game::~Game()
{
	currentBoard = boards.begin();

	while (currentBoard != boards.end())
	{
		delete *currentBoard;
		currentBoard++;
	}
}

void Game::nextPlayer()
{
	while (true)
	{
		currentBoard++;
		if (currentBoard == boards.end())
		{
			currentBoard = boards.begin();
		}

		if ((*currentBoard)->getTurn())
		{
			break;
		}
	}
}

int Game::currentPlayer()
{
	int cnt = 0;

	for (auto x : boards)
	{
		if (x == *currentBoard)
		{
			return cnt;
		}
		cnt++;
	}

	throw "unable to find current player";
}
