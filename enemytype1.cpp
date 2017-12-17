#include "enemytype1.h"

EnemyType1::EnemyType1(int w,int h, int livesStep) : Enemy(w,h)
{
    lives = 1+livesStep;
    speed = 1;
    price = 10;

}
