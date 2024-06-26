#include "tower.hpp"

bool tower::in_range(std::pair<int, int> pos_enemy) {
    if ((pos_enemy.first <= this->pos_x + (int)this->range) && (pos_enemy.second <= this->pos_x + (int)this->range)) return true;
    else if ((pos_enemy.first <= this->pos_x - (int)this->range) && (pos_enemy.second <= this->pos_x + (int)this->range)) return true;
    else if ((pos_enemy.first <= this->pos_x + (int)this->range) && (pos_enemy.second <= this->pos_x - (int)this->range)) return true;
    else if ((pos_enemy.first <= this->pos_x - (int)this->range) && (pos_enemy.second <= this->pos_x - (int)this->range)) return true;
    else return false;
}

/**
 * Crée une tour selon un type donné
 */
tower create_tower(int pos_x, int pos_y, TOWER_TYPE type) {
    tower tower {};

    switch (type) {
        case TOWER_TYPE::BOW:
            tower = {type, pos_x, pos_y, 50, 4, 3, 8};
            break;
            
        case TOWER_TYPE::CROSSBOW:
            tower = {type, pos_x, pos_y, 100, 6, 5, 5};
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
            string_type = "STRAW HAT";
            break;
            
        case TOWER_TYPE::CROSSBOW:
            string_type = "WHITE BEARD";
            break;

        default:
            break;
    }

    return string_type;
}

/**
 * Récupère le coût du type de la tour
 */
int get_cost_from_type(TOWER_TYPE type) {
    int cost {};

    switch (type) {
        case TOWER_TYPE::BOW:
            cost = 50;
            break;
            
        case TOWER_TYPE::CROSSBOW:
            cost = 75;
            break;

        default:
            break;
    }

    return cost;
}
