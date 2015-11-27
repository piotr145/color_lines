#pragma once
#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>

class Board {
private:
    int tab[9][9];
    int to_remove[9][9];
    int free_ctr;
    int colors;
    int points = 0;

    std::vector<std::vector<sf::Vector2u>> get_lines();
    int count_marked();
    void remove_marked();
    void place_new(int i);
    bool check_for_move(sf::Vector2u start, sf::Vector2u stop);
    void mark_to_rem();

public:
    Board(int colors);
    Board() {}
    bool make_move(sf::Vector2u start, sf::Vector2u stop);
    bool is_playing();
    int get_points();
    bool is_empty(sf::Vector2u a);
    int get_element(int x, int y) const;
};
