#ifndef BLOCK_H
#define BLOCK_H

#include "grid.h"

class Block : public Grid
{
public:
  Block();
  Block(char blockType, int id, int level);

  bool move(Coord &direction, Grid &other);
  bool rotate(int rotation, Grid &other);

  int getColumn();

  int getRow();

private:
  int column;
  int row;
};

#endif
