/**
 * interface.cpp
 */
#include "interface.h"

/**
 * @brief      Function that hangles all of the IO
 */
int Interface::start() {
	board = new Board();
	char input;
	int player = 1;
	bool error = false;

	while (input != 'q') {
		cout << endl << endl;
		cout << "=------------------------------------------------------------=\n";
		cout << "| Use the numbers (1-7) to drop a peice in one of the slots. |\n";
		cout << "| Or enter (c) to let the computer make a move for you.      |\n";
		cout << "|                  ___________________                       |\n";

		if (player == -1)
			cout << "| Quit (q)        | CURRENT PLAYER: O |        Reset Game(r) |\n";
		else
			cout << "| Quit (q)        | CURRENT PLAYER: X |        Reset Game(r) |\n";

		cout << "=------------------------------------------------------------=\n";
		board->print(error);
		error = false;
		cout << "=------------------------------------------------------------***\n";
		cout << "PLAYER " << player << ": ";
		cin >> input;

		switch (input) {
		case 'q':
			return 0;
			break;

		case 'r':
			delete board;
			board = new Board();
			break;

		case 'c':
			board->computerMove(player);
			break;

		case '1':
			if (!board->move(player, 0)) error = true;

			break;

		case '2':
			if (!board->move(player, 1)) error = true;

			break;

		case '3':
			if (!board->move(player, 2)) error = true;

			break;

		case '4':
			if (!board->move(player, 3)) error = true;

			break;

		case '5':
			if (!board->move(player, 4)) error = true;

			break;

		case '6':
			if (!board->move(player, 5)) error = true;

			break;

		case '7':
			if (!board->move(player, 6)) error = true;

			break;

		default:
			error = true;
			break;
		}

		//Switch players
		if (error == false)
			player *= -1;
	}
}