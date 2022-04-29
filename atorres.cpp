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

// Function for Midterm ---------------------------------
void atorres(int x, int y)                                      
{            
    if (x >= y)    
        printf("%i falls outside the range\n", x);
    else 
        printf("%i is not outside the range\n", x);  
}

//-------------------------------------------------------
Menu::Menu() 
{
    display = true;
    pause = false;
}

// pass in rgb values to change color of created window
void Menu::show_menu(int red, int green, int blue, int xres, int yres)
{
    glColor3ub(red,green,blue);
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

void Menu::pause_screen(int red, int green, int blue, int xres, int yres)
{
	show_menu(0,0,0, xres, yres);
	glColor3ub(red,green,blue);
    glPushMatrix();
    //Build a square and give it vertices 
    glBegin(GL_QUADS);
    glVertex2f( xres/4, yres/4);
    glVertex2f( (xres/4)*3, yres/4);
    glVertex2f( (xres/4)*3, (yres/4)*3);
    glVertex2f( xres/4, (yres/4)*3);
    glEnd();
    glPopMatrix();
}

void Menu::credit_page(int xres, int yres)
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

void Menu::show_controls()
{
    printf("KeyBindings\n");
    printf("-----------\n");
    printf("Arrow keys to move\n");
    printf("Space to shoot\n");
    printf("'f' to show names and midterm function\n");
    printf("'Esc' to exit the game\n");
    printf("'r' to reset your position\n");
} 

void Menu::terminal_text()
{
    //output the controls 
}

void Menu::name()
{
    printf("Alex\n");
}


Menu::~Menu()
{
}

