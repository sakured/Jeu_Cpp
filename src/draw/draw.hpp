#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <img/img.hpp>

#include <sstream>
#include <utility>

#include "simpletext.h"
#include "utils.hpp"
#include "draw/GLHelpers.hpp"

#include "app/screen.hpp"
#include "app/App.hpp"

#pragma once

void draw_tower(const Case & my_case, const GLuint & tower_sprite);

void draw_case(const Case & my_case);

void draw_map(const std::vector<Case> & case_list);

void update_case_texture (int x_pos, int y_pos);

void draw_level_informations (int level, SimpleText & TextRenderer, float width, float height, int money, int life, std::vector<GLuint> & tower_sprites, std::vector<GLuint> & enemy_sprites);

void draw_start_button(bool is_playing, float width, float height);