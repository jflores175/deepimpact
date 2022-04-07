#ifndef ATORRES_H
#define ATORRES_H

class Menu
{
public:
	bool display;
	Menu();

	// As of right now it should set the background for the menu
	void show_menu(int xres, int yres);
	// This function will print out message from this file
	void name();
	// Function to print out a string
	void output(int xpos, int ypos, char* sent);
	~Menu();
	
};

void atorres(int x, int y);

#endif
