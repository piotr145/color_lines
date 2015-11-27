#pragma once
#include <bits/stdc++.h>

class HS_Record {
public:
    std::string name;
    unsigned int score;
};

class High_scores {
public:
    static bool is_high(unsigned int score);
    static void update(HS_Record rec);
    static void write(const std::vector<HS_Record> &tab);
    static std::vector<HS_Record> get_scores();
};
