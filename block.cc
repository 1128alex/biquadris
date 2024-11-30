#include "block.h"

using namespace std;

Block::Block() {}

Block::Block(char blockType, int id, int level)
{
  // Initialize block shapes based on type
  switch (blockType)
  {
  case 'I': // Line block
  {
    vector<vector<Cell>> iBlock{
        {'I', 'I', 'I', 'I'}};

    column = 4;
    row = 1;
    blockGrid = iBlock;

    break;
  }
  case 'J': // J-shaped block
  {
    vector<vector<Cell>> jBlock{
        {' ', ' ', 'J'}, {'J', 'J', 'J'}};

    column = 3;
    row = 2;
    blockGrid = jBlock;

    break;
  }
  case 'L': // L-shaped block
  {
    vector<vector<Cell>> lBlock{
        {'L', ' ', ' '}, {'L', 'L', 'L'}};

    column = 3;
    row = 2;
    blockGrid = lBlock;

    break;
  }
  case 'O': // Square block
  {
    vector<vector<Cell>> oBlock{
        {'O', 'O'}, {'O', 'O'}};

    column = 2;
    row = 2;
    blockGrid = oBlock;

    break;
  }
  case 'S': // S-shaped block
  {
    vector<vector<Cell>> sBlock{
        {'S', 'S', ' '}, {' ', 'S', 'S'}};

    column = 3;
    row = 2;
    blockGrid = sBlock;

    break;
  }
  case 'Z': // Z-shaped block
  {
    vector<vector<Cell>> zBlock{
        {' ', 'Z', 'Z'}, {'Z', 'Z', ' '}};

    column = 3;
    row = 2;
    blockGrid = zBlock;

    break;
  }
  case 'T': // T-shaped block
  {
    vector<vector<Cell>> tBlock{
        {' ', 'T', ' '}, {'T', 'T', 'T'}};

    column = 3;
    row = 2;
    blockGrid = tBlock;

    break;
  }
  case '*': // Special single-block type
  {
    vector<vector<Cell>> starBlock{
        {'*'}};

    column = 1;
    row = 1;
    blockGrid = starBlock;

    break;
  }
  case 'b': // Blinder block
  {
    vector<vector<Cell>> blinderBlock;
    for (int i = 0; i < 10; i++)
    {
      blinderBlock.push_back(vector<Cell>{'?', '?', '?', '?', '?', '?', '?'});
    }

    column = 7;
    row = 10;
    blockGrid = blinderBlock;

    break;
  }
  default: // Invalid block type
    column = 0;
    row = 0;

    break;
  }

  // Set default offsets based on block type
  if (blockType == '*')
  {
    gridPosition = Coord(5, 14);
  }
  else if (blockType == 'b')
  {
    gridPosition = Coord(2, 3);
  }
  else
  {
    gridPosition = Coord(0, 14);
  }

  for (int i = 0; i < row; i++)
  {
    for (int j = 0; j < column; j++)
    {
      blockGrid[i][j].setID(id);
      blockGrid[i][j].setLevel(level);
    }
  }
}

bool Block::move(Coord &direction, Grid &other)
{
  gridPosition += direction;
  if (other.collide(*this))
  {
    gridPosition -= direction;
    return false;
  }

  return true;
}

bool Block::rotate(int rotation, Grid &other)
{
  Block obj; // Temporary rotated grid
  obj.gridPosition = gridPosition;

  obj.blockGrid.assign(column, vector<Cell>());

  // Perform the rotation
  for (int i = 0; i < row; i++)
  {
    for (int j = 0; j < column; j++)
    {

      if (rotation == 1) // Perform the rotation
      {
        obj[j].push_back(blockGrid[i][column - 1 - j]);
      }
      else // Counterclockwise rotation
      {
        obj[j].insert(obj[j].begin(), blockGrid[i][j]);
      }
    }
  }

  if (other.collide(obj))
  {
    return false; // Collision detected
  }

  // Apply the rotation
  blockGrid = obj.blockGrid;
  swap(column, row);
  return true;
}

int Block::getColumn()
{
  return column;
}

int Block::getRow()
{
  return row;
}
