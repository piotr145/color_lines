#pragma once
#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>
#include "high_scores.h"

void HS_window_create(std::vector<HS_Record> tab);

class HS_window {
private:
    std::unique_ptr<sf::RenderWindow> window;
    std::vector<HS_Record> tab;
public:
    HS_window(std::vector<HS_Record> tab);
    void window_loop();
    void draw();
};

