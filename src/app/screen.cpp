#include "screen.hpp"
#include <utility>
#include <random>

/**
* Permet d'obtenir la position (x,y) d'une cas à partir de son id
*/
std::pair<int,int> Case::get_position_from_id(int const id) {
    std::pair<int,int> position {};
    position.first = (id % WIDTH_OF_MAP) * SIZE_OF_CASE;
    position.second = (id % WIDTH_OF_MAP) * SIZE_OF_CASE;
    return position;
}

/**
* Permet d'obtenir l'id d'une cas à partir de sa position (x,y)
*/
int Case::get_id_from_position(int const pos_x, int const pos_y) {
    return (pos_y * WIDTH_OF_MAP + pos_x) / SIZE_OF_CASE;
}

std::vector<Case> create_case_list(float map_pos_x, float map_pos_y) {
    std::vector<Case> case_list {};
    unsigned int case_id = 0;
    for (float i = map_pos_x; i < map_pos_x + SIZE_OF_MAP; i += SIZE_OF_CASE) {
        for (float j = map_pos_y; j < map_pos_y + SIZE_OF_MAP; j += SIZE_OF_CASE ) { 
            case_list.push_back({case_id, i, j, CASE_TYPE::END, true});
            case_id++;
        }
    }
    return case_list;
}