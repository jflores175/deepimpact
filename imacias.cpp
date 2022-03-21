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
#include <cstring>

typedef double Flt;
typedef double Vec[3];

#define rnd() (((double)rand())/(double)RAND_MAX)

// This function will print out message from this file
void print_my_name() {
	printf("Ivan Macias\n");
	printf("-------------\n"); // Tells what key was pressed
}

class Info {
    public:
        int x_res, y_res;
        int num_rows, num_cols;
        unsigned char arr[16][80];

        Vec box[20];
        Flt tile_size[2];
        Flt fsize[2];
        Flt base;
        Flt camera[2];
        
        Info() {
            x_res = 640;
            y_res = 480;

            for (int i=0; i<20; i++) {
                box[i][0] = rnd() * x_res;
                box[i][1] = rnd() * (y_res-220) + 220.0;
                box[i][2] = 0.0;
            }
            tile_size[0] = 32;
            tile_size[1] = 32;
            
            fsize[0] = (Flt)(tile_size[0]);
            fsize[1] = (Flt)(tile_size[1]);
            base = 220.0;

            camera[0] = camera[1] = 0.0;
            /*
            FILE *fpi = fopen("level1.txt", "r");
            if (fpi) {
                num_rows = 0;
                char line[100];
                while (fgets(line, 100, fpi) != NULL) {
                    removeCrLf(line);
                    int len = strlen(line);
                    num_cols = len;

                    for (int j=0; j<len; j++) {
                        arr[num_rows][j] = line[j];
                    }
                    printf("\n");
                }
            }
        }
        void removeCrLf(char *str) {
            char *p = str;
            while (*p) {
                if (*p == 10 || *p == 13) {
                    *p = '\0';
                    break;
                }
                ++p;
            }
        }*/
        }
} info;

void Background::color_bg()
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

void Background::draw_bg()
{
    //show boxes as stars for background
    for (int i=0; i<20; i++) {
        glPushMatrix();
        glTranslated(info.box[i][0],info.box[i][1],info.box[i][2]);
        glColor3ub( 200, 200, 0);
        glBegin(GL_QUADS);
            glVertex2i( 0,  0);
            glVertex2i( 0, 10);
            glVertex2i(10, 10);
            glVertex2i(10,  0);
        glEnd();
        glPopMatrix();
    }
}
/*
void Background::render_tiles()
{
    int tx = (int) info.tile_size[0];
    int ty = (int) info.tile_size[1];
    Flt dd = info.fsize[0];
    Flt offy = info.base;
    int ncols_to_render = info.x_res / info.tile_size[0] + 2;
    int col = (int)(info.camera[0] / dd);
    col = col % info.num_cols;
    //Partial tile offset must be determined here.
    //The leftmost tile might be partially off-screen.
    //cdd: camera position in terms of tiles.
    Flt cdd = info.camera[0] / dd;
    //flo: just the integer portion
    Flt flo = floor(cdd);
    //dec: just the decimal portion
    Flt dec = (cdd - flo);
    //offx: the offset to the left of the screen to start drawing tiles
    Flt offx = -dec * dd;
    //Log("gl.camera[0]: %lf   offx: %lf\n",gl.camera[0],offx);
    for (int j=0; j<ncols_to_render; j++) {
        int row = info.num_rows-1;
        for (int i=0; i<info.num_rows; i++) {
            if (info.arr[row][col] == 'w') {
                glColor3f(0.8, 0.8, 0.6);
                glPushMatrix();
                //put tile in its place
                glTranslated((Flt)j*dd+offx, (Flt)i*info.fsize[1]+offy, 0.0);
                glBegin(GL_QUADS);
                    glVertex2i( 0,  0);
                    glVertex2i( 0, ty);
                    glVertex2i(tx, ty);
                    glVertex2i(tx,  0);
                glEnd();
                glPopMatrix();
            }
            if (info.arr[row][col] == 'b') {
                glColor3f(0.9, 0.2, 0.2);
                glPushMatrix();
                glTranslated((Flt)j*dd+offx, (Flt)i*info.fsize[1]+offy, 0.0);
                glBegin(GL_QUADS);
                    glVertex2i( 0,  0);
                    glVertex2i( 0, ty);
                    glVertex2i(tx, ty);
                    glVertex2i(tx,  0);
                glEnd();                                                                                                        glPopMatrix();
            }
            --row;
        }
    }
}*/
