#include "high_scores.h"
#include "config.h"

extern std::unique_ptr<Config> config;


void High_scores::load() {
    tab.clear(); // clear previous content of tab
    std::fstream file;
    file.open(config->get_high_scores_file(), std::fstream::in);
    if(!file.is_open())
        std::cerr << "WARNING: unable to open high score file" << std::endl;

    bool cont = false; // true if next value in file is score
    std::string name;
    unsigned score;
    while(!file.eof()) {
        if(tab.size() >= 10)
            break; // we only care about 10 best scores
        if(!cont) {
            file >> name;
        }
        else {
            file >> score;
            tab.push_back({name, score});
        }
        cont = !cont;
    }

    file.close();
}

bool High_scores::is_high(unsigned int score) {
    load();
    if(tab.size() == 0)
        return true;
    return tab[tab.size() - 1].score < score;
}

void High_scores::update(HS_Record rec) {
    std::vector<HS_Record> newtab;
    int i = 0;
    for(; i < tab.size() && tab[i].score >= rec.score; ++i) {
        newtab.push_back(tab[i]);
    }
    newtab.push_back(rec);
    for(; i < tab.size(); ++i) {
        newtab.push_back(tab[i]);
    }
    newtab.resize(10);
    tab = move(newtab);
    write();
}

std::vector<HS_Record> High_scores::get_scores() {
    load();
    return tab;
}

void High_scores::write() {
    std::fstream file;

    file.open(config->get_high_scores_file(), std::fstream::out);
    if(!file.is_open()) {
        std::cerr << "ERROR: unable to create high score file" << std::endl;
        return;
    }

    for(HS_Record i: tab) {
        file << i.name << " " << i.score << std::endl;
    }
    file.close();
}
