/**
 * board.h
 */
#ifndef BOARD_H
#define BOARD_H

#define BOARD_HEIGHT 6
#define BOARD_WIDTH 7

#include <iostream>

using namespace std;


/**
 * @brief      Class for board.
 */
class Board {

	//The datastructure that holds the game pieces.
	int[BOARD_HEIGHT][BOARD_WIDTH] board;
	//This integer value will be either 1 or 2 to signify the winner of the game.
	int winner;

	//Search directions used in checkLastMoveForWin(int slot);
	static const int searchX[] = { -1, -1, -1, 0, 0, 1, 1, 1 };
	static const int searchY[] = { -1, 0, 1, -1, 1, -1, 0, 1 };

	int checkLastMoveForWin(int slot);

public:

	Board ();
	int move(int player, int slot);
	int getWinner();

};

#endif