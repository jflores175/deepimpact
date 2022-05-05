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

#include <iostream>
#include <GL/glx.h>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include "imacias.h"
#include "images.h"
#include <string>
#include <iomanip>

using namespace std;

// This function will print out message from this file
void print_my_name() {
	printf("Ivan Macias\n");
	printf("-------------\n");
}

// -----------------------------------------------------------
// This function will return the number of times a user has
// fired a shot. 
// -----------------------------------------------------------
int display_imacias(bool start_shooting)
{
    static int shot_count = 0;
    
    if (start_shooting)
    {
        shot_count++;
    }
    
    return shot_count;
}

// --------------------------------------------------------------------------
// This function will check how many shots were fired this round.
// If the number is greater than 25, then a message will appear to let the
// user know to be more precise with their shooting.
// --------------------------------------------------------------------------
void check_shots(int shot)
{
    cout << "\nThe number of shots fired this round: " << shot << endl;
    
    if(shot == 0)
    {
        cout << "\nBOO! YOU DIDN'T TAKE ANY SHOTS" << endl;
    }
    else if (shot <= 20)
    {
        cout << "\nGOOD JOB!\nYOU ARE A SHARP SHOOTER!!!" << endl;
    }
    else
    {
        cout << "\nTOO MANY! TRY TO SHOOT LESS!!!" << endl;
        cout << "\n5 POINT PENALTY" << endl;
    } 
}

// -----------------------------------------------------------------------
// This will set the background color to a dark blue if any of the images
// fail to load
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
void Background::add_image_level(Image *img, int u, int xres, int yres)
{
    float w = 325.0;
    glPushMatrix();
    glTranslatef(xres/2, yres/2, 0);
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
// level being played.
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
// If so, it will render the menu images such as the game logo,
// and start button.
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
void Background::add_menu_image(Image *menu, int pic, int xres, int yres)
{   
    float w = 325.0;
    glPushMatrix();
    glTranslatef(xres/2, yres/2, 0);
    glColor3ub(255, 255, 255);
    glBindTexture(GL_TEXTURE_2D, menu[pic].textid);
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
// "Press S to Start".
// ---------------------------------------------------------------------------
void Background::add_menu_text(Image *text, int a, int xres, int yres)
{    
    float u = 275.0;
    glColor3ub(255, 255, 255); 
    glPushMatrix();
    glTranslatef(xres/2, yres/4, 0);
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
// This means it will and appear, then disappear repeatadly. 
// ----------------------------------------------------------------------------
void Background::blink_text(Image *text, int text_size, int x, int y)
{
    // This is to get the button to blink
    static bool flip = 0;
    if (flip == true) {         
        add_menu_text(text, text_size, x, y);
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
void Background::load_game_logo(Image *logo, int c, int xres)
{ 
    float u = 128.0;          // Default size for game logo
    float f = 64.0;           // Default size for game logo
    float const yres = 300.0; // Constant yres for game logo

    glColor3ub(255, 255, 255); 
    glPushMatrix();
    glTranslatef(xres/2, yres, 0);
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

// ----------------------------------------------------------------------------------------------------
// This function will draw every sprite in the game, including the player and enemy.
// ----------------------------------------------------------------------------------------------------
void GameSprite::draw_sprite(Image *user, int model, float *pos, float side1, float side2, float angle)
{
    glPushMatrix();
    glTranslatef(pos[0],pos[1],pos[2]);
    glRotatef(angle,0.0f,0.0f,1.0f);
    glColor3ub(255, 255, 255); 
    glBindTexture(GL_TEXTURE_2D, user[model].textid);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f); 
        glVertex2f(-side1,  -side2);
        glTexCoord2f(1.0f, 0.0f); 
        glVertex2f(-side1,   side2);
        glTexCoord2f(1.0f, 1.0f); 
        glVertex2f( side1,   side2);
        glTexCoord2f(0.0f, 1.0f); 
        glVertex2f( side1,  -side2);
    glBindTexture(GL_TEXTURE_2D, 0);
    glEnd();
    glPopMatrix();    
}

// --------------------------------------------------------
// This function will display user score in a leaderboard
// --------------------------------------------------------
void display_leaderboard(int score)
{
    int width = 4;
    string username;

    if (score == 0)
    {
       cout << "\nLeaderboard is for those who play!" << endl;
    }
    else
    {
        cout << "\nEnter a username (3 LETTERS): ";
        getline(cin, username);
        
        for (auto & letter: username) letter = toupper(letter);

        if (score > 20)
            score +=5;

        cout << "\n| Player | SCORE |" << endl;
        cout << "   "         << username
             << setw(width)   << ":" 
             << setw(width+1) <<  score << endl;
    }
}
