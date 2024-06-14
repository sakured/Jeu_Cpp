#include <utility>
#include <vector>
#include <string>
#include <stdint.h>

#pragma once

#ifndef CASE_VALUES

inline const int WIDTH_OF_MAP {16}; 
inline float SIZE_OF_MAP {2.f}; 
inline const float SIZE_OF_CASE {SIZE_OF_MAP / (float)WIDTH_OF_MAP};

inline const float START_OF_MAP_X {0.0f};
inline const float START_OF_MAP_Y {0.0f};

inline std::string MAP_FILE_NAME {};
inline std::vector<int> IN {};
inline std::vector<int> OUT {};
inline std::vector<int> PATH {};

#endif

enum class CASE_TYPE {
    START,
    END,
    ROAD,
    BLANK,
};

struct Case {
    unsigned int case_id {};
    float pos_x {};
    float pos_y {};
    CASE_TYPE type {};
    bool is_occupied { false };
};

// Je pense que cette structure est inutile,
// seules les fonctions "action()", "is_pressed()" et "draw_button()"
// mais elles seront propres à chaque bouton
struct Button {
    unsigned int button_id {};
    int pos_x {};
    int pos_y {};

    void action();
    bool is_pressed();
};

std::pair<int,int> get_position_from_id(int const id);

int get_id_from_position(int const pos_x, int const pos_y);

std::pair<int, int> get_case_coordonates_from_gl_coordonates(float x, float y);

std::pair<float, float> get_gl_coordonates_from_case_coordonates(int pos_x, int pos_y);


Case get_case_from_coordinates(int const pos_x, int const pos_y, std::vector<Case> list);

std::vector<Case> create_case_list(uint8_t *map_reference, size_t size);

CASE_TYPE get_case_type_from_rgb(int r, int g, int b);