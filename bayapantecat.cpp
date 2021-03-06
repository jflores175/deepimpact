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
    radius = 10;                              
    VecZero(vel);          
    angle = 270.0;
    move = 0;
    path = 1;
    prev = NULL;
    next = NULL;
}

void EnemyShip::flight() 
{
    if (path == 1)
        rightLeft();
    if (path == 2)
        zpattern();
    if (path == 3)
        diamond_ccwise();
    if (path == 4)
        diamond_cwise();
    if (path == 5)
        zigzag();
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

void EnemyShip::zpattern() {
    if (move == 0) 
    {
        shift_position(pos, 0, 3);
        if (pos[1] >= 480) {
            move = 1;
        }
    }
    if (move == 1) {
        shift_position(pos, -2, -3);
        if (pos[1] <= 0) {
            move = 2;
        }
    }
    if (move == 2) {
        shift_position(pos, -2, 3);
        if (pos[1] >= 480) {
            move = 3;
        }
    }
    if (move == 3) {
        shift_position(pos, 2, -3);
        if (pos[1] <= 0) {
            move = 4;
        }
    }
    if (move == 4) {
        shift_position(pos, 2, 3);
        if (pos[1] >= 480) {
            move = 1;
        }
    }
}