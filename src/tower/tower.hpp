#include <iostream>
#pragma once

enum class TOWER_TYPE {
    BOW,
    CROSSBOW,
    NONE
};

static const TOWER_TYPE ALL_TOWER_TYPES[] = {TOWER_TYPE::BOW, TOWER_TYPE::CROSSBOW};

static const std::string ALL_TOWER_SPRITES[] = {"images/Towers/turret_01_mk1.gif", "images/Towers/turret_02_mk1.gif"};

struct tower {
    TOWER_TYPE type;

    int pos_x;
    int pos_y;

    unsigned int cost;
    unsigned int damage;
    unsigned int range;
    unsigned int pace;

};

// Crée une nouvelle tour selon une position et un type
tower create_tower(int pos_x, int pos_y, TOWER_TYPE type);

std::string get_sprite_from_type(TOWER_TYPE type);

std::string tower_type_to_string(TOWER_TYPE type);