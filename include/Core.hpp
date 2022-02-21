#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <memory>
#include <chrono>
#include <thread>
#include "UICell.hpp"


#ifndef CORE_H

class Game;
class Bot;

#define SIZE_2048 4

class Core
{
private:
    sf::RenderWindow win;
    sf::View view;
    std::unique_ptr<Game> g2048;
    std::unique_ptr<Bot> bot;
    std::vector<std::shared_ptr<UICell>> cells;

public:
    Core(int, int, const std::string &);
    ~Core();

    void manageEvents();
    void loop();
    void drawItems();
    void updateUI();
};

#endif // !CORE_H