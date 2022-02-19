#include <SFML/Graphics.hpp>

class UICell
{
private:
    sf::RectangleShape cell;
    sf::Text text;
    sf::Font font;

public:
    UICell(const sf::Vector2f &);
    UICell(const sf::Vector2f &, const sf::Vector2f &);
    ~UICell();

    const sf::RectangleShape &getCell();
    void setText(const std::string &);
    void draw(sf::RenderWindow &);
};
