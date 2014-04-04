#include "stdafx.h"

// direction vectors
const std::pair<int, int> DIRECTIONS[8] = {
	std::make_pair<int, int>(1, 0),
	std::make_pair<int, int>(0, 1),
	std::make_pair<int, int>(-1, 0),
	std::make_pair<int, int>(0, -1),
};

const int BOARD_SIZE = 10;
const int BLACK = -1;
const int EMPTY = 0;

typedef int puzzle[BOARD_SIZE][BOARD_SIZE];

bool isIlluminated(puzzle p, std::pair<int, int> coord, std::vector<std::pair<int, int>> litCoords) {

}

void test_akari(void) {

}