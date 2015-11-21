#pragma once
#include <SFML/Graphics.hpp>

class Config {
private:
    const sf::Color color_tab[7] = {sf::Color::Black, sf::Color::Red, sf::Color::Blue, sf::Color::Magenta, sf::Color::Yellow, sf::Color::Green, sf::Color::Cyan};
    int window_x, window_y; //size of window
    std::string window_name;

public:
    sf::Color get_color(int x);
    sf::VideoMode get_video_mode();
    std::string get_window_name();
};

