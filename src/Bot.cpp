#include "Bot.hpp"
#include "Cell.hpp"
#include "Game.hpp"


Bot::Bot(const int &w, const int &h) :
	w(w),
	h(h),
	lastMove(DOWN),
	timeLastMove(0),
	timeUnchanged(0)
{
}

Bot::~Bot()
{
}

void Bot::reset()
{
	lastMove = DOWN;
	timeLastMove = 0;
	timeUnchanged = 0;
}

void Bot::setMap(const std::vector<std::vector<Cell>> &newState)
{
	map = newState;
}

bool Bot::isTopLineFull(const std::vector<std::vector<Cell>> &state, int size)
{
	for (int i = 0; i < size; i++) {
		if (state[0][i] == 0 ||
		(i > 0 && state[0][i - 1] == state[0][i])
		|| (i < size && state[0][i + 1] == state[0][i]))
			return false;
	}
	return true;
}

bool Bot::isRightColumnFull(const std::vector<std::vector<Cell>> &state, int size)
{
	for (int i = 0; i < size; i++) {
		if (state[i][size - 1] == 0 ||
		(i > 0 && state[i - 1][size - 1] == state[i][size - 1])
		|| (i < size && state[i + 1][size - 1] == state[i][size - 1]))
			return false;
	}
	return true;
}

bool Bot::isMaxInCorner(const std::vector<std::vector<Cell>> &state, int size)
{
	return state[0][size - 1] == getMax(state, size);
}

int Bot::getMax(const std::vector<std::vector<Cell>> &state, int size)
{
	int currentMax = 0;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			currentMax = state[i][j].value > currentMax ? state[i][j].value : currentMax;
		}
	}
	return currentMax;
}

int Bot::updateValuesAndReturn(int code, const std::vector<std::vector<Cell>> &newState)
{
	if (lastMove != code)
		timeLastMove = 0;
	lastMove = code;
	map = newState;
	return code;
}

int Bot::thinkAndPlay(const std::vector<std::vector<Cell>> &newState)
{
	timeLastMove += 1;
	std::cout << timeUnchanged << std::endl;
	if (newState != map) {
		timeUnchanged = 0;
		map = newState;
	}
	timeUnchanged += 1;
	if (timeUnchanged >= 3) {
		if (isTopLineFull(newState, w) && timeUnchanged < 10) {
			return updateValuesAndReturn(LEFT, newState);
		}
		if (isRightColumnFull(newState, w) && timeUnchanged < 10) {
			return updateValuesAndReturn(DOWN, newState);
		}
		std::cout << timeUnchanged << std::endl;
		if (timeUnchanged > 10)
			return updateValuesAndReturn(DOWN, newState);
		return updateValuesAndReturn(LEFT, newState);
	}
	switch (lastMove) {
		case (UP):
			if (timeLastMove >= 1) {
				return updateValuesAndReturn(RIGHT, newState);
			}
			return updateValuesAndReturn(UP, newState);
		case (RIGHT):
			return updateValuesAndReturn(UP, newState);
		case (DOWN):
			return updateValuesAndReturn(UP, newState);
		case (LEFT):
			if (isMaxInCorner(newState, w))
				return updateValuesAndReturn(UP, newState);
			return updateValuesAndReturn(RIGHT, newState);
		default:
			return updateValuesAndReturn(UP, newState);
	}
}