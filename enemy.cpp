#include "enemy.h"

Enemy::Enemy(int w, int h)
{
    point.setX(rand()%w);
    point.setY(10);
}

void Enemy::move(int w, int h)
{
    point+=QPoint(0,speed);
}

Bullet Enemy::shoot()
{
    Bullet ammo(point,2);
    return ammo;
}

