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
	Board(int boardSize = 3);
	int getBoardSize() const;
	void printBoard() const;
	void placeMark(int xPos, int yPos, States state);
private:
	int size;
	std::vector<std::vector<States>> states;
};