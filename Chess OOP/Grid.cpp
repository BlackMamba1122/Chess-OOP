#include "Grid.h"
#include "Utility.h"
#include <iostream>
using namespace std;

void printBox(int sr, int sc, int rdim, int cdim, char s, int c)
{
	SetClr(c, c);
	for (int r = 0; r < rdim; r++)
	{
		gotorowcol(sr+r+10, sc+20);
		for (int c = 0; c < cdim; c++)
		{
			cout << s;
		}
	}
	
}

void printGrid(int rows, int cols, int d, int& eachRow, int& eachCol, char sym,int c1,int c2)
{
	eachRow = rows / d;
	eachCol = cols / d;
	for (int r = 0; r < d; r++)
	{
		for (int c = 0; c < d; c++)
		{
			int _r = r * eachRow, _c = c * eachCol;
			if(r%2==0)
			{
				if (c % 2 == 0)
					printBox(_r, _c, eachRow, eachCol, sym, c1);
				else
					printBox(_r, _c, eachRow, eachCol, sym, c2);
			}
			else
			{
				if (c % 2 == 1)
					printBox(_r, _c, eachRow, eachCol, sym, c1);
				else
					printBox(_r, _c, eachRow, eachCol, sym, c2);
			}

		}
	}
}

void prevForm(position pos,int c1,int c2,int dim)
{
	int c;
	if (pos.ri % 2 == 0)
	{
		if (pos.ci % 2 == 0)
			c = c1;
		else
			c = c2;
	}
	else
	{
		if (pos.ci % 2 == 1)
			c = c1;
		else
			c = c2;
	}
	printBox(pos.ri * dim, pos.ci * dim, dim, dim, -37, c);
}