/* Author: Julius Flores
Purpose: 
Add functionality of controlling the ship
Prevent ship from going off edges
*/

#include <stdio.h>
#include <string.h>
#include <GL/glx.h>
#include "credits.h"
#include "jflores.h"
//#include "defs.h"

void printnamejulius() 
{
	printf("Julius\n");
}

//-----------------------------------------------------------------------------
//resets position of the ship to the left edge of the screen and in the middle
//middle vertically
//-----------------------------------------------------------------------------
void reset_position(Vec pos) 
{
	pos[0] = 0;
	pos[1] = 240;
	pos[2] = 0;
}

void change_position(Vec pos, int x, int y) {
	pos[0] = x;
	pos[1] = y;
	pos[2] = 0;
}


//-----------------------------------------------------------------------------
//detects if the ship has reached the edges of the screen
//if so, prevents the ship from going past it
//-----------------------------------------------------------------------------
void detect_edges_ship(Vec pos, int xres, int yres) 
{
	//detect if position is at edges and if so prevent moving past them 
	//first check corners

	// top left corner
	if (pos[0] < 0.0 && pos[1] > yres) {
		pos[0] = 0;
		pos[1] = yres;
	}
	//bottom left corner
	else if (pos[0] < 0.0 && pos[1] < 0) {
		pos[0] = 0;
		pos[1] = 0;
	}
	// top right corner
	else if (pos[0] > xres && pos[1] > yres) {
		pos[0] = xres;
		pos[1] = yres;
	}
	// bottom right corner
	else if (pos[0] > xres && pos[1] < 0) {
		pos[0] = xres;
		pos[1] = 0;
	}
	// left edge
	else if (pos[0] < 0.0) {
		pos[0] = 0;
	}
	// right edge
	else if (pos[0] > xres) {
		pos[0] = xres; // was -= (float)gl.xres
	}
	// bottom edge
	else if (pos[1] < 0.0) {
		pos[1] = 0; // was += (float)gl.yres
	}
	// top edge
	else if (pos[1] > yres) {
		pos[1] = yres; // was -= (float)gl.yres
	}
}

//----------------------------------------------------
//checks arrow key presses
//then move in their respective directions
//----------------------------------------------------
void check_arrow_keys(Vec pos, unsigned char keys[]) 
{
	// left and right are pos[0]
	// up and down are pos[1]
	if (keys[XK_Left]) 
		pos[0] -= 4;
	if (keys[XK_Right]) 
		pos[0] += 4;
	if (keys[XK_Up])
		pos[1] += 4;
	if (keys[XK_Down])
		pos[1] -= 4;
}

void jflores(int number) 
{
    if (number == 0)
        printf("Your number was 0\n");
    else if (number > 0) 
        printf("Your number was positive\n");
    else
        printf("Your number was negative and failed\n");
}

Credits credits;

/*
void Credits::showPage() 
{
	glColor3ub(255,255,0); //yellow
	glPushMatrix();
	glBegin(GL_TRIANGLES);

	static float rot = 0.0;
	static float angle = 0.0;

	glTranslatef(xres/2, yres/2);
	glRotatef(rot, 0.0f, 0.0f, 1.0f);
	glTranslatef(-xres/2, -yres/2);

	rot = sin(angle) * 20.0;
	angle += 0.05;
	glBegin(GL_TRIANGLES);
		glVertex2f(20.0);
		glVertex2f(xres/2.0,yres-20);
		glVertex2f(x-res-20, 20.0);
		glEnd();
		glPopMatrix();
}
*/
