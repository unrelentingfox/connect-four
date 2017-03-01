/**
 * board.cpp
 */
#include "board.h"

/**
 * @brief      Initializes the board the empty.
 */
Board::Board () {
	for (int y = 0; y < BOARD_HEIGHT; y++) {
		for (int x = 0; x < BOARD_WIDTH; x++) {
			board[y][x] = 0;
		}
	}
}

/**
 * @brief      Inserts a game peice into the given slot
 *
 * @param[in]  player  The player number (1 or 2)
 * @param[in]  slot    The slot number (0-6)
 *
 * @return     Returns 1 if the move was successfull and 0 if the move was
 *             unsuccessful (slot is full)
 */
int Board::move(int player, int slot) {
	//Iterate down the column until you reach the end or the top most game peice in the slot
	for (int i = 0; i < BOARD_HEIGHT; i ++) {
		if (board[i][slot] != 0)
			break;
	}

	//Insert the piece and check if it caused a win.
	if (--i; >= 0) {
		board[i][slot] = player;
		checkPieceForWin(slot, i - 1)
		return 1;
	}

	return 0;
}

int checkPieceForWin(int x, int y) {
	for
}

int Board::checkWin(int slot);