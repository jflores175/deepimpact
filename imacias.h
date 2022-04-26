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

typedef float Vec[3];
class Asteroid;

// This function will print out message from this file
void print_my_name();
void display_imacias(bool);
class Image;
void init_images(Image*, int);

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

class Tank {
    public:
        void draw_tank(Image*, int, float*);
        void trans_tank();
};

class Enemy {
    public:
        void draw_enemy(Image*, int, float*);
        void load_enemy_sprites(Image*, int, float*);
};
#endif
