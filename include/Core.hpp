#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <memory>
#include "Game.hpp"
#include "UICell.hpp"

#define WIDTH_2048 4
#define HEIGHT_2048 4

class Core
{
private:
    sf::RenderWindow win;
    sf::View view;
    std::unique_ptr<Game> g2048;
    std::vector<std::shared_ptr<UICell>> cells;

public:
    Core(int, int, const std::string &);
    ~Core();

    void manageEvents();
    void loop();
    void drawItems();
    void updateUI();
};
