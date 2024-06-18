#include <iostream>
#include "draw.hpp"
#include "../app/App.hpp"
#include <tower/tower.hpp>
#include <enemy/enemy.hpp>

/**
 * Dessine une case
 */
void draw_case(const Case & my_case, const std::vector<GLuint> & sprites) {
    GLuint case_sprite {};
    // Choix de la bonne texture de la case
    switch (my_case.type) {
        case CASE_TYPE::START :
            case_sprite = sprites[0];
            glColor3f(IN[0], IN[1], IN[2]);
            break;
        case CASE_TYPE::END :
            case_sprite = sprites[1];
            glColor3f(OUT[0], OUT[1], OUT[2]);
            break;
        case CASE_TYPE::ROAD :
            case_sprite = sprites[2];
            glColor3f(PATH[0], PATH[1], PATH[2]);
            break;
        default :
            case_sprite = sprites[3];
            glColor3f(0.0f, 0.0f, 0.0f);
            break;
    }

    // Dessin de la case
     glPushMatrix();
        glScalef(.8, -.8, 1);
        glTranslatef(-1, -1, 0);
        glTranslatef(my_case.pos_x + SIZE_OF_CASE/2.f, my_case.pos_y + SIZE_OF_CASE/2.f, 0);
        glScalef(SIZE_OF_CASE, SIZE_OF_CASE, 1);
        draw_quad_with_texture(case_sprite);
    glPopMatrix();

    // Dessin de la tour s'il y en a une
    if (my_case.type == CASE_TYPE::TOWER) draw_tower(my_case, my_case.tower_sprite);
}

/**
 * Dessine une map
 */
void draw_map(const std::vector<Case> & case_list, const std::vector<GLuint> & sprites) {
    for (auto & my_case : case_list) {
        draw_case(my_case, sprites);
    }
}

/**
 * Dessine le bouton start / pause
 */
void draw_start_button(bool is_playing, float width, float height) {
    GLuint image_if_playing {};
    if (is_playing) {
        image_if_playing = loadTexture(img::load(make_absolute_path("images/pause.png", true), 4, true));
    } else {
        image_if_playing = loadTexture(img::load(make_absolute_path("images/start.png", true), 4, true));
    }
    glPushMatrix();
        glTranslatef(width/height-.25, -.85, 0);
        glScalef(.35, .35, 1);
        draw_quad_with_texture(image_if_playing);
    glPopMatrix();
}

/**
 * Dessine une tour
 */
void draw_tower(const Case & my_case, const GLuint & tower_sprite) {
    glPushMatrix();
        glScalef(0.8, 0.8, 1);
        glTranslatef(-1+my_case.pos_x+SIZE_OF_CASE/2, 1-my_case.pos_y-SIZE_OF_CASE/2, 0);
        glScalef(SIZE_OF_CASE, SIZE_OF_CASE, 1);
        draw_quad_with_texture(tower_sprite);
    glPopMatrix();
}

/**
 * Dessine un ennemi
 */
void draw_enemy(enemy enemy, const GLuint & enemy_sprite) {
    glPushMatrix();
        // Ennemi
        glScalef(0.8, 0.8, 1);
        glTranslatef(-1+enemy.pos_x+SIZE_OF_CASE/2, 1-enemy.pos_y-SIZE_OF_CASE/2, 0);
        glScalef(SIZE_OF_CASE, SIZE_OF_CASE, 1);
        draw_quad_with_texture(enemy_sprite);
        // Barre de vies
        glTranslatef(0., 0.9f, 0.);
        glScalef(enemy.pv/90.f, 0.1f, 1);
        draw_quad();
    glPopMatrix();  
}

/**
 * Dessine tous les ennemis
 */
void draw_enemies(const std::vector<enemy> enemies, std::vector<GLuint> & enemy_sprites) {
    for (auto & enemy : enemies) {
        draw_enemy(enemy, enemy_sprites[(int)enemy.type]);
    }    
}

/**
 * Dessine l'écran de game over
 */
void draw_game_over() {
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    img::Image game_over {img::load(make_absolute_path("images/gameover.png", true), 4, true)};
    glPushMatrix();
        glScalef(2.5, .5, 1);
        draw_quad_with_texture(loadTexture(game_over));  
    glPopMatrix();
}

/**
 * Dessine l'écran de victoire
 */
void draw_victory() {
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    img::Image game_over {img::load(make_absolute_path("images/welldone.png", true), 4, true)};
    glPushMatrix();
        glScalef(3., .5, 1);
        draw_quad_with_texture(loadTexture(game_over));  
    glPopMatrix();
}

/**
 * Dessine l'écran d'accueil du jeu
 */
void draw_starting(SimpleText & TextRenderer, float width, float height, int salve_number) {
    glPushMatrix();
        glTranslatef(0, 0.3, 0);
        glScalef(.7f, .7f, 1);
        draw_quad_with_texture(loadTexture(img::load(make_absolute_path("images/logo.png", true), 4, true)));  
    glPopMatrix();
    TextRenderer.Label("Welcome in the One Piece Tower Defense !", width/2, height/2+100, SimpleText::CENTER);
    TextRenderer.Label("The goal is very simple. You are the pirates, and you have to prevent the marine from attacking the devil fruit.", width/2, height/2+120, SimpleText::CENTER);
    TextRenderer.Label("To attack the different types of marine admirals, build boats of pirates. You can buy them with money.", width/2, height/2+140, SimpleText::CENTER);
    TextRenderer.Label("You have the possibility to build different sorts of boats. Click on the associated tile to build the chosen boat and then where you want to build it.", width/2, height/2+160, SimpleText::CENTER);
    TextRenderer.Label("(Ex : key 1 for boat of type 1)", width/2, height/2+180, SimpleText::CENTER);
    std::stringstream stream {};
    stream << std::fixed << "You have to survive " << salve_number << std::fixed << " salvos of attacks to win.";
    TextRenderer.Label(stream.str().c_str(), width/2, height/2+200, SimpleText::CENTER);
    TextRenderer.Label("You can pause and restart the game at any time if you click on P.", width/2, height/2+220, SimpleText::CENTER);
    TextRenderer.Label("Click on space to start.", width/2, height/2+240, SimpleText::CENTER);
}

/**
 * Dessine les informations du level et des ressources du joueur
 */
void draw_level_informations (int level, SimpleText & TextRenderer, float width, float height, int money, int life, double next_salve, std::vector<GLuint> & tower_sprites, std::vector<GLuint> & enemy_sprites) {
    
    // Marges
    int tower_margin = (int)(height * 0.33);
    int enemy_margin = (int)(height * 0.13);
    float tower_sprite_margin = 0.3f;
    float enemy_sprite_margin = 0.68f;

    // Titre
    GLuint title { loadTexture(img::load(make_absolute_path("images/towerdefense.png", true), 4, true)) };
    glPushMatrix();
        glTranslatef(0, .9, 0);
        glScalef(.9, .1, 1);
        draw_quad_with_texture(title);
    glPopMatrix();

    // Temps avant la prochaine salve d'attaque
    std::stringstream stream {};
    stream << std::fixed << "Time before next salve of enemies : " << std::setprecision(2) << next_salve;
    TextRenderer.Label(stream.str().c_str(), width/2, height-30, SimpleText::CENTER);

    // Informations sur l'argent
    stream.str("");
    stream << money;
    TextRenderer.Label(stream.str().c_str(), 100, (.28*height)/2., SimpleText::LEFT);
    GLuint piece { loadTexture(img::load(make_absolute_path("images/money.png", true), 4, true)) };
    glPushMatrix();
        glTranslatef(-(width-100)/height, .74, 0);
        glScalef(.1, .1, 1);
        draw_quad_with_texture(piece);
    glPopMatrix();

    // Informations sur les vies
    stream.str("");
    stream << life;
    TextRenderer.Label(stream.str().c_str(), 100, (.42*height)/2., SimpleText::LEFT);
    GLuint heart { loadTexture(img::load(make_absolute_path("images/heart.png", true), 4, true)) };
    glPushMatrix();
        glTranslatef(-(width-100)/height, .6, 0);
        glScalef(.11, .11, 1);
        draw_quad_with_texture(heart);
    glPopMatrix();

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
        stream << std::fixed << "BOAT TYPE " << i+1 << " " << tower_type_to_string(tower_examples[i].type);
        TextRenderer.Label(stream.str().c_str(), 100, tower_margin + i * 120, SimpleText::LEFT);
        stream.str("");
        stream << std::fixed << "Cost : " << tower_examples[i].cost;
        TextRenderer.Label(stream.str().c_str(), 100, tower_margin + 20 + i * 120, SimpleText::LEFT);
        stream.str("");
        stream << std::fixed << "Damage : " << tower_examples[i].damage;
        TextRenderer.Label(stream.str().c_str(), 100, tower_margin + 40 + i * 120, SimpleText::LEFT);
        stream.str("");
        stream << std::fixed << "Range : " << tower_examples[i].range;
        TextRenderer.Label(stream.str().c_str(), 100, tower_margin + 60 + i * 120, SimpleText::LEFT);
        glPushMatrix();
            glTranslatef(-(2*(width-100)/2)/height, tower_sprite_margin - (120*2/height) * i, 0);
            glScalef((2*80)/height, (2*80)/height, 1);
            draw_quad_with_texture(tower_sprites[i]);
        glPopMatrix();
    }

    // Informations sur les ennemis
    for (int i=0; i<enemy_examples.size(); i++) {
        stream.str("");
        stream << std::fixed << "ENEMY TYPE " << enemy_type_to_string(enemy_examples[i].type);
        TextRenderer.Label(stream.str().c_str(), width - 100, enemy_margin + i * 160, SimpleText::RIGHT);
        stream.str("");
        stream << std::fixed << "Reward : " << enemy_examples[i].gain;
        TextRenderer.Label(stream.str().c_str(), width - 100, enemy_margin + 20 + i * 160, SimpleText::RIGHT);
        stream.str("");
        stream << std::fixed << "Damage : " << enemy_examples[i].damage;
        TextRenderer.Label(stream.str().c_str(), width - 100, enemy_margin + 40 + i * 160, SimpleText::RIGHT);
        stream.str("");
        stream << std::fixed << "Range : " << enemy_examples[i].range;
        TextRenderer.Label(stream.str().c_str(), width - 100, enemy_margin + 60 + i * 160, SimpleText::RIGHT);
        stream.str("");
        stream << std::fixed << "PV : " << enemy_examples[i].pv;
        TextRenderer.Label(stream.str().c_str(), width - 100, enemy_margin + 80 + i * 160, SimpleText::RIGHT);
        stream.str("");
        stream << std::fixed << "Speed : " << enemy_examples[i].speed_label;
        TextRenderer.Label(stream.str().c_str(), width - 100, enemy_margin + 100 + i * 160, SimpleText::RIGHT);
        glPushMatrix();
            glTranslatef((2*(width-100)/2)/height, enemy_sprite_margin - (165*2/height) * i, 0);
            glScalef((2*80)/height, (2*80)/height, 1);
            draw_quad_with_texture(enemy_sprites[i]);
        glPopMatrix();
    }

    // Affichage du rendu
    TextRenderer.Render();
}