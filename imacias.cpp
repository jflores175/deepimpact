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
#ifdef USE_OPENAL_SOUND
#include </usr/include/AL/alut.h>
#endif //USE_OPENAL_SOUND

typedef double Flt;
typedef double Vec[3];

#define rnd() (((double)rand())/(double)RAND_MAX)

// This function will print out message from this file
void print_my_name() {
	printf("Ivan Macias\n");
	printf("-------------\n"); // Tells what key was pressed
}

//class Level; possibly implement multiple levels: 1-3
//class Sound; possibly implement sound to level

class Info {
    public:
        int x_res, y_res;
        Vec box[20];
        
        Info() {
            x_res = 680;
            y_res = 480;            
            for (int i=0; i<20; i++) {
                box[i][0] = rnd() * x_res;
                box[i][1] = rnd() * (y_res-220) + 220.0;
                box[i][2] = 0.0;
            }
        }
} info;

// This will be for the space level
void Background::color_bg()
{
    glClearColor(0.0, 0.0, 0.15, 0.0);   
}

// This will be for the space level
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

// This is for the first level
void Background::add_bg_image(int x, int y, unsigned int textid)
{
    float w = 325.0;
    glPushMatrix();
    glTranslatef(x/2, y/2, 0);
    glColor3ub(255, 255, 255);
    glBindTexture(GL_TEXTURE_2D, textid);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 1.0f); glVertex2f(-w, -w);
        glTexCoord2f(0.0f, 0.0f); glVertex2f(-w,  w);
        glTexCoord2f(1.0f, 0.0f); glVertex2f( w,  w);
        glTexCoord2f(1.0f, 1.0f); glVertex2f( w, -w);
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


