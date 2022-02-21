#include <iostream>

#ifndef CELL_H

struct Cell {
    int value = 0;
    bool merged = false;
};

std::ostream &operator<<(std::ostream &os, Cell const &c);
bool operator==(const Cell &c, const Cell &other);
bool operator==(const Cell &c, const int &other);

#endif // !CELL_H