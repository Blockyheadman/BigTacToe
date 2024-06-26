#include <iostream>
#include <array>
#include <stdlib.h>

#include "Board.h"

static void clearScreen()
{
	std::cout << "\033[2J"  // clear the screen
		<< "\033[1;1H";     // move cursor home
}

static std::array<unsigned short, 2> getUserInput(unsigned short boardSize)
{
	unsigned short xPos = 0;
	unsigned short yPos = 0;

	do
	{
		std::cout << "Enter row #: ";
		if (!(std::cin >> xPos) && xPos > boardSize || xPos < 0) {
			xPos = boardSize + 1;
			std::cout << "Try entering a number between 1 and " << boardSize << std::endl;
			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n');
			continue;
		}

		std::cout << "Enter column #: ";
		if (!(std::cin >> yPos) || yPos > boardSize || yPos < 0) {
			yPos = boardSize + 1;
			std::cout << "Try entering a number between 1 and " << boardSize << std::endl;
			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n');
			continue;
		}

	} while (xPos > boardSize || yPos > boardSize);

	std::array<unsigned short, 2> input{};
	input[0] = xPos;
	input[1] = yPos;

	return input;
}

int main()
{
	unsigned int turn = 0;

	Board *pBigBoard = new Board();
	if (NULL == pBigBoard) {
		puts("could not allocate memory to heap.");
		return -1;
	}

	Board *pInnerBoards = (Board*)malloc(9 * sizeof(Board));
	if (NULL == pInnerBoards) {
		puts("could not allocate memory to heap.");
		return -1;
	}

	for (int i = 0; i < 9; i++)
		new (pInnerBoards + i) Board();

	unsigned short bigXPos;
	unsigned short bigYPos;
	unsigned short xPos;
	unsigned short yPos;

	bool insideInnerBoard;

	std::array<unsigned short, 2> input_array{};

	std::cout << "\n\n";

	do
	{
		pBigBoard->printBoard();
		std::cout << (turn % 2 == 0 ? "X" : "O") << " turn.\n-----\n";

		// get big board option
		input_array = getUserInput(pBigBoard->getBoardSize());

		bigXPos = input_array[0];
		bigYPos = input_array[1];

		clearScreen();

		if (pBigBoard->getState(bigXPos, bigYPos) != States::Nil)
		{
			std::cout << "This board has already been completed. Pick a different one.\n" << std::endl;
			continue;
		}

		// get smaller board option
		unsigned short currentBoard = (bigXPos - 1) * 3 + (bigYPos - 1);
		insideInnerBoard = true;

		std::cout << "\n";

		while (insideInnerBoard)
		{
			std::cout << "Inner board #" << currentBoard + 1 << '\n';
			pInnerBoards[currentBoard].printBoard();

			input_array = getUserInput(pBigBoard->getBoardSize());

			xPos = input_array[0];
			yPos = input_array[1];

			if (!pInnerBoards[currentBoard].placeMark(xPos, yPos, turn % 2 == 0 ? States::X : States::O))
			{
				clearScreen();
				std::cout << "Spot already taken! Try a different spot." << std::endl;
				continue;
			}

			States innerWin = pInnerBoards[currentBoard].checkBoardWin(xPos, yPos);
			if (innerWin != States::Nil && innerWin != States::Draw)
				pBigBoard->placeMark(bigXPos, bigYPos, turn % 2 == 0 ? States::X : States::O);
			else if (innerWin == States::Draw)
				pBigBoard->placeMark(bigXPos, bigYPos, States::Draw);

			insideInnerBoard = false;
		}


		clearScreen();
		std::cout << "\n\n";

		if (pBigBoard->checkBoardWin(bigXPos, bigYPos) != States::Nil) {
			break;
		}

		turn++;

	} while (true);

	pBigBoard->printBoard();
	if (pBigBoard->checkBoardWin(bigXPos, bigYPos) == States::Draw)
		std::cout << "\nThe game is a draw!" << std::endl;
	else
		std::cout << '\n' << Board::getStateString(turn % 2 == 0 ? States::X : States::O) << " has won the game!\n" << std::endl;

	for (int i = 0; i < 9; i++)
		pInnerBoards[i].~Board();

	delete pBigBoard;
	free(pInnerBoards);

	return 0;
}
