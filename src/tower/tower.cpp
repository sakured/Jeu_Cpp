#include "tower.hpp"

tower tower::create_tower(int pos_x, int pos_y, TOWER_TYPE type) {
    tower tower {};

    switch (type) {
        case TOWER_TYPE::BOW:
            tower = {type, pos_x, pos_y, "", 50, 4, 10, 10};
            break;
            
        case TOWER_TYPE::CROSSBOW:
            tower = {type, pos_x, pos_y, "", 75, 8, 12, 5};
            break;

        default:
            break;
    }

    return tower;
}
