#include "Cell.hpp"

std::ostream &operator<<(std::ostream &os, Cell const &c)
{ 
    return os << "[" << c.value << "]";
}

bool operator==(const Cell &c, const Cell &other)
{ 
    return c.value == other.value;
}

bool operator==(const Cell &c, const int &other)
{ 
    return c.value == other;
}
