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
	explicit Board(unsigned short boardSize = 3);

	[[nodiscard]] unsigned short getBoardSize() const;
	void printBoard() const;
	[[nodiscard]] States checkBoardWin(unsigned short xPos, unsigned short yPos) const;
	[[nodiscard]] States getState(unsigned short xPos, unsigned short yPos) const;

	bool placeMark(unsigned short xPos, unsigned short yPos, States state);
	static const char* getStateString(States state);
private:
	unsigned short size;
	std::vector<std::vector<States>> states;
};