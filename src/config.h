#pragma once
#include <SFML/Graphics.hpp>

class Config {
private:
    const sf::Color color_tab[7] = {sf::Color::Black, sf::Color::Red, sf::Color::Blue, sf::Color::Magenta, sf::Color::Yellow, sf::Color::Green, sf::Color::Cyan};
    unsigned window_x=750, window_y=600; //size of window
    unsigned draw_x=600, draw_y=600; //size of draw area
    std::string window_name="snake";
    bool grid_mode = true;
    unsigned colors_number=5;
    std::string high_scores_file = "";

public:
    sf::Color get_color(int x);
    sf::VideoMode get_video_mode();
    std::string get_window_name();
    bool get_grid_mode();
    int get_draw_x();
    int get_draw_y();
    int get_colors_number();
    std::string get_high_scores_file();
    void set_colors_number(int colors);
};
