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
	Board(unsigned short boardSize = 3);

	unsigned short getBoardSize() const;
	void printBoard() const;
	States checkBoardWin(unsigned short xPos, unsigned short yPos) const;
	States getState(unsigned short xPos, unsigned short yPos) const;

	bool placeMark(unsigned short xPos, unsigned short yPos, States state);
	static const char* getStateString(States state);
private:
	unsigned short size;
	std::vector<std::vector<States>> states;
};