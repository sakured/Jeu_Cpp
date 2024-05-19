#include <iostream>
#pragma once

enum class ENEMY_TYPE {
    ARCHER,
    KNIGHT,
    BOMBER
};

struct enemy {
    ENEMY_TYPE type;

    int pos_x;
    int pos_y;

    std::string sprite;

    unsigned int gain;
    unsigned int damage;
    unsigned int range;
    unsigned int pace;
    unsigned int speed;
    int pv;
    
    // Crée un nouvel ennemi selon une position et un type
    enemy create_enemy(int pos_x, int pos_y, ENEMY_TYPE type);
};