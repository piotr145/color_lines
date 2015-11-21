#pragma once
#include <SFML/Graphics.hpp>

class Config {
private:
    const sf::Color color_tab[7] = {sf::Color::Black, sf::Color::Red, sf::Color::Blue, sf::Color::Magenta, sf::Color::Yellow, sf::Color::Green, sf::Color::Cyan};
    int window_x=600, window_y=600; //size of window
    std::string window_name="snake";

public:
    sf::Color get_color(int x);
    sf::VideoMode get_video_mode();
    std::string get_window_name();
};

