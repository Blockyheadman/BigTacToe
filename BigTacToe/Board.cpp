#include "Board.h"

#include <iostream>

Board::Board(unsigned short boardSize)
{
	size = boardSize;
	states.resize(size, std::vector<States>(size));
}

unsigned short Board::getBoardSize() const
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

			switch (states[i][j]) {
			case States::X:
				std::cout << " X ";
				break;
			case States::O:
				std::cout << " O ";
				break;
			case States::Draw:
				std::cout << "Tie";
				break;
			default:
				std::cout << "   ";
			}
		}
		std::cout << "|" << std::endl;
		std::cout << "  ";
		for (int k = 0; k < (states.size() * 4) + 1; k++)
			std::cout << "-";
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

bool Board::placeMark(unsigned short xPos, unsigned short yPos, States state)
{
	if (state == States::Nil || states[xPos - 1][yPos - 1] != States::Nil)
		return false;
	else
	{
		states[xPos - 1][yPos - 1] = state;
		return true;
	}

}

// checks the board winning state, optional parameters if not checking a win from the stored win state.
States Board::checkBoardWin(unsigned short xPos, unsigned short yPos) const
{

	const States playerState = states[xPos - 1][yPos - 1];

	if (playerState == States::Nil)
		return States::Nil;

	// check for column win
	for (unsigned short i = 0; i < size; i++) {
		if (states[xPos - 1][i] != playerState)
			break;
		if (i == size - 1) {
			return playerState;
		}
	}

	// check for row win
	for (unsigned short i = 0; i < size; i++) {
		if (states[i][yPos - 1] != playerState)
			break;
		if (i == size - 1)
			return playerState;
	}

	// check diagonal win
	if (xPos - 1 == yPos - 1) {
		for (unsigned short i = 0; i < size; i++) {
			if (states[i][i] != playerState)
				break;
			if (i == size - 1)
				return playerState;
		}
	}

	// check anti diagonal win
	if (xPos - 1 + yPos - 1 == size - 1) {
		for (unsigned short i = 0; i < size; i++) {
			if (states[i][(size - 1) - i] != playerState)
				break;
			if (i == size - 1)
				return playerState;
		}
	}

	for (int i = 0; i < states.size(); i++) {
		for (int j = 0; j < states[i].size(); j++)
			if (states[i][j] == States::Nil)
				return States::Nil;
	}

	return States::Draw;
}

States Board::getState(unsigned short xPos, unsigned short yPos) const
{
	return states[xPos - 1][yPos - 1];
}

const char* Board::getStateString(States state)
{
	switch (state) {
	case States::X: return "X";
	case States::O: return "O";
	case States::Nil: return "Nil";
	}
}