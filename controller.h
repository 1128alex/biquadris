#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <string>
#include <vector>

#include "game.h"

using namespace std;

class ControllerPair
{
public:
	ControllerPair(string str, char code);
	string str;
	char code;
};

class Controller
{
public:
	Controller(Game *game);
	void parseString(string);
	friend ControllerPair;

private:
	void map(char c, int n);
	vector<ControllerPair> keys;
	Game *game;
	bool forceCheck;
	bool sequenceCheck;
};

#endif
