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

#include <GL/glx.h>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include "imacias.h"
#include "images.h"

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
        //*(ptr+3) = (a|b|c);
        *(ptr+3) = ((a^b)&c);
        ptr += 4;
        data += 3;
    }
    return newdata;
}
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
    printf("\nThe number of shots fired this round: %i\n", shot);
    
    if (shot <= 20)
    {
        printf("GOOD JOB!\nYOU ARE A SHARP SHOOTER!!!\n");
    }
    else
    {
        printf("\nTOO MANY! TRY TO SHOOT LESS!!!\n");
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
    float u = 128.0;
    float f = 64.0; 
    float yres = 300.0;

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

void Tank::draw_tank(Image *user, int model, float *pos)
{
    float u = 32.0;//64
    float s = 16.0;//32
    float angle = 270.0;

    glPushMatrix();
    glTranslatef(pos[0],pos[1],pos[2]);
    glRotatef(angle,0.0f,0.0f,1.0f);
    glColor3ub(255, 255, 255); 
    glBindTexture(GL_TEXTURE_2D, user[model-1].textid);
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
void Enemy::draw_enemy(Image *enemies, int level, float *a)
{  
    float side = 32.0; 
    float ANGLE = 90.0f;
    int w = enemies[level].width;
    int h = enemies[level].height;
    unsigned char *e = buildAlphaData(&enemies[level]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA,
            GL_UNSIGNED_BYTE, e);
    free(e);
    glPushMatrix();
    //glColor3ub(255, 255, 255); 
    glColor4ub(255,255,255,1);
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.0f);
    glTranslatef(a[0], a[1], a[2]);
    glRotatef(ANGLE, 0.0f, 0.0f, 1.0f); 
    glBindTexture(GL_TEXTURE_2D, enemies[level].textid);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f); 
        glVertex2f(-side,  -side);
        glTexCoord2f(1.0f, 0.0f); 
        glVertex2f(-side,   side);
        glTexCoord2f(1.0f, 1.0f); 
        glVertex2f( side,   side);
        glTexCoord2f(0.0f, 1.0f); 
        glVertex2f( side,  -side);
    glBindTexture(GL_TEXTURE_2D, 0);
    glEnd();
    glPopMatrix();  
}

// --------------------------------------------------------------------------
// This function determines which level the players is currently on and
//      loads the correct enemy based on level.
// --------------------------------------------------------------------------
void Enemy::load_enemy_sprites(Image *e, int current_level, float *p)
{
    if (current_level == 1)
    {
        draw_enemy(e, current_level-1, p);
    }
    else if (current_level == 2)
    {
        draw_enemy(e, current_level-2, p);
    }
}

