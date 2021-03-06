// Bryan Ayapantecatl
// Julius Flores
// Ivan Macias
// Alex Torres
// discord bot test

//program: asteroids.cpp
//author:  Gordon Griesel
//date:    2014 - 2021
//mod spring 2015: added constructors
//This program is a game starting point for a 3350 project.
//
//
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <ctime>
#include <cmath>
#include <X11/Xlib.h>
//#include <X11/Xutil.h>
//#include <GL/gl.h>
//#include <GL/glu.h>
#include <X11/keysym.h>
#include <GL/glx.h>
//#include "log.h"
#include "fonts.h"
#include "project.h"
#include "atorres.h"
#include "credits.h"
#include "imacias.h"
#include "bayapantecat.h"
#include "jflores.h"
#include "images.h"

extern class Menu menu;
static int Esc_count = 0;
//defined types
typedef float Flt;
typedef float Vec[3];
//vector has x, y, and magnitude
typedef Flt	Matrix[4][4];

//macros
#define rnd() (((Flt)rand())/(Flt)RAND_MAX)                       //Creates a random float number
#define random(a) (rand()%a)                                      //Creates random number integer
#define VecZero(v) (v)[0]=0.0,(v)[1]=0.0,(v)[2]=0.0               //Fills a 3 element array with zeros
#define MakeVector(x, y, z, v) (v)[0]=(x),(v)[1]=(y),(v)[2]=(z)   //Create and set a 3 element 
#define VecCopy(a,b) (b)[0]=(a)[0];(b)[1]=(a)[1];(b)[2]=(a)[2]    //Copies two 3 element vector a to b
#define VecDot(a,b)	((a)[0]*(b)[0]+(a)[1]*(b)[1]+(a)[2]*(b)[2])   //Calculates the dotproduct of two 3 element vectors
#define VecSub(a,b,c) (c)[0]=(a)[0]-(b)[0]; \
						(c)[1]=(a)[1]-(b)[1]; \
						(c)[2]=(a)[2]-(b)[2]                      //Subtracts vector b from a and stores it in c
//constants
const float timeslice = 1.0f;            //NO DESCRIPTION
const float gravity = -0.2f;             //Gravity Variable
#define PI 3.141592653589793             //Pi value
#define ALPHA 1                          //Alpha value
const int MAX_BULLETS = 11;              //Maximum amount of bullets on the screen
const Flt MINIMUM_ASTEROID_SIZE = 60.0;  //Minimum size asteroids are allowed to exist

//-----------------------------------------------------------------------------
//Setup timers
const double physicsRate = 1.0 / 60.0;          //NO DESCRIPTION; 1/60
const double oobillion = 1.0 / 1e9;             //No DESCRIPTION: 1/1,000,000,000
extern struct timespec timeStart, timeCurrent;  //Seems to be intial time variable
extern struct timespec timePause;               //Seems to hold a time placeholder
extern double physicsCountdown;                 
extern double timeSpan;
extern double timeDiff(struct timespec *start, struct timespec *end); //Subracts the end time from the start time
extern void timeCopy(struct timespec *dest, struct timespec *source); //Copys one time variable to another
//-----------------------------------------------------------------------------

// Global Class
class Global {
public:
    unsigned char keys[65536];
    unsigned int textid;
    int xres, yres;              //X and Y Resolution variables
    
    int credits_state;		     //States whether credit is showing
    
    int shot_count;//testing

    Global() {	//Global Constructor
        xres = 640;              //Sets X Resolution to 640
		yres = 480;              //Sets Y Resolution to 480
		memset(keys, 0, 65536);  //All elements of Keys array get set to 0
		credits_state = 0;       //Credit state initialized to be false
        shot_count = 0;//testing
    }
        //memset(keys, 0, 65536);	
} gl; 
//Global instance named gl


//Ship Class
class Ship {
public:
	Vec pos;          //Ship Position vector 
	Vec dir;          //Ship Direction vector
	Vec vel;          //Ship Velocity vector
	Vec acc;          //Ship Acceleration vector
	float angle;      //Ship Angle variable
	float color[3];   //Ship Color array, 3 elements
public:
	Ship() {   //Ship Constructor
		pos[0] = (Flt)(gl.xres/2);              //Position #1: Half X resolution
		pos[1] = (Flt)(gl.yres/2);              //Position #2: Half Y resolution
		pos[2] = 0.0f;                          //Position #3: 0.0
		VecZero(dir);          //First 3 elements of Direction vector set to 0.0
		VecZero(vel);          //First 3 elements of Velocity vector set to 0.0
		VecZero(acc);          //First 3 elements of Accleration vector set to 0.0
		//angle = 0.0;
		angle = 270.0;                          //Angle set to 270 degrees
		color[0] = color[1] = color[2] = 1.0;   //All 3 elements of color array set to 1.0
	}
};


//Bullet Class
class Bullet {
public:
	Vec pos;                 //Bullet Position vector
	Vec vel;                 //Bullet Veclocity vector
	float color[3];          //Bullet color array, 3 elements
	struct timespec time;    //Bullet time
public:
	Bullet() { } //Bullet Constructor
};


class Game {
public:
	Ship ship;        //Ship object named ship
	
	EnemyShip badGuy;
	EnemyShip enemies[4];

	EnemyShip *ahead2;   //EnemyShip pointer named ahead

	Bullet *barr;     //Bullet pointer named barr
	
	int nbullets;     //Number of bullets
	int nenemies;
	
	struct timespec bulletTimer;       //Bullet Timer 
	struct timespec mouseThrustTimer;  //Mouse Thruster Timer
	bool mouseThrustOn; //Mouse Thrust boolean
public:
	Game() {  //Game constructor
		ahead2 = NULL;                              //Astroid ahead pointer set to NULL
		barr = new Bullet[MAX_BULLETS];            //Bullet barr pointer set to a Bullet array of MAX_BULLETS = 11

		nenemies = 0;                         //Zero asteroids
		nbullets = 0;                              //Zero bullets
		mouseThrustOn = false;                     //Mouse Thrust OFF
		
		//build 4 enemyships
		
		int path = 1;
		for (int j = 0; j<5; j++) {
			EnemyShip *e = new EnemyShip;

			//e->pos[0] = (Flt)(rand() % gl.xres);      
			//e->pos[1] = (Flt)(rand() % gl.yres);

			e->path = path;


			//enemies[j] = *e;
			e->next = ahead2;
			if (ahead2 != NULL) {
				ahead2->prev = e;
			}
			ahead2 = e;
			nenemies++;
			path++;
		}
		




		clock_gettime(CLOCK_REALTIME, &bulletTimer);
	}
	~Game() { //Destructor
		delete [] barr; //Delete Bullet object
	}
} g;
// Game instance named g


//X Windows variables
class X11_wrapper {
private:
	Display *dpy;
	Window win;
	GLXContext glc;
public:
	X11_wrapper() { }
	X11_wrapper(int w, int h) {
		GLint att[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };
		//GLint att[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, None };
		XSetWindowAttributes swa;
		setup_screen_res(gl.xres, gl.yres);
		dpy = XOpenDisplay(NULL);
		if (dpy == NULL) {
			std::cout << "\n\tcannot connect to X server" << std::endl;
			exit(EXIT_FAILURE);
		}
		Window root = DefaultRootWindow(dpy);
		XWindowAttributes getWinAttr;
		XGetWindowAttributes(dpy, root, &getWinAttr);
		int fullscreen = 0;
		gl.xres = w;
		gl.yres = h;
		if (!w && !h) {
			//Go to fullscreen.
			gl.xres = getWinAttr.width;
			gl.yres = getWinAttr.height;
			//When window is fullscreen, there is no client window
			//so keystrokes are linked to the root window.
			XGrabKeyboard(dpy, root, False,
				GrabModeAsync, GrabModeAsync, CurrentTime);
			fullscreen=1;
		}
		XVisualInfo *vi = glXChooseVisual(dpy, 0, att);
		if (vi == NULL) {
			std::cout << "\n\tno appropriate visual found\n" << std::endl;
			exit(EXIT_FAILURE);
		} 
		Colormap cmap = XCreateColormap(dpy, root, vi->visual, AllocNone);
		swa.colormap = cmap;
		swa.event_mask = ExposureMask | KeyPressMask | KeyReleaseMask |
			PointerMotionMask | MotionNotify | ButtonPress | ButtonRelease |
			StructureNotifyMask | SubstructureNotifyMask;
		unsigned int winops = CWBorderPixel|CWColormap|CWEventMask;
		if (fullscreen) {
			winops |= CWOverrideRedirect;
			swa.override_redirect = True;
		}
		win = XCreateWindow(dpy, root, 0, 0, gl.xres, gl.yres, 0,
			vi->depth, InputOutput, vi->visual, winops, &swa);
		//win = XCreateWindow(dpy, root, 0, 0, gl.xres, gl.yres, 0,
		//vi->depth, InputOutput, vi->visual, CWColormap | CWEventMask, &swa);
		set_title();
		glc = glXCreateContext(dpy, vi, NULL, GL_TRUE);
		glXMakeCurrent(dpy, win, glc);
		show_mouse_cursor(0);
	}
	~X11_wrapper() {
		XDestroyWindow(dpy, win);
		XCloseDisplay(dpy);
	}
	void set_title() {
		//Set the window title bar.
		XMapWindow(dpy, win);
		XStoreName(dpy, win, "Asteroids template");
	}
	void check_resize(XEvent *e) {
		//The ConfigureNotify is sent by the
		//server if the window is resized.
		if (e->type != ConfigureNotify)
			return;
		XConfigureEvent xce = e->xconfigure;
		if (xce.width != gl.xres || xce.height != gl.yres) {
			//Window size did change.
			reshape_window(xce.width, xce.height);
		}
	}
	void reshape_window(int width, int height) {
		//window has been resized.
		setup_screen_res(width, height);
		glViewport(0, 0, (GLint)width, (GLint)height);
		glMatrixMode(GL_PROJECTION); glLoadIdentity();
		glMatrixMode(GL_MODELVIEW); glLoadIdentity();
		glOrtho(0, gl.xres, 0, gl.yres, -1, 1);
		set_title();
	}
	void setup_screen_res(const int w, const int h) {
		gl.xres = w;
		gl.yres = h;
	}
	void swapBuffers() {
		glXSwapBuffers(dpy, win);
	}
	bool getXPending() {
		return XPending(dpy);
	}
	XEvent getXNextEvent() {
		XEvent e;
		XNextEvent(dpy, &e);
		return e;
	}
	void set_mouse_position(int x, int y) {
		XWarpPointer(dpy, None, win, 0, 0, 0, 0, x, y);
	}
	void show_mouse_cursor(const int onoff) {
		if (onoff) {
			//this removes our own blank cursor.
			XUndefineCursor(dpy, win);
			return;
		}
		//vars to make blank cursor
		Pixmap blank;
		XColor dummy;
		char data[1] = {0};
		Cursor cursor;
		//make a blank cursor
		blank = XCreateBitmapFromData (dpy, win, data, 1, 1);
		if (blank == None)
			std::cout << "error: out of memory." << std::endl;
		cursor = XCreatePixmapCursor(dpy, blank, blank, &dummy, &dummy, 0, 0);
		XFreePixmap(dpy, blank);
		//this makes the cursor. then set it using this function
		XDefineCursor(dpy, win, cursor);
		//after you do not need the cursor anymore use this function.
		//it will undo the last change done by XDefineCursor
		//(thus do only use ONCE XDefineCursor and then XUndefineCursor):
	}
} x11(gl.xres, gl.yres);
// ---> for fullscreen x11(0, 0);

//function prototypes
void init_opengl(void);
void check_mouse(XEvent *e);
int check_keys(XEvent *e);
void physics();
void render();

//==========================================================================
// M A I N
//==========================================================================
int main()
{
	//logOpen();
	init_opengl();
	srand(time(NULL));
	clock_gettime(CLOCK_REALTIME, &timePause);
	clock_gettime(CLOCK_REALTIME, &timeStart);
	x11.set_mouse_position(100,100);
	int done=0;
	menu.show_controls();
    while (!done) {
		while (x11.getXPending()) {
			XEvent e = x11.getXNextEvent();
			x11.check_resize(&e);
			//check_mouse(&e); //removed mouse controls
			done = check_keys(&e);
		}
		clock_gettime(CLOCK_REALTIME, &timeCurrent);
		timeSpan = timeDiff(&timeStart, &timeCurrent);
		timeCopy(&timeStart, &timeCurrent);
		physicsCountdown += timeSpan;
		if (menu.pause != true) {
			while (physicsCountdown >= physicsRate) {
				physics();
				physicsCountdown -= physicsRate;
			}
		}
		render();
		x11.swapBuffers();
	}

    // Checks how many shots were fired each round
	check_shots(gl.shot_count);
    display_scoreboard(gl.shot_count);
    cleanup_fonts();
	//logClose();
	return 0;
}

void init_opengl(void)
{     
    //OpenGL initialization
	glViewport(0, 0, gl.xres, gl.yres);
	//Initialize matrices
	glMatrixMode(GL_PROJECTION); glLoadIdentity();
	glMatrixMode(GL_MODELVIEW); glLoadIdentity();
	//This sets 2D mode (no perspective)
	glOrtho(0, gl.xres, 0, gl.yres, -1, 1);
	//
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_FOG);
	glDisable(GL_CULL_FACE);
	//
	//Clear the screen to black
    //glClearColor(0.0, 0.0, 0.0, -1.0);
    
    //Do this to allow fonts
	glEnable(GL_TEXTURE_2D);
	initialize_fonts();
}

void normalize2d(Vec v)
{
	Flt len = v[0]*v[0] + v[1]*v[1];
	if (len == 0.0f) {
		v[0] = 1.0;
		v[1] = 0.0;
		return;
	}
	len = 1.0f / sqrt(len);
	v[0] *= len;
	v[1] *= len;
}

void check_mouse(XEvent *e)
{
	//Did the mouse move?
	//Was a mouse button clicked?
	static int savex = 0;
	static int savey = 0;
	//
	static int ct=0;
	//std::cout << "m" << std::endl << std::flush;
	if (e->type == ButtonRelease) {
		return;
	}
	if (e->type == ButtonPress) {
		if (e->xbutton.button==1) {
			//Left button is down
			//a little time between each bullet
			struct timespec bt;
			clock_gettime(CLOCK_REALTIME, &bt);
			double ts = timeDiff(&g.bulletTimer, &bt);
			if (ts > 0.1) {
				timeCopy(&g.bulletTimer, &bt);
				//shoot a bullet...
				if (g.nbullets < MAX_BULLETS) {
					Bullet *b = &g.barr[g.nbullets];
					timeCopy(&b->time, &bt);
					b->pos[0] = g.ship.pos[0];
					b->pos[1] = g.ship.pos[1];
					b->vel[0] = g.ship.vel[0];
					b->vel[1] = g.ship.vel[1];
					//convert ship angle to radians
					Flt rad = ((g.ship.angle+90.0) / 360.0f) * PI * 2.0;
					//convert angle to a vector
					Flt xdir = cos(rad);
					Flt ydir = sin(rad);
					b->pos[0] += xdir*20.0f;
					b->pos[1] += ydir*20.0f;
					b->vel[0] += xdir*6.0f + rnd()*0.1;
					b->vel[1] += ydir*6.0f + rnd()*0.1;
					b->color[0] = 1.0f;
					b->color[1] = 1.0f;
					b->color[2] = 1.0f;
					++g.nbullets;
				}
			}
		}
		if (e->xbutton.button==3) {
			//Right button is down
		}
	}
	//keys[XK_Up] = 0;
	if (savex != e->xbutton.x || savey != e->xbutton.y) {
		//Mouse moved
		int xdiff = savex - e->xbutton.x;
		int ydiff = savey - e->xbutton.y;
		if (++ct < 10)
			return;		
		//std::cout << "savex: " << savex << std::endl << std::flush;
		//std::cout << "e->xbutton.x: " << e->xbutton.x << std::endl <<
		//std::flush;
		if (xdiff > 0) {
			//std::cout << "xdiff: " << xdiff << std::endl << std::flush;
			g.ship.angle += 0.05f * (float)xdiff;
			if (g.ship.angle >= 360.0f)
				g.ship.angle -= 360.0f;
		}
		else if (xdiff < 0) {
			//std::cout << "xdiff: " << xdiff << std::endl << std::flush;
			g.ship.angle += 0.05f * (float)xdiff;
			if (g.ship.angle < 0.0f)
				g.ship.angle += 360.0f;
		}
		if (ydiff > 0) {
			//apply thrust
			//convert ship angle to radians
			Flt rad = ((g.ship.angle+90.0) / 360.0f) * PI * 2.0;
			//convert angle to a vector
			Flt xdir = cos(rad);
			Flt ydir = sin(rad);
			g.ship.vel[0] += xdir * (float)ydiff * 0.01f;
			g.ship.vel[1] += ydir * (float)ydiff * 0.01f;
			Flt speed = sqrt(g.ship.vel[0]*g.ship.vel[0]+
												g.ship.vel[1]*g.ship.vel[1]);
			if (speed > 10.0f) {
				speed = 10.0f;
				normalize2d(g.ship.vel);
				g.ship.vel[0] *= speed;
				g.ship.vel[1] *= speed;
			}
			g.mouseThrustOn = false;
			clock_gettime(CLOCK_REALTIME, &g.mouseThrustTimer);
		}
		x11.set_mouse_position(100,100);
		savex = 100;
		savey = 100;
	}
}

int check_keys(XEvent *e)
{
    int rand_num = rand() % 1000;
    static bool shot_check = false;
    //int shots = 0;	
    static int shift=0;
	if (e->type != KeyRelease && e->type != KeyPress) {
		//not a keyboard event
		return 0;
	}
	int key = (XLookupKeysym(&e->xkey, 0) & 0x0000ffff);
	//Log("key: %i\n", key);
	if (e->type == KeyRelease) {
		gl.keys[key] = 0;
		if (key == XK_Shift_L || key == XK_Shift_R)
			shift = 0;
		return 0;
	}
	if (e->type == KeyPress) {
		//std::cout << "press" << std::endl;
		gl.keys[key]=1;
		if (key == XK_Shift_L || key == XK_Shift_R) {
			shift = 1;
			return 0;
		}
	}
	(void)shift;
	;
	switch (key) {
		case XK_Escape:
			Esc_count++;
			// used for testing purposes
			//printf("%i", Esc_count);
			menu.pause = true;
			if (Esc_count >= 2)
				return 1;
			break;
		case XK_f:
			printnamejulius();
			menu.name();
			print_my_name();
			bayapantecat(rand_num);
            atorres(100, 420);
            jflores(rand_num);
			break;
		case XK_s:
			menu.display = false;
			Esc_count = 0;
			menu.pause = false;
			//display_imacias(shots);
            break;
		case XK_Down:
			break;
		case XK_equal:
			break;
		case XK_minus:
			break;
        case XK_space:
            gl.shot_count = display_imacias(shot_check);
            //gl.shot_count++;
            shot_check = true;
            break;
        //new
		case XK_c:
			menu.credits = true;
			gl.credits_state = !gl.credits_state;
			break;
		case XK_r:
			reset_position(g.ship.pos); 
		//bew
	}
	return 0;
}


void deleteEnemies(Game *g, EnemyShip *node) 
{
	if (node->prev == NULL) {
		if (node->next == NULL) {
			//only 1 item in list.
			g->ahead2 = NULL;
		} else {
			//at beginning of list.
			node->next->prev = NULL;
			g->ahead2 = node->next;
		}
	} else {
		if (node->next == NULL) {
			//at end of list.
			node->prev->next = NULL;
		} else {
			//in middle of list.
			node->prev->next = node->next;
			node->next->prev = node->prev;
		}
	}
	delete node;
	node = NULL;
}

void physics()
{
	
	Flt d0,d1,dist;

	//g.badGuy.rightLeft();
	//g.badGuy.zpattern();


	//Update ship position
	//g.ship.pos[0] += g.ship.vel[0];
	//g.ship.pos[1] += g.ship.vel[1];
	//Check for collision with window edges
	
	//edit the below to prevent it from going out of bounds
	//Julius Flores
	
	
	detect_edges_ship(g.ship.pos);

	//
	//
	//Update bullet positions
	struct timespec bt;
	clock_gettime(CLOCK_REALTIME, &bt);
	int i = 0;
	while (i < g.nbullets) {
		Bullet *b = &g.barr[i];
		//How long has bullet been alive?
		double ts = timeDiff(&b->time, &bt);
		if (ts > 2.5) {
			//time to delete the bullet.
			memcpy(&g.barr[i], &g.barr[g.nbullets-1],
				sizeof(Bullet));
			g.nbullets--;
			//do not increment i.
			continue;
		}
		//move the bullet
		b->pos[0] += b->vel[0];
		b->pos[1] += b->vel[1];
		//Check for collision with window edges
		
		//delete bullets at edges 
		//jflores

		if (b->pos[0] < 0.0) {
			//b->pos[0] += (float)gl.xres; 
			memcpy(&g.barr[i], &g.barr[g.nbullets-1],
				sizeof(Bullet));
			g.nbullets--;
		}
		else if (b->pos[0] > (float)gl.xres) {
			//b->pos[0] -= (float)gl.xres;
			memcpy(&g.barr[i], &g.barr[g.nbullets-1],
				sizeof(Bullet));
			g.nbullets--;
		}
		else if (b->pos[1] < 0.0) {
			//b->pos[1] += (float)gl.yres;
			memcpy(&g.barr[i], &g.barr[g.nbullets-1],
				sizeof(Bullet));
			g.nbullets--;
		}
		else if (b->pos[1] > (float)gl.yres) {
			//b->pos[1] -= (float)gl.yres;
			memcpy(&g.barr[i], &g.barr[g.nbullets-1],
				sizeof(Bullet));
			g.nbullets--;
		}
		++i;
	}
	
	EnemyShip *e = g.ahead2;

	while (e) 
	{
		e->flight();
		//e->zpattern();
		e = e->next;
	}


	//Enemy collision with bullets?
	//If collision detected:
	//     1. delete the bullet
	//     2. break the asteroid into pieces
	//        if asteroid small, delete it
	e = g.ahead2;
	while (e) 
	{
		//is there a bullet within its radius?
		int i=0;
		while (i < g.nbullets) 
		{
			Bullet *b = &g.barr[i];
			d0 = b->pos[0] - e->pos[0];
			d1 = b->pos[1] - e->pos[1];
			dist = (d0*d0 + d1*d1);

			if (dist < (e->radius*e->radius)) 
			{
				
				//delete the asteroid and bullet
				EnemyShip *savee = e->next;
				deleteEnemies(&g, e);
				e = savee;
				g.nenemies--;
                				                                          
				//delete the bullet...
				memcpy(&g.barr[i], &g.barr[g.nbullets-1], sizeof(Bullet));
				g.nbullets--;
				if (e == NULL)
					break;
			}
			i++;
		}
		if (e == NULL)
			break;
		e = e->next;
	}
	//---------------------------------------------------
	//check keys pressed now


	check_arrow_keys(g.ship.pos, gl.keys);


	if (gl.keys[XK_space]) 
	{
		//a little time between each bullet
		struct timespec bt;
		clock_gettime(CLOCK_REALTIME, &bt);
		double ts = timeDiff(&g.bulletTimer, &bt);

		if (ts > 0.1) 
		{
			timeCopy(&g.bulletTimer, &bt);

			if (g.nbullets < MAX_BULLETS) 
			{
				//shoot a bullet...
				//Bullet *b = new Bullet;
				Bullet *b = &g.barr[g.nbullets];
				timeCopy(&b->time, &bt);
				b->pos[0] = g.ship.pos[0];
				b->pos[1] = g.ship.pos[1];
				b->vel[0] = g.ship.vel[0];
				b->vel[1] = g.ship.vel[1];
				//convert ship angle to radians
				Flt rad = ((g.ship.angle+90.0) / 360.0f) * PI * 2.0;
				//convert angle to a vector
				Flt xdir = cos(rad);
				Flt ydir = sin(rad);
				b->pos[0] += xdir*20.0f;
				b->pos[1] += ydir*20.0f;
				b->vel[0] += xdir*6.0f + rnd()*0.1;
				b->vel[1] += ydir*6.0f + rnd()*0.1;
				b->color[0] = 1.0f;
				b->color[1] = 1.0f;
				b->color[2] = 1.0f;
				g.nbullets++;
			}
		}
	}
	if (g.mouseThrustOn) 
	{
		//should thrust be turned off
		struct timespec mtt;
		clock_gettime(CLOCK_REALTIME, &mtt);
		double tdif = timeDiff(&mtt, &g.mouseThrustTimer);
		//std::cout << "tdif: " << tdif << std::endl;
		if (tdif < -0.3)
			g.mouseThrustOn = false;
	}

}

// --------------------------------------------------------
// Instances of the image class.
// --------------------------------------------------------
Image menu_img[3] = {"./images/menu_image.png",
                     "./images/deep_logo.png",
                     "./images/title.png"};

Image bg[3] = {"./images/game.png",
               "./images/clouds.png",
               "./images/space.png"};

Image user[1] = {"./images/tank1.png"};

Image enemy[2] = {"./images/enemy1.png",
                  "./images/enemy2.png"};
// ----------------------------------------------------------

void render()
{
	Rect r;
	glClear(GL_COLOR_BUFFER_BIT);
	    
    // ----------------------------------------------------   
    Background bg_images;   // Background class from imacias.cpp  
    GameSprite player;        // GameSprite class from imacias.cpp
    GameSprite enemies;

    int game_level = 0;
    
    // --------------------------------------------------------
    // All of these size_of functions will return the length
    //      of each image array to be used to load the images.
    // --------------------------------------------------------
    int size_of_menu = *(&menu_img + 1) - menu_img;  
    init_images(menu_img, size_of_menu);
    
    int size_of_bg = *(&bg + 1) - bg;
    init_images(bg, size_of_bg);
    
    int size_of_user = *(&user + 1) - user;
    init_images(user, size_of_user);
    
    int size_of_enemy = *(&enemy + 1) - enemy;
    init_images(enemy, size_of_enemy);
    //-----------------------------------------------------------
    
    
    //NEW
	//if (gl.credits_state) {
	//	credits.showPage(gl.xres, gl.yres);
	//	return;
	//}
	//NEW
	//
	if(menu.display == true)
	{
		menu.show_menu(250,214,165,gl.xres, gl.yres);
		r.bot = gl.yres - 220;
		r.left = 240;
		r.center = 0;	
		ggprint8b(&r, 16, 0x00ff0000, "Press s to start");
		//menu.output(320,240, "Press F to start");
		
        // ------------------------------------------------------------
        // This method call load_menu_check will use the boolean value 
        //      of menu.display to see if currently on start  menu, then
        //      it will load all images for the menu. When False, it
        //      stop displaying them and move to the next menu. 
        // ------------------------------------------------------------
        bg_images.load_menu_check(menu_img, menu.display, gl.xres, gl.yres);
        
        // exit the game if exit is pressed on the menu screen
        if (Esc_count >= 1)
        	exit(0);
    
    }
    else 
    {
    	if (menu.pause == true)
    	{
    		// render only this portion if the user has pressed Esc
    		// Esc brings the pause menu. To fully exit the game you
    		// press esc again while in the pause menu
    		menu.pause_screen(gl.xres, gl.yres); 
    		r.bot = gl.yres - 110;
			r.left = 140;
			r.center = 0;
			//ggprint8b(&r, 16, 0x00ff0000, "3350 - Asteroids");
			ggprint8b(&r, 16, 0x00000000, "PAUSED");
			ggprint8b(&r, 16, 0x00000000, "---------");
			ggprint8b(&r, 16, 0x00000000, "press Esc to exit");
			ggprint8b(&r, 16, 0x00000000, "press s to continue");
			ggprint8b(&r, 16, 0x00000000, "press c to enter the credits page");
			if (gl.credits_state == true)
			{
				r.bot = gl.yres - 200;
				r.left = 200;
				r.center = 0;	
				// Bryan Ayapantecatl
				// Julius Flores
				// Ivan Macias
				// Alex Torres
				menu.credit_page(gl.xres, gl.yres);
				ggprint8b(&r, 16, 0x00000000, "Thanks your for playing our game");
				ggprint8b(&r, 16, 0x00000000, "Original Artwork by Ivan Macias");
				ggprint8b(&r, 16, 0x00000000, "Enemy projectiles by Bryan Ayapantecatl");
				ggprint8b(&r, 16, 0x00000000, "Controls by Julius Flores");
				ggprint8b(&r, 16, 0x00000000, "Menus by Alexis Torres");
				ggprint8b(&r, 16, 0x00000000, "FrameWork by Gordon Griesel");
			}
    	}
   		else
   		{

	        // ---------------------------------------------------------
	        // This method call will be used to load the image for 
	        //      the first level. Pending multiple levels that
	        //      will create complex functionality to this function.
	        // ---------------------------------------------------------
	        game_level = 1;        
	        bg_images.load_game_background(bg, game_level, gl.xres, gl.yres);
	        //static bool shoot = true;
	        //gl.shot_count = display_imacias(shoot);
	        //check_shots(gl.shot_count);
	        

	        r.bot = gl.yres - 20;
			r.left = 10;
			r.center = 0;
			//ggprint8b(&r, 16, 0x00ff0000, "3350 - Asteroids");
			ggprint8b(&r, 16, 0x00ffff00, "n bullets: %i", g.nbullets);
			ggprint8b(&r, 16, 0x00ffff00, "n enemies: %i", g.nenemies);
			//------------------------------------------------------------------
	        
	        // -----------------------------------------------
	        // This function is from imacias.cpp and will
	        //      draw the shape for the tank, and will 
	        //      add the image for the tank.
	        // -----------------------------------------------
	        int current_model = 0;  // Current player model
            float side1 = 16.0;     // Default size for ship image
            float side2 = 32.0;     // Default size for ship image
            float angle = 270.0;    // Default size for ship image
	        player.draw_sprite(user, current_model, g.ship.pos, side1, side2, angle); //User Tank  
	        
	        if (!gl.keys[XK_Left] || g.mouseThrustOn) {  // original line
				int i;
				//draw thrust
				Flt rad = ((g.ship.angle+90.0) / 360.0f) * PI * 2.0;
				//convert angle to a vector
				Flt xdir = cos(rad);
				Flt ydir = sin(rad);
				Flt xs,ys,xe,ye,r;
				glBegin(GL_LINES);
				for (i=0; i<16; i++) {
					xs = -xdir * 11.0f + rnd() * 4.0 - 2.0;
					ys = -ydir * 11.0f + rnd() * 4.0 - 2.0;
					r = rnd()*40.0+40.0;
					xe = -xdir * r + rnd() * 18.0 - 9.0;
					ye = -ydir * r + rnd() * 18.0 - 9.0;
					glColor3f(rnd()*.3+.7, rnd()*.3+.7, 0);
					glVertex2f(g.ship.pos[0]+xs,g.ship.pos[1]+ys);
					glVertex2f(g.ship.pos[0]+xe,g.ship.pos[1]+ye);
				}
				glEnd();
			}
			//---------------------------------------------------------------------
			//Draw the asteroids
			{
                float img_side = 32.0; // For sizing enemy image
				int enemy_img = 0;     // For loading element from array
                float angle2 = 90.0;   // Default angle for enemy sprite
                //Asteroid *a = g.ahead;
                EnemyShip *e = g.ahead2;
				// Instance of enemy class from imacias.cpp
	            
	            while (e) {
				    // ----------------------------------------
	                // This function creates an enemy sprite
	                //      in place of the asteroids.
	                //      They will be deleted when hit with
	                //      a bullet.
	                // ---------------------------------------- 
	                //
					//important V 
	                
	                //enemies.draw_sprite(enemy, enemy_img, a->pos, img_side, img_side, angle2);
	            	enemies.draw_sprite(enemy, enemy_img, e->pos, img_side, img_side, angle2);
	                
	                // This code is for the enemy that moves back and forth!!!
	                //important ^
					
					glColor3f(1.0f, 0.0f, 0.0f);
					glBegin(GL_POINTS);
					glVertex2f(e->pos[0], e->pos[1]);
					glEnd();
					e = e->next;
	            }
	          }
	        //---------------------------------------------------------------------
			//Draw the bullets        
	        for (int i=0; i<g.nbullets; i++) {
				Bullet *b = &g.barr[i];
				//Log("draw bullet...\n");
				glColor3f(1.0, 1.0, 1.0);
				glBegin(GL_POINTS);
				glVertex2f(b->pos[0],      b->pos[1]);
				glVertex2f(b->pos[0]-1.0f, b->pos[1]);
				glVertex2f(b->pos[0]+1.0f, b->pos[1]);
				glVertex2f(b->pos[0],      b->pos[1]-1.0f);
				glVertex2f(b->pos[0],      b->pos[1]+1.0f);
				glColor3f(0.8, 0.8, 0.8);
				glVertex2f(b->pos[0]-1.0f, b->pos[1]-1.0f);
				glVertex2f(b->pos[0]-1.0f, b->pos[1]+1.0f);
				glVertex2f(b->pos[0]+1.0f, b->pos[1]-1.0f);
				glVertex2f(b->pos[0]+1.0f, b->pos[1]+1.0f);
				glEnd();
			}
        }
	}
}




