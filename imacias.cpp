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
#include "images.h"

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

// -----------------------------------------------------------------------
// This will set the background color to a dark blue if any of the images
//      fail to load
// 	----------------------------------------------------------------------
void Background::color_bg()
{
    glClearColor(0.0, 0.0, 0.15, 0.0);   
}

// Initialize every image in img array
void init_images(Image *img, int size)
{
    for (int i=0; i<size; i++)
    {
        int w = img[i].width;
        int h = img[i].height;
        
        glGenTextures(1, &img[i].textid);
        glBindTexture(GL_TEXTURE_2D, img[i].textid);
    
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
        glTexImage2D(GL_TEXTURE_2D, 0, 3, w, h, 0,
            GL_RGB, GL_UNSIGNED_BYTE, img[i].data);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}

// ---------------------------------------------------------------
// This function will add the background image for the first level
// ---------------------------------------------------------------
void Background::add_image_level(Image *img, int u, int x, int y)
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
void Background::load_game_background(Image *menu_img, int level, int x, int y)
{
    if (level == 1)
    {
        add_image_level(menu_img, level-1, x, y);
    }

    // pending new levels
}

// -----------------------------------------------------------------
// This function check whether the user in on the menu screen.
//      If so, it will render the menu images such as the game logo,
//      and start button.
// -----------------------------------------------------------------
void Background::load_menu_check(Image *im, bool on_menu, int xres, int yres)
{
    int a = 0;
    int b = 1;
    int c = 2;

    if (on_menu)
    {
        // load menu images
        add_menu_image(im, a, xres, yres);
        load_game_logo(im, b, xres);
        blink_text(im, c, xres, yres);
    }
    else
    {
        color_bg();
    }
}

// ---------------------------------------------------------------
// This function will add a background image for the menu screen.
// ---------------------------------------------------------------
void Background::add_menu_image(Image *mnu, int o, int x, int y)
{   
    float w = 325.0;
    glPushMatrix();
    glTranslatef(x/2, y/2, 0);
    glColor3ub(255, 255, 255);
    glBindTexture(GL_TEXTURE_2D, mnu[o].textid);
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
void Background::add_menu_text(Image *text, int a, int x, int y)
{    
    float u = 275.0;
    glColor3ub(255, 255, 255); 
    glPushMatrix();
    glTranslatef(x/2, y/4, 0);
    glBindTexture(GL_TEXTURE_2D, text[a].textid);
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
void Background::blink_text(Image *tx, int tx_size, int x, int y)
{
    // This is to get the button to blink
    static bool flip = 0;
    if (flip == true) {         
        add_menu_text(tx, tx_size, x, y);
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
void Background::load_game_logo(Image *logo, int c, int x)
{ 
    float u = 128.0;
    float f = 64.0; 
    float y = 300.0;

    glColor3ub(255, 255, 255); 
    glPushMatrix();
    glTranslatef(x/2, y, 0);
    glBindTexture(GL_TEXTURE_2D, logo[c].textid);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 1.0f); glVertex2f(-u,  -f);
        glTexCoord2f(0.0f, 0.0f); glVertex2f(-u,   f);
        glTexCoord2f(1.0f, 0.0f); glVertex2f( u,   f);
        glTexCoord2f(1.0f, 1.0f); glVertex2f( u,  -f);
    glBindTexture(GL_TEXTURE_2D, 0);
    glEnd();
    glPopMatrix();    
}

void Tank::draw_tank(Image *us, int model)
{
    float u = 32.0;//64
    float s = 16.0;//32
    glPushMatrix();
    glColor3ub(255, 255, 255); 
    glBindTexture(GL_TEXTURE_2D, us[model-1].textid);
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
void Enemy::draw_enemy(Image *enem, int level)
{  
    float s = 32.0; 
    glPushMatrix();
    glColor3ub(255, 255, 255); 
    glBindTexture(GL_TEXTURE_2D, enem[level].textid);
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
void Enemy::load_enemy_sprites(Image *e, int current_level)
{
    if (current_level == 1)
    {
        draw_enemy(e, current_level-1);
    }
    else if (current_level == 2)
    {
        draw_enemy(e, current_level-2);
    }
}

