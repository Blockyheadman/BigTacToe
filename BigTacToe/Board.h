#pragma once

#include <vector>

enum States
{
	Nil = 0,
	X = 1,
	O = 2
};

class Board
{
public:
	Board(unsigned short int boardSize = 3);

	unsigned short int getBoardSize() const;
	void printBoard() const;
	States checkBoardWin(unsigned short int xPos, unsigned short int yPos) const;
	States getState(unsigned short int xPos, unsigned short int yPos) const;

	bool placeMark(unsigned short int xPos, unsigned short int yPos, States state);
	static const char* getStateString(States state);
private:
	unsigned short int size;
	std::vector<std::vector<States>> states;
};