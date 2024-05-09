#pragma once

#define BLACK 0
#define BROWN 6
#define WHITE 15
#define GREEN 2
#define RED 4
#define LBLUE 9

class Piece;
struct position
{
	int ri;
	int ci;
};

struct info
{
	position start;
	position end;
	Piece* piece;
	bool state;
};
enum Color{Black,White};

void gotorowcol(int rpos, int cpos);


void SetClr(int tcl, int bcl);

bool getRowColbyLeftClick(int& rpos, int& cpos);

void save(position select, position move, bool undo);

void startscreen(bool& n);

void checkkk();

void stalemate();
