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
// This function will track the number of times a user has
//      fired a shot. If it was the first then a message
//      will let the player know.
// -----------------------------------------------------------
void display_imacias(bool start_shooting)
{
    static int shot_count = 0;

    if (start_shooting == false)
    {
        printf("(imacias) First shot fired!\n");
        shot_count++;
    }
    else
    {
        printf("(imacias) Shots fired: %i\n", shot_count);
    }
    shot_count++;
}

#include "images.h"

Image img[10] = {"./images/menu_image.png",
                 "./images/game.png",
                 "./images/clouds.png",
                 "./images/space.png",
                 "./images/title.png",
                 "./images/deep_logo.png",
                 "./images/tank1.png",
                 "./images/enemy.png",
                 "./images/enemy2.png",
                 "./images/blue_beam.png"};

// -----------------------------------------------------------------------
// This will set the background color to a dark blue if any of the images
//      fail to load
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
void Background::add_image_level(int u, int x, int y)
{
    float w = 325.0;
    glPushMatrix();
    glTranslatef(x/2, y/2, 0);
    glColor3ub(255, 255, 255);
    glBindTexture(GL_TEXTURE_2D, img[u].textid);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 1.0f); glVertex2f(-w, -w);
        glTexCoord2f(0.0f, 0.0f); glVertex2f(-w,  w);
        glTexCoord2f(1.0f, 0.0f); glVertex2f( w,  w);
        glTexCoord2f(1.0f, 1.0f); glVertex2f( w, -w);
    glBindTexture(GL_TEXTURE_2D, 0);
    glEnd();
    glPopMatrix();
}

// ------------------------------------------------------------------
// This function will load the background image based on the current
//      level being played.
// ------------------------------------------------------------------
void Background::load_game_background(int level, int x, int y)
{
    if (level == 1)
    {
        add_image_level(level, x, y);
    }

    // pending new levels
}

// -----------------------------------------------------------------
// This function check whether the user in on the menu screen.
//      If so, it will render the menu images such as the game logo,
//      and start button.
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
// --------------------------------------------------------------------------
// This function will load enemy sprite based on current level.
// --------------------------------------------------------------------------
void Enemy::draw_enemy(int element_num)
{     
    float s = 64.0; 
    glPushMatrix();
    glColor3ub(255, 255, 255); 
    glBindTexture(GL_TEXTURE_2D, img[element_num].textid);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f); 
        glVertex2f(-s,  -s);
        glTexCoord2f(1.0f, 0.0f); 
        glVertex2f(-s,   s);
        glTexCoord2f(1.0f, 1.0f); 
        glVertex2f( s,   s);
        glTexCoord2f(0.0f, 1.0f); 
        glVertex2f( s,  -s);
    glBindTexture(GL_TEXTURE_2D, 0);
    glEnd();
    glPopMatrix();  
}

// --------------------------------------------------------------------------
// This function determines which level the players is currently on and
//      loads the correct enemy based on level.
// --------------------------------------------------------------------------
void Enemy::load_enemy_sprites(int current_level, int img_num)
{
    if (current_level == 1 && img_num == 7)
    {
        draw_enemy(img_num);
    }
    else if (current_level == 2 && img_num == 8)
    {
        draw_enemy(img_num);
    }
}

