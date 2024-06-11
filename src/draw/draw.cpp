#include <iostream>
#include "draw.hpp"
#include "../app/App.hpp"


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
void draw_level_informations (int level, SimpleText & TextRenderer, float width, float height, int money, std::vector<GLuint> & tower_sprites) {
    // Titre
    TextRenderer.Label("TOWER DEFENSE", width / 2, 30, SimpleText::CENTER);

    // Informations sur l'argent
    std::string money_label_text {};
    std::stringstream money_stream {};
    money_stream << std::fixed << "Money avalaible : " << std::setprecision(2) << money;
    money_label_text = money_stream.str();
    TextRenderer.Label(money_label_text.c_str(), 30, 30, SimpleText::LEFT);

    // Marge du haut
    int margin = (int)(height * 0.13);

    // Informations sur les tours
    TextRenderer.Label("TOWER TYPE BOW", 100, margin, SimpleText::LEFT);
    TextRenderer.Label("Cost : 50", 100, margin + 20, SimpleText::LEFT);
    TextRenderer.Label("Damage : 12", 100, margin + 40, SimpleText::LEFT);
    TextRenderer.Label("Range : 3", 100, margin + 60, SimpleText::LEFT);
    TextRenderer.Label("TOWER TYPE CROSSBOW", 100, margin + 120, SimpleText::LEFT);
    TextRenderer.Label("Cost : 75", 100, margin + 140, SimpleText::LEFT);
    TextRenderer.Label("Damage : 10", 100, margin + 160, SimpleText::LEFT);
    TextRenderer.Label("Range : 5", 100, margin + 180, SimpleText::LEFT);

    // Informations sur les ennemis
    TextRenderer.Label("ENEMY TYPE ARCHER", width - 100, margin, SimpleText::RIGHT);
    TextRenderer.Label("Reward : 10", width - 100, margin + 20, SimpleText::RIGHT);
    TextRenderer.Label("Damage : 2", width - 100, margin + 40, SimpleText::RIGHT);
    TextRenderer.Label("Range : 4", width - 100, margin + 60, SimpleText::RIGHT);
    TextRenderer.Label("PV : 50", width - 100, margin + 80, SimpleText::RIGHT);
    TextRenderer.Label("ENEMY TYPE KNIGHT", width - 100, margin + 140, SimpleText::RIGHT);
    TextRenderer.Label("Reward : 12", width - 100, margin + 160, SimpleText::RIGHT);
    TextRenderer.Label("Damage : 4", width - 100, margin + 180, SimpleText::RIGHT);
    TextRenderer.Label("Range : 1", width - 100, margin + 200, SimpleText::RIGHT);
    TextRenderer.Label("PV : 100", width - 100, margin + 220, SimpleText::RIGHT);
    TextRenderer.Label("ENEMY TYPE BOMBER", width - 100, margin + 280, SimpleText::RIGHT);
    TextRenderer.Label("Reward : 8", width - 100, margin + 300, SimpleText::RIGHT);
    TextRenderer.Label("Damage : 10", width - 100, margin + 320, SimpleText::RIGHT);
    TextRenderer.Label("Range : 1", width - 100, margin + 340, SimpleText::RIGHT);
    TextRenderer.Label("PV : 20", width - 100, margin + 360, SimpleText::RIGHT);

    TextRenderer.Render();
}