#include "config.h"

sf::Color Config::get_color(int x) {
    return color_tab[x];
}

sf::VideoMode Config::get_video_mode() {
    return sf::VideoMode(window_x, window_y);
}

std::string Config::get_window_name() {
    return window_name;
}

bool Config::get_grid_mode() {
    return grid_mode;
}
