#include "Queen.h"
#include "Rook.h"
#include "Bishop.h"
#include "iostream"

Queen::Queen(position _p, Color _c, Board* _b)
	:Piece(_p, _c, _b) {}

void Queen::draw(int row, int col)
{
	((c == White) ? SetClr(8, 8) : SetClr(0, 0));
	piecePrint(Queenp,row,col);
}


bool Queen::isLegal(position move)
{
	return (Rook(pos,c,b).isLegal(move) || Bishop(pos, c, b).isLegal(move));
}

char Queen::getSym()
{
	return 'q';
}
