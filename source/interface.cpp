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
	int player = 0;
	bool error = false;

	while (input != 'q') {
		cout << endl << endl;
		cout << "=------------------------------------------------------------=\n";
		cout << "| Use the numbers (1-7) to drop a peice in one of the slots. |\n";
		cout << "|                  ___________________                       |\n";
		cout << "| Quit (q)        | CURRENT PLAYER: " << player + 1 << " |        Reset Game(r) |\n";
		cout << "=------------------------------------------------------------=\n";
		board->print(error);
		error = false;
		cout << "=------------------------------------------------------------***\n";
		cout << "PLAYER " << player + 1 << ": ";
		cin >> input;

		switch (input) {
		case 'q':
			return 0;
			break;

		case 'r':
			board = new Board();
			break;

		case '1':
			if (!board->move(player + 1, 0)) error = true;

			break;

		case '2':
			if (!board->move(player + 1, 1)) error = true;
			break;

		case '3':
			if (!board->move(player + 1, 2)) error = true;
			break;

		case '4':
			if (!board->move(player + 1, 3)) error = true;
			break;

		case '5':
			if (!board->move(player + 1, 4)) error = true;
			break;

		case '6':
			if (!board->move(player + 1, 5)) error = true;
			break;

		case '7':
			if (!board->move(player + 1, 6)) error = true;
			break;

		default:
			error = true;
			break;
		}

		//Switch players
		if (error == false)
			player ^= 1;
	}
}