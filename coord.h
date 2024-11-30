#ifndef COORD_H
#define COORD_H

class Coord
{
public:
	int x, y;

	Coord();
	Coord(int x, int y);

	Coord operator+(Coord &coord);

	Coord operator-();
	Coord operator-(Coord &coord);

	bool operator==(Coord &coord);

	Coord &operator+=(Coord &coord);

	Coord &operator-=(Coord &coord);
};

#endif
