#pragma once
#include <SFML/Graphics.hpp>
#include "board.h"

class Game {
private:
    sf::RenderWindow *window;
    Board board;
    int get_pos(int size, float point);
public:
    Game();
    ~Game();
    void loop();
    void draw_balls();
    void draw_grid();

};