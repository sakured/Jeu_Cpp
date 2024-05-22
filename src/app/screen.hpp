#include <utility>
#include <vector>

#ifndef CASE_VALUES

inline const int WIDTH_OF_MAP {16}; // à changer
inline const float SIZE_OF_MAP {1.6f}; // à changer
inline const float SIZE_OF_CASE {SIZE_OF_MAP / (float)WIDTH_OF_MAP};

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

    std::pair<int,int> get_position_from_id(int const id);
    int get_id_from_position(int const pos_x, int const pos_y);
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

std::vector<Case> create_case_list(float map_pos_x, float map_pos_y);