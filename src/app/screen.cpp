#include "screen.hpp"
#include <utility>

#include <iostream>

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

CASE_TYPE get_case_type_from_rgb(int r, int g, int b) {
    if (r == 0 && g == 0 && b == 0) return CASE_TYPE::BLANK;
    if (r== 167 && g== 0 && b == 250) return CASE_TYPE::START;
    else return CASE_TYPE::BLANK;
}

// Créer une liste de case à partir d'un tableau de pixel (celui de la map de référence)
std::vector<Case> create_case_list(uint8_t *map_reference, size_t size) {
    std::vector<Case> case_list {};
    unsigned int case_id {0};
    size_t case_size {size/WIDTH_OF_MAP/WIDTH_OF_MAP};

    for (size_t i {0}; i < size; i += case_size) {
        float pos_x {START_OF_MAP_X + i/case_size%WIDTH_OF_MAP*SIZE_OF_CASE};
        float pos_y {START_OF_MAP_Y + i/case_size/WIDTH_OF_MAP*SIZE_OF_CASE};

        CASE_TYPE case_type = get_case_type_from_rgb(map_reference[i], map_reference[i+1], map_reference[i+2]);

        case_list.push_back({case_id, pos_x, pos_y, case_type, true});
        case_id++;
    }
    
    // for (float i = START_OF_MAP_X; i < START_OF_MAP_X + SIZE_OF_MAP; i += SIZE_OF_CASE) {
    //     for (float j = START_OF_MAP_Y; j < START_OF_MAP_Y + SIZE_OF_MAP; j += SIZE_OF_CASE ) { 
    //         case_list.push_back({case_id, i, j, CASE_TYPE::END, true});
    //         case_id++;
    //     }
    // }
    return case_list;
}