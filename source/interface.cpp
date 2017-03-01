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

	while (input != 'q') {
		cout << "=------------------------------------------------------------=\n";
		cout << "| Use the numbers (1-7) to drop a peice in one of the slots. |\n";
		cout << "|                  ___________________                       |\n";
		cout << "| Quit (q)        | CURRENT PLAYER: " << player+1 << " |        Reset Game(r) |\n";
		cout << "=------------------------------------------------------------=\n";
		board->print();
		cout << "=------------------------------------------------------------***\n";
		cout << "PLAYER " << player+1 << ": ";
		cin >> input;

		switch (input) {
		case 'q':
			return 0;
			break;

		case 'r':
			board = new Board();
			break;

		case '1':
			board->move(player+1, 0);
			break;

		case '2':
			board->move(player+1, 1);
			break;

		case '3':
			board->move(player+1, 2);
			break;

		case '4':
			board->move(player+1, 3);
			break;

		case '5':
			board->move(player+1, 4);
			break;

		case '6':
			board->move(player+1, 5);
			break;

		case '7':
			board->move(player+1, 6);
			break;
		}

		//Switch players
		player ^= 1;
	}
}