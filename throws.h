#ifndef THROW_H
#define THROW_H

class Board;
class Game;

struct BlockDropped
{
};

struct Effect
{
    Board *player;
};

struct GameOver
{
    Board *player;
};

struct Restart
{
    Game *newGame;
};

#endif
