#pragma once
#include "Board.h"
#include "Utility.h"
#include "Player.h"
class Chess
{
	position select, move;
	Player* ply[2];
	Board* b;
	int turn;
public:
	Chess();
	void play();
	void replay();
private:
	void displayTurnMsg(Player* p);
	void selectPiece(int dim,bool& Undo);
	void selectDestination(int dim);
	bool validSelect(position _select);
	bool validmove(position _move);
	void turnChange();
	void highlight(bool H[][8], position _select);
	void highlightBox(bool H[][8], int c,int dim);
	void UnhighlightBox(bool H[][8],int dim,int c1,int c2);
	bool check(int& kr, int& kc);
	void findKing(int& kr,int& kc);
	void legality(bool H[][8], position _select,int kr=0,int kc=0);
	void selfcheck(bool H[][8], position _select, int ri, int ci, int kr=0, int kc=0);
	void castling(bool H[][8], position _select);
	bool moveAvaliable(bool H[][8]);
	bool gameEnd();
};

