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
#include <unistd.h>
#ifdef USE_OPENAL_SOUND
#include </usr/include/AL/alut.h>
#endif //USE_OPENAL_SOUND

// This function will print out message from this file
void print_my_name() {
	printf("Ivan Macias\n");
	printf("-------------\n");
}

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

Image img[6] = {"./images/menu_image.png",
                "./images/game.png",
                "./images/clouds.png",
                "./images/space.png",
                "./images/title.png",
		"./images/deep_logo.png"};

// This will be for the space level.
// It will set the background color
// 	to a dark blue.
void Background::color_bg()
{
    glClearColor(0.0, 0.0, 0.15, 0.0);   
}

// This is for the first level
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

// This is for the second level in the clouds
//
void Background::add_image_level2(int x, int y)
{
    float w = 325.0;
    glPushMatrix();
    glTranslatef(x/2, y/2, 0);
    glColor3ub(255, 255, 255);
    glBindTexture(GL_TEXTURE_2D, img[2].textid);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 1.0f); glVertex2f(-w, -w);
        glTexCoord2f(0.0f, 0.0f); glVertex2f(-w,  w);
        glTexCoord2f(1.0f, 0.0f); glVertex2f( w,  w);
        glTexCoord2f(1.0f, 1.0f); glVertex2f( w, -w);
    glBindTexture(GL_TEXTURE_2D, 0);
    glEnd();
    glPopMatrix();
}

// This is for the third level in the clouds
//
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

// This function will add the game logo to menu page
void Background::game_logo(int x)
{
   //Define texture maps for background image stream
    glGenTextures(1, &img[5].textid);
    glBindTexture(GL_TEXTURE_2D, img[5].textid);
    //
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, img[5].width, img[5].height, 0,
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

/*
void Background::music() {
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
}*/

// ------------------------------------------------------------------------
//
// Should we do a while loop into a switch statement for multiple levels?
// That way if the user wants to go back to main menu then they have that
// option, and they can choose from various levels we desgin.
//
// ------------------------------------------------------------------------

