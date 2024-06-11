#include "enemy.hpp"

/**
 * Crée un ennemi d'un type donné
*/
enemy create_enemy(int pos_x, int pos_y, ENEMY_TYPE type) {
    enemy enemy {};

    switch (type) {
        case ENEMY_TYPE::ARCHER:
            enemy = {type, pos_x, pos_y, 10, 2, 4, 5, 10, 50};
            break;
        
        case ENEMY_TYPE::KNIGHT:
            enemy = {type, pos_x, pos_y, 12, 4, 1, 3, 8, 100};
            break;

        case ENEMY_TYPE::BOMBER:
            enemy = {type, pos_x, pos_y, 8, 10, 1, 3, 15, 20};
            break;

        default:
            break;
    }

    return enemy;
};

/**
 * Récupère le sprite de l'ennemi
 */
std::string get_sprite_from_type(ENEMY_TYPE type) {
    return ALL_ENEMY_SPRITES[(int)type];
}

/**
 * Récupère le nom du type de l'ennemi'
*/
std::string enemy_type_to_string(ENEMY_TYPE type) {
    std::string string_type {};

    switch (type) {
        case ENEMY_TYPE::ARCHER:
            string_type = "ARCHER";
            break;
            
        case ENEMY_TYPE::KNIGHT:
            string_type = "KNIGHT";
            break;

        case ENEMY_TYPE::BOMBER:
            string_type = "BOMBER";
            break;

        default:
            break;
    }

    return string_type;
}
