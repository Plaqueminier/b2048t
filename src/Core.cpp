#include "Core.hpp"

Core::Core(int w, int h, const std::string &name) :
    win(sf::VideoMode(w, h), name),
    g2048(std::make_unique<Game>(WIDTH_2048, HEIGHT_2048))
{
    g2048->dump();
    view.reset(sf::FloatRect(0, 0, 200 * WIDTH_2048, 200 * HEIGHT_2048));
    win.setView(view);
    
    for (int i = 0; i < WIDTH_2048; i++) {
        for (int j = 0; j < HEIGHT_2048; j++) {
            cells.push_back(std::make_shared<UICell>(
                sf::Vector2f(150, 150), 
                sf::Vector2f(
                    50 + 75 + 150 * j + j * (((200 * HEIGHT_2048 - 100) - 150 * HEIGHT_2048) / HEIGHT_2048),
                    50 + 75 + 150 * i + i * (((200 * WIDTH_2048 - 100) - 150 * WIDTH_2048) / WIDTH_2048)
                )
            ));
        }
    }
    updateUI();
}

Core::~Core()
{
}

void Core::manageEvents()
{
    sf::Event event;

    while (win.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            win.close();
        }

        if (event.type == sf::Event::KeyReleased) {
            if (event.key.code >= 71 && event.key.code <= 74) {
                try {
                    g2048->updateCells(static_cast<ArrowDirection>(event.key.code));
                } catch(int e) {
                    std::cout << "Your maximum was " << e << std::endl;
                    win.close();
                }
                updateUI();
            }
        }

        if (event.type == sf::Event::Resized) {
            view.setViewport(sf::FloatRect(
                (win.getSize().x > win.getSize().y) ? (1 - static_cast<float>(win.getSize().y) / static_cast<float>(win.getSize().x)) / 2 : 0,
                (win.getSize().x < win.getSize().y) ? (1 - static_cast<float>(win.getSize().x) / static_cast<float>(win.getSize().y)) / 2 : 0,
                (win.getSize().x > win.getSize().y) ? static_cast<float>(win.getSize().y) / static_cast<float>(win.getSize().x) : 1,
                (win.getSize().x < win.getSize().y) ? static_cast<float>(win.getSize().x) / static_cast<float>(win.getSize().y) : 1
            ));
            win.setView(view);
        }
    }
}

void Core::loop()
{
    while (win.isOpen()) {
        manageEvents();
        win.clear();
        drawItems();
        win.display();
    }
}

void Core::drawItems()
{
    for (auto &cell : cells) {
        cell->draw(win);
    }
}

void Core::updateUI()
{
    for (int i = 0; i < static_cast<int>(cells.size()); i++) {
        cells[i]->setText(std::to_string(g2048->getCellValue(i)));
    }
}
