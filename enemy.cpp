#include "enemy.h"

Enemy::Enemy(int w, int h)
{
    point.setX(rand()%w);
    point.setY(10);
}

bool Enemy::move(int h)
{
    point+=QPoint(0,speed);
    if(point.y()+r>=h)
        return false;
    return true;
}

Bullet Enemy::shoot()
{
    Bullet ammo(point,2);
    return ammo;
}

