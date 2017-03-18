/**
 * board.h
 */
#ifndef BOARD_H
#define BOARD_H

#define BOARD_HEIGHT 6
#define BOARD_WIDTH 7
#define GOAL 4 //must be <= BOARD_WIDTH and BOARD_HEIGHT
#define NUM_OF_DIRECTIONS 8
#define DEPTH 3

#include <iostream>
#include <array>
#include <unistd.h>
#include <string>
#include <algorithm>
#include <climits>
#include <stdlib.h>
#include <time.h>
#include <list>

using namespace std;


/**
 * @brief      Class for board.
 */
class Board {

	//The datastructure that holds the game pieces.
	int board[BOARD_HEIGHT][BOARD_WIDTH];
	//This integer value will be either 1 or 2 to signify the winner of the game.
	int winner;
	int winningMove;
	//The total moves of the game.
	int moves;

	//Search directions used in checkLastMoveForWin(int slot);
	array<int, NUM_OF_DIRECTIONS> SEARCH_X;
	array<int, NUM_OF_DIRECTIONS> SEARCH_Y;
	// array<string, NUM_OF_DIRECTIONS> DIRECTIONS;

	int checkWin(int slot);
	int unMove(int slot);
	int negaMax(int move, int depth, int alpha, int beta, int player);

public:

	Board ();
	int move(int player, int slot);
	int computerMove(int player);
	int getWinner();
	int print(bool error = false);

};

#endif