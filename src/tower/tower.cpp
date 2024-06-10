#include "tower.hpp"

/**
 * Crée une tour selon un type donné
*/
tower create_tower(int pos_x, int pos_y, TOWER_TYPE type) {
    tower tower {};

    switch (type) {
        case TOWER_TYPE::BOW:
            tower = {type, pos_x, pos_y, "", 50, 3, 12, 10};
            break;
            
        case TOWER_TYPE::CROSSBOW:
            tower = {type, pos_x, pos_y, "", 75, 5, 10, 5};
            break;

        default:
            break;
    }

    return tower;
}
