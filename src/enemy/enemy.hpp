#include <iostream>
#include <vector>
#pragma once

enum class ENEMY_TYPE {
    ARCHER,
    KNIGHT,
    BOMBER
};

static const int NUMBER_OF_ENEMY_TYPE = 3;

static const ENEMY_TYPE ALL_ENEMY_TYPES[NUMBER_OF_ENEMY_TYPE] = {ENEMY_TYPE::ARCHER, ENEMY_TYPE::KNIGHT, ENEMY_TYPE::BOMBER};

static const std::string ALL_ENEMY_SPRITES[NUMBER_OF_ENEMY_TYPE] = {"images/Enemies/body_tracks.gif", "images/Enemies/body_halftrack.gif", "images/Enemies/body_tracks.gif"};

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
    float range {};
    unsigned int pace {};
    float speed {};
    std::string speed_label {};
    int pv {};

    bool attacking {false};
    DIRECTION facing {DIRECTION::DOWN};
    int current_node {0};
    float crossed_distance {0};

    void kill();

    void update_position();
    void update_direction(std::vector<std::pair<float, float>>);
};

enemy create_enemy(float pos_x, float pos_y, ENEMY_TYPE type);

std::string get_sprite_from_type(ENEMY_TYPE type);

std::string enemy_type_to_string(ENEMY_TYPE type);


DIRECTION calculate_direction(std::pair<float, float> current_node, std::pair<float, float> next_node);


size_t quick_sort_partition(std::vector<enemy> & vec, size_t const left, size_t const right);

void quick_sort(std::vector<enemy> & vec, size_t const left, size_t const right);

void quick_sort(std::vector<enemy> & vec);

void create_salve_enemy(std::vector<enemy> & enemy_liste, std::pair<float,float> & in_pos , int number_of_enemy);