#ifndef IMAGES_H
#define IMAGES_H

#include <stdio.h>
#include <GL/glx.h>
#include <math.h>
#include "fonts.h"
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include "imacias.h"
#include <cstring>
#include <unistd.h>

class Image {
    public:
        unsigned int textid;
        int width, height;
        unsigned char *data;
        ~Image() { delete [] data; }
        Image(const char *fname) {
        if (fname[0] == '\0')
            return;
        //
        int ppmFlag = 0;
        char name[40];
        strcpy(name, fname);
        int slen = strlen(name);
        char ppmname[80];
        if (strncmp(name+(slen-4), ".ppm", 4) == 0)
            ppmFlag = 1;
        if (ppmFlag) {
            strcpy(ppmname, name);
        } else {
            name[slen-4] = '\0';
            //printf("name **%s**\n", name);
            sprintf(ppmname,"%s.ppm", name);
            //printf("ppmname **%s**\n", ppmname);
            char ts[100];
            //system("convert eball.jpg eball.ppm");
            sprintf(ts, "convert %s %s", fname, ppmname);
            system(ts);
        }

        FILE *fpi = fopen(ppmname, "r");
        if (fpi) {
            char line[200];
            fgets(line, 200, fpi);
            fgets(line, 200, fpi);
            //
            while (line[0] == '#' || strlen(line) < 2)
                fgets(line, 200, fpi);
            sscanf(line, "%i %i", &width, &height);
            fgets(line, 200, fpi);
            //
            int n = width * height * 3;
            data = new unsigned char[n];
            for (int i=0; i<n; i++) 
                data[i] = fgetc(fpi);
            fclose(fpi);
         } else {
            printf("ERROR opening image: %s\n",ppmname);
            exit(0);
         }
         if (!ppmFlag) 
            unlink(ppmname);
    }        
};
/*
Image img[9] = {"./images/menu_image.png",
                "./images/game.png",
                "./images/clouds.png",
                "./images/space.png",
                "./images/title.png",
                "./images/deep_logo.png",
                "./images/tank.png",
                "./images/enemy.png",
                "./images/enemy2.png"};


unsigned char *buildAlphaData(Image *img)
{
    int i;
    int a,b,c;
    unsigned char *newdata, *ptr;
    unsigned char *data = (unsigned char *)img->data;
    newdata = (unsigned char *)malloc(img->width * img->height * 4);
    ptr = newdata;
    for (i=0; i<img->width * img->height * 3; i+=3) {
        a = *(data+0);
        b = *(data+1);
        c = *(data+2);

        *(ptr+3) = (a|b|c);

        ptr += 4;
        data += 3;
    }
    return newdata;
}*/

#endif //IMAGES_H
