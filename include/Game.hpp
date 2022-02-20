#include <vector>
#include <iostream>
#include <chrono>
#include <functional>

struct Cell;

enum ArrowDirection {
    LEFT = 71,
    RIGHT = 72,
    UP = 73,
    DOWN = 74,
};

class Game
{
    private:
        int w;
        int h;
        std::vector<std::vector<Cell>> map;
        int minValue;

    public:
        Game(const int &w, const int &h);
        ~Game();

        void dump();
        int getCellValue(const int &);
        int countValue(const int &);
        bool addRandomMinValue();
        std::vector<std::vector<Cell>> &updateCells(const ArrowDirection &);
        void moveLeft();
        void moveRight();
        void moveUp();
        void moveDown();
        bool shiftCell(std::reference_wrapper<Cell> &, const int &, const int &);
        int getMax();
};
