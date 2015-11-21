#include <bits/stdc++.h>
#include "game.h"
#include "config.h"

Config* config;

int main() {
    config = new Config;
    srand(time(0));
    Game game;
    game.loop();
    delete config;
    exit(0);
}

