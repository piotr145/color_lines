#include <bits/stdc++.h>
#include "game.h"
#include "config.h"

std::unique_ptr<Config> config;

int main() {
    config.reset(new Config);
    srand(time(0));
    Game game;
    game.loop();
    exit(0);
}
