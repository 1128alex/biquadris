#include <iostream>
#include <fstream>
#include <string>

#include "sequence.h"

using namespace std;

Sequence::Sequence(string fileName, Controller *controller) : fileName{fileName}, controller{controller}
{
  file.open(fileName);
  if (!file)
  {
    for (int i = 0; i < 30; i++)
    {
      cout << endl;
    }

    cout << "Error opening " + fileName + ".";

    cin.get();
    cin.get();
  }
}

void Sequence::execute()
{
  if (!file)
  {
    return;
  }

  string cmd;
  while (file >> cmd)
  {
    controller->parseString(cmd);
  }
}
