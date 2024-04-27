#include "Bishop.h"
#include "iostream"

Bishop::Bishop(position _p, Color _c, Board* _b)
	:Piece(_p, _c, _b) {}

void Bishop::draw(int row, int col)
{
	((c == White) ? SetClr(8,8) : SetClr(0, 0));
	piecePrint(Bishopp,row,col);
}

bool Bishop::isLegal(position move)
{
	return (isDiagnolmove(move) && isDiagnolClear(move));
}

char Bishop::getSym()
{
	return 'b';
}
