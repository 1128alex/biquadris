#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include <fstream>
#include <iostream>

using namespace std;

// Manages game levels, block generation, and randomness
class Level
{
public:
	Level(std::string fileName, int level = 0);

	int setLevel(int amount);
	int getLevel();

	void setIsRandom(bool isRandom);
	bool getIsRandom();

	Block *generateBlock();

private:
	int level;
	int minL;
	int maxL;
	int id;
	bool isRandom;

	const string fileName;
	ifstream file;
};

#endif
