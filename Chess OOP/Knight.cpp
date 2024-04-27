#include "Knight.h"
#include "iostream"

Knight::Knight(position _p, Color _c, Board* _b)
	:Piece(_p, _c, _b) {}

void Knight::draw(int row, int col)
{
	((c == White) ? SetClr(8, 8) : SetClr(0, 0));
	piecePrint(Knightp,row,col);
}


bool Knight::isLegal(position move)
{
	return abs((pos.ri-move.ri)*(pos.ci-move.ci))==2;
}

char Knight::getSym()
{
	return 'n';
}
