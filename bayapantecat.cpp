//Author: Bryan Ayapantecatl
//Course: CMPS 3350
//Assign: Gaming Project
//Manage: Enemy Projectiles

#include <unistd.h>
#include <stdio.h>
#include <iostream>
#include "bayapantecat.h"
#include "jflores.h"

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

EnemyShip::EnemyShip()
{
    pos[0] = (Flt)(640);              
    pos[1] = (Flt)(240);              
    pos[2] = 0.0f;    
    radius = 5;                              
    VecZero(vel);          
    angle = 270.0;
    move = 0;
}

void EnemyShip::rightLeft()
{
     //Left = 0 Right = 1
    if (move == 0)
    {
        shift_position(pos, -5, 0);
        if (pos[0] < 0)
            move = 1;
    }

    if (move == 1)
    {
        shift_position(pos, 5, 0);
        if (pos[0] > 640)
            move = 0;
    }
}