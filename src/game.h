#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "board.h"


class Game {
private:
    std::unique_ptr<sf::RenderWindow> window;
    Board board;
    int get_pos(int size, float point);
    std::vector<std::unique_ptr<sf::Thread>> help_windows;

    void draw_balls();
    void draw_grid();
    void draw_points();
    void draw_game_over();
    void create_HS_window();
public:
    Game();
    void loop();

};
