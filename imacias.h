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

// This function will print out message from this file
void print_my_name();
void display_imacias(bool);
class Image;
class Background {
    public:
        void init_images();
        void color_bg();
	    
        void add_image_level(int, int, int);	    // Add image for level 1
        void load_game_background(int, int, int); 
        void load_menu_check(bool, int, int);

        void add_menu_image(int, int); 		// Adds image for menu
        void add_menu_text(int, int);
        void blink_text(int, int);
        
        void load_game_logo(int);
        void draw_tank(int, int);
};

class Tank {
    public:
        //void init_tank();
        void draw_tank();
        void trans_tank();
};

class Enemy {
    public:
        void draw_enemy(int);
        void load_enemy_sprites(int, int);
};
#endif
