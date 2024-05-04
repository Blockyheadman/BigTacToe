#include <iostream>

#include "Board.h"

static void clearScreen()
{
	std::cout << "\033[2J"  // clear the screen
		<< "\033[1;1H";     // move cursor home
}

static int* getUserInput(unsigned short int boardSize)
{
	unsigned short int xPos = 0;
	unsigned short int yPos = 0;

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

	int input[] = { xPos, yPos };

	return input;
}

int main()
{
	unsigned int turn = 0;
	Board bigBoard = Board();
	Board innerBoards[9];

	for (unsigned short int i = 0; i < 9; i++)
		innerBoards[i] = Board();

	unsigned short int bigXPos;
	unsigned short int bigYPos;
	unsigned short int xPos;
	unsigned short int yPos;

	bool insideInnerBoard;

	int* input_ptr;

	std::cout << "\n\n";

	/*bigBoard.placeMark(1, 1, States::X);
	bigBoard.placeMark(2, 2, States::X);
	innerBoards[8].placeMark(1, 1, States::X);
	innerBoards[8].placeMark(2, 2, States::X);*/

	do
	{
		bigBoard.printBoard();
		std::cout << (turn % 2 == 0 ? "X" : "O") << " turn.\n-----\n";

		// get big board option
		input_ptr = getUserInput(bigBoard.getBoardSize());

		bigXPos = input_ptr[0];
		bigYPos = input_ptr[1];

		clearScreen();

		if (bigBoard.getState(bigXPos, bigYPos) != States::Nil)
		{
			std::cout << "This board has already been completed. Pick a different one.\n" << std::endl;
			continue;
		}

		// get smaller board option
		unsigned short int currentBoard = (bigXPos - 1) * 3 + (bigYPos - 1);
		insideInnerBoard = true;

		std::cout << "\n";

		while (insideInnerBoard)
		{
			std::cout << "Inner board #" << currentBoard + 1 << '\n';
			innerBoards[currentBoard].printBoard();

			input_ptr = getUserInput(bigBoard.getBoardSize());

			xPos = input_ptr[0];
			yPos = input_ptr[1];

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
