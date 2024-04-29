#include "Board.h"
#include "iostream"
#include "Grid.h"
using namespace std;
Board::Board()
{
	init();
}

void Board::init()
{
	for (int ri = 0; ri < 8; ri++)
	{
		for (int ci = 0; ci < 8; ci++)
		{
			if (ri == 1)
				Ps[ri][ci] = new Pawn(position{ ri,ci }, Black, this);
			else if (ri == 6)
				Ps[ri][ci] = new Pawn(position{ ri,ci }, White, this);

			else if (ri == 0 && (ci == 0 || ci == 7))
				Ps[ri][ci] = new Rook(position{ ri,ci }, Black, this);
			else if (ri == 7 && (ci == 0 || ci == 7))
				Ps[ri][ci] = new Rook(position{ ri,ci }, White, this);

			else if (ri == 0 && (ci == 1 || ci == 6))
				Ps[ri][ci] = new Knight(position{ ri,ci }, Black, this);
			else if (ri == 7 && (ci == 1 || ci == 6))
				Ps[ri][ci] = new Knight(position{ ri,ci }, White, this);

			else if (ri == 0 && (ci == 2 || ci == 5))
				Ps[ri][ci] = new Bishop(position{ ri,ci }, Black, this);
			else if (ri == 7 && (ci == 2 || ci == 5))
				Ps[ri][ci] = new Bishop(position{ ri,ci }, White, this);

			else if (ri == 0 && ci == 3)
				Ps[ri][ci] = new Queen(position{ ri,ci }, Black, this);
			else if (ri == 7 && ci == 3)
				Ps[ri][ci] = new Queen(position{ ri,ci }, White, this);

			else if (ri == 0 && ci == 4)
				Ps[ri][ci] = new King(position{ ri,ci }, Black, this);
			else if (ri == 7 && ci == 4)
				Ps[ri][ci] = new King(position{ ri,ci }, White, this);

			else
				Ps[ri][ci] = nullptr;

		}
	}

}

Piece* Board::getpiece(position loc)
{
	return Ps[loc.ri][loc.ci];
}


void Board::displayBoard(int dim)
{
	for (int ri = 0; ri < 8; ri++)
	{
		for (int ci = 0; ci < 8; ci++)
		{
			int newr = ri*dim+10;
			int newc = ci*dim+20;

			if (Ps[ri][ci] == nullptr)
				continue;
			else
				Ps[ri][ci]->draw(newr,newc);
		}
		cout << endl;

	}
}
void Board::movee(position select, position move, bool c, bool d)
{
	if (!d)
		temp = Ps[move.ri][move.ci];
	if (c)
	{
		undo.push({ select, move, temp });
	}
	Ps[select.ri][select.ci]->Move(move);
	Ps[move.ri][move.ci] = Ps[select.ri][select.ci];
	if (c)
	{
		if (Ps[select.ri][select.ci]->getFirst() == false)
			Ps[select.ri][select.ci]->setFirst(true);
		Ps[select.ri][select.ci] = nullptr;
	}
	else
	{

		if(d)
			Ps[select.ri][select.ci] = temp;
		else
			Ps[select.ri][select.ci] = nullptr;
	}
}

void Board::update(position select, position move,int c1,int c2,int dim)
{
	prevForm(select,c1,c2,dim);
	prevForm(move, c1, c2,dim);
	Ps[move.ri][move.ci]->draw(move.ri*dim+10,move.ci*dim+20);
	gotorowcol(8,0);
}

void Board::Undoo(int c1, int c2, int dim, bool replay, info tempinfo, Color c,char piece)
{
	if(!replay)
		tempinfo = undo.top();
	if(Ps[tempinfo.end.ri][tempinfo.end.ci]->getSym() == 'k')
	{
		
		if (tempinfo.start.ci - tempinfo.end.ci == 2)
		{
			Ps[tempinfo.end.ri][3]->Move({tempinfo.start.ri, 0});
			Ps[tempinfo.start.ri][0] = Ps[tempinfo.end.ri][3];
			Ps[tempinfo.end.ri][3] = nullptr;
			UndooUpdate({ {tempinfo.start.ri,0},{tempinfo.end.ri,3},nullptr }, c1, c2, dim);
		}
		else if (tempinfo.start.ci - tempinfo.end.ci == -2)
		{
			Ps[tempinfo.end.ri][5]->Move({ tempinfo.start.ri, 7 });
			Ps[tempinfo.start.ri][7] = Ps[tempinfo.end.ri][5];
			Ps[tempinfo.end.ri][5] = nullptr;
			UndooUpdate({ {tempinfo.start.ri,7},{tempinfo.end.ri,5},nullptr }, c1, c2, dim);
		}

	}
	Ps[tempinfo.end.ri][tempinfo.end.ci]->Move(tempinfo.start);
	Ps[tempinfo.start.ri][tempinfo.start.ci] = Ps[tempinfo.end.ri][tempinfo.end.ci];
	if(!replay)
		Ps[tempinfo.end.ri][tempinfo.end.ci] = tempinfo.piece;
	else
	{
			switch (piece)
			{
			case'-':
				Ps[tempinfo.end.ri][tempinfo.end.ci] = nullptr;
				break;
			case'p':
				Ps[tempinfo.end.ri][tempinfo.end.ci] = new Pawn(position{ tempinfo.end.ri,tempinfo.end.ci }, c, this);
				break;
			case'r':
				Ps[tempinfo.end.ri][tempinfo.end.ci] = new Rook(position{ tempinfo.end.ri,tempinfo.end.ci }, c, this);
				break;
			case'n':
				Ps[tempinfo.end.ri][tempinfo.end.ci] = new Knight(position{ tempinfo.end.ri,tempinfo.end.ci }, c, this);
				break;
			case'b':
				Ps[tempinfo.end.ri][tempinfo.end.ci] = new Bishop(position{ tempinfo.end.ri,tempinfo.end.ci }, c, this);
				break;
			case'q':
				Ps[tempinfo.end.ri][tempinfo.end.ci] = new Queen(position{ tempinfo.end.ri,tempinfo.end.ci }, c, this);
				break;
			case'k':
				Ps[tempinfo.end.ri][tempinfo.end.ci] = new King(position{ tempinfo.end.ri,tempinfo.end.ci }, c, this);
				break;

		}
	}
	if (Ps[tempinfo.start.ri][tempinfo.start.ci]->getSym() == 'p')
	{
		if (Ps[tempinfo.start.ri][tempinfo.start.ci]->getcolor() == Black && tempinfo.start.ri == 1)
			Ps[tempinfo.start.ri][tempinfo.start.ci]->setFirst(false);
		if (Ps[tempinfo.start.ri][tempinfo.start.ci]->getcolor() == White && tempinfo.start.ri == 6)
			Ps[tempinfo.start.ri][tempinfo.start.ci]->setFirst(false);
	}
	if(piece!='-' && replay)
		UndooUpdate(tempinfo, c1, c2, dim,1);
	else
		UndooUpdate(tempinfo, c1, c2, dim);
	undo.pop();
}
void Board::UndooUpdate(info temp, int c1, int c2, int dim, bool replay)
{
	prevForm(temp.end, c1, c2, dim);
	prevForm(temp.start, c1, c2, dim);
	Ps[temp.start.ri][temp.start.ci]->draw(temp.start.ri * dim + 10, temp.start.ci * dim + 20);
	if(temp.piece!=nullptr || replay)
		Ps[temp.end.ri][temp.end.ci]->draw(temp.end.ri * dim + 10, temp.end.ci * dim + 20);
	gotorowcol(8, 0);
}
