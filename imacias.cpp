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

// This function will print out message from this file
void print_my_name() {
	printf("Ivan Macias\n");
	printf("-------------\n");
}

// -----------------------------------------------------------
// This function will contain my Odin username that accepts
//      an argument of type int. If it fails then a response
//      is generated asking to press 's' again.
// -----------------------------------------------------------
void display_imacias(int display_name)
{
    if (display_name > 0 && display_name < 100)
    {
        printf("My odin username is: imacias\n");
    }
    else
    {
        printf("Number not within 1-99\nPress 's' again.\n");
    }
}

#include "images.h"

Image img[10] = {"./images/menu_image.png",
                "./images/game.png",
                "./images/clouds.png",
                "./images/space.png",
                "./images/title.png",
                "./images/deep_logo.png",
                "./images/tank.png",
                "./images/enemy.png",
                "./images/enemy2.png",
                "./images/blue_beam.png"};

// -----------------------------------------------------------------------
// This will set the background color to a dark blue if any of the images
// 	fail to load
// 	----------------------------------------------------------------------
void Background::color_bg()
{
    glClearColor(0.0, 0.0, 0.15, 0.0);   
}

// Initialize every image in img array
void Background::init_images()
{
    int num_imgs = sizeof(img) / sizeof(img[0]);

    for (int i=0; i<num_imgs; i++)
    {
        glGenTextures(1, &img[i].textid);
        glBindTexture(GL_TEXTURE_2D, img[i].textid);
    
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
        glTexImage2D(GL_TEXTURE_2D, 0, 3, img[i].width, img[i].height, 0,
            GL_RGB, GL_UNSIGNED_BYTE, img[i].data);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}

// ---------------------------------------------------------------
// This function will add the background image for the first level
// ---------------------------------------------------------------
void Background::add_image_level(int x, int y)
{
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

// -----------------------------------------------------------------
// This function will add the background image for the second level 
//      in the clouds.
// -----------------------------------------------------------------
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

// -------------------------------------------------------------------------
// This function will add the background image for the third level in space.
// -------------------------------------------------------------------------
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

// -----------------------------------------------------------------
// This function check whether the user in on the menu screen.
// If so, it will render the menu images such as the game logo,
// and start button.
// -----------------------------------------------------------------
void Background::load_menu_check(bool on_menu, int xres, int yres)
{
    if (on_menu)
    {
        // load menu images
        add_menu_image(xres, yres);
        load_game_logo(xres);
        blink_text(xres, yres);
    }
    else
    {
        color_bg();
    }
}

// ---------------------------------------------------------------
// This function will add a background image for the menu screen.
// ---------------------------------------------------------------
void Background::add_menu_image(int x, int y)
{   
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

// ---------------------------------------------------------------------------
// This function will add a non-functional button on the menu screen that says
//      "Press S to Start".
// ---------------------------------------------------------------------------
void Background::add_menu_text(int x, int y)
{    
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

// ----------------------------------------------------------------------------
// This function will make the non-functional button switch between on and off.
//      This means it will and appear, then disappear repeatadly. 
// ----------------------------------------------------------------------------
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

// ----------------------------------------------------------
// This function will add the games logo to the menu screen.
// ----------------------------------------------------------
void Background::load_game_logo(int x)
{ 
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
    glEnd();
    glEnd();
    glPopMatrix();  
}

void Enemy::draw_enemy2()
{
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

