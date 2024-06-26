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

// Liste des touches à cliquer pour créer des tours de différents types
std::vector<int> key_list {GLFW_KEY_KP_1, GLFW_KEY_KP_2, GLFW_KEY_KP_3, GLFW_KEY_KP_4, GLFW_KEY_KP_5};

App::App() : _viewSize(2.0)
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
    create_salve_enemy(_enemy_list, _in_pos, _number_of_enemy_of_type);
    
    // Sprites des tours
    for (auto & tower_type : ALL_TOWER_TYPES) {
        img::Image tower {img::load(make_absolute_path(get_sprite_from_type(tower_type).c_str(), true), 4, true)};
        _tower_sprites.push_back(loadTexture(tower));
    }

    // Sprites des ennemis
    for (auto & enemy_type : ALL_ENEMY_TYPES) {
        img::Image enemy {img::load(make_absolute_path(get_sprite_from_type(enemy_type).c_str(), true), 4, true)};
        _enemy_sprites.push_back(loadTexture(enemy));
    }

    // Sprites des cases
    _tiles_sprites.push_back(loadTexture(img::load(make_absolute_path("images/start.png", true), 4, false)));
    _tiles_sprites.push_back(loadTexture(img::load(make_absolute_path("images/end.png", true), 4, false)));
    _tiles_sprites.push_back(loadTexture(img::load(make_absolute_path("images/road.png", true), 4, false)));
    _tiles_sprites.push_back(loadTexture(img::load(make_absolute_path("images/blank.png", true), 4, false)));
}

void App::setup()
{
    // Set the clear color to a nice black
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // Setup the text renderer with blending enabled and white text color
    _TextRenderer.ResetFont();
    _TextRenderer.SetColor(SimpleText::TEXT_COLOR, SimpleText::Color::WHITE);
    _TextRenderer.SetColorf(SimpleText::BACKGROUND_COLOR, 0.f, 0.f, 0.f, 0.f);
    _TextRenderer.EnableBlending(true);

    _TextRenderer.Render();
}

void App::update()
{
    // Check si le joueur a perdu
    if (_life <= 0) {
        _is_playing = false;
    
    // Check si le joueur a gagné
    } else if (_number_of_enemy_of_type == _salve_number && _enemy_list.empty()) {
        _is_playing = false;
    
    // Sinon
    } else if (_is_playing) {

        _n_tic++;

        // Actions des ennemis
        for (auto it = _enemy_list.begin(); it < _enemy_list.end(); it++) {
            // L'ennemi attaque s'il est sur le dernier noeud
            if (it->is_attacking) {
                if (_n_tic % it->pace == 0) {
                    _life -= it->damage;
                    if (it->type == ENEMY_TYPE::BOMBER) it->pv = 0;
                }
            }
            // Sinon il se déplace
            else {
                it->update_position();         
                it->update_direction(_path);
            }
        }

        // Tri des ennemis par ordre de leur distance entre le début et la fin du niveau
        if(_enemy_list.size() != 0) merge_sort(_enemy_list);

        // Action des tours
        for (auto & tower : _tower_list) {
            for (auto it = _enemy_list.begin(); it < _enemy_list.end(); it++) {
                if ((_n_tic % it->pace == 0) && tower.in_range(get_case_coordonates_from_gl_coordonates(it->pos_x, it->pos_y))) {
                    it->pv -= tower.damage;
                    if (it->pv <= 0) _money += it->gain;
                    break;
                }   
            }
        }

        // Tue les ennemis 
        auto new_end = std::remove_if(_enemy_list.begin(), _enemy_list.end(), [](enemy enemy) {
            return enemy.pv <= 0;
        });        

        _enemy_list.erase(new_end, _enemy_list.end());


        // Création des salves d'ennemis (chaque fois plus puissantes)

        const double current_time{glfwGetTime() - _time_before_start};

        _salve_timer = _salve_pace - fmod(current_time, _salve_pace);

        if (current_time >= _next_salve && _number_of_enemy_of_type < _salve_number) {
            _number_of_enemy_of_type ++;
            create_salve_enemy(_enemy_list, _in_pos, _number_of_enemy_of_type);
            _next_salve += _salve_pace;
        }
    } else if (!_is_game_started) {
        _time_before_start = glfwGetTime();
    }
    
    // Mise à jour de la map
    render();
}

void App::render()
{
    // Clear the color and depth buffers of the frame buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    if (_is_playing) {

        // Dessin de la map et des infos
        draw_map(_tile_list, _tiles_sprites);
        draw_level_informations(1, _TextRenderer, _width, _height, _money, _life, _salve_timer, _tower_sprites, _enemy_sprites); 
        // draw_start_button(_is_playing, _width, _height);

        draw_enemies(_enemy_list, _enemy_sprites);
    } else if (_life <= 0) {

        //Affiche le game over
        draw_game_over();

    } else if (_number_of_enemy_of_type == _salve_number && _enemy_list.empty()) {

        // Affiche la victoire
        draw_victory();

    } else {

        // Affiche l'écran d'accueil
        draw_starting(_TextRenderer, _width, _height, _salve_number);
    }
    
    // Mise à jour du texte
    _TextRenderer.Render();
}

void App::key_callback(int key, int scancode, int action, int mods)
{
    // Démarrage du jeu
    if (!_is_game_started) {
        if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
            _is_game_started = true;
            _is_playing= true;
        }
    }

    // Met en pause et redémarre le jeu
    if (_is_game_started) {
        if (key == GLFW_KEY_P && action == GLFW_PRESS) {
            // draw_start_button(_is_playing, _width, _height);
            if (_is_playing) _is_playing = false;
            else _is_playing = true;
        }
    }

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

    // Affiche l'écran d'accueil même quand on change la taille de la fenêtre
    if (!_is_game_started) {
        draw_starting(_TextRenderer, _width, _height, _salve_number);
        _TextRenderer.Render();
    }
}
