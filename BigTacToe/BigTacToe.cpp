#include <iostream>

#include "Board.h"

int main()
{
    Board bigBoard = Board();
    Board innerBoards[9];

    for (int i = 0; i < 9; i++)
        innerBoards[i] = Board();

    for (int i = 0; i < bigBoard.getBoardSize(); i++)
        for (int j = 0; j < bigBoard.getBoardSize(); j++)
            bigBoard.placeMark(i, j, i-j % 2 ? States::X : States::O);

    bigBoard.printBoard();
}
