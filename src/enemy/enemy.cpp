#include "enemy.hpp"

/**
 * Tue l'ennemi
 */
void enemy::kill() {
    delete this;
}

/**
 * Met à jour la direction de l'ennemi
 */
void enemy::update_position() {
    switch (this->facing) {
    case DIRECTION::DOWN :
        this->pos_y += 0.05f;
        break;
    case DIRECTION::UP :
        this->pos_y -= 0.05f;
        break;
    case DIRECTION::LEFT :
        this->pos_x -= 0.05f;
        break;
    case DIRECTION::RIGHT :
        this->pos_x += 0.05f;
        break;
    default:
        break;
    }
}

/**
 * Met à jour la direction de l'ennemi pour le chemin
 */
void enemy::update_direction(std::vector<std::pair<float, float>> path) {
    if (this->facing == DIRECTION::LEFT || this->facing == DIRECTION::UP) {
        if (path[this->current_node].first <= path[this->current_node+1].first || path[this->current_node].second <= path[this->current_node+1].second) {
            this->facing = calculate_direction(path[this->current_node], path[this->current_node+1]);
            this->current_node++;
            this->attacking = (this->current_node == path.size()-1);
        }
    } else if (this->facing == DIRECTION::RIGHT || this->facing == DIRECTION::DOWN) {
        if (path[this->current_node].first >= path[this->current_node+1].first || path[this->current_node].second >= path[this->current_node+1].second) {
            this->facing = calculate_direction(path[this->current_node], path[this->current_node+1]);
            this->current_node++;
            this->attacking = (this->current_node == path.size()-1);
        }
    }
}

/**
 * Crée un ennemi d'un type donné
 */
enemy create_enemy(float pos_x, float pos_y, ENEMY_TYPE type) {
    enemy enemy {};

    switch (type) {
        case ENEMY_TYPE::ARCHER:
            enemy = {type, pos_x, pos_y, 10, 2, 4, 5, 0.01, "average", 50};
            break;
        
        case ENEMY_TYPE::KNIGHT:
            enemy = {type, pos_x, pos_y, 12, 4, 1, 3, 0.005, "slow", 100};
            break;

        case ENEMY_TYPE::BOMBER:
            enemy = {type, pos_x, pos_y, 8, 10, 1, 3, 0.02, "fast", 20};
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
 * Récupère le nom du type de l'ennemi
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

/**
 * Calcule la direction à prendre par l'ennemi
 */
DIRECTION calculate_direction(std::pair<float, float> current_node_coord, std::pair<float, float> next_node_coord) {
    if ((current_node_coord.first - next_node_coord.first) < 0) return DIRECTION::RIGHT;
    else if ((current_node_coord.first - next_node_coord.first) > 0) return DIRECTION::LEFT;
    else if ((current_node_coord.second - next_node_coord.second) > 0) return DIRECTION::UP;
    else return DIRECTION::DOWN;
}