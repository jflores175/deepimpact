//Author: Bryan Ayapantecatl
//Course: CMPS 3350
//Assign: Gaming Project
//Manage: Enemy Projectiles
typedef float Vec[3];
typedef float Flt;
#define VecZero(v) (v)[0]=0.0,(v)[1]=0.0,(v)[2]=0.0

using namespace std;

void show_name();
void bayapantecat(int test);

class EnemyShip
{
    public:
        Vec pos;          //Ship Position vector 
        Vec vel;          //Ship Velocity vector
        Flt radius;          //Ship radius for enemy ship
        int angle;
        int move;
        int path;
        
        struct EnemyShip *prev;
        struct EnemyShip *next;


        //constructor
        EnemyShip();
        void flight();
        void rightLeft();
        void diamond_cwise();
        void diamond_ccwise();
        void zpattern();
};
