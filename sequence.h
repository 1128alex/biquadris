#ifndef SEQUENCE_H
#define SEQUENCE_H

#include "controller.h"

using namespace std;

// A sequence of commands read from a file
class Sequence
{
public:
  Sequence(string fileName, Controller *controller);
  void execute();

private:
  Controller *controller;

  const string fileName;
  ifstream file;
};

#endif
