#include "Board.h"

#include <iostream>

Board::Board (unsigned short int boardSize)
{
	size = boardSize;
	states.resize(size, std::vector<States>(size));
}

unsigned short int Board::getBoardSize() const
{
	return size;
}

void Board::printBoard() const
{
    std::cout << "    ";
    for (int i = 0; i < states.size(); i++)
        std::cout << i + 1 << "   ";

    std::cout << std::endl << "  ";
    for (int i = 0; i < (states.size() * 4) + 1; i++)
        std::cout << "-";
    std::cout << std::endl;

    for (int i = 0; i < states.size(); i++)
    {
        std::cout << i + 1 << " ";
        for (int j = 0; j < states[i].size(); j++)
        {
            std::cout << "|";
            if (states[i][j] == States::X) std::cout << " X ";
            else if (states[i][j] == States::O) std::cout << " O ";
            else if (states[i][j] == States::Nil) std::cout << "Nil";
            else std::cout << "   ";
        }
        std::cout << "|" << std::endl;
        std::cout << "  ";
        for (int k = 0; k < (states.size() * 4) + 1; k++)
            std::cout << "-";
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void Board::placeMark(unsigned short int xPos, unsigned short int yPos, States state)
{
    if (state == States::Nil)
        return;

    states[xPos][yPos] = state;
}

States Board::checkBoardWin(unsigned short int xPos, unsigned short int yPos) const
{
    const States state = states[xPos][yPos];

    // check for column win
    for (int i = 0; i < size; i++) {
        if (states[xPos][i] != state)
            break;
        if (i == size - 1)
            return state == States::O ? States::O : States::X;
    }

    // check for row win
    for (int i = 0; i < size; i++) {
        if (states[i][yPos] != state)
            break;
        if (i == size - 1)
            return state == States::O ? States::O : States::X;
    }

    // check diagonal win
    if (xPos == yPos) {
        for (int i = 0; i < size; i++) {
            if (states[i][i] != state)
                break;
            if (i == size - 1)
                return state == States::O ? States::O : States::X;
        }
    }

    // check anti diagonal win
    if (xPos + yPos == size - 1) {
        for (int i = 0; i < size; i++) {
            if (states[i][(size - 1) - i] != state)
                break;
            if (i == size - 1)
                return state == States::O ? States::O : States::X;
        }
    }

    return States::Nil;
}