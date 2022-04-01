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

// This function will print out message from this file
void print_my_name();
class Image;
class Background {
    public:
        void color_bg();
	void add_image_level(int, int);	// Add image for level 1
	void add_image_level2(int, int);	// Add image for level 2
	void add_image_level3(int, int);	// Add image for level 3
	void add_menu_image(int, int); 			// Adds image for menu
        void add_menu_text(int, int);
        void blink_text(int, int);
        void game_logo(int);
        void draw_tank(int, int);
        void music();
};

class Tank {
    public:
        void draw_tank();
};

class Beam {
    public:
        void draw_beams(int);
};

#endif
