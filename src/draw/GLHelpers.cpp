#include "GLHelpers.hpp"
#include "glad/glad.h"
#include <iostream>

/**
 * Télécharge une texture
 */
GLuint loadTexture(uint8_t const* data, int width, int height) {
    GLuint textureId {};

    glEnable(GL_TEXTURE_2D);
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glPixelStorei(GL_PACK_ALIGNMENT, 1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    // Error on MACOS (segmentation fault) when using glGenerateMipmap
    // glGenerateMipmap(GL_TEXTURE_2D);
    glDisable(GL_TEXTURE_2D);

    return textureId;
}

/**
 * Dessine un quadrilatère avec une texture donnée
 */
void draw_quad_with_texture(GLuint textureId) {
    glEnable(GL_BLEND);
    glEnable(GL_TEXTURE_2D);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBindTexture(GL_TEXTURE_2D, textureId);
    glColor3ub(255, 255, 255);
    glBegin(GL_QUADS);
        glTexCoord2d(0,0);
        glVertex2f(-0.5f, -0.5f);

        glTexCoord2d(1,0);
        glVertex2f(0.5f, -0.5f);

        glTexCoord2d(1,1);
        glVertex2f(0.5f, 0.5f);

        glTexCoord2d(0,1);
        glVertex2f(-0.5f, 0.5f);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
}

/**
 * Dessine un quadrilatère
 */
void draw_quad() {
    glColor3ub(255, 0, 0);
    glBegin(GL_QUADS);
        glTexCoord2d(0,0);
        glVertex2f(-0.5f, -0.5f);

        glTexCoord2d(1,0);
        glVertex2f(0.5f, -0.5f);

        glTexCoord2d(1,1);
        glVertex2f(0.5f, 0.5f);

        glTexCoord2d(0,1);
        glVertex2f(-0.5f, 0.5f);
    glEnd();
}