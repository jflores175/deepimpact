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
        int angle;
        int move;
        EnemyShip();
        void rightLeft();
        void diamond_cwise();
        void diamond_ccwise();
};
