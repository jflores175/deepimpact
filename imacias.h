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
class Background {
    public:
        void color_bg();    				// Colors background
        void draw_bg();     				// Draws background
	void add_image_level(int, int, unsigned int);	// Add image for level 1
	void add_image_level2(int, int, unsigned int);	// Add image for level 2
	void add_image_level3(int, int, unsigned int);	// Add image for level 3
};

#endif
