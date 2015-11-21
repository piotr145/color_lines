#include "game.h"
#include "board.h"
#include "config.h"

#define NULLVECTOR sf::Vector2u(10, 10)

extern Config* config;

int get_pos(int size, float point) {
    int res = 0;
    while(point > (size/9.0)*(res+1))
        res++;
    return res;
}

void draw_board(sf::RenderWindow &window, const Board &board) {
    window.clear(sf::Color::Black);
    for(int x = 0; x < 9; ++x)
        for(int y = 0; y < 9; ++y) {
            sf::CircleShape block(0.45*(window.getSize().x/9.0));
            block.setFillColor(config->get_color(board.get_element(x, y)));
            block.setPosition(
                    (window.getSize().x/9.0)*x,
                    (window.getSize().y/9.0)*y);
            window.draw(block);
        }
    window.display();
}

void game_loop() {
    sf::RenderWindow window(config->get_video_mode(),
            "snake",
            sf::Style::Default,
            sf::ContextSettings(0,0,2)
            );
    Board board(5);

    sf::Vector2u pos = NULLVECTOR;

    while(window.isOpen()) {
        sf::Event event;
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed)
                window.close();
            if(event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2u clicked_field = sf::Vector2u(
                        get_pos(window.getSize().x, event.mouseButton.x), 
                        get_pos(window.getSize().y, event.mouseButton.y));

                if(pos == NULLVECTOR)
                    pos = clicked_field;
                else if(pos == clicked_field)
                    pos = NULLVECTOR;
                else if(!board.is_empty(clicked_field))
                    pos = clicked_field;
                else {
                    board.make_move(pos, clicked_field);
                    pos = NULLVECTOR;
                }
            }
        }

        draw_board(window, board);
    }
}

