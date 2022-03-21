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
        void color_bg();    // Colors background
        void draw_ground(); 
        void draw_bg();     // Draws background
        void render_tiles();
};
/*
class Info {
    public:
        void removeCrLf(char *);
};*/
#endif
