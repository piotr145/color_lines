#include <bits/stdc++.h>
#include "game.h"
#include "config.h"
#include "high_scores.h"
#include <X11/Xlib.h>

std::unique_ptr<Config> config;
sf::Font font;
High_scores high_scores;
std::mutex high_scores_mutex;
//app will crash if two thread run sf::Window->display() simultaneously
std::mutex display_mutex;



void load_font() {
    font.loadFromFile("/usr/share/fonts/TTF/arial.ttf");
}

int main() {
    config.reset(new Config);
    load_font();
    XInitThreads(); // without this app will crash
    srand(time(0));
    Game game;
    game.loop();
    exit(0);
}
