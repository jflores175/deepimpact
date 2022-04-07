/* Julius Flores */ 
#include <stdio.h>
#include <string.h>
#include <GL/glx.h>
#include "credits.h"

void printnamejulius() 
{
	printf("Julius\n");
}

void reset_position() 
{
	
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
