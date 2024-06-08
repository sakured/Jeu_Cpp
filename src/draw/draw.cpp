#include <iostream>
#include "draw.hpp"

/**
 * TO DO :
 * DRAW TOUR
 * DRAW ENNEMI
 * DRAW BOUTONS
 * DRAW TOUT LE TEXTE AUTOUR DANS UNE FONCTION SETUP()
*/

/**
 * Dessine une tour
*/
void draw_tour(Case my_case, GLuint sprite) {
    glColor3f(0.5f, 0.5f, 0.5f);
    glPushMatrix();
    glScalef(1, -1, 1);
    glTranslatef(-0.8, -0.75, 0);
	glBegin(GL_QUADS);
		glVertex2f(my_case.pos_x, my_case.pos_y);
		glVertex2f(my_case.pos_x, my_case.pos_y + SIZE_OF_CASE);
		glVertex2f(my_case.pos_x + SIZE_OF_CASE, my_case.pos_y + SIZE_OF_CASE);
		glVertex2f(my_case.pos_x + SIZE_OF_CASE, my_case.pos_y);
	glEnd();
    glScalef(0.8f, 0.8f, 0.8f);
    draw_quad_with_texture(sprite);
    glPopMatrix();
}

/**
 * Dessine une case
*/
void draw_case(Case my_case) {
    // Choix de la bonne texture
    switch (my_case.type) {
        case CASE_TYPE::START :
            glColor3f(0.0f, 0.0f, 1.0f);
            break;
        case CASE_TYPE::END :
            glColor3f(1.0f, 0.0f, 0.0f);
            break;
        case CASE_TYPE::TOWER :
            glColor3f(0.0f, 1.0f,0.0f);
            break;
        case CASE_TYPE::ROAD :
            glColor3f(1.0f, 1.0f,1.0f);
            break;
        default :
            glColor3f(0.0f, 0.0f, 0.0f);
            break;
    }

    // Dessin de la case
	glBegin(GL_QUADS);
		glVertex2f(my_case.pos_x, my_case.pos_y);
		glVertex2f(my_case.pos_x, my_case.pos_y + SIZE_OF_CASE);
		glVertex2f(my_case.pos_x + SIZE_OF_CASE, my_case.pos_y + SIZE_OF_CASE);
		glVertex2f(my_case.pos_x + SIZE_OF_CASE, my_case.pos_y);
	glEnd();
}

/**
 * Dessine une map
*/
void draw_map(std::vector<Case> case_list) {
    for (auto & my_case : case_list) {
        draw_case(my_case);
    }
}