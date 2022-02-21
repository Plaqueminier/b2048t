#include "Game.hpp"
#include "Cell.hpp"

Game::Game(const int &w, const int &h) :
	w(w),
	h(h),
	map(w, std::vector<Cell>(h)),
	minValue(2)
{
	srand(std::chrono::system_clock::now().time_since_epoch() / std::chrono::milliseconds(1));
	addRandomMinValue();
}

Game::~Game()
{
}

void Game::dump()
{
	for (int i = 0; i < w; i++) {
		for (int j = 0; j < h; j++) {
			std::cout << map[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

void Game::reset()
{
	for (int i = 0; i < w; i++) {
		for (int j = 0; j < h; j++) {
			map[i][j].value = 0;
		}
	}
	addRandomMinValue();
}

int Game::getCellValue(const int &index)
{
	for (int i = 0; i < w; i++) {
		for (int j = 0; j < h; j++) {
			if (i * h + j == index)
				return map[i][j].value;
		}
	}
	return -1;	
}

int Game::countValue(const int &val)
{
	int count = 0;
	for (int i = 0; i < w; i++) {
		for (int j = 0; j < h; j++) {
			if (map[i][j].value == val)
				count += 1;
		}
	}
	return count;
}

bool Game::addRandomMinValue()
{
	int freeCells = countValue(0);
	if (!freeCells)
		return false;
	int randomFreeCell = rand() % countValue(0);
	int whichValue = rand() % 10;
	std::cout << randomFreeCell << std::endl;
	int index = 0;
	for (int i = 0; i < w; i++) {
		for (int j = 0; j < h; j++) {
			if (map[i][j].value == 0 && index == randomFreeCell) {
				map[i][j].value = whichValue > 1 ? minValue : minValue * 2;
				return true;
			}
			index += (map[i][j].value == 0) ? 1 : 0;
		}
	}
	return false;
}

std::vector<std::vector<Cell>> &Game::getMap()
{
	return map;
}

std::vector<std::vector<Cell>> &Game::updateCells(const ArrowDirection &direction)
{
	std::vector<std::vector<Cell>> mapCopy = map;
	switch (direction) {
		case ArrowDirection::LEFT:
			moveLeft();
			break;
		case ArrowDirection::RIGHT:
			moveRight();
			break;
		case ArrowDirection::UP:
			moveUp();
			break;
		case ArrowDirection::DOWN:
			moveDown();
			break;
		default:
			std::cerr << "Should not happen, update with invalid direction" << std::endl;
			break;
	}
	for (int i = 0; i < w; i++) {
		for (int j = 0; j < h; j++) {
			map[i][j].merged = false;
		}
	}
	if (mapCopy != map) {
		if (!addRandomMinValue()) {
			std::cout << "YOU LOSE !" << std::endl;
			throw(getMax());
		}
		dump();
	} else {
		if (!countValue(0)) {
			std::cout << "YOU LOSE !" << std::endl;
			throw(getMax());
		}
		std::cout << "CANNOT MOVE THIS WAY" << std::endl;
	}
	return map;
}

void Game::moveLeft()
{
	for (int i = 0; i < w; i++) {
		for (int j = 0; j < h; j++) {
			if (map[i][j].value != 0) {
				std::reference_wrapper<Cell> currentCell = std::ref(map[i][j]);
				for (int col = j - 1; col >= 0; col--) {
					if (!shiftCell(currentCell, i, col))
						break;
				}
			}
		}
	}
}

void Game::moveRight()
{
	for (int i = w - 1; i >= 0; i--) {
		for (int j = h - 1; j >= 0; j--) {
			if (map[i][j].value != 0) {
				std::reference_wrapper<Cell> currentCell = std::ref(map[i][j]);
				for (int col = j + 1; col < w; col++) {
					if (!shiftCell(currentCell, i, col))
						break;
				}
			}
		}
	}
}

void Game::moveUp()
{
	for (int i = 0; i < w; i++) {
		for (int j = 0; j < h; j++) {
			if (map[i][j].value != 0) {
				std::reference_wrapper<Cell> currentCell = std::ref(map[i][j]);
				for (int line = i - 1; line >= 0; line--) {
					if (!shiftCell(currentCell, line, j))
						break;
				}
			}
		}
	}
}

void Game::moveDown()
{
	for (int i = w - 1; i >= 0; i--) {
		for (int j = h - 1; j >= 0; j--) {
			if (map[i][j].value != 0) {
				std::reference_wrapper<Cell> currentCell = std::ref(map[i][j]);
				for (int line = i + 1; line < h; line++) {
					if (!shiftCell(currentCell, line, j))
						break;
				}
			}
		}
	}
}

bool Game::shiftCell(std::reference_wrapper<Cell> &currentCell, const int &line, const int &col)
{
	if (map[line][col].value == 0) {
		int tmp = currentCell.get().value;
		currentCell.get().value = 0;
		map[line][col].value = tmp;
		currentCell = std::ref(map[line][col]);
		return true;
	} else if (map[line][col] == currentCell.get() && !map[line][col].merged && !currentCell.get().merged) {
		currentCell.get().value = 0;
		map[line][col].value *= 2;
		currentCell = std::ref(map[line][col]);
		currentCell.get().merged = true;
		return true;
	}
	return false;
}

int Game::getMax()
{
	int currentMax = 0;
	for (int i = 0; i < w; i++) {
		for (int j = 0; j < h; j++) {
			currentMax = map[i][j].value > currentMax ? map[i][j].value : currentMax;
		}
	}
	return currentMax;
}
