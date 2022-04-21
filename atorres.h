#ifndef ATORRES_H
#define ATORRES_H

class Menu
{
public:
	bool display;
	bool pause;
	Menu();

	// As of right now it should set the background for the menu
	void show_menu(int red, int green, int blue, int xres, int yres);
	
	// This function will print out message from this file
	void name();
	
	// Function to print out a string
	void output(int xpos, int ypos, char* sent);
	
	// Function that should pause the game current game and show some options
	void pause_screen(int red, int green, int blue, int xres, int yres);
	
	void credit_page(int xres, int yres);
	~Menu();
	
};

void atorres(int x, int y);

#endif
