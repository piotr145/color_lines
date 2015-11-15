#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "board.h"
#define NULLVECTOR sf::Vector2u(10,10)

int get_pos(int size, float point)
{
    int res = 0;
    while(point > (size/9.0)*(res+1))
        res++;
    return res;
}

void game_loop()
{
    sf::RenderWindow window(sf::VideoMode(600, 600),
            "snake",
            sf::Style::Default,
            sf::ContextSettings(0,0,2)
            );
    SFMLBoard game(5);

    sf::Vector2u pos = NULLVECTOR;

    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();
            if(event.type == sf::Event::MouseButtonPressed)
            {
                sf::Vector2u clicked_field = sf::Vector2u(
                        get_pos(window.getSize().x, event.mouseButton.x), 
                        get_pos(window.getSize().y, event.mouseButton.y));

                if(pos == NULLVECTOR)
                    pos = clicked_field;
                else if(pos == clicked_field)
                    pos = NULLVECTOR;
                else if(!game.is_empty(clicked_field))
                    pos = clicked_field;
                else
                {
                    game.make_move(pos, clicked_field);
                    pos = NULLVECTOR;
                }
            }
        }

        game.sfml_draw(window);
    }
}

int main()
{
    srand(time(0));
    game_loop();
    exit(0);
}

