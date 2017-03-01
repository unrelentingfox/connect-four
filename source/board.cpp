/**
 * board.cpp
 */
#include "board.h"

/**
 * @brief      Initializes the board the empty.
 */
Board::Board () {
	winner = 0;
	SEARCH_Y = { -1, 0, 1, -1, 1, -1, 0, 1 };
	SEARCH_X = { -1, -1, -1, 0, 0, 1, 1, 1 };

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
	//Don't allow moves after game over.
	if (winner != 0)
		return 0;

	//Input validation.
	if (player != 1 && player != 2)
		return 0;

	if (slot < 0 || slot > BOARD_WIDTH)
		return 0;

	//Iterate down the column until you reach the end or the top most game peice in the slot
	int i;

	for (i = 0; i < BOARD_HEIGHT; i ++) {
		if (board[i][slot] != 0)
			break;
	}

	//Insert the piece and check if it caused a win.
	if (--i >= 0) {
		board[i][slot] = player;
		moves++;
		this->checkPieceForWin(slot, i);
		return 1;
	}

	return 0;
}


/**
 * @brief      Checks all of the tiles around the x and y indicies of the board
 *             for the player's tiles to see if it is a part of a 'connect-4'.
 *
 * @param[in]  x     The x index of the tile to check
 * @param[in]  y     The y index of the tile to check
 *
 * @return     Returns 1 if the tile is a 'connect-4', 0 otherwise.
 */
int Board::checkPieceForWin(int x, int y) {
	int yt = y;
	int xt = y;
	int count = 0;
	int player = board[y][x];
	// cout << "player was  " << player << endl;

	if (player != 1 && player != 2) {
		return 0;
		// cout << "invalid player\n";
	}

	int loop = 1;

	for (int i = 0; i < DIRECTIONS; i++) {
		// cout << "starting checking \n";
		yt = y;
		xt = x;
		loop = 1;
		count = 0;

		while (count <= GOAL && loop) {
			// cout << "checking direction (" << yt << ", " << xt << ")";

			//Check if yt and xt are still within the bounds of the board.
			if (yt >= BOARD_HEIGHT || yt < 0 || xt >= BOARD_WIDTH || xt < 0) {
				loop = 0;
				// cout << " ...Out of bounds" << endl;
			}
			else if (board[yt][xt] != player) {
				loop = 0;
				// cout << " ...not the right piece" << endl;
			}
			else {
				// cout << "counter increased\n";
				count++;
			}

			//Increment in the desired direction.
			yt += SEARCH_Y[i];
			xt += SEARCH_X[i];
		}

		if (count == GOAL) {
			winner = player;
			return 1;
		}
	}

	winner = 0;
	return 0;
}


int Board::getWinner() {
	return winner;
}


int Board::print() {
	//create an array of output options based upon the number in Board[y][x].
	array<string, 3> output;
	output[0] = "   |";
	output[1] = "(#)|";
	output[2] = "[_]|";
	//Output the top of the board.
	cout << endl << "             1   2   3   4   5   6   7        Player 1 = (*)";
	cout << endl << "           |---------------------------|      Player 2 = [_]" << endl;
	cout << "           |";

	for (int y = 0; y < BOARD_HEIGHT; y++) {
		//Output the body of the board.
		for (int x = 0; x < BOARD_WIDTH; x++) {
			cout << output[board[y][x]];
		}

		//Output the vertical dividers of the board.
		cout << endl << "           |---------------------------|" << endl;

		//Output the bottom of the board.
		if (y + 1 < BOARD_HEIGHT)
			cout << "           |";
		else {
			if (winner != 0)
				cout << "           !!      PLAYER " << winner << " WINS      !!";
			else
				cout << "           ||                         ||";

			cout << "      Total Moves: " <<  moves << endl;
		}
	}

	cout << endl;
}