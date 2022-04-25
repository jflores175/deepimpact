//Author: Bryan Ayapantecatl
//Course: CMPS 3350
//Assign: Gaming Project
//Manage: Enemy Projectiles

#include <stdio.h>
#include <iostream>
#include "bayapantecat.h"

typedef float Vec[3];
#define VecZero(v) (v)[0]=0.0,(v)[1]=0.0,(v)[2]=0.0

using namespace std;

void show_name()
{
    printf("Bryan\n");
}

void bayapantecat(int test)
{
    cout << "Please give me a positive nubmer: " << test << endl;

    if (test > 0)
        cout << "Congrats! It's positive!" << endl;
    else
        cout << "TEST FAILED!" << endl;
}

/*
class EnemyShip
{
    public:
        Vec pos;          //Ship Position vector 
        Vec vel;          //Ship Velocity vector
    public:
        EnemyShip() 
        {   //EnemyShip Constructor
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
*/