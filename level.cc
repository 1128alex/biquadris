#include <string>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>

#include "board.h"
#include "level.h"

using namespace std;

Level::Level(string fileName, int level) : level{level}, fileName{fileName}, id{10}, minL{0}, maxL{4}, isRandom{true}
{
  file.open(fileName);

  if (!file)
  {

    for (int i = 0; i < 30; i++)
    {
      cout << endl;
    }

    cout << "Unable to open " + fileName + ", this means that level zero is unavailable, press enter key to continue";

    cin.get();

    minL = 1;
    setLevel(0);
  }
}

int Level::setLevel(int amount)
{
  level += amount;

  if (level < minL)
  {
    level = minL;
  }
  else if (level > maxL)
  {
    level = maxL;
  }

  return level;
}

int Level::getLevel()
{
  return level;
}

void Level::setIsRandom(bool isRandom)
{
  this->isRandom = isRandom;
}

bool Level::getIsRandom()
{
  return isRandom;
}

Block *Level::generateBlock()
{

  if (level == 0)
  {
    char piece;
    while (file)
    {
      while (file >> piece)
      {
        if (piece == 'I' || piece == 'O' || piece == 'S' || piece == 'Z' || piece == 'L' || piece == 'J' || piece == 'T')
        {
          id++;
          return new Block(piece, id, level);
        }
      }
      file.clear();
      file.seekg(0, file.beg);
    }
  }
  else if (level == 1)
  {
    int num;

    num = rand() % 12;
    if (num == 0)
    {
      id++;
      return new Block('S', id, level);
    }
    else if (num == 1)
    {
      id++;
      return new Block('Z', id, level);
    }
    else if (num == 2 || num == 3)
    {
      id++;
      return new Block('O', id, level);
    }
    else if (num == 4 || num == 5)
    {
      id++;
      return new Block('L', id, level);
    }
    else if (num == 6 || num == 7)
    {
      id++;
      return new Block('J', id, level);
    }
    else if (num == 8 || num == 9)
    {
      id++;
      return new Block('T', id, level);
    }
    else
    {
      id++;
      return new Block('I', id, level);
    }
  }
  else if (level == 2)
  {
    int num;
    while (true)
    {
      num = rand() % 7;
      if (num == 0)
      {
        id++;
        return new Block('S', id, level);
      }
      else if (num == 1)
      {
        id++;
        return new Block('Z', id, level);
      }
      else if (num == 2)
      {
        id++;
        return new Block('O', id, level);
      }
      else if (num == 3)
      {
        id++;
        return new Block('L', id, level);
      }
      else if (num == 4)
      {
        id++;
        return new Block('J', id, level);
      }
      else if (num == 5)
      {
        id++;
        return new Block('T', id, level);
      }
      else
      {
        id++;
        return new Block('I', id, level);
      }
    }
  }
  else if (level == 3)
  {
    if (getIsRandom())
    {
      int num;
      while (true)
      {
        num = rand() % 9;
        if (num == 0 || num == 1)
        {
          id++;
          return new Block('S', id, level);
        }
        else if (num == 2 || num == 3)
        {
          id++;
          return new Block('Z', id, level);
        }
        else if (num == 4)
        {
          id++;
          return new Block('O', id, level);
        }
        else if (num == 5)
        {
          id++;
          return new Block('L', id, level);
        }
        else if (num == 6)
        {
          id++;
          return new Block('J', id, level);
        }
        else if (num == 7)
        {
          id++;
          return new Block('T', id, level);
        }
        else
        {
          id++;
          return new Block('I', id, level);
        }
      }
    }
    else
    {
      char piece;
      while (file)
      {
        while (file >> piece)
        {
          if (piece == 'I' || piece == 'O' || piece == 'S' || piece == 'Z' || piece == 'L' || piece == 'J' || piece == 'T')
          {
            id++;
            return new Block(piece, id, level);
          }
        }
        file.clear();
        file.seekg(0, file.beg);
      }
    }
  }
  else
  {
    if (getIsRandom())
    {
      int num;
      while (true)
      {
        num = rand() % 9;
        if (num == 0 || num == 1)
        {
          id++;
          return new Block('S', id, level);
        }
        else if (num == 2 || num == 3)
        {
          id++;
          return new Block('Z', id, level);
        }
        else if (num == 4)
        {
          id++;
          return new Block('O', id, level);
        }
        else if (num == 5)
        {
          id++;
          return new Block('L', id, level);
        }
        else if (num == 6)
        {
          id++;
          return new Block('J', id, level);
        }
        else if (num == 7)
        {
          id++;
          return new Block('T', id, level);
        }
        else
        {
          id++;
          return new Block('I', id, level);
        }
      }
    }
    else
    {
      char piece;
      while (file)
      {
        while (file >> piece)
        {
          if (piece == 'I' || piece == 'O' || piece == 'S' || piece == 'Z' || piece == 'L' || piece == 'J' || piece == 'T')
          {
            id++;
            return new Block(piece, id, level);
          }
        }
        file.clear();
        file.seekg(0, file.beg);
      }
    }
  }
}
