#pragma once
#include "Piece.h"

class King :
    public Piece
{
    int Kingp[7][7] = {
    {0, 0, 0, 0, 0, 0, 0},
    {0, 0, 1, 0, 1, 0, 0},
    {0, 0, 1, 1, 1, 0, 0},
    {0, 0, 0, 1, 0, 0, 0},
    {0, 0, 1, 1, 1, 0, 0},
    {0, 0, 1, 1, 1, 0, 0},
    {0, 1, 1, 1, 1, 1, 0}
    };
public:
    King(position _p, Color _c, Board* _b);
    virtual void draw(int row, int col);
    virtual bool isLegal(position move);
    virtual char getSym();

};

