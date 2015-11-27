#include "get_name.h"

extern std::mutex high_scores_mutex;
extern std::mutex display_mutex;
extern sf::Font font;

Get_name_window::Get_name_window(unsigned score) {
    this->score = score;
    window.reset(new sf::RenderWindow(
            sf::VideoMode(350, 200),
            "snake"));
}

void Get_name_window::window_loop() {
    while(window->isOpen()) {
        sf::Event event;
        while(window->pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window->close();
            if(event.type == sf::Event::TextEntered) {
                // accept only printable characters
                if(event.text.unicode >= 32 && event.text.unicode < 127) {
                    name += static_cast<char>(event.text.unicode);
                }
            }
            if(event.type == sf::Event::KeyReleased) {
                name_to_long = false; // pressing any kay should reset this value
                if(event.key.code == sf::Keyboard::BackSpace) {
                    if(name.size() > 0)
                        name.pop_back();
                }
                if(event.key.code == sf::Keyboard::Return) {
                    if(name.size() < 10) {
                        std::lock_guard<std::mutex> lock(high_scores_mutex);
                        High_scores::update({name, score});
                        window->close();
                    }
                    else {
                        name_to_long = true;
                        name.clear();
                    }
                }
            }
        }
        draw();
    }
}

void Get_name_window::draw() {
    window->clear(sf::Color::White);
    if(name_to_long) {
        sf::Text name_text("name is too long", font, 40);
        name_text.setColor(sf::Color::Black);
        name_text.setPosition(sf::Vector2f(20, 50));
        window->draw(name_text);
    }
    else {
        sf::Text enter_text("enter your name:", font, 35);
        enter_text.setColor(sf::Color::Black);
        enter_text.setPosition(sf::Vector2f(20, 20));
        window->draw(enter_text);

        sf::Text name_text(name, font, 35);
        name_text.setColor(sf::Color::Black);
        name_text.setPosition(sf::Vector2f(20, 100));
        window->draw(name_text);
    }

    std::lock_guard<std::mutex> lock(display_mutex);
    window->display();
}

void create_name_window(int score) {
    Get_name_window window(score);
    window.window_loop();
}
