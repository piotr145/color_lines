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

int Config::get_draw_x() {
    return draw_x;
}

int Config::get_draw_y() {
    return draw_y;
}

int Config::get_colors_number() {
    return colors_number;
}

std::string Config::get_high_scores_file() {
    return high_scores_file;
}
