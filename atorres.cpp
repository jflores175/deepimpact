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
    credits = false;
}

// pass in rgb values to change color of created window
void Menu::show_menu(int red, int green, int blue, int xres, int yres)
{
    glColor3ub(red,green,blue);
    glPushMatrix();
    //Build a square and give it vertices 
    // build a square with fpr vertices
    glBegin(GL_QUADS);
    // top left corner
    glVertex2f( 0.0, 0.0);
    // top right corner
    glVertex2f( xres, 0.0);
    // bottom right corner
    glVertex2f( xres, yres);
    // bottom left corner 
    glVertex2f( 0.0, yres);
    glEnd();
    //connects back to the top left corner and gets ready to render
    glPopMatrix();
}

void Menu::pause_screen(int red, int green, int blue, int xres, int yres)
{
    // create a blank canvas to draw another square
	//show_menu(0,0,0, xres, yres);
	glColor3ub(red,green,blue);
    glPushMatrix();
    //Build a square and give it vertices 
    glBegin(GL_QUADS);
    // divide the screen into quarter sized segments
    // then fill in four center segments to create another rectangle 
    // in the center of the screen 
    glVertex2f( xres/4, yres/4);
    glVertex2f( (xres/4)*3, yres/4);
    glVertex2f( (xres/4)*3, (yres/4)*3);
    glVertex2f( xres/4, (yres/4)*3);
    glEnd();
    glPopMatrix();

}

void Menu::credit_page(int xres, int yres)
{
	// glColor3ub(250,214,165);
	// glPushMatrix();
	// //Build a square and give it vertices 
	// glBegin(GL_QUADS);
	// glVertex2f( 0.0, 0.0);
	// glVertex2f( xres, 0.0);
	// glVertex2f( xres, yres);
	// glVertex2f( 0.0, yres);
	// glEnd();
	//glPopMatrix();

    //blackout the background so the pause menu wont show
    show_menu(0,0,0,xres,yres);
    //output an asteroid like shape that will rotate 
    glColor3ub(95,78,67);
    glPushMatrix();
    glBegin(GL_POLYGON);
    glVertex2f((64*4),(32*14.5)); //1
    glVertex2f((64*5),(32*14)); //2
    glVertex2f((64*8),(32*12)); //3
    glVertex2f((64*7.5),(32*10)); //4
    glVertex2f((64*8),(32*9)); //5
    glVertex2f((64*7),(32*7)); //6
    glVertex2f((64*6),(32*4)); //7
    glVertex2f((64*5),(32*4.5)); //8
    glVertex2f((64*4),(32*2)); //9
    glVertex2f((64*2),(32*3)); //10
    glVertex2f((64*1),(32*8)); //11
    glVertex2f((64*1.5),(32*10)); //12
    glVertex2f((64*3),(32*12)); //13
    glVertex2f((64*3.5),(32*14)); //14
    glEnd();
    glPopMatrix();
    //dark spot on credit asteroid, to make it look better
    //spot located in bottom left of the asteroid
    glColor3ub(71,57,48);
    glPushMatrix();
    glBegin(GL_POLYGON);
    glVertex2f((64*2.5),(32*7)); //1
    glVertex2f((64*2.75),(32*6.85)); //2
    glVertex2f((64*3),(32*6)); //3
    glVertex2f((64*2.65),(32*5.5)); //4
    glVertex2f((64*2.5),(32*3)); //5
    glVertex2f((64* 2.25),(32*3.5)); //6
    glVertex2f((64*2),(32*6)); //7
    glVertex2f((64*2.35),(32*6.5)); //8
    glEnd();
    glPopMatrix();

    //dark spot number 2
    //located at top left 
    glColor3ub(71,57,48);
    glPushMatrix();
    glBegin(GL_POLYGON);
    glVertex2f((64*3),(32*10.7)); //1
    glVertex2f((64*3.25),(32*10)); //2
    glVertex2f((64*3),(32*9.5)); //3 
    glVertex2f((64*2),(32*10)); //4
    glVertex2f((64*2.5),(32*11)); //5 
    glEnd();
    glPopMatrix();
   
    //dark spot number 3
    //located at top 
    glColor3ub(71,57,48);
    glPushMatrix();
    glBegin(GL_POLYGON);
    glVertex2f((64*4),(32*13)); //1 
    glVertex2f((64*4.5),(32*12.5)); //2
    glVertex2f((64*4.25),(32*11.5)); //3
    glVertex2f((64*4),(32*12)); //4
    glVertex2f((64*3.5),(32*12)); //5
    glEnd();
    glPopMatrix();

    //dark spot number 4
    //located at the center 
    glColor3ub(71,57,48);
    glPushMatrix();
    glBegin(GL_POLYGON);
    glVertex2f((64*4.5),(32*10)); //1
    glVertex2f((64*4.5),(32*9)); //2
    glVertex2f((64*4.9),(32*8.5)); //3
    glVertex2f((64*4.25),(32*8.5)); //4
    glVertex2f((64*4),(32*8)); //5
    glVertex2f((64*3.5),(32*8.25)); //6
    glVertex2f((64*3.9),(32*9)); //7
    glEnd();
    glPopMatrix();

    //darkspot number 5
    //located at the bottom right 
    glColor3ub(71,57,48);
    glPushMatrix();
    glBegin(GL_POLYGON);
    glVertex2f((64*6),(32*7)); // 1 
    glVertex2f((64*6.5),(32*6.75)); // 2
    glVertex2f((64*6.15),(32*6.25)); // 3
    glVertex2f((64*6.5),(32*5.75)); // 4
    glVertex2f((64*6),(32*6)); // 5
    glVertex2f((64*5.75),(32*6.5)); // 6
    glEnd();
    glPopMatrix();

}


// print the controls to the terminal so the user 
// can see what the keybindins are
void Menu::show_controls()
{
    printf("KeyBindings\n");
    printf("-----------\n");
    printf("Arrow keys to move\n");
    printf("Space to shoot\n");
    printf("'f' to show names and midterm function\n");
    printf("'Esc' to open the pause menu\n");
    printf("'r' to reset your position\n");
} 


void Menu::name()
{
    printf("Alex\n");
}


Menu::~Menu()
{
}

