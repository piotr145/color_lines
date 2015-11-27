#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>
#include "board.h"

Board::Board(int colors) {
    this->colors = colors;
    memset(tab, 0, sizeof(int)*9*9);
    memset(to_remove, 0, sizeof(int)*9*9);
    free_ctr = 9*9;
    place_new(3);
}

bool Board::is_playing() {
    return free_ctr > 0;
}

void Board::place_new(int i) {
    if(!free_ctr || !i)
        return;
    int place = (rand() % free_ctr);
    for(int x = 0; x < 9; ++x)
        for(int y = 0; y < 9; ++y) {
            if(tab[x][y] != 0)
                continue;
            if(!place) {
                tab[x][y] = (rand() % colors) + 1;
                free_ctr--;
                place_new(i-1);
                return;
            }
            place--;
        }
}

void Board::remove_marked() {
    free_ctr += count_marked();
    for(int x = 0; x < 9; ++x)
        for(int y = 0; y < 9; ++y)
            if(to_remove[x][y])
                tab[x][y] = 0;
    memset(to_remove, 0, sizeof(int)*9*9);
}

int Board::count_marked() {
    int res = 0;
    for(int x = 0; x < 9; ++x)
        for(int y = 0; y < 9; ++y)
            if(to_remove[x][y])
                res++;
    return res;
}

bool Board::check_for_move(sf::Vector2u start, sf::Vector2u stop) {
    // non-zero mean either non-empty or visited
    int visit[9][9];
    memcpy(visit, tab, sizeof(int)*9*9); 
    std::queue<sf::Vector2u> bfs_queue;
    bfs_queue.push(start);
    //run BFS on board to check if is path from start to stop
    while(!bfs_queue.empty()) {
        sf::Vector2u top = bfs_queue.front();
        bfs_queue.pop();
        if(top == stop)
            return true;
        
        if(top.x > 0 && !visit[top.x - 1][top.y]) {
            visit[top.x - 1][top.y] = 1;
            bfs_queue.emplace(top.x - 1, top.y);
        }
        if(top.x < 8 && !visit[top.x + 1][top.y]) {
            visit[top.x + 1][top.y] = 1;
            bfs_queue.emplace(top.x + 1, top.y);
        }
        if(top.y > 0 && !visit[top.x][top.y - 1]) {
            visit[top.x][top.y - 1] = 1;
            bfs_queue.emplace(top.x, top.y - 1);
        }
        if(top.y < 8 && !visit[top.x][top.y + 1]) {
            visit[top.x][top.y + 1] = 1;
            bfs_queue.emplace(top.x, top.y + 1);
        }
    }
    return false;
}

bool Board::make_move(sf::Vector2u start, sf::Vector2u stop) {
    //check if there is no ball on start field
    if(tab[start.x][start.y] == 0)
        return false;
    //check if move is possible
    if(!check_for_move(start, stop))
        return false;
    //move ball
    tab[stop.x][stop.y] = tab[start.x][start.y];
    tab[start.x][start.y] = 0;

    mark_to_rem();
    if(count_marked() > 0) {
        points += count_marked();
        remove_marked();
        return true;
    }
    remove_marked();
    place_new(3);
    mark_to_rem();
    points += 4*count_marked();
    remove_marked();

    return true;
}

std::vector<sf::Vector2u> skew_line_up(int x, int y) {
    std::vector<sf::Vector2u> res;
    while(x < 9 && y >= 0)
        res.emplace_back(x++, y--);
    return move(res);
}

std::vector<sf::Vector2u> skew_line_down(int x, int y) {
    std::vector<sf::Vector2u> res;
    while(x < 9 && y < 9)
        res.emplace_back(x++, y++);
    return move(res);
}

std::vector<std::vector<sf::Vector2u>> Board::get_lines() {
    std::vector<std::vector<sf::Vector2u>> res;
    for(int x = 0; x < 9; ++x) {
        std::vector<sf::Vector2u> k;
        for(int y = 0; y < 9; ++y)
            k.emplace_back(x, y);
        res.push_back(move(k));
    }

    for(int y = 0; y < 9; ++y) {
        std::vector<sf::Vector2u> k;
        for(int x = 0; x < 9; ++x)
            k.emplace_back(x, y);
        res.push_back(move(k));
    }

    for(int i = 0; i < 9; ++i)
        res.push_back(skew_line_up(0, i));

    for(int i = 1; i < 9; ++i)
        res.push_back(skew_line_up(i, 8));

    for(int i = 0; i < 9; ++i)
        res.push_back(skew_line_down(i, 0));

    for(int i = 1; i < 9; ++i)
        res.push_back(skew_line_down(0, i));
    return move(res);
}

void Board::mark_to_rem() {
    static std::vector<std::vector<sf::Vector2u>> lines;
    if(lines.size() == 0)
        lines = get_lines();
    
    for(auto line: lines) {
        // to short for 5 of same color
        if(line.size() < 5)
            continue;

        int mid = line.size()/2;

        //if there is no ball on middle field
        if(tab[line[mid].x][line[mid].y] == 0)
            continue;

        int ctr = 1;
        int left = mid;
        while(left > 0) {
            if(tab[line[left-1].x][line[left-1].y] 
                    != tab[line[mid].x][line[mid].y])
                break;
            ctr++;
            left--;
        }

        int right = mid;
        while(right < line.size() - 1) {
            if(tab[line[right+1].x][line[right+1].y] 
                    != tab[line[mid].x][line[mid].y])
                break;
            ctr++;
            right++;
        }
        if(ctr < 5)
            continue;
        for(int i = left; i <= right; ++i)
            to_remove[line[i].x][line[i].y] = 1;
    }

}

int Board::get_points() {
    return points;
}

bool Board::is_empty(sf::Vector2u a) {
    return tab[a.x][a.y] == 0;
}

int Board::get_element(int x, int y) const {
    return tab[x][y];
}
