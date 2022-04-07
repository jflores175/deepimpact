//Author: Bryan Ayapantecatl
//Course: CMPS 3350
//Assign: Gaming Project
//Manage: Enemy Projectiles

#include <stdio.h>
#include <iostream>
#include "bayapantecat.h"

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
