#include <cstdlib>

#include "controller.h"
#include "game.h"
#include "throws.h"

using namespace std;

int main(int argc, char *argv[])
{
	// Initialize default settings
	string p1Seq = "sequence1.txt";
	string p2Seq = "sequence2.txt";
	int level = 0;
	bool textMode = false;
	bool isSeed = false;

  // Parse command-line arguments
	for (int i = 1; i < argc; i++)
	{
		string args = string(argv[i]);
		if (args == "-text")
		{
			textMode = true;
		}
		else if (args == "-seed")
		{
			if (i < argc)
			{
				isSeed = true;
				int seed = stoi(string(argv[++i]));
				srand(seed);
			}
		}
		else if (args == "-scriptp1Seq")
		{
			if (i < argc)
			{
				p1Seq = string(argv[++i]);
			}
		}
		else if (args == "-scriptp2Seq")
		{
			if (i < argc)
			{
				p2Seq = string(argv[++i]);
			}
		}
		else if (args == "-startlevel")
		{
			if (i < argc)
			{
				level = stoi(string(argv[++i]));
			}
		}
		else
		{
			cerr << "Unknown Command: " << argv[i] << endl;
		}
	}

	// If no seed was provided, use the current time for randomization
	if (!isSeed)
	{
		srand(time(NULL));
	}

	// Main game loop
	string input;
	vector<string> files{p1Seq, p2Seq};
	Game *game;
	Controller *controller;

	// Loop until the end of the input stream
	while (!cin.eof())
	{
		game = new Game(files, cout, level, textMode);
		controller = new Controller(game);

		try
		{
			while (cin >> input || !cin.eof())
			{
				controller->parseString(input);
			}
		}
		catch (Restart restart)
		{
		}

		delete game;
		delete controller;
	}
}
