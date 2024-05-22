#include "screen.hpp"
#include <utility>

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