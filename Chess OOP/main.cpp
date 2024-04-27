#include <iostream>
#include "Chess.h"
#include <conio.h>

using namespace std;

int main()
{
    Chess c;
    char n;
    bool validInput = false;

    do {
        cout << "1. New Game\n" << "2. Continue\n";
        n = _getch();

        if (n == '1' || n == '2')
            validInput = true;
        else
            cout << "Invalid input. Please enter 1 or 2.\n";
    } while (!validInput);
    system("cls");
    c.play(n);
    return 0;
}
