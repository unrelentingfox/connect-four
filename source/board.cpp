/**
 * board.cpp
 */
#include "board.h"

/**
 * @brief      Initializes the board the empty.
 */
Board::Board () {
	winner = 0;
	winningMove = 0;
	SEARCH_Y = { 0, 0, -1, 1, -1, 1, -1, 1};
	SEARCH_X = { -1, 1, 0, 0, 1, -1, -1, 1};
	// DIRECTIONS = {"LEFT", "RIGHT", "UP", "DOWN", "UP-RIGHT", "DOWN-LEFT", "UP-LEFT", "DOWN-RIGHT"};

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

		if (this->checkWin(slot) == INT_MAX) {
			winner = player;
			winningMove = slot;
		}

		return 1;
	}

	return 0;
}

int Board::unMove(int slot) {
	int removed = 0;

	if (slot == winningMove) {
		winner = 0;
	}

	for (int i = 0; removed == 0 && i < BOARD_HEIGHT; i++) {
		if (board[i][slot] != 0) {
			board[i][slot] = 0;
			removed = 1;
		}
	}

	return removed;
}


/**
 * @brief      Uses the Min-Max algorithm to make a move based upon the current board state
 *
 * @param[in]  player  The player who's move will be made
 *
 * @return     { description_of_the_return_value }
 */
int Board::computerMove(int player) {
	srand (time(NULL));
	int bestMove = 4;
	int bestScore = -100000;
	int worstScore = 100000;
	int currScore = 0;
	array<int, 7> movesMax = {0, 0, 0, 0, 0, 0, 0};
	array<int, 7> movesMin = {0, 0, 0, 0, 0, 0, 0};

	//MinMax Algorithm returns slot
	for (int move = 0; move < BOARD_WIDTH; move++) {
		if (this->move(player, move)) {
			currScore = this->negaMax(move, 8, INT_MIN, INT_MAX, player) * player;
			movesMax[move] = currScore;

			if (currScore > bestScore) {
				bestMove = move;
				bestScore = currScore;
			}
			else if (currScore < worstScore) {
				worstScore = currScore;
			}

			this->unMove(move);
		}
	}

	cout << movesMax[0] << " " << movesMax[1] << " " << movesMax[2] << " " << movesMax[3] << " " << movesMax[4] << " " << movesMax[5] << " " <<
	     movesMax[6] << endl;
	cout << movesMin[0] << " " << movesMin[1] << " " << movesMin[2] << " " << movesMin[3] << " " << movesMin[4] << " " << movesMin[5] << " " <<
	     movesMin[6] << endl;

	//do a random move if all of the moves are the same.
	if (bestScore == worstScore) {
		do {
			bestMove = rand() % 7;
		}
		while (!this->move(player, bestMove));
	}
	else
		this->move(player, bestMove);

	return 1;
}

int Board::negaMax(int move, int depth, int alpha, int beta, int player) {
	int h = 0;

	if (depth == 0 ) {
		return (checkWin(move) * player);
	}else if (winner == true){
		return checkWin(move);
	}

	int bestValue = INT_MIN;

	for (int childMove = 0; childMove < BOARD_WIDTH; childMove++) {
		if (this->move(player, childMove)) {
			int v = negaMax(childMove, depth - 1, -beta, -alpha, player * -1)
			bestValue = max(bestValue, v);
			alpha = max(bestValue, v);
			this->unMove(childMove);

			if (alpha >= beta)
				break;
		}
	}

	return bestValue;
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
int Board::checkWin(int slot) {
	//find the x y coordinate of the peice
	int y;

	for (y = 0; y < BOARD_HEIGHT; y ++) {
		if (board[y][slot] != 0)
			break;
	}

	int player = board[y][slot];
	int yt = y;
	int xt = slot;
	int score = 0;
	int count = 1;
	int countMax = 1;
	int verticalHeight = 0;
	int verticalHeightOfMax = 0;
	int direction1 = 3;
	int direction2 = 0;
	bool interference = false;

	for (int axis = 0; axis < NUM_OF_DIRECTIONS; axis += 2) {
		direction1 = 3;
		direction2 = 0;

		while (direction1 >= 0) {
			yt = y;
			xt = slot;

			//Search in one direction.
			for (int j = 0; j < direction1 && interference == false; j++) {
				yt += SEARCH_Y[axis];
				xt += SEARCH_X[axis];

				//Check if yt and xt are still within the bounds of the board.
				if (yt >= BOARD_HEIGHT || yt < 0 || xt >= BOARD_WIDTH || xt < 0)
					break;

				if (board[yt][xt] == player) {
					count++;
				}
				//When there is an empty space between peices, find out the depth of the gap.
				else if (board[yt][xt] == 0) {
					for (int i = yt; i < BOARD_HEIGHT; i++) {
						if (board[i][xt] != 0)
							break;

						verticalHeight++;
					}
				}
				else if (board[yt][xt] == player * -1) {
					interference = true;
				}
			}

			//check for win or inteerference by other player's peice.
			if (count >= 4) {
				return INT_MAX;
			}
			else if (interference) {
				count = 1;
			}

			//Reset yt and xt back to the original positions.
			yt = y;
			xt = slot;

			//Search in the opposite direction as before.
			for (int j = 0; j < direction2 && interference == false; j++) {
				yt += SEARCH_Y[axis + 1];
				xt += SEARCH_X[axis + 1];

				//Check if yt and xt are still within the bounds of the board.
				if (yt >= BOARD_HEIGHT || yt < 0 || xt >= BOARD_WIDTH || xt < 0)
					break;

				if (board[yt][xt] == player) {
					count++;
				}
				//When there is an empty space between peices, find out the depth of the gap.
				else if (board[yt][xt] == 0) {
					for (int i = yt; i < BOARD_HEIGHT; i++) {
						if (board[i][xt] != 0)
							break;

						verticalHeight++;
					}
				}
				else if (board[yt][xt] == player * -1) {
					interference = true;
				}
			}

			//check for win or inteerference by other player's peice.
			if (count >= 4) {
				return INT_MAX;
			}
			else if (interference) {
				count = 1;
			}

			//Set the maximum count for this axis.
			if (count > countMax) {
				countMax = count;
				verticalHeightOfMax = verticalHeight;
			}
			else if (count == countMax && verticalHeight < verticalHeightOfMax) {
				verticalHeightOfMax = verticalHeight;
			}

			direction1--;
			direction2++;
			count = 1;
			verticalHeight = 0;
			interference = false;
		}

		//Add to the score
		if (countMax == 3) {
			score += 1000 - (100 * verticalHeightOfMax);
		}
		else if (countMax == 2) {
			score += 100 - (10 * verticalHeightOfMax);
		}
		else {
			score += 1 - verticalHeightOfMax;
		}

		countMax = 1;
	}

	return score;
}

int Board::getWinner() {
	return winner;
}

int Board::print(bool error) {
	//create an array of output options based upon the number in Board[y][x].
	array<string, 3> output;
	output[0] = "   |";
	output[1] = " X |";
	output[2] = " O |";
	//Output the top of the board.
	cout << endl << "             1   2   3   4   5   6   7        Player 1 = X";
	cout << endl << "           |---------------------------|      Player 2 = O" << endl;
	cout << "           |";

	for (int y = 0; y < BOARD_HEIGHT; y++) {
		//Output the body of the board.
		for (int x = 0; x < BOARD_WIDTH; x++) {
			if (board[y][x] == 1)
				cout << " X |";
			else if (board[y][x] == -1)
				cout << " O |";
			else
				cout << "   |";
		}

		//Output the vertical dividers of the board.
		cout << endl << "           |---------------------------|" << endl;

		//Output the bottom of the board.
		if (y + 1 < BOARD_HEIGHT)
			cout << "           |";
		else {
			if (winner != 0) {
				cout << "           !! '+.= PLAYER " << winner << " WINS =.+' !!";
			}
			else if (error) {
				cout << "           !! INVALID MOVE, TRY AGAIN !!";
			}
			else {
				cout << "           ||                         ||";
			}

			cout << "      Total Moves: " <<  moves << endl;
		}
	}

	cout << endl;
}