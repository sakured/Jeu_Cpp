#include <iostream>
#include "draw.hpp"
#include "../app/App.hpp"
#include <tower/tower.hpp>
#include <enemy/enemy.hpp>


/**
 * Dessine une tour
*/
void draw_tower(Case my_case) {
    GLuint sprite {};
    glColor3f(0.f, 1.f, 0.f);
    glPushMatrix();
        glScalef(.8, -.8, 1);
        glTranslatef(-1, -1, 0);
        glBegin(GL_QUADS);
            glVertex2f(my_case.pos_x, my_case.pos_y);
            glVertex2f(my_case.pos_x, my_case.pos_y + SIZE_OF_CASE);
            glVertex2f(my_case.pos_x + SIZE_OF_CASE, my_case.pos_y + SIZE_OF_CASE);
            glVertex2f(my_case.pos_x + SIZE_OF_CASE, my_case.pos_y);
        glEnd();
        // draw_quad_with_texture(sprite);
    glPopMatrix();
}

/**
 * Dessine une case
*/
void draw_case(Case my_case) {
    // Choix de la bonne couleur
    switch (my_case.type) {
        case CASE_TYPE::START :
            glColor3f(IN[0], IN[1], IN[2]);
            break;
        case CASE_TYPE::END :
            glColor3f(OUT[0], OUT[1], OUT[2]);
            break;
        case CASE_TYPE::TOWER :
            glColor3f(0.0f, 1.0f, 0.0f);
            break;
        case CASE_TYPE::ROAD :
            glColor3f(PATH[0], PATH[1], PATH[2]);
            break;
        default :
            glColor3f(0.0f, 0.0f, 0.0f);
            break;
    }

    // Dessin de la case
     glPushMatrix();
        glScalef(.8, -.8, 1);
        glTranslatef(-1, -1, 0);
        glBegin(GL_QUADS);
            glVertex2f(my_case.pos_x, my_case.pos_y);
            glVertex2f(my_case.pos_x, my_case.pos_y + SIZE_OF_CASE);
            glVertex2f(my_case.pos_x + SIZE_OF_CASE, my_case.pos_y + SIZE_OF_CASE);
            glVertex2f(my_case.pos_x + SIZE_OF_CASE, my_case.pos_y);
        glEnd();
    glPopMatrix();
}

/**
 * Dessine une map
*/
void draw_map(std::vector<Case> case_list) {
    for (auto & my_case : case_list) {
        draw_case(my_case);
    }
}

/**
 * Dessine les informations du level (tours, ennemis...)
 */
void draw_level_informations (int level, SimpleText & TextRenderer, float width, float height, int money, std::vector<GLuint> & tower_sprites, std::vector<GLuint> & enemy_sprites) {
    
    // Titre
    GLuint title { loadTexture(img::load(make_absolute_path("images/towerdefense.png", true), 4, true)) };
    glPushMatrix();
        glTranslatef(0, .9, 0);
        glScalef(.9, .1, 1);
        draw_quad_with_texture(title);
    glPopMatrix();

    // Informations sur l'argent
    std::stringstream stream {};
    stream << std::fixed << "Money avalaible : " << money;
    TextRenderer.Label(stream.str().c_str(), 100, 40, SimpleText::LEFT);

    // Marge du haut
    int margin = (int)(height * 0.13);

    // Liste de tours
    std::vector<tower> tower_examples {};
    for (auto & tower_type : ALL_TOWER_TYPES) {
        tower_examples.push_back(create_tower(-1, -1, tower_type));
    }

    // Liste d'ennemis
    std::vector<enemy> enemy_examples {};
    for (auto & enemy_type : ALL_ENEMY_TYPES) {
        enemy_examples.push_back(create_enemy(-1, -1, enemy_type));
    }

    // Informations sur les tours
    for (int i=0; i<tower_examples.size(); i++) {
        stream.str("");
        stream << std::fixed << "TOWER TYPE " << tower_type_to_string(tower_examples[i].type);
        TextRenderer.Label(stream.str().c_str(), 100, margin + i * 120, SimpleText::LEFT);
        stream.str("");
        stream << std::fixed << "Cost : " << tower_examples[i].cost;
        TextRenderer.Label(stream.str().c_str(), 100, margin + 20 + i * 120, SimpleText::LEFT);
        stream.str("");
        stream << std::fixed << "Damage : " << tower_examples[i].damage;
        TextRenderer.Label(stream.str().c_str(), 100, margin + 40 + i * 120, SimpleText::LEFT);
        stream.str("");
        stream << std::fixed << "Range : " << tower_examples[i].range;
        TextRenderer.Label(stream.str().c_str(), 100, margin + 60 + i * 120, SimpleText::LEFT);
        glPushMatrix();
            glTranslatef(-(2*(width-100)/2)/height, .7 - (120*2/height) * i, 0);
            glScalef((2*100)/height, (2*100)/height, 1);
            draw_quad_with_texture(tower_sprites[i]);
        glPopMatrix();
    }

    // Informations sur les ennemis
    for (int i=0; i<enemy_examples.size(); i++) {
        stream.str("");
        stream << std::fixed << "ENEMY TYPE " << enemy_type_to_string(enemy_examples[i].type);
        TextRenderer.Label(stream.str().c_str(), width - 100, margin + i * 140, SimpleText::RIGHT);
        stream.str("");
        stream << std::fixed << "Reward : " << enemy_examples[i].gain;
        TextRenderer.Label(stream.str().c_str(), width - 100, margin + 20 + i * 140, SimpleText::RIGHT);
        stream.str("");
        stream << std::fixed << "Damage : " << enemy_examples[i].damage;
        TextRenderer.Label(stream.str().c_str(), width - 100, margin + 40 + i * 140, SimpleText::RIGHT);
        stream.str("");
        stream << std::fixed << "Range : " << enemy_examples[i].range;
        TextRenderer.Label(stream.str().c_str(), width - 100, margin + 60 + i * 140, SimpleText::RIGHT);
        stream.str("");
        stream << std::fixed << "PV : " << enemy_examples[i].pv;
        TextRenderer.Label(stream.str().c_str(), width - 100, margin + 80 + i * 140, SimpleText::RIGHT);
        glPushMatrix();
            glTranslatef((2*(width-100)/2)/height, .68 - (140*2/height) * i, 0);
            glScalef((2*100)/height, (2*100)/height, 1);
            draw_quad_with_texture(enemy_sprites[i]);
        glPopMatrix();
    }

    // Affichage du rendu
    TextRenderer.Render();
}