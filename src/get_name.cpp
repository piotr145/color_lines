#include "get_name.h"

extern High_scores high_scores;
extern std::mutex high_scores_mutex;
extern std::mutex display_mutex;
extern sf::Font font;

Get_name_window::Get_name_window(int score) {
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
                if(event.text.unicode < 128) { //ASCII only
                    name += static_cast<char>(event.text.unicode);
                }
            }
            if(event.type == sf::Event::KeyReleased) {
                name_to_long = false; // pressing any kay should reset this value
                if(event.key.code == sf::Keyboard::BackSpace) {
                    name.pop_back();
                }
                if(event.key.code == sf::Keyboard::Return) {
                    if(name.size() < 10) {
                        high_scores_mutex.lock();
                        high_scores.update({name, score});
                        high_scores_mutex.unlock();
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

    }
    else {
        sf::Text name_text(name, font, 30);
        name_text.setColor(sf::Color::Black);
        name_text.setPosition(sf::Vector2f(20,20));
        window->draw(name_text);
    }

    std::lock_guard<std::mutex> lock(display_mutex);
    window->display();
}

void create_name_window(int score) {
    Get_name_window window(score);
    window.window_loop();
}
