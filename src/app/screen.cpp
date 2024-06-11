#include "screen.hpp"
#include <utility>
#include <iostream>

/**
 * Permet d'obtenir la position (x,y) d'une cas à partir de son id
*/
std::pair<int,int> get_position_from_id(int const id) {
    std::pair<int,int> position {};
    position.first = id % WIDTH_OF_MAP;
    position.second = id - (id % WIDTH_OF_MAP) / WIDTH_OF_MAP;
    return position;
}

/**
 * Permet d'obtenir l'id d'une case à partir de sa position (x,y)
*/
int get_id_from_position(int const pos_x, int const pos_y) {
    return (pos_y * WIDTH_OF_MAP + pos_x);
}

/**
 * Permet d'obtenir une case à partir de sa position (x,y)
*/
Case get_case_from_coordinates(int const pos_x, int const pos_y, std::vector<Case> list) {
    return list[get_id_from_position(pos_x, pos_y)];
}

/**
 * @brief Get the case coordonates from gl coordonates object
 * 
 * @param x 
 * @param y 
 * @return std::pair<int, int> 
 */
std::pair<int, int> get_case_coordonates_from_gl_coordonates(float x, float y) {
    return std::make_pair((int)((x - START_OF_MAP_X)/SIZE_OF_CASE), (int)((y - START_OF_MAP_Y)/SIZE_OF_CASE));
}

/**
 * @brief Get the gl coordonates from case coordonates object
 * 
 * @param pos_x 
 * @param pos_y 
 * @return std::pair<float, float> 
 */
std::pair<float, float> get_gl_coordonates_from_case_coordonates(int pos_x, int pos_y) {
    return std::make_pair((float)(pos_x*SIZE_OF_CASE + START_OF_MAP_X), (float)(pos_y*SIZE_OF_CASE + START_OF_MAP_Y));
}


/**
 * Permet d'obtenir le type d'une case à partir de sa couleur (rgb)
*/
CASE_TYPE get_case_type_from_rgb(int r, int g, int b) {
    if (r == IN[0] && g == IN[1] && b == IN[2]) return CASE_TYPE::START;
    if (r == OUT[0] && g == OUT[1] && b == OUT[2]) return CASE_TYPE::END;
    if (r == PATH[0] && g == PATH[1] && b == PATH[2]) return CASE_TYPE::ROAD;
    if (r == 0 && g == 255 && b == 0) return CASE_TYPE::TOWER; 
    else return CASE_TYPE::BLANK;
}

/**
 * Crée une liste de cases à partir d'un tableau de pixel (celui de la map de référence)
*/ 
std::vector<Case> create_case_list(uint8_t *map_reference, size_t size) {
    std::vector<Case> case_list {};
    unsigned int case_id {0};
    size_t case_size {size/WIDTH_OF_MAP/WIDTH_OF_MAP};

    for (size_t i {0}; i < size; i += case_size) {
        float pos_x {START_OF_MAP_X + i/case_size%WIDTH_OF_MAP * SIZE_OF_CASE};
        float pos_y {START_OF_MAP_Y + (WIDTH_OF_MAP-1 - i/case_size/WIDTH_OF_MAP) * SIZE_OF_CASE};

        CASE_TYPE case_type = get_case_type_from_rgb(map_reference[i], map_reference[i+1], map_reference[i+2]);

        if (case_type == CASE_TYPE::BLANK) case_list.push_back({case_id, pos_x, pos_y, case_type, true});
        else case_list.push_back({case_id, pos_x, pos_y, case_type, false});

        case_id++;
    }
    
    return case_list;
}