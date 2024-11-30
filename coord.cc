#include "coord.h"

Coord::Coord() : x{0}, y{0} {}

Coord::Coord(int x, int y) : x{x}, y{y} {}

Coord Coord::operator+(Coord &coord)
{
	return Coord(x + coord.x, y + coord.y);
}

Coord Coord::operator-()
{
	return Coord(-x, -y);
}

Coord Coord::operator-(Coord &coord)
{
	return Coord(x - coord.x, y - coord.y);
}

bool Coord::operator==(Coord &coord)
{
	return x == coord.x && y == coord.y;
}

Coord &Coord::operator+=(Coord &coord)
{
	x += coord.x;
	y += coord.y;
	return *this;
}

Coord &Coord::operator-=(Coord &coord)
{
	x -= coord.x;
	y -= coord.y;
	return *this;
}
