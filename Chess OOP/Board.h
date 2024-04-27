#pragma once
#include "Piece.h"
#include "Pawn.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"
#include <stack>
using namespace std;
class Piece;
class Board
{
	Piece* Ps[8][8];
	Piece* temp;
public:
	std::stack<info>undo;
	Board();
	void init();
	Piece* getpiece(position loc);
	void displayBoard(int dim);
	void movee(position select, position move,bool c,bool d=0);
	void update(position select, position move,int c1,int c2, int dim);
	void Undoo(int c1, int c2, int dim, bool replay, info tempinfo = { {0,0 } ,{0,0},nullptr }, Color c=Black, char piece=' ');
	void UndooUpdate(info temp, int c1, int c2, int dim, bool replay=0);
};

