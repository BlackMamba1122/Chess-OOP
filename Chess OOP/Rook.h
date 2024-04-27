#pragma once
#include "Piece.h"

class Rook :
    public Piece
{
    int Rookp[7][7] = {
    {0, 0, 0, 0, 0, 0, 0},
    {0, 1, 1, 1, 1, 1, 0},
    {0, 1, 1, 1, 1, 1, 0},
    {0, 0, 1, 1, 1, 0, 0},
    {0, 0, 1, 1, 1, 0, 0},
    {0, 1, 1, 1, 1, 1, 0},
    {0, 0, 0, 0, 0, 0, 0}
    };
public:
    Rook(position _p, Color _c, Board* _b);
    virtual void draw(int r, int col);
    virtual bool isLegal(position move);
    virtual char getSym();
};

