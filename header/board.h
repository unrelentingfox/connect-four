/**
 * board.h
 */
#ifndef BOARD_H
#define BOARD_H

#define BOARD_HEIGHT 6
#define BOARD_WIDTH 7
#define GOAL 4 //must be <= BOARD_WIDTH and BOARD_HEIGHT
#define NUM_OF_DIRECTIONS 8
#define DEPTH 4

#include <iostream>
#include <array>
#include <unistd.h>
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
	array<int, NUM_OF_DIRECTIONS> SEARCH_X;
	array<int, NUM_OF_DIRECTIONS> SEARCH_Y;
	// array<string, NUM_OF_DIRECTIONS> DIRECTIONS;

	int checkWin(int x, int y);
	int unMove(int slot);
	int miniMax(int player, int move, int depth);

public:

	Board ();
	int move(int player, int slot);
	int computerMove(int player);
	int getWinner();
	int print(bool error = false);

};

#endif