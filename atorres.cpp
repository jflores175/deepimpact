/* Author: Alexis Torres
Purpose: To build a menu for a game and in game HUB 
which will inclide health
Also credit screen
*/
#include "atorres.h"
#include <stdio.h>
#include <string.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glx.h>

class Menu menu;

Menu::Menu() 
{
    display = true;
}

void Menu::show_menu(int xres, int yres)
{
    glColor3ub(250,214,165);
    glPushMatrix();
    //Build a square and give it vertices 
    glBegin(GL_QUADS);
    glVertex2f( 0.0, 0.0);
    glVertex2f( xres, 0.0);
    glVertex2f( xres, yres);
    glVertex2f( 0.0, yres);
    glEnd();
    glPopMatrix();
}

void Menu::name()
{
    printf("Alex\n");
}


Menu::~Menu()
{
}

// Function for Midterm ---------------------------------
void atorres(int x, int y)                                      
{            
    if (x => y)    
        printf("%i falls outside the range", x);
    else 
        printf("%i is not outside the range", x);  
}            
