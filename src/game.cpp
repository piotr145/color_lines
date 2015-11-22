#include <boost/lexical_cast.hpp>
#include "game.h"
#include "config.h"

#define NULLVECTOR sf::Vector2u(10, 10)

extern std::unique_ptr<Config> config;

int Game::get_pos(int size, float point) {
    int res = 0;
    while (point > (size / 9.0) * (res + 1))
        res++;
    return res;
}

void Game::draw_balls() {
    for (int x = 0; x < 9; ++x)
        for (int y = 0; y < 9; ++y) {
            sf::CircleShape block(0.45 * (config->get_draw_x() / 9.0));
            block.setFillColor(config->get_color(board.get_element(x, y)));
            block.setPosition(
                    (config->get_draw_x() / 9.0) * x,
                    (config->get_draw_y() / 9.0) * y);
            window->draw(block);
        }
}

void Game::draw_grid() {
    for (int x = 1; x <= 9; ++x) {
        sf::RectangleShape line(sf::Vector2f(
                config->get_draw_x() / 180.0,
                config->get_draw_y() - config->get_draw_x() / 100.0));
        line.setPosition(
                sf::Vector2f(config->get_draw_x() / 9.0 * x - config->get_draw_x() / 100.0, 0));
        line.setFillColor(sf::Color::White);
        window->draw(line);
    }
    for (int y = 1; y <= 9; ++y) {
        sf::RectangleShape line(sf::Vector2f(
                config->get_draw_x() - config->get_draw_y() / 100.0,
                config->get_draw_y() / 180.0));
        line.setPosition(
                sf::Vector2f(0, config->get_draw_y() / 9.0 * y - config->get_draw_y() / 100.0));
        line.setFillColor(sf::Color::White);
        window->draw(line);
    }
}

Game::Game() {
    window.reset(new sf::RenderWindow(config->get_video_mode(),
            config->get_window_name(),
            sf::Style::Default,
            sf::ContextSettings(0, 0, 2)));
    board = Board(config->get_colors_number());
    font.loadFromFile("/usr/share/fonts/TTF/arial.ttf");
}

void Game::loop() {
    sf::Vector2u pos = NULLVECTOR;

    while (window->isOpen()) {
        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window->close();
            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2u clicked_field = sf::Vector2u(
                        get_pos(config->get_draw_x(), event.mouseButton.x),
                        get_pos(config->get_draw_y(), event.mouseButton.y));

                if (pos == NULLVECTOR)
                    pos = clicked_field;
                else if (pos == clicked_field)
                    pos = NULLVECTOR;
                else if (!board.is_empty(clicked_field))
                    pos = clicked_field;
                else {
                    board.make_move(pos, clicked_field);
                    pos = NULLVECTOR;
                }
            }
        }

        window->clear(sf::Color::Black);
        draw_balls();
        if(config->get_grid_mode())
            draw_grid();
        draw_points();
        window->display();
    }
}

void Game::draw_points() {
    sf::Text res_string("result:", font, 30);
    res_string.setColor(sf::Color::White);
    res_string.setPosition(sf::Vector2f(620, 40));
    window->draw(res_string);

    sf::Text points(boost::lexical_cast<std::string>
                            (board.get_points()*5) + " pkt", font, 30);
    points.setColor(sf::Color::White);
    points.setPosition(sf::Vector2f(620, 80));
    window->draw(points);
}
