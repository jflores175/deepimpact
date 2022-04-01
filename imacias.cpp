/*
 *  Name: Ivan Macias
 *  Date: Feb 24, 2022
 *
 *  @source: imacias.cpp
 *  
 *  My role is to create and implement the artwork for Deep Impact.
 *  This includes designing the backgrounds for multiple levels, 
 *  create sprites for the in-game character and enemies, and 
 *  adding any effects that we can if there is time. This includes 
 *  adding sound to the game. 
 */

#include <stdio.h>
#include <GL/glx.h>
#include <math.h>
#include "fonts.h"
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include "imacias.h"
#include <cstring>
#include <unistd.h>
#ifdef USE_OPENAL_SOUND
#include </usr/include/AL/alut.h>
#endif //USE_OPENAL_SOUND

typedef float Vec[3];

// This function will print out message from this file
void print_my_name() {
	printf("Ivan Macias\n");
	printf("-------------\n");
}
class Bullet {
    public:
        Vec pos;
        Vec vel;
        Bullet();
};

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

Image img[9] = {"./images/menu_image.png",
                "./images/game.png",
                "./images/clouds.png",
                "./images/space.png",
                "./images/title.png",
                "./images/deep_logo.png",
                "./images/tank.png",
                "./images/enemy.png",
                "./images/enemy2.png"};
/*
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

// ---------------------------------------
// This will set the background color
// 	to a dark blue if any of the images
// 	fail to load
// 	--------------------------------------
void Background::color_bg()
{
    glClearColor(0.0, 0.0, 0.15, 0.0);   
}

// -----------------------------------------
// This function will add the background
//      image for the first level
// -----------------------------------------
void Background::add_image_level(int x, int y)
{
    //Define texture maps for background image stream
    glGenTextures(1, &img[1].textid);
    glBindTexture(GL_TEXTURE_2D, img[1].textid);
    //
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, img[1].width, img[1].height, 0,
        GL_RGB, GL_UNSIGNED_BYTE, img[1].data);
    glBindTexture(GL_TEXTURE_2D, 0);
 
    float w = 325.0;
    glPushMatrix();
    glTranslatef(x/2, y/2, 0);
    glColor3ub(255, 255, 255);
    glBindTexture(GL_TEXTURE_2D, img[1].textid);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 1.0f); glVertex2f(-w, -w);
        glTexCoord2f(0.0f, 0.0f); glVertex2f(-w,  w);
        glTexCoord2f(1.0f, 0.0f); glVertex2f( w,  w);
        glTexCoord2f(1.0f, 1.0f); glVertex2f( w, -w);
    glBindTexture(GL_TEXTURE_2D, 0);
    glEnd();
    glPopMatrix();
}

// -----------------------------------------------
// This function will add the background image
//      for the second level in the clouds.
// -----------------------------------------------
void Background::add_image_level2(int x, int y)
{
    float w = 325.0;
    
    glPushMatrix();
    glTranslatef(x/2, y/2, 0);
    glColor3ub(255, 255, 255);
    glBindTexture(GL_TEXTURE_2D, img[2].textid);
    glBegin(GL_POLYGON);
        glTexCoord2f(0.0f, 1.0f); glVertex2f(-w, -w);
        glTexCoord2f(0.0f, 0.0f); glVertex2f(-w,  w);
        glTexCoord2f(1.0f, 0.0f); glVertex2f( w,  w);
        glTexCoord2f(1.0f, 1.0f); glVertex2f( w, -w);
    glBindTexture(GL_TEXTURE_2D, 0);
    glEnd();
    glPopMatrix();
}

// ---------------------------------------------
// This function will add the background image
//      for the third level in space.
// ---------------------------------------------
void Background::add_image_level3(int x, int y)
{
    float w = 325.0;
    glPushMatrix();
    glTranslatef(x/2, y/2, 0);
    glColor3ub(255, 255, 255);
    glBindTexture(GL_TEXTURE_2D, img[3].textid);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 1.0f); glVertex2f(-w, -w);
        glTexCoord2f(0.0f, 0.0f); glVertex2f(-w,  w);
        glTexCoord2f(1.0f, 0.0f); glVertex2f( w,  w);
        glTexCoord2f(1.0f, 1.0f); glVertex2f( w, -w);
    glBindTexture(GL_TEXTURE_2D, 0);
    glEnd();
    glPopMatrix();
}

// ------------------------------------------------
// This function will add a background image for 
//      the menu screen.
// ------------------------------------------------
void Background::add_menu_image(int x, int y)
{
    //Define texture maps for background image stream
    glGenTextures(1, &img[0].textid);
    glBindTexture(GL_TEXTURE_2D, img[0].textid);
    //
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, img[0].width, img[0].height, 0,
        GL_RGB, GL_UNSIGNED_BYTE, img[0].data);
    glBindTexture(GL_TEXTURE_2D, 0);
    
    float w = 325.0;
    glPushMatrix();
    glTranslatef(x/2, y/2, 0);
    glColor3ub(255, 255, 255);
    glBindTexture(GL_TEXTURE_2D, img[0].textid);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 1.0f); glVertex2f(-w, -w);
        glTexCoord2f(0.0f, 0.0f); glVertex2f(-w,  w);
        glTexCoord2f(1.0f, 0.0f); glVertex2f( w,  w);
        glTexCoord2f(1.0f, 1.0f); glVertex2f( w, -w);
    glBindTexture(GL_TEXTURE_2D, 0);
    glEnd();
    glPopMatrix();
    
}

// ------------------------------------------------
// This function will add a non-functional button
//      on the menu screen that says
//      "Press S to Start".
// ------------------------------------------------
void Background::add_menu_text(int x, int y)
{
    //Define texture maps for background image stream
    glGenTextures(1, &img[4].textid);
    glBindTexture(GL_TEXTURE_2D, img[4].textid);
    //
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, img[4].width, img[4].height, 0,
        GL_RGB, GL_UNSIGNED_BYTE, img[4].data);
    glBindTexture(GL_TEXTURE_2D, 0);
    

    float u = 275.0;
    glColor3ub(255, 255, 255); 
    glPushMatrix();
    glTranslatef(x/2, y/4, 0);
    glBindTexture(GL_TEXTURE_2D, img[4].textid);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 1.0f); glVertex2f(-u,  -40);
        glTexCoord2f(0.0f, 0.0f); glVertex2f(-u,   20);
        glTexCoord2f(1.0f, 0.0f); glVertex2f( u,   20);
        glTexCoord2f(1.0f, 1.0f); glVertex2f( u,  -40);
    glBindTexture(GL_TEXTURE_2D, 0);
    glEnd();
    glPopMatrix();
}

// -------------------------------------------
// This function will make the non-functional
//      button switch between on and off.
//      This means it will and appear, then
//      disappear repeatadly. 
// ------------------------------------------
void Background::blink_text(int x, int y)
{
    // This is to get the button to blink
    static bool flip = 0;
    if (flip == true) {         
        add_menu_text(x, y);
    }
    else 
    {
        flip = 0;
    }
    flip = !flip;
}

// ------------------------------------
// This function will add the games
//      logo to the menu screen.
// ------------------------------------
void Background::game_logo(int x)
{ 
    glGenTextures(1, &img[5].textid);
    glBindTexture(GL_TEXTURE_2D, img[5].textid);
    
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img[5].width, img[5].height, 0,
        GL_RGB, GL_UNSIGNED_BYTE, img[5].data);
    glBindTexture(GL_TEXTURE_2D, 0);
    
    float u = 128.0;
    float f = 64.0; 
    float y = 300.0;

    glColor3ub(255, 255, 255); 
    glPushMatrix();
    glTranslatef(x/2, y, 0);
    glBindTexture(GL_TEXTURE_2D, img[5].textid);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 1.0f); glVertex2f(-u,  -f);
        glTexCoord2f(0.0f, 0.0f); glVertex2f(-u,   f);
        glTexCoord2f(1.0f, 0.0f); glVertex2f( u,   f);
        glTexCoord2f(1.0f, 1.0f); glVertex2f( u,  -f);
    glBindTexture(GL_TEXTURE_2D, 0);
    glEnd();
    glPopMatrix();    
}

void Tank::draw_tank()
{
    glGenTextures(1, &img[6].textid);
    glBindTexture(GL_TEXTURE_2D, img[6].textid);
    
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img[6].width, img[6].height, 0,
        GL_RGB, GL_UNSIGNED_BYTE, img[6].data);
    glBindTexture(GL_TEXTURE_2D, 0);
    
    float u = 64.0;
    float s = 32.0; 
    glPushMatrix();
    glColor3ub(255, 255, 255); 
    glBindTexture(GL_TEXTURE_2D, img[6].textid);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f); 
        glVertex2f(-s,  -u);
        glTexCoord2f(1.0f, 0.0f); 
        glVertex2f(-s,   u);
        glTexCoord2f(1.0f, 1.0f); 
        glVertex2f( s,   u);
        glTexCoord2f(0.0f, 1.0f); 
        glVertex2f( s,  -u);
    glBindTexture(GL_TEXTURE_2D, 0);
    glEnd();
    glPopMatrix();    
}

void Enemy::draw_enemy()
{
    glGenTextures(1, &img[7].textid);
    glBindTexture(GL_TEXTURE_2D, img[7].textid);

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img[7].width, img[7].height, 0,
        GL_RGB, GL_UNSIGNED_BYTE, img[7].data);
    glBindTexture(GL_TEXTURE_2D, 0);

    float u = 64.0;
    float s = 64.0; 
    glPushMatrix();
    glColor3ub(255, 255, 255); 
    glBindTexture(GL_TEXTURE_2D, img[7].textid);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f); 
        glVertex2f(-s,  -u);
        glTexCoord2f(1.0f, 0.0f); 
        glVertex2f(-s,   u);
        glTexCoord2f(1.0f, 1.0f); 
        glVertex2f( s,   u);
        glTexCoord2f(0.0f, 1.0f); 
        glVertex2f( s,  -u);
    glBindTexture(GL_TEXTURE_2D, 0);
    glEnd();
    glPopMatrix();  
}

void Enemy::draw_enemy2()
{
    glGenTextures(1, &img[8].textid);
    glBindTexture(GL_TEXTURE_2D, img[8].textid);

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img[8].width, img[8].height, 0,
        GL_RGB, GL_UNSIGNED_BYTE, img[8].data);
    glBindTexture(GL_TEXTURE_2D, 0);

    float u = 64.0;
    float s = 64.0; 
    glPushMatrix();
    glColor3ub(255, 255, 255); 
    glBindTexture(GL_TEXTURE_2D, img[8].textid);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f); 
        glVertex2f(-s,  -u);
        glTexCoord2f(1.0f, 0.0f); 
        glVertex2f(-s,   u);
        glTexCoord2f(1.0f, 1.0f); 
        glVertex2f( s,   u);
        glTexCoord2f(0.0f, 1.0f); 
        glVertex2f( s,  -u);
    glBindTexture(GL_TEXTURE_2D, 0);
    glEnd();
    glPopMatrix();  
}

/*
void Beam::draw_beams(int num_bullets)
{
    float c = 1.0;
    for (int i=0; i<num_bullets; i++)
    {
        Bullet *barr
        b = &g.barr[i];
        glColor3f(c, c, c);
        glBegin(GL_QUADS);
        glVertex2f(b->pos[0],       b->pos[1]);
        glVertex2f(b->pos[0]-1.0f,  b->pos[1]);
        glVertex2f(b->pos[0]+1.0f,  b->pos[1]);
        glVertex2f(b->pos[0],       b->pos[1]-1.0f);
        glVertex2f(b->pos[0],       b->pos[1]+1.0f); 
    }
}*/


void Background::music() {/*
//Get started right here.
#ifdef USE_OPENAL_SOUND
	alutInit(0, NULL);
	if (alGetError() != AL_NO_ERROR) {
		printf("ERROR: alutInit()\n");
		return 0;
	}
	//Clear error state.
	alGetError();
	//
	//Setup the listener.
	//Forward and up vectors are used.
	float vec[6] = {0.0f,0.0f,1.0f, 0.0f,1.0f,0.0f};
	alListener3f(AL_POSITION, 0.0f, 0.0f, 0.0f);
	alListenerfv(AL_ORIENTATION, vec);
	alListenerf(AL_GAIN, 1.0f);
	//
	//Buffer holds the sound information.
	ALuint alBuffer;
	alBuffer = alutCreateBufferFromFile("mega_man.wav");
	//
	//Source refers to the sound.
	ALuint alSource;
	//Generate a source, and store it in a buffer.
	alGenSources(1, &alSource);
	alSourcei(alSource, AL_BUFFER, alBuffer);
	//Set volume and pitch to normal, no looping of sound.
	alSourcef(alSource, AL_GAIN, 1.0f);
	alSourcef(alSource, AL_PITCH, 1.0f);
	alSourcei(alSource, AL_LOOPING, AL_FALSE);
	if (alGetError() != AL_NO_ERROR) {
		printf("ERROR: setting source\n");
		return 0;
	}
	for (int i=0; i<4; i++) {
		alSourcePlay(alSource);
		usleep(250000);
	}
	//Cleanup.
	//First delete the source.
	alDeleteSources(1, &alSource);
	//Delete the buffer.
	alDeleteBuffers(1, &alBuffer);
	//Close out OpenAL itself.
	//Get active context.
	ALCcontext *Context = alcGetCurrentContext();
	//Get device for active context.
	ALCdevice *Device = alcGetContextsDevice(Context);
	//Disable context.
	alcMakeContextCurrent(NULL);
#endif
    return 0;*/
}

