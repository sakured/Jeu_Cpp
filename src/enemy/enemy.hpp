#include <iostream>
#pragma once

enum class ENEMY_TYPE {
    ARCHER,
    KNIGHT,
    BOMBER
};

static const ENEMY_TYPE ALL_ENEMY_TYPES[] = {ENEMY_TYPE::ARCHER, ENEMY_TYPE::KNIGHT, ENEMY_TYPE::BOMBER};

static const std::string ALL_ENEMY_SPRITES[] = {"images/Enemies/body_tracks.gif", "images/Enemies/body_halftrack.gif", "images/Enemies/body_tracks.gif"};

struct enemy {
    ENEMY_TYPE type;

    int pos_x;
    int pos_y;

    unsigned int gain;
    unsigned int damage;
    unsigned int range;
    unsigned int pace;
    unsigned int speed;
    int pv;
};

enemy create_enemy(int pos_x, int pos_y, ENEMY_TYPE type);

std::string get_sprite_from_type(ENEMY_TYPE type);

std::string enemy_type_to_string(ENEMY_TYPE type);