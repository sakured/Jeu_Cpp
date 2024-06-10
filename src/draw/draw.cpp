#include <iostream>
#include "draw.hpp"


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