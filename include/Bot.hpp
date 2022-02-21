#include <vector>
#include <iostream>
#include <chrono>
#include <functional>
#include <thread>

#ifndef BOT_H

struct Cell;

class Bot
{
    private:
        int w;
        int h;
        std::vector<std::vector<Cell>> map;
        int lastMove;
        int timeLastMove;
        int timeUnchanged;

    public:
        Bot(const int &w, const int &h);
        ~Bot();

        void reset();
        int thinkAndPlay(const std::vector<std::vector<Cell>> &);
        void setMap(const std::vector<std::vector<Cell>> &);
        int updateValuesAndReturn(int, const std::vector<std::vector<Cell>> &);

        static bool isTopLineFull(const std::vector<std::vector<Cell>> &state, int size);
        static bool isRightColumnFull(const std::vector<std::vector<Cell>> &state, int size);
        static bool isMaxInCorner(const std::vector<std::vector<Cell>> &state, int size);
        static int getMax(const std::vector<std::vector<Cell>> &state, int size);

};

#endif // !BOT_H
