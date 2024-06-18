#include "enemy.hpp"
#include <random>

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
    this->crossed_distance += this->speed;

    switch (this->facing) {
        case DIRECTION::DOWN :
            this->pos_y += this->speed;
            break;
        case DIRECTION::UP :
            this->pos_y -= this->speed;
            break;
        case DIRECTION::LEFT :
            this->pos_x -= this->speed;
            break;
        case DIRECTION::RIGHT :
            this->pos_x += this->speed;
            break;
        default:
            break;
    }
}

/**
 * Met à jour la direction de l'ennemi pour le chemin
 */
void enemy::update_direction(std::vector<std::pair<float, float>> path) {
    bool update {false};
    float range = this->current_node+1 != path.size()-1 ? 0 : this->range; // Si le prochain noeud est le dernier, il faut prendre la range en compte
    
    switch (this->facing) {
        case DIRECTION::LEFT :
            update = pos_x <= path[this->current_node+1].first + range;
            break;
        case DIRECTION::DOWN :
            update = pos_y >= path[this->current_node+1].second + range;
            break;
        case DIRECTION::RIGHT :
            update = pos_x >= path[this->current_node+1].first + range;
            break;
        case DIRECTION::UP :
            update = pos_y <= path[this->current_node+1].second + range;
            break;
        default:
            break;
    }
    if (update) {
        this->facing = calculate_direction(path[this->current_node], path[this->current_node+1]);
        this->current_node++;
        this->is_attacking = (this->current_node == path.size()-1);
    }
}

/**
 * Crée un ennemi d'un type donné
 */
enemy create_enemy(float pos_x, float pos_y, ENEMY_TYPE type) {
    enemy enemy {};

    switch (type) {
        case ENEMY_TYPE::ARCHER:
            enemy = {type, pos_x, pos_y, 10, 2, 0.5f, 10, 0.015625f, "average", 60};
            break;
        
        case ENEMY_TYPE::KNIGHT:
            enemy = {type, pos_x, pos_y, 12, 4, 0, 12, 0.0078125f, "slow", 80};
            break;

        case ENEMY_TYPE::BOMBER:
            enemy = {type, pos_x, pos_y, 8, 10, 0, 1, 0.03125f, "fast", 40};
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
            string_type = "MARINE GENERAL";
            break;
            
        case ENEMY_TYPE::KNIGHT:
            string_type = "MARINE ADMIRAL";
            break;

        case ENEMY_TYPE::BOMBER:
            string_type = "BOMB";
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

/**
 * Créé des salves d'ennemis
 */
void create_salve_enemy(std::vector<enemy> & enemy_list, std::pair<float,float> & in_pos, int number_of_enemy) {
    for (int i=0; i<number_of_enemy; i++) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis_y(-0.2, 0.2);
        double delay_y = dis_y(gen);
        std::uniform_real_distribution<> dis_x(-0.01, 0.01);
        double delay_x = dis_x(gen);
        for (ENEMY_TYPE enemy_type : ALL_ENEMY_TYPES) {
            enemy_list.push_back(create_enemy(in_pos.first + delay_x, in_pos.second + delay_y, enemy_type));
        }
    }
}