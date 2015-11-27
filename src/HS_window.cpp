#include "HS_window.h"

extern sf::Font font;
extern std::mutex display_mutex;


void HS_window_create(std::vector<HS_Record> tab) {
    HS_window window(tab);
    window.window_loop();
}

HS_window::HS_window(std::vector<HS_Record> tab) {
    this->tab = tab;
    window.reset(new sf::RenderWindow(
            sf::VideoMode(350, std::max(400, 100 + static_cast<int>(tab.size()*50))),
            "snake"));
}

void HS_window::window_loop() {
    while(window->isOpen()) {
        sf::Event event;
        while(window->pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window->close();
        }
        draw();
    }
}

void HS_window::draw() {
    window->clear(sf::Color::White);
    sf::Text text("high scores:", font, 30);
    text.setColor(sf::Color::Black);
    text.setPosition(sf::Vector2f(60, 10));
    window->draw(text);

    unsigned posy = 100; // initial record Y position

    for(HS_Record i: tab) {
        sf::Text name(i.name, font, 30);
        name.setColor(sf::Color::Black);
        name.setPosition(sf::Vector2f(10, posy));
        window->draw(name);

        sf::Text points(std::to_string(i.score), font, 30);
        points.setColor(sf::Color::Black);
        points.setPosition(sf::Vector2f(250, posy));
        window->draw(points);

        posy += 50;
    }

    std::lock_guard<std::mutex> lock(display_mutex);
    window->display();
}
