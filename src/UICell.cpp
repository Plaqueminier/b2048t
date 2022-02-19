#include <iostream>
#include "UICell.hpp"

UICell::UICell(const sf::Vector2f &size)
{
    cell.setSize(sf::Vector2f(size.x - 2, size.y - 2));
    cell.setOrigin(sf::Vector2f(size.x / 2, size.y / 2));
    cell.setOutlineColor(sf::Color::Red);
    cell.setOutlineThickness(2);

    if (!font.loadFromFile("./img/Lato-Regular.ttf")) {
        std::cerr << "Error loading font" << std::endl;
    }
    text.setFont(font);
    text.setCharacterSize(size.x / 2);
    text.setString("");
    text.setFillColor(sf::Color::Black);
    text.setOrigin(sf::Vector2f(size.x / 4, size.y / 4));
}

UICell::UICell(const sf::Vector2f &size, const sf::Vector2f &position)
{
    cell.setSize(sf::Vector2f(size.x - 2, size.y - 2));
    cell.setOrigin(sf::Vector2f((size.x - 2) / 2, (size.y - 2) / 2));
    cell.setPosition(position);
    cell.setOutlineColor(sf::Color::Red);
    cell.setOutlineThickness(2);

    if (!font.loadFromFile("./img/Lato-Regular.ttf")) {
        std::cerr << "Error loading font" << std::endl;
    }
    text.setFont(font);
    text.setCharacterSize(size.x / 2);
    text.setString("");
    text.setFillColor(sf::Color::Black);
    text.setOrigin(sf::Vector2f(size.x / 4, size.y / 4));
    text.setPosition(sf::Vector2f(position.x, position.y));
}

UICell::~UICell()
{
}

const sf::RectangleShape &UICell::getCell()
{
    return cell;
}

void UICell::setText(const std::string &str)
{
    text.setString(str);
}

void UICell::draw(sf::RenderWindow &win)
{
    win.draw(cell);
    win.draw(text);
}