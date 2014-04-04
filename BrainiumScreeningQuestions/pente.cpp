#include "stdafx.h"

// direction vectors
const std::pair<int, int> DIRECTIONS[8] = {
	std::make_pair<int, int>(1, 0),
	std::make_pair<int, int>(1, 1),
	std::make_pair<int, int>(0, 1),
	std::make_pair<int, int>(-1, 1),
	std::make_pair<int, int>(-1, 0),
	std::make_pair<int, int>(-1, -1),
	std::make_pair<int, int>(0, -1),
	std::make_pair<int, int>(1, -1)
};

const int BOARD_SIZE = 19;
const int PLAYER_1 = 1;
const int PLAYER_2 = -1;
const int EMPTY = 0;

typedef int board[BOARD_SIZE][BOARD_SIZE];
typedef std::vector<std::pair<int, int>> captures;

const bool fiveInARow(const board state, const int player) {
	// check every tile
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			// check each direction
			for (auto p : DIRECTIONS) {
				int same_count = 0;
				// looking for 5 in a row
				for (int c = 0; c < 5; c++) {
					// disregard sets of 5 that go off the board
					if ((i + 4 * p.first) < 0 || (i + 4 * p.first) >= BOARD_SIZE || (j + 4 * p.second) < 0 || (j + 4 * p.second) >= BOARD_SIZE) {
						continue;
					}
					if (state[i + c * p.first][j + c * p.second] == player) {
						same_count++;
					}
				}
				if (same_count == 5) {
					return true;
				}
			}
		}
	}

	return false;
}

const captures getCaptures(board state, std::pair<int, int> lastMoveCoord) {
	captures retval = captures();

	// who just moved?
	const int player = state[lastMoveCoord.first][lastMoveCoord.second];

	for (auto p : DIRECTIONS) {
		if ((lastMoveCoord.first + 3 * p.first) < 0 || (lastMoveCoord.first + 3 * p.first) >= BOARD_SIZE || (lastMoveCoord.second + 3 * p.second) < 0 || (lastMoveCoord.second + 3 * p.second) >= BOARD_SIZE) {
			continue;
		}

		int one = state[lastMoveCoord.first + p.first][lastMoveCoord.second + p.second];
		int two = state[lastMoveCoord.first + 2 * p.first][lastMoveCoord.second + 2 * p.second];
		int three = state[lastMoveCoord.first + 3 * p.first][lastMoveCoord.second + 3 * p.second];

		if (player == three &&  -1 * player == one && -1 * player == two) {
			retval.push_back(std::make_pair<int, int>(lastMoveCoord.first + 1 * p.first, lastMoveCoord.second + 1 * p.second));
			retval.push_back(std::make_pair<int, int>(lastMoveCoord.first + 2 * p.first, lastMoveCoord.second + 2 * p.second));
		}
	}


	return retval;
}

void test_pente(void) {
	board test = { 0 };

	assert(fiveInARow(test, PLAYER_1) == false);
	assert(fiveInARow(test, PLAYER_2) == false);

	for (int d = 0; d < 5; d++) {
		test[d][d] = PLAYER_1;
	}

	assert(fiveInARow(test, PLAYER_1) == true);
	assert(fiveInARow(test, PLAYER_2) == false);


	board test2 = { 0 };
	for (int d = 0; d < 5; d++) {
		test2[d + 3][7] = PLAYER_2;
	}

	assert(fiveInARow(test2, PLAYER_1) == false);
	assert(fiveInARow(test2, PLAYER_2) == true);

	board test3 = { 0 };
	test3[0][0] = PLAYER_1;
	test3[1][0] = PLAYER_2;
	test3[2][0] = PLAYER_2;
	test3[0][1] = PLAYER_2;
	test3[0][2] = PLAYER_2;
	test3[0][3] = PLAYER_1;
	test3[3][0] = PLAYER_1;

	auto captures_0_0 = getCaptures(test3, std::make_pair<int, int>(0, 0));
	assert(captures_0_0.size() == 4);
	assert(std::find(captures_0_0.begin(), captures_0_0.end(), std::make_pair<int, int>(0, 1)) != captures_0_0.end());
	assert(std::find(captures_0_0.begin(), captures_0_0.end(), std::make_pair<int, int>(0, 2)) != captures_0_0.end());
	assert(std::find(captures_0_0.begin(), captures_0_0.end(), std::make_pair<int, int>(1, 0)) != captures_0_0.end());
	assert(std::find(captures_0_0.begin(), captures_0_0.end(), std::make_pair<int, int>(2, 0)) != captures_0_0.end());

	auto captures_0_3 = getCaptures(test3, std::make_pair<int, int>(0, 3));
	assert(captures_0_3.size() == 2);
	assert(std::find(captures_0_3.begin(), captures_0_3.end(), std::make_pair<int, int>(0, 1)) != captures_0_3.end());
	assert(std::find(captures_0_3.begin(), captures_0_3.end(), std::make_pair<int, int>(0, 2)) != captures_0_3.end());

	auto captures_3_0 = getCaptures(test3, std::make_pair<int, int>(3, 0));
	assert(captures_3_0.size() == 2);
	assert(std::find(captures_3_0.begin(), captures_3_0.end(), std::make_pair<int, int>(1, 0)) != captures_3_0.end());
	assert(std::find(captures_3_0.begin(), captures_3_0.end(), std::make_pair<int, int>(2, 0)) != captures_3_0.end());

	auto captures_2_0 = getCaptures(test3, std::make_pair<int, int>(2, 0));
	assert(captures_2_0.size() == 0);
}