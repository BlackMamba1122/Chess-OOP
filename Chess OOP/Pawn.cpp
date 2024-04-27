#include "Pawn.h"
#include "iostream"
#include "Board.h"
Pawn::Pawn(position _p, Color _c, Board* _b)
	:Piece(_p, _c, _b) {}


void Pawn::draw(int row,int col)
{
	((c == White) ? SetClr(8,8) : SetClr(0,0));
	piecePrint(PawnP,row,col);
}

bool Pawn::isLegal(position move)
{
	if (c == Black && (move.ri - pos.ri) < 0)
		return false;
	else if (c == White && (move.ri - pos.ri) > 0)
		return false;
	int dr = abs(pos.ri - move.ri);
	int dc = abs(pos.ci - move.ci);

	if(b->getpiece(move)==nullptr)
	{
		if (!first)
			return ((dr < 3 && dr>0) && dc == 0);
		else
			return ((dr < 2 && dr>0) && dc == 0);
	}
	else
		return(dr == 1 && dc == 1);
}

char Pawn::getSym()
{
	return 'p';
}
