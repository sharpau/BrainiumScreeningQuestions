// BrainiumScreeningQuestions.cpp : Defines the entry point for the console application.
//

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
const int PLAYER_2 = 2;
const int EMPTY = 0;

typedef int board[BOARD_SIZE][BOARD_SIZE];

const bool fiveInARow(const board state, const int player) {
	// check every tile
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			for (auto p : DIRECTIONS) {
				int same_count = 0;
				for (int c = 0; c < 5; c++) {
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


int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

