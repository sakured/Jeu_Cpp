#include <iostream>
#pragma once

enum class TOWER_TYPE {
    BOW,
    CROSSBOW
};

struct tower {
    TOWER_TYPE type;

    int pos_x;
    int pos_y;

    std::string sprite;

    unsigned int cost;
    unsigned int damage;
    unsigned int range;
    unsigned int pace;

};

// Crée une nouvelle tour selon une position et un type
tower create_tower(int pos_x, int pos_y, TOWER_TYPE type);