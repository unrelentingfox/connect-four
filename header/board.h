/**
 * board.h
 */
#ifndef BOARD_H
#define BOARD_H

#define BOARD_HEIGHT 6
#define BOARD_WIDTH 7
#define GOAL 4 //must be <= BOARD_WIDTH and BOARD_HEIGHT
#define DIRECTIONS 8

#include <iostream>
#include <array>
#include <string>

using namespace std;


/**
 * @brief      Class for board.
 */
class Board {

	//The datastructure that holds the game pieces.
	int board[BOARD_HEIGHT][BOARD_WIDTH];
	//This integer value will be either 1 or 2 to signify the winner of the game.
	int winner;
	//The total moves of the game.
	int moves;

	//Search directions used in checkLastMoveForWin(int slot);
	array<int, DIRECTIONS> SEARCH_X;
	array<int, DIRECTIONS> SEARCH_Y;

	int checkPieceForWin(int x, int y);

public:

	Board ();
	int move(int player, int slot);
	int getWinner();
	int print();

};

#endif