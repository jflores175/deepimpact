/*
 *  Name: Ivan Macias
 *  Date: Feb 24, 2022
 *
 *  @source: imacias.h
 *
 */

#ifndef IMACIAS_H
#define IMACIAS_H

#include <stdio.h>
#include <cstring>
#include "images.h"

class Asteroid;
class Image;

void print_my_name();
int display_imacias(bool);
void check_shots(int);
void init_images(Image*, int);
void display_leaderboard(int);

class Background {
    public: 
        void color_bg();
	    
        void add_image_level(Image*, int, int, int);
        void load_game_background(Image*, int, int, int); 
        void load_menu_check(Image*, bool, int, int);

        void add_menu_image(Image*, int, int, int);
        void add_menu_text(Image*, int, int, int);
        void blink_text(Image*, int, int, int);
        
        void load_game_logo(Image*, int, int);
};

class GameSprite {
    public:
        void draw_sprite(Image*, int, float*, float, float, float); 
};
#endif
