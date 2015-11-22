#pragma once
#include <bits/stdc++.h>

class HS_Record {
public:
    std::string name;
    unsigned int score;
};

class High_scores {
private:
    std::vector<HS_Record> tab;
public:
    void load();
    bool is_high(unsigned int score);
    void update(HS_Record rec);
    void write();
    std::vector<HS_Record> get_scores();
};
