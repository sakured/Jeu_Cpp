#include "App.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <img/img.hpp>

#include <iostream>
#include <sstream>

#include "simpletext.h"
#include "utils.hpp"
#include "draw/GLHelpers.hpp"

#include <draw/draw.hpp>

#include "screen.hpp"
#include "../graph/graph.hpp"
#include "../tower/tower.hpp"
#include "../enemy/enemy.hpp"

App::App() : _previousTime(0.0), _viewSize(2.0)
{
    // Télécharge l'image de la map
    img::Image map {img::load(make_absolute_path("images/map.png", true), 3, true)};

    // Lecture du fichier ITD
    _graph = read_ITD(MAP_FILE_NAME, IN, OUT, PATH);

    // Création de la liste de case
    _tile_list = create_case_list(map.data(), map.data_size());

    // Tower sprites
    for (auto & tower_type : ALL_TOWER_TYPES) {
        img::Image tower {img::load(make_absolute_path(get_sprite_from_type(tower_type).c_str(), true), 4, true)};
        _tower_sprites.push_back(loadTexture(tower));
    }

    // Enemy sprites
    for (auto & enemy_type : ALL_ENEMY_TYPES) {
        img::Image enemy {img::load(make_absolute_path(get_sprite_from_type(enemy_type).c_str(), true), 4, true)};
        _enemy_sprites.push_back(loadTexture(enemy));
    }
}

void App::setup()
{
    // Set the clear color to a nice blue
    glClearColor(0.0f, 0.0f, 0.4f, 1.0f);

    // Setup the text renderer with blending enabled and white text color
    _TextRenderer.ResetFont();
    _TextRenderer.SetColor(SimpleText::TEXT_COLOR, SimpleText::Color::WHITE);
    _TextRenderer.SetColorf(SimpleText::BACKGROUND_COLOR, 0.f, 0.f, 0.f, 0.f);
    _TextRenderer.EnableBlending(true);
}

void App::update()
{

    const double currentTime{glfwGetTime()};
    const double elapsedTime{currentTime - _previousTime};
    _previousTime = currentTime;

    render();
}

void App::render()
{
    // Clear the color and depth buffers of the frame buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Dessin de la map et des infos
    draw_map(_tile_list);
    draw_level_informations(1, _TextRenderer, _width, _height, _money, _life, _tower_sprites, _enemy_sprites); 
    draw_start_button(_is_playing, _width, _height);
    
    // Mise à jour du texte
    _TextRenderer.Render();
}

void App::key_callback(int key, int scancode, int action, int mods)
{
    // Choix du type de la tour à créer
    if (key == GLFW_KEY_KP_1 && action == GLFW_PRESS) {
        _new_tower_type = TOWER_TYPE::BOW;
    }
    else if (key == GLFW_KEY_KP_2 && action == GLFW_PRESS) {
        _new_tower_type = TOWER_TYPE::CROSSBOW;
    }
}

void App::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    // Récupération des coordonnées du curseur lors du clic
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		double x, y;
        glfwGetCursorPos(window, &x, &y);

        // Met à jour le bouton start / pause
        draw_start_button(_is_playing, _width, _height);
        if (_is_playing) _is_playing = false;
        else _is_playing = true;

        // Récupération des coordonées de la case cliquée
        float vertical_margin = 0.2 * _height / 2;
        float map = _height - 2 * vertical_margin;
        x -= (_width / 2) - (map / 2);
        y -= vertical_margin;
        std::pair<int,int> case_coordinate { (int)(x/(map/WIDTH_OF_MAP)) , (int)(y/(map/WIDTH_OF_MAP)) };
        
        
        // Création d'une tour BOW à la case cliquée
        if (_new_tower_type != TOWER_TYPE::NONE 
        && !get_case_from_coordinates(case_coordinate.first, case_coordinate.second, _tile_list).is_occupied
        && x >= 0 && case_coordinate.first < WIDTH_OF_MAP && y >= 0 && case_coordinate.second < WIDTH_OF_MAP) {
            tower tower { create_tower(case_coordinate.first, case_coordinate.second, _new_tower_type) };
            _tile_list[get_id_from_position(case_coordinate.first, case_coordinate.second)].is_occupied = true;
            _tile_list[get_id_from_position(case_coordinate.first, case_coordinate.second)].type = CASE_TYPE::TOWER;
            _tile_list[get_id_from_position(case_coordinate.first, case_coordinate.second)].tower_sprite = loadTexture(img::load(make_absolute_path(get_sprite_from_type(_new_tower_type), true), 4, true));
            _money -= tower.cost;
            _new_tower_type = TOWER_TYPE::NONE;
        }
	}
}

void App::scroll_callback(double /*xoffset */, double /*yoffset */)
{
}

void App::cursor_position_callback(double /*xpos */, double /*ypos */)
{
}

void App::size_callback(int width, int height) {
    _width = width;
    _height = height;

    // make sure the viewport matches the new window dimensions
    glViewport(0, 0, _width, _height);

    const float aspectRatio {_width / (float)_height};

    // Change the projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (aspectRatio > 1.0f)
    {
        glOrtho(-_viewSize / 2.0f * aspectRatio, _viewSize / 2.0f * aspectRatio, -_viewSize / 2.0f, _viewSize / 2.0f, -1.0f, 1.0f);
    }
    else
    {
        glOrtho(-_viewSize / 2.0f, _viewSize / 2.0f, -_viewSize / 2.0f / aspectRatio, _viewSize / 2.0f / aspectRatio, -1.0f, 1.0f);
    }
}
