#pragma once
#include <SFML/Graphics.hpp>

class Config
{
    const sf::Color color_tab[7] = {sf::Color::Black, sf::Color::Red, sf::Color::Blue, sf::Color::Magenta, sf::Color::Yellow, sf::Color::Green, sf::Color::Cyan};
public:
    sf::Color get_color(int x);
};

