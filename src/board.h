#pragma once
#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>

class Board
{
protected:
    int tab[9][9];
    int to_remove[9][9];
    int free_ctr;
    int colors;
    int points = 0;
    const sf::Color color_tab[7] = {sf::Color::Black, sf::Color::Red, sf::Color::Blue, sf::Color::Magenta, sf::Color::Yellow, sf::Color::Green, sf::Color::Cyan};
public:
    Board(int colors);
    bool make_move(sf::Vector2u start, sf::Vector2u stop);
    bool check_for_move(sf::Vector2u start, sf::Vector2u stop);
    void mark_to_rem();
    std::vector<std::vector<sf::Vector2u>> get_lines();
    int count_marked();
    void remove_marked();
    void place_new(int i);
    bool is_playing();
    int get_points();
    void draw();
    bool is_empty(sf::Vector2u a);
};

class SFMLBoard : public Board
{
public:
    SFMLBoard(int x) : Board(x) {}
    void sfml_draw(sf::RenderWindow &window);
};

