#include "screen.hpp"
#include <utility>

const int X_START_MAP {100}; // à changer
const int Y_START_MAP {300}; // à changer
const int WIDTH_OF_MAP {16}; // à changer
const int SIZE_OF_MAP {500}; // à changer
const int SIZE_OF_CASE { SIZE_OF_MAP / WIDTH_OF_MAP };

/**
  * Permet d'obtenir la position (x,y) d'une cas à partir de son id
  */
std::pair<int,int> Case::get_position_from_id(int const id) {
    std::pair<int,int> position {};
    position.first = (id % WIDTH_OF_MAP + X_START_MAP) * SIZE_OF_CASE;
    position.second = (id % WIDTH_OF_MAP + Y_START_MAP) * SIZE_OF_CASE;
    return position;
}

/**
  * Permet d'obtenir l'id d'une cas à partir de sa position (x,y)
  */
int Case::get_id_from_position(int const pos_x, int const pos_y) {
    return ((pos_y - Y_START_MAP) * WIDTH_OF_MAP + (pos_x - X_START_MAP)) / SIZE_OF_CASE;
}