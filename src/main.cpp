#include <iostream>
#include "Core.hpp"

int main(void) {
    Core core(800, 600, "Hello World");
    core.loop();
    return 0;
}