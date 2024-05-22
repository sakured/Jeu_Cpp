#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <img/img.hpp>

#include <sstream>

#include "simpletext.h"
#include "utils.hpp"
#include "draw/GLHelpers.hpp"

#include "app/screen.hpp"

#include <utility>

#pragma once

void draw_tour(Case my_case, GLuint sprite);

void draw_case(Case my_case);
void draw_map(std::vector<Case> case_list);