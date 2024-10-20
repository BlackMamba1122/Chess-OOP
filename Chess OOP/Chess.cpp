#include "Chess.h"
#include "iostream"
#include "Grid.h"
#include <Windows.h>
#include <fstream>

using namespace std;
Chess::Chess()
{
	move.ri = 0, move.ci = 0, select.ri = 0, select.ci = 0;
	ply[0] = new Player("Ahmad1", Black);
	ply[1] = new Player("Ahmad2", White);
	b = new Board();
	turn = 0;
}

void Chess::displayTurnMsg(Player* p)
{
if (!p->getcolor())
	std::cout << R"(
											  (  (    (     (  (         
											 ()) )\   )\   ()) )\        
											(_)()(_) (_() ((_))(_)__     
											| _ ) |  /   \/ __| |/ /     
											| _ \ |__| - | (__|   <      
											|___/____|_|_|\___|_|\_\     )" << '\n';
else
	std::cout << R"(
											 (     (  ( (   ((        (( 
											 )\    )\ )\)\  ))\)\ )\ (\()
											((_)  ((()_)(_)((_)(_)(_))(_)
											\ \    / / || |_ _|_   _| __|
											 \ \/\/ /| __ || |  | | | _| 
											  \_/\_/ |_||_|___| |_| |___|)" << '\n';
}

void Chess::selectPiece(int dim,bool& Undo)
{
	Undo=getRowColbyLeftClick(select.ri, select.ci);
	select.ri = (select.ri - 10) / dim;
	select.ci = (select.ci - 20) / dim;
	if (b->undo.empty())
		Undo = false;
}

void Chess::selectDestination(int dim)
{

	bool t=true;
	while(t)
	{
		t = getRowColbyLeftClick(move.ri, move.ci);
		move.ri = (move.ri - 10) / dim;
		move.ci = (move.ci - 20) / dim;
	}
}

bool Chess::validSelect(position _select)
{
	if (_select.ri < 0 || _select.ri>7 || _select.ci < 0 || _select.ci >7)
		return false;
	Piece* piece = b->getpiece(_select);
	return piece != nullptr && piece->getcolor() == ply[turn]->getcolor();
}

bool Chess::validmove(position _move)
{
	if (_move.ri < 0 || _move.ri>7 || _move.ci < 0 || _move.ci >7)
		return false;
	Piece* piece = b->getpiece(_move);
	return piece == nullptr || piece->getcolor() != ply[turn]->getcolor();
}

void Chess::turnChange()
{
	turn++;
	if (turn > 1)
		turn = 0;
}

void Chess::highlight(bool H[][8],position _select)
{
	for (int ri = 0; ri < 8; ri++)
		for (int ci = 0; ci < 8; ci++)
			H[ri][ci] = ((validmove(position{ ri,ci })) && (b->getpiece(_select)->isLegal(position{ ri,ci })));
}

void Chess::highlightBox(bool H[][8], int c,int dim)
{
	for (int ri = 0; ri < 8; ri++)
		for (int ci = 0; ci < 8; ci++)
		{
			if (H[ri][ci])
			{
				printBox(ri * dim, ci * dim, dim, dim, -37, c);
				if (b->getpiece(position{ ri,ci }) != nullptr)
				{
					printBox(ri * dim, ci * dim, dim, dim, -37, 4);
					b->getpiece(position{ ri,ci })->draw(ri * dim + 10, ci * dim + 20);
				}
			}
		}
}

void Chess::UnhighlightBox(bool H[][8], int dim,int c1,int c2)
{
	for (int ri = 0; ri < 8; ri++)
		for (int ci = 0; ci < 8; ci++)
		{
			if (H[ri][ci])
			{
				prevForm(position{ ri,ci }, c1, c2, dim);
				if (b->getpiece(position{ ri,ci }) != nullptr)
					b->getpiece(position{ ri,ci })->draw(ri * dim + 10, ci * dim + 20);
			}
		}
}

bool Chess::check(int& kr, int& kc)
{
	turnChange();
	findKing(kr, kc);
	turnChange();
	for (int ri = 0; ri < 8; ri++)
		for (int ci = 0; ci < 8; ci++)
			if (validSelect(position{ ri,ci }))
				if ((validmove(position{ kr,kc })) && (b->getpiece(position{ ri,ci })->isLegal(position{ kr,kc })))
					return true;
	return false;
}

void Chess::findKing(int& kr, int& kc)
{
	for (int ri = 0; ri < 8; ri++)
		for (int ci = 0; ci < 8; ci++)
		{
			if (b->getpiece(position{ ri,ci }) != nullptr)
				if (b->getpiece(position{ ri,ci })->getcolor() == ply[turn]->getcolor())
					if(b->getpiece(position{ ri,ci })->getSym()=='k')
					{			
						kr = ri;
						kc = ci;
					}
		}
}

void Chess::legality(bool H[][8], position _select,int kr, int kc)
{
	for (int ri = 0; ri < 8; ri++)
		for (int ci = 0; ci < 8; ci++)
		{
			if (H[ri][ci])
			{
				selfcheck(H,_select,ri,ci,kr,kc);
			}
		}
}

void Chess::selfcheck(bool H[][8], position _select, int ri, int ci, int kr, int kc)
{
	b->movee(_select, position{ ri,ci }, 0, 0);
	turnChange();
	H[ri][ci] = !check(kr, kc);
	b->movee(position{ ri,ci }, _select, 0, 1);
	turnChange();
}

void Chess::castling(bool H[][8], position _select)
{
	if (!b->getpiece(_select)->getFirst() && b->getpiece(position{_select.ri,7})!=nullptr)
		if(!b->getpiece(position{ _select.ri,7 })->getFirst())
			if (b->getpiece(position{ _select.ri,5 }) == nullptr && b->getpiece(position{ _select.ri,6 }) == nullptr)
			{
				selfcheck(H, _select, _select.ri, 5);
				if (H[_select.ri][5])
					selfcheck(H, _select, _select.ri, 6);
			}
	if (!b->getpiece(_select)->getFirst() && b->getpiece(position{ _select.ri,0 }) != nullptr)
		if (!b->getpiece(position{ _select.ri,0 })->getFirst())
			if (b->getpiece(position{ _select.ri,3 }) == nullptr && b->getpiece(position{ _select.ri,2 }) == nullptr && b->getpiece(position{ _select.ri,1 }) == nullptr)
			{
				selfcheck(H, _select, _select.ri, 3);
				if (H[_select.ri][3])
					selfcheck(H, _select, _select.ri, 2);
			}
}

bool Chess::moveAvaliable(bool H[][8])
{
	for (int ri = 0; ri < 8; ri++)
		for (int ci = 0; ci < 8; ci++)
			if (H[ri][ci])
				return true;
	return false;
}

bool Chess::gameEnd()
{
	bool H[8][8];
	for (int ri = 0; ri < 8; ri++)
		for (int ci = 0; ci < 8; ci++)
		{
			if(validSelect(position{ ri,ci }))
			{
				highlight(H, position{ri,ci});
				legality(H, position{ ri,ci });
				if (moveAvaliable(H))
					return true;
			}
		}
	return false;
}


void Chess::play()
{
	ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
	bool rep=false;
	startscreen(rep);
	fstream rdr;
	int c1 = 6, c2 = 14;
	int kr=-1, kc=-1;
	bool H[8][8],Ischeck=false;
	bool game = true;
	bool Undo = false;
	int eachRow,  eachCol,dim=8,tB=8;
	printGrid(tB*dim,tB*dim,tB,eachRow, eachCol, -37,c1,c2);
	b->displayBoard(dim);
	if (rep)
	{
		replay();
		rdr.open("info.txt", std::ios::in | std::ios::out | std::ios::app);
	}
	else
		rdr.open("info.txt", std::ios::in | std::ios::out | std::ios::trunc);
	while (game)
	{	
		SetClr(15, 0);
		gotorowcol(10, 0);
		displayTurnMsg(ply[turn]);
		//do		{

		do
		{
			if (Ischeck)
			{
				printBox(kr * dim, kc * dim, dim, dim, -37, 12);
				b->getpiece(position{ kr,kc })->draw(kr * dim + 10, kc * dim + 20);
			}
			
			do
			{
				selectPiece(dim,Undo);
				if(Undo)
					break;
			} while (!validSelect(select));
			if (Undo)
				break;
			highlight(H,select);
			legality(H, select,kr, kc);
			if (!Ischeck && b->getpiece(select)->getSym() == 'k')
				castling(H, select);
			if (!moveAvaliable(H))
				continue;
			if(!Ischeck)
				printBox(select.ri * dim, select.ci * dim, dim, dim, -37, 2);
			b->getpiece(select)->draw(select.ri * dim + 10, select.ci * dim + 20);

			highlightBox(H, 3, dim);
			selectDestination(dim);
			UnhighlightBox(H, dim, c1, c2);

			prevForm(select, c1, c2, dim);
			b->getpiece(select)->draw(select.ri * dim + 10, select.ci * dim + 20);
		} while (!H[move.ri][move.ci]);
			//} while (!validmove(move));
//		} while (!(b->getpiece(select)->isLegal(move)));
		if (Undo)
		{
			info a = b->undo.top();
			if (a.piece != nullptr)
				rdr << Undo << "  " << a.start.ri << "  " << a.start.ci << "  " << a.end.ri << "  " << a.end.ci << "  " << a.piece->getSym() << " " << a.piece->getcolor() <<endl;
			else
				rdr << Undo << "  " << a.start.ri << "  " << a.start.ci << "  " << a.end.ri << "  " << a.end.ci <<"   -   " << endl;

			b->Undoo(c1, c2, dim,0);
			if (Ischeck)
			{
				prevForm(position{ kr,kc }, c1, c2, dim);
				if (b->getpiece(position{ kr,kc }) != nullptr)
					b->getpiece(position{ kr,kc })->draw(kr * dim + 10, kc * dim + 20);
			}
			Ischeck = false;
			Undo = false;
		}
		else
		{
			rdr << Undo << "  " << select.ri << "  " << select.ci << "  " << move.ri << "  " << move.ci << endl;
		if (Ischeck)
		{
			prevForm(position{kr,kc}, c1, c2, dim);
			b->getpiece(position{ kr,kc })->draw(kr * dim + 10, kc * dim + 20);
			Ischeck = false;
		}

				if (b->getpiece(select)->getSym() == 'k')
				{
					if (select.ci - move.ci == 2)
					{
						b->movee(position{ select.ri,0 }, position{ select.ri,3 }, 1);
						b->update(position{ select.ri,0 }, position{ select.ri,3 }, c1, c2, dim);
					}
					else if (select.ci - move.ci == -2)
					{
						b->movee(position{ select.ri,7 }, position{ select.ri,5 }, 1);
						b->update(position{ select.ri,7 }, position{ select.ri,5 }, c1, c2, dim);

					}

				}
			b->movee(select, move, 1);
			b->update(select, move,c1,c2,dim);
		}
		rdr << endl;
		Ischeck=check(kr,kc);
		turnChange();
		if (!gameEnd())
			game = false;
	}
	system("cls");
	SetClr(15, 0);
	gotorowcol(20, 50);
	if (Ischeck)
		checkkk();
	else
		stalemate();
}

void Chess::replay()
{
	ifstream rdr;
	rdr.open("info.txt", std::ios::in);
	int c1 = 6, c2 = 14;
	int kr = -1, kc = -1;
	bool Ischeck = false;
	bool game = true;
	bool Undo = false;
	int dim = 8, tB = 8;

	while (rdr >> Undo)
	{
		Sleep(400);
		if (Undo)
		{
			info temp;
			char sym;
			int c = 0;
			rdr >> temp.start.ri >> temp.start.ci >> temp.end.ri >> temp.end.ci >> sym;
			temp.piece = nullptr;
			if (sym != '-')
			{
				rdr >> c;
			}
			if (c == 0)
				b->Undoo(c1, c2, dim, 1, temp, Black, sym);
			else
				b->Undoo(c1, c2, dim, 1, temp, White, sym);

		}
		else
		{
			rdr >> select.ri >> select.ci >> move.ri >> move.ci;
			b->movee(select, move, 1);
			b->update(select, move, c1, c2, dim);
		}
		if (Ischeck)
		{
			prevForm(position{ kr,kc }, c1, c2, dim);
			if(b->getpiece(position{ kr,kc })!=nullptr)
				b->getpiece(position{ kr,kc })->draw(kr * dim + 10, kc * dim + 20);
			Ischeck = false;
			if (b->getpiece(move) != nullptr)
			{
				if (b->getpiece(move)->getSym() == 'k')
				{
					if (select.ci - move.ci == 2)
					{
						b->movee(position{ select.ri,0 }, position{ select.ri,3 }, 1);
						b->update(position{ select.ri,0 }, position{ select.ri,3 }, c1, c2, dim);
					}
					else if (select.ci - move.ci == -2)
					{
						b->movee(position{ select.ri,7 }, position{ select.ri,5 }, 1);
						b->update(position{ select.ri,7 }, position{ select.ri,5 }, c1, c2, dim);

					}

				}
			}
		}
		Ischeck = check(kr, kc);
		if (Ischeck)
		{
			printBox(kr * dim, kc * dim, dim, dim, -37, 12);
			b->getpiece(position{ kr,kc })->draw(kr * dim + 10, kc * dim + 20);
		}
		turnChange();
		if (!gameEnd())
			game = false;
	}
	if (!game)
	{
		system("cls");
		SetClr(15, 0);
		gotorowcol(60, 50);
		if (Ischeck)
			cout << "   Check Mate   \n\n\n\n\n\n\n";
		else
			cout << "   StaleMate   \n\n\n\n\n\n\n\n";

		exit(0);
	}

}
