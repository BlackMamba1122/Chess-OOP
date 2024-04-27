#include "King.h"
#include "iostream"
#include "Queen.h"
King::King(position _p, Color _c, Board* _b)
	:Piece(_p, _c, _b) {}

void King::draw(int row, int col)
{
	((c == White) ? SetClr(8, 8) : SetClr(0, 0));
	piecePrint(Kingp,row,col);
}

bool King::isLegal(position move)
{
	int dr = pos.ri - move.ri;
	int dc = pos.ci - move.ci;
	return (Queen(pos, c, b).isLegal(move) && (dr<2 && dr>-2) && (dc<2 && dc>-2));
}

char King::getSym()
{
	return 'k';
}
