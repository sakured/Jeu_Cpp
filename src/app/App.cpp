#include "App.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <img/img.hpp>

#include <iostream>
#include <sstream>
#include <random>

#include "simpletext.h"
#include "utils.hpp"
#include "draw/GLHelpers.hpp"

#include <draw/draw.hpp>
#include "screen.hpp"
#include "../graph/graph.hpp"
#include "../tower/tower.hpp"
#include "../enemy/enemy.hpp"

// Liste des touches à cliquer pour créer des tours de différents types
std::vector<int> key_list {GLFW_KEY_KP_1, GLFW_KEY_KP_2, GLFW_KEY_KP_3, GLFW_KEY_KP_4, GLFW_KEY_KP_5};

App::App() : _previousTime(0.0), _viewSize(2.0)
{
    // Lecture du fichier ITD
    auto itd = read_ITD(MAP_FILE_NAME, IN, OUT, PATH);

    // Télécharge l'image de la map
    img::Image map {img::load(make_absolute_path(MAP_FILE_NAME, true), 3, false)};

    // Création de la liste de case
    _tile_list = create_case_list(map.data(), map.data_size());

    // Recherche du des positions du début et de la fin
    for (auto & tile : _tile_list) {
        if (tile.type == CASE_TYPE::START) _in_pos = {tile.pos_x, tile.pos_y};
        if (tile.type == CASE_TYPE::END) _out_pos = {tile.pos_x, tile.pos_y};
    }

    // Création du chemin pour les ennemis
    auto graph = itd.first;
    auto node_positions = itd.second;
    int start {0};
    int end {(int)node_positions.size()-1};

    // Obtention du chemin des ennemis
    std::vector<std::pair<int, int>> path = find_path(graph, node_positions, start, end);

    // Obtention les coordonnées des noeuds du chemin des ennemis
    for (auto & node_coord : path) {
        _path.push_back(get_gl_coordonates_from_case_coordonates(node_coord.first, node_coord.second));
    }
    
    // Création de la liste des ennemis
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis_y(-0.2, 0.2);
    double delay_y = dis_y(gen);
    std::uniform_real_distribution<> dis_x(-0.01, 0.01);
    double delay_x = dis_x(gen);
    _enemy_list.push_back(create_enemy(_in_pos.first + delay_x, _in_pos.second + delay_y, ENEMY_TYPE::ARCHER));
    
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
    // Check si le joueur a perdu
    if (_life <= 0) {
        _is_playing = false;
        draw_game_over();
    
    // Sinon
    } else {
        const double currentTime{glfwGetTime()};
        const double elapsedTime{currentTime - _previousTime};
        _previousTime = currentTime;

    _n_tic++;

    std::vector<std::vector<enemy>::iterator> to_kill; // Contient les ennemis à tuer
    
    // Actions des ennemis
    for (auto it = _enemy_list.begin(); it < _enemy_list.end(); it++) {
        // L'ennemi attaque s'il est sur le dernier noeud
        if (it->attacking) {
            if (_n_tic % it->pace == 0) {
                if (it->type == ENEMY_TYPE::BOMBER) to_kill.push_back(it);
                _life -= it->damage;
            }
        }
        // Sinon il se déplace
        else {
            it->update_position();         
            it->update_direction(_path);
        }
    }

    // Tri des ennemis dans l'ordre

    // Action des tours
    for (auto & tower : _tower_list) {
        for (auto it = _enemy_list.begin(); it < _enemy_list.end(); it++) {
            if ((_n_tic % it->pace == 0) && tower.in_range(get_case_coordonates_from_gl_coordonates(it->pos_x, it->pos_y))) {
                it->pv -= tower.damage;
                _money += it->gain;
                if (it->pv <= 0) to_kill.push_back(it);
            }   
        }
    }
    
    for (auto & enemy_it : to_kill) {
        _enemy_list.erase(enemy_it);
    }
    
    // Mise à jour de la map
    render();
    }
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
    draw_enemies(_enemy_list, _enemy_sprites);
    
    // Mise à jour du texte
    _TextRenderer.Render();
}

void App::key_callback(int key, int scancode, int action, int mods)
{
    // Choix du type de la tour à créer selon la touche cliquée
    if (_is_playing) {
        for (int i=0; i<NUMBER_OF_TOWER_TYPE; i++) {
            if (key == key_list[i] && action == GLFW_PRESS) {
                _new_tower_type = ALL_TOWER_TYPES[i];
            }
        }
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
        
        // Création d'une tour à la case cliquée
        if (_new_tower_type != TOWER_TYPE::NONE && _money >= get_cost_from_type(_new_tower_type) 
        && x >= 0 && case_coordinate.first < WIDTH_OF_MAP && y >= 0 && case_coordinate.second < WIDTH_OF_MAP
        && !get_case_from_coordinates(case_coordinate.first, case_coordinate.second, _tile_list).is_occupied) {
            tower tower { create_tower(case_coordinate.first, case_coordinate.second, _new_tower_type) };
            int id { get_id_from_position(case_coordinate.first, case_coordinate.second) };
            _tile_list[id].is_occupied = true;
            _tile_list[id].type = CASE_TYPE::TOWER;
            _tile_list[id].tower_sprite = loadTexture(img::load(make_absolute_path(get_sprite_from_type(_new_tower_type), true), 4, true));
            _money -= tower.cost;
            _new_tower_type = TOWER_TYPE::NONE;
            _tower_list.push_back(tower);
        }
	}
}

void App::scroll_callback(double /*xoffset */, double /*yoffset */)
{
}

void App::cursor_position_callback(double /*xpos */, double /*ypos */)
{
}

void App::size_callback(int width, int height) 
{
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
