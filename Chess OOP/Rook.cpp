#include "Rook.h"
#include "iostream"

Rook::Rook(position _p, Color _c, Board* _b)
	:Piece(_p, _c, _b) {}

void Rook::draw(int row, int col)
{
	((c == White) ? SetClr(8, 8) : SetClr(0, 0));
	piecePrint(Rookp,row,col);
}



bool Rook::isLegal(position move)
{
	return ((isHorizontalmove(move) && isHorizontalClear(move)) || (isVerticalmove(move) && isVerticalClear(move)));
}

char Rook::getSym()
{
	return 'r';
}
