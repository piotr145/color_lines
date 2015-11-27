#include <boost/lexical_cast.hpp>
#include "game.h"
#include "config.h"
#include "HS_window.h"
#include "get_name.h"

#define NULLVECTOR sf::Vector2u(10, 10)

extern std::unique_ptr<Config> config;
extern sf::Font font;
extern std::mutex display_mutex;
extern High_scores high_scores;
extern std::mutex high_scores_mutex;

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
}

void Game::loop() {
    sf::Vector2u pos = NULLVECTOR;

    while (window->isOpen()) {
        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                exit(0);
            }
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
                else if(board.is_playing()){
                    board.make_move(pos, clicked_field);
                    pos = NULLVECTOR;
                    std::lock_guard<std::mutex> lock(high_scores_mutex);
                    if(!board.is_playing() && high_scores.is_high(board.get_points())) {
                        create_name_window_thread();
                    }
                }
            }
            if(event.type == sf::Event::KeyReleased) {
                if(event.key.code == sf::Keyboard::H) {
                    create_HS_window_thread();
                }
                if(event.key.code == sf::Keyboard::F2) {
                    std::lock_guard<std::mutex> lock(high_scores_mutex);
                    if(high_scores.is_high(board.get_points())) {
                        create_name_window_thread();
                    }
                    board = Board(config->get_colors_number());
                }
            }
        }

        window->clear(sf::Color::Black);
        draw_balls();
        if(config->get_grid_mode())
            draw_grid();
        draw_points();
        draw_game_over();

        std::lock_guard<std::mutex> lock(display_mutex);
        window->display();
    }
}

void Game::draw_points() {
    sf::Text res_string("result:", font, 30);
    res_string.setColor(sf::Color::White);
    res_string.setPosition(sf::Vector2f(620, 40));
    window->draw(res_string);

    sf::Text points(boost::lexical_cast<std::string>
                            (board.get_points()) + " pkt", font, 30);
    points.setColor(sf::Color::White);
    points.setPosition(sf::Vector2f(620, 80));
    window->draw(points);
}

void Game::draw_game_over() {
    //if game is over print "GAME OVER"
    if(board.is_playing())
        return;
    sf::Text text("GAME OVER", font, 100);
    text.setColor(sf::Color::White);
    text.setPosition(sf::Vector2f(100, 200));
    window->draw(text);
}

void Game::create_HS_window_thread() {
    std::lock_guard<std::mutex> lock(high_scores_mutex);
    help_windows.emplace_back(new sf::Thread(HS_window_create, high_scores.get_scores()));
    help_windows.back()->launch();
}

void Game::create_name_window_thread() {
    help_windows.emplace_back(new sf::Thread(create_name_window, board.get_points()));
    help_windows.back()->launch();
}
