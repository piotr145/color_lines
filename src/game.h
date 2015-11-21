#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "board.h"

class Game {
private:
    sf::RenderWindow *window;
    Board board;
    int get_pos(int size, float point);
    sf::Font font;
public:
    Game();
    ~Game();
    void loop();
    void draw_balls();
    void draw_grid();
    void draw_points();
};