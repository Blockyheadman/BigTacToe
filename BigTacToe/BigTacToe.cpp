#include <iostream>

#include "Board.h"

void clearScreen()
{
    std::cout << "\033[2J"  // clear the screen
        << "\033[1;1H";     // move cursor home
}

int main()
{
   unsigned int turn = 0;
    Board bigBoard = Board();
    Board innerBoards[9];

    for (int i = 0; i < 9; i++)
        innerBoards[i] = Board();

    unsigned short int xPos = 0;
    unsigned short int yPos = 0;

    do {
        std::cout << ":";
        do {

        } while (yPos < 0);
    } while (xPos < 0);

    /*for (int i = 0; i < bigBoard.getBoardSize(); i++)
        for (int j = 0; j < bigBoard.getBoardSize(); j++)
            bigBoard.placeMark(i, j, i-j % 2 ? States::X : States::O);*/
    
    std::cout << bigBoard.checkBoardWin(0,0) << std::endl;

    bigBoard.printBoard();
}
