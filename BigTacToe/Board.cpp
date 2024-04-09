#include "Board.h"

#include <iostream>

Board::Board(int boardSize)
{
	size = boardSize;
	states.resize(size, std::vector<States>(size));
}

int Board::getBoardSize() const
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

void Board::placeMark(int xPos, int yPos, States state)
{
    if (state == States::Nil)
        return;

    states[xPos][yPos] = state;
}