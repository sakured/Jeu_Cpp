#include "tower.hpp"

/**
 * Crée une tour selon un type donné
 */
tower create_tower(int pos_x, int pos_y, TOWER_TYPE type) {
    tower tower {};

    switch (type) {
        case TOWER_TYPE::BOW:
            tower = {type, pos_x, pos_y, 50, 3, 12, 10};
            break;
            
        case TOWER_TYPE::CROSSBOW:
            tower = {type, pos_x, pos_y, 75, 5, 10, 5};
            break;

        default:
            break;
    }

    return tower;
}


/**
 * Récupère le sprite de la tour
 */
std::string get_sprite_from_type(TOWER_TYPE type) {
    return ALL_TOWER_SPRITES[(int)type];
}

/**
 * Récupère le nom du type de la tour
 */
std::string tower_type_to_string(TOWER_TYPE type) {
    std::string string_type {};

    switch (type) {
        case TOWER_TYPE::BOW:
            string_type = "BOW";
            break;
            
        case TOWER_TYPE::CROSSBOW:
            string_type = "CROSSBOW";
            break;

        default:
            break;
    }

    return string_type;
}
