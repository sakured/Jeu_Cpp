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

/**
 * Permet d'obtenir le type d'une cas à partir de sa couleur (rgb)
*/
CASE_TYPE get_case_type_from_rgb(int r, int g, int b) {
    if (r == 0 && g == 0 && b == 255) return CASE_TYPE::START;
    if (r == 255 && g == 0 && b == 0) return CASE_TYPE::END;
    if (r == 0 && g == 255 && b == 0) return CASE_TYPE::TOWER;
    if (r == 255 && g == 255 && b == 255) return CASE_TYPE::ROAD;
    else return CASE_TYPE::BLANK;
}

// CASE_TYPE get_case_type_from_rgb(int r, int g, int b) {
//     if (r == IN[0] && g == IN[1] && b == IN[2]) return CASE_TYPE::START;
//     if (r == OUT[0] && g == OUT[1] && b == OUT[2]) return CASE_TYPE::END;
//     if (r == PATH[0] && g == PATH[1] && b == PATH[2]) return CASE_TYPE::ROAD;
//     if (r == 0 && g == 255 && b == 0) return CASE_TYPE::TOWER; // Pas sûr que ça soit utile (aucune tour au départ)
//     else return CASE_TYPE::BLANK;
// }

/**
 * Crée une liste de cases à partir d'un tableau de pixel (celui de la map de référence)
*/ 
std::vector<Case> create_case_list(uint8_t *map_reference, size_t size) {
    std::vector<Case> case_list {};
    unsigned int case_id {0};
    size_t case_size {size/WIDTH_OF_MAP/WIDTH_OF_MAP};

    for (size_t i {0}; i < size; i += case_size) {
        float pos_x {START_OF_MAP_X + i/case_size%WIDTH_OF_MAP*SIZE_OF_CASE};
        float pos_y {START_OF_MAP_Y + (WIDTH_OF_MAP-1 - i/case_size/WIDTH_OF_MAP)%WIDTH_OF_MAP*SIZE_OF_CASE};

        CASE_TYPE case_type = get_case_type_from_rgb(map_reference[i], map_reference[i+1], map_reference[i+2]);

        case_list.push_back({case_id, pos_x, pos_y, case_type, true});
        case_id++;
    }
    
    return case_list;
}