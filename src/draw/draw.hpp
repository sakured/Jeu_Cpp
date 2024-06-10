#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <img/img.hpp>

#include <sstream>

#include "simpletext.h"
#include "utils.hpp"
#include "draw/GLHelpers.hpp"

#include "app/screen.hpp"
#include "app/App.hpp"

#include <utility>

#pragma once

void draw_tower(Case my_case);

void draw_case(Case my_case);

void draw_map(std::vector<Case> case_list);

void update_case_texture (int x_pos, int y_pos);

// void draw_level_informations (int level, /*SimpleText Renderer,*/ float width, float height, int money);