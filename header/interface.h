/**
 * interface.h
 */
#ifndef INTERFACE_H
#define INTERFACE_H

#include <iostream>
#include "board.h"

using namespace std;

/**
 * @brief      Class for the user interface that handles all user inputs
 */
class Interface {
	Board* board;

public:
	int start();

};

#endif