#include "stdafx.h"

// direction vectors
const std::pair<int, int> DIRECTIONS[4] = {
	std::make_pair<int, int>(1, 0),
	std::make_pair<int, int>(0, 1),
	std::make_pair<int, int>(-1, 0),
	std::make_pair<int, int>(0, -1),
};

const int BOARD_SIZE = 10;
const int BLACK = -1;
const int EMPTY = 0;

typedef int puzzle[BOARD_SIZE][BOARD_SIZE];

// returns true if coord is illuminated OR contains a light
const bool isIlluminated(puzzle p, std::pair<int, int> coord, std::vector<std::pair<int, int>> litCoords) {
	for (auto d : DIRECTIONS) {
		int x = coord.first;
		int y = coord.second;

		// check each direction until we hit a number or a black square
		while (p[x][y] == EMPTY && x >= 0 && y >= 0 && x < BOARD_SIZE && y < BOARD_SIZE) {
			// does this square have a light?
			if (std::find(litCoords.begin(), litCoords.end(), std::make_pair(x, y)) != litCoords.end()) {
				return true;
			}
			x += d.first;
			y += d.second;
		}
	}
	return false;
}

void test_akari(void) {
	puzzle test = { 0 };
	test[0][3] = BLACK;
	test[1][2] = 2;
	test[2][1] = BLACK;
	test[3][0] = 3;

	std::vector<std::pair<int, int>> lights;
	lights.push_back(std::make_pair(1, 1));

	assert(isIlluminated(test, std::make_pair(0, 0), lights) == false);
	assert(isIlluminated(test, std::make_pair(1, 0), lights) == true);
	assert(isIlluminated(test, std::make_pair(1, 1), lights) == true);
	assert(isIlluminated(test, std::make_pair(3, 3), lights) == false);
	assert(isIlluminated(test, std::make_pair(1, 5), lights) == false);

}