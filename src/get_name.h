#pragma once
#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>
#include "high_scores.h"

void create_name_window(int score);

class Get_name_window {
private:
    std::unique_ptr<sf::RenderWindow> window;
    int score;
    std::string name;
    bool name_to_long = false;
public:
    Get_name_window(int score);
    void window_loop();
    void draw();
};
