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
            x_res = 750; // testing from 640
            y_res = 550; // testing from 480
            
            // testing from 20
            for (int i=0; i<40; i++) {
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

void Background::draw_bg()
{
    //show boxes as stars for background
    for (int i=0; i<40; i++) {
        glPushMatrix();
        glTranslated(info.box[i][0],info.box[i][1],info.box[i][2]);
        glColor3ub(200, 200, 0);
        glBegin(GL_QUADS);
            glVertex2i( 0,  0);
            glVertex2i( 0, 10);
            glVertex2i(10, 10);
            glVertex2i(10,  0);
        glEnd();
        glPopMatrix();
    }
}
