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
    sf::Font font;

    void draw_balls();
    void draw_grid();
    void draw_points();
    void draw_game_over();
public:
    Game();
    void loop();

};
