#ifndef JFLORES_H
#define JFLORES_H

//#include "defs.h"

typedef float Vec[3];

void reset_position(Vec pos);
void detect_edges_ship(Vec pos, int xres = 640, int yres= 480);
void detect_edges_bullet(Vec pos, int xres = 640, int yres= 480);
void jflores(int number);
void check_arrow_keys(Vec pos, unsigned char keys[]);
void reset_position(Vec pos);
void change_position(Vec pos, int x, int y);
void shift_position(Vec pos, int x, int y);

#endif
