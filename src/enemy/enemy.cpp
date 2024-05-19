#include "enemy.hpp"

enemy enemy::create_enemy(int pos_x, int pos_y, ENEMY_TYPE type) {
    enemy enemy {};

    switch (type) {
        case ENEMY_TYPE::ARCHER:
            enemy = {type, pos_x, pos_y, "", 10, 2, 4, 5, 10, 50};
            break;
        
        case ENEMY_TYPE::KNIGHT:
            enemy = {type, pos_x, pos_y, "", 12, 4, 0, 3, 8, 100};
            break;

        case ENEMY_TYPE::BOMBER:
            enemy = {type, pos_x, pos_y, "", 8, 10, 0, 3, 15, 20};
            break;

        default:
            break;
    }

    return enemy;
};