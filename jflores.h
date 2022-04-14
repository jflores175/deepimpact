#ifndef JFLORES_H
#define JFLORES_H

//#include "defs.h"

typedef float Vec[3];

void reset_position(Vec pos);
void detect_edges_ship(Vec pos, int xres = 640, int yres= 480);
void detect_edges_bullet(Vec pos, int xres = 640, int yres= 480);
void jflores(int number);
void check_ship_keys(Vec pos, unsigned char keys[]);

#endif
