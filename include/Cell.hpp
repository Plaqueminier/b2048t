#include <iostream>

struct Cell {
    int value = 0;
    bool merged = false;
};

std::ostream &operator<<(std::ostream &os, Cell const &c)
{ 
    return os << "[" << c.value << "]";
}

bool operator==(const Cell &c, const Cell &other)
{ 
    return c.value == other.value;
}