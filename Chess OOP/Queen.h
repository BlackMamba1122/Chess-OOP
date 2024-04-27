#pragma once
#include "Piece.h"
class Queen :
    public Piece
{
    int Queenp[7][7] = {
       {0, 0, 0, 0, 0, 0, 0},
       {0, 1, 0, 1, 1, 0, 1},
       {0, 0, 1, 1, 1, 1, 0},
       {0, 0, 0, 1, 1, 0, 0},
       {0, 0, 1, 1, 1, 1, 0},
       {0, 0, 1, 1, 1, 1, 0},
       {0, 1, 1, 1, 1, 1, 1}
    };
public:
    Queen(position _p, Color _c, Board* _b);
    virtual void draw(int row, int col);
    virtual bool isLegal(position move);
    virtual char getSym();

};

