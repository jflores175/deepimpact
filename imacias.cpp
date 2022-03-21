/*
 *  Name: Ivan Macias
 *  Date: Feb 24, 2022
 *
 *  @source: imacias.cpp
 *
 */

#include <stdio.h>
#include <GL/glx.h>
#include <math.h>
#include "fonts.h"
#include <X11/Xlib.h>
#include "imacias.h"

typedef double Flt;
typedef double Vec[3];

#define rnd() (((double)rand())/(double)RAND_MAX)
#define MakeVector(v, x, y, z) (v)[0]=(x),(v)[1]=(y),(v)[2]=(z)

// This function will print out message from this file
void print_my_name() {
	printf("Ivan Macias\n");
	printf("-------------\n"); // Tells what key was pressed
}


class Info {
    public:
        int x_res;
        int y_res;
        Vec box[20];
    
        Info() {
            x_res = 640;
            y_res = 480;

            for (int i=0; i<20; i++) {
                box[i][0] = rnd() * x_res;
                box[i][1] = rnd() * (y_res-220) + 220.0;
                box[i][2] = 0.0;
            }
        }
} info;

void Background::draw_background()
{
    glClearColor(0.0, 0.0, 0.15, 0.0);   
}

void Background::draw_ground()
{
    int x = info.x_res;
    int y = info.y_res;
    //
    //show ground
    glBegin(GL_QUADS);
        glColor3f(0.2, 0.2, 0.2);
        glVertex2i(0,       220);
        glVertex2i(x, 220);
        glColor3f(0.4, 0.4, 0.4);
        glVertex2i(y,   0);
        glVertex2i(0,         0);
    glEnd();
}

void Background::show_boxes()
{
    for (int i=0; i<20; i++) {
        glPushMatrix();
        glTranslated(info.box[i][0],info.box[i][1],info.box[i][2]);
        glColor3f(0.2, 0.2, 0.2);
        glBegin(GL_QUADS);
            glVertex2i( 0,  0);
            glVertex2i( 0, 30);
            glVertex2i(20, 30);
            glVertex2i(20,  0);
        glEnd();
        glPopMatrix();
    }
}

