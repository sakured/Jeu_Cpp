#include <iostream>
#include <vector>
#pragma once

enum class ENEMY_TYPE {
    ARCHER,
    KNIGHT,
    BOMBER
};

static const ENEMY_TYPE ALL_ENEMY_TYPES[] = {ENEMY_TYPE::ARCHER, ENEMY_TYPE::KNIGHT, ENEMY_TYPE::BOMBER};

static const std::string ALL_ENEMY_SPRITES[] = {"images/Enemies/body_tracks.gif", "images/Enemies/body_halftrack.gif", "images/Enemies/body_tracks.gif"};


enum class DIRECTION {
    UP,
    DOWN,
    RIGHT,
    LEFT,
};


struct enemy {
    ENEMY_TYPE type {};

    float pos_x {};
    float pos_y {};

    unsigned int gain {};
    unsigned int damage {};
    unsigned int range {};
    unsigned int pace {};
    unsigned int speed {};
    int pv {};

    bool attacking {false};
    DIRECTION facing {DIRECTION::DOWN};
    int current_node {0};

    void kill();

    void update_position();
    void update_direction(std::vector<std::pair<float, float>>);
};

enemy create_enemy(float pos_x, float pos_y, ENEMY_TYPE type);

std::string get_sprite_from_type(ENEMY_TYPE type);

std::string enemy_type_to_string(ENEMY_TYPE type);


DIRECTION calculate_direction(std::pair<float, float> current_node, std::pair<float, float> next_node);