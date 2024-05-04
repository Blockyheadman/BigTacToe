#include <iostream>
#include <array>

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
		if (!(std::cin >> xPos)) {
			xPos = boardSize + 1;
			std::cout << "Try again." << std::endl;
			std::cin.clear();
			std::cin.ignore();
			continue;
		}

		if (xPos > boardSize || xPos < 0) {
			xPos = boardSize + 1;
			std::cout << "Try entering a number between 1 and " << boardSize << std::endl;
			std::cin.clear();
			std::cin.ignore();
			continue;
		}
		std::cout << "Enter column #: ";
		if (!(std::cin >> yPos)) {
			yPos = boardSize + 1;
			std::cout << "Try again." << std::endl;
			std::cin.clear();
			std::cin.ignore();
			continue;
		}

		if (yPos > boardSize || yPos < 0) {
			yPos = boardSize + 1;
			std::cout << "Incorrect input, try again." << std::endl;
			std::cin.clear();
			std::cin.ignore();
			continue;
		}

	} while (xPos > boardSize || yPos > boardSize);

	std::array<unsigned short, 2> input;
	input[0] = xPos;
	input[1] = yPos;

	return input;
}

int main()
{
	unsigned int turn = 0;
	Board bigBoard = Board();
	Board innerBoards[9];

	for (short i = 0; i < 9; i++)
		innerBoards[i] = Board();

	unsigned short bigXPos = 0;
	unsigned short bigYPos = 0;
	unsigned short xPos = 0;
	unsigned short yPos = 0;

	bool insideInnerBoard;

	std::array<unsigned short, 2> input_array;

	std::cout << "\n\n";

	do
	{
		bigBoard.printBoard();
		std::cout << (turn % 2 == 0 ? "X" : "O") << " turn.\n-----\n";

		// get big board option
		input_array = getUserInput(bigBoard.getBoardSize());

		bigXPos = input_array[0];
		bigYPos = input_array[1];

		clearScreen();

		if (bigBoard.getState(bigXPos, bigYPos) != States::Nil)
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
			innerBoards[currentBoard].printBoard();

			input_array = getUserInput(bigBoard.getBoardSize());

			xPos = input_array[0];
			yPos = input_array[1];

			if (!innerBoards[currentBoard].placeMark(xPos, yPos, turn % 2 == 0 ? States::X : States::O))
			{
				clearScreen();
				std::cout << "Spot already taken! Try a different spot." << std::endl;
				continue;
			}

			if (innerBoards[currentBoard].checkBoardWin(xPos, yPos) != States::Nil)
				bigBoard.placeMark(bigXPos, bigYPos, turn % 2 == 0 ? States::X : States::O);

			insideInnerBoard = false;
		}


		clearScreen();
		std::cout << "\n\n";

		if (bigBoard.checkBoardWin(bigXPos, bigYPos) != States::Nil) {
			break;
		}

		turn++;

	} while (true);

	bigBoard.printBoard();
	std::cout << '\n' << Board::getStateString(turn % 2 == 0 ? States::X : States::O) << " has won the game!\n\n";
}
