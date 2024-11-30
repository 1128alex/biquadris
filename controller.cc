#include <ctype.h>

#include "controller.h"
#include "coord.h"
#include "sequence.h"

using namespace std;

ControllerPair::ControllerPair(string str, char code) : str{str}, code{code} {}

Controller::Controller(Game *game) : game{game}, forceCheck{false}, sequenceCheck{false}, keys{}
{
	keys.push_back(ControllerPair("right", 'r'));
	keys.push_back(ControllerPair("left", 'l'));
	keys.push_back(ControllerPair("down", 'd'));
	keys.push_back(ControllerPair("drop", 'D'));
	keys.push_back(ControllerPair("clockwise", 'c'));
	keys.push_back(ControllerPair("counterclockwise", 'C'));
	keys.push_back(ControllerPair("levelup", 'Q'));
	keys.push_back(ControllerPair("leveldown", 'q'));
	keys.push_back(ControllerPair("blind", 'b'));
	keys.push_back(ControllerPair("heavy", 'h'));
	keys.push_back(ControllerPair("force", 'f'));
	keys.push_back(ControllerPair("sequence", 's'));
	keys.push_back(ControllerPair("I", 'I'));
	keys.push_back(ControllerPair("J", 'J'));
	keys.push_back(ControllerPair("L", 'L'));
	keys.push_back(ControllerPair("O", 'O'));
	keys.push_back(ControllerPair("S", 'S'));
	keys.push_back(ControllerPair("Z", 'Z'));
	keys.push_back(ControllerPair("T", 'T'));
}

// Parses the input string and executes the corresponding actions
void Controller::parseString(string input)
{
	if (forceCheck)
	{
		if (!(game->effect('f', input[0])))
		{
			return;
		};
		forceCheck = false;
		return;
	}
	else if (sequenceCheck)
	{
		sequenceCheck = false;
		Sequence seq(input, this);
		seq.execute();
		game->render();
		return;
	}

	vector<ControllerPair> temp = keys;
	int repeat = 0;

	while (input.size() != 0 && !isalpha(input[0]))
	{
		repeat *= 10;
		repeat += input[0] - '0';
		input = string(++input.begin(), input.end());
	}

	for (int i = 0; i < input.size(); i++)
	{
		for (int j = 0; j < temp.size(); j++)
		{
			if (input[i] != temp[j].str[i])
			{
				temp.erase(temp.begin() + j);
				j--;
			}
		}
	}

	if (repeat == 0)
	{
		repeat = 1;
	}
	if (temp.size() == 1)
	{
		map(temp[0].code, repeat);
	}
}

// Maps a command code and executes it
void Controller::map(char c, int n)
{

	switch (c)
	{
	case 'D':
		game->drop(n);
		break;
	case 'd':
	{
		Coord coord(0, -n);
		game->move(coord);
		break;
	}
	case 'l':
	{
		Coord coord(-n, 0);
		game->move(coord);
		break;
	}
	case 'r':
	{
		Coord coord(n, 0);
		game->move(coord);
		break;
	}
	case 'c':
	{
		game->rotate(n);
		break;
	}
	case 'C':
	{
		game->rotate(-n);
		break;
	}
	case 'Q':
	{
		game->changeLevel(n);
		break;
	}
	case 'q':
	{
		game->changeLevel(-n);
		break;
	}
	case 'f':
		forceCheck = true;
		break;
	case 'b':
	case 'h':
		game->effect(c);
		break;
	case 's':
		sequenceCheck = true;
		break;
	case 'I':
	case 'J':
	case 'L':
	case 'O':
	case 'S':
	case 'Z':
	case 'T':
		game->force(c);
		break;
	default:
		break;
	}
}
