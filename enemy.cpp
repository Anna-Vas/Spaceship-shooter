#include "enemy.h"

Enemy::Enemy(int w, int h)
{
    point.setX(rand()%w);
    point.setY(10);
}

bool Enemy::move(int h)
{
    point+=QPoint(0,speed);
        if(point.y()+2*15>=h)
            return false;
        return true;
}

Bullet Enemy::shoot()
{
    return Bullet(point,2);
}

void Enemy::draw(QPainter &painter)
{
    painter.drawImage(point.x(), point.y(), QImage(":/img/space-invaders-clipart-ship-10.png").scaled(2*15, 2*15));
}

QPoint Enemy::getPoint()
{
    return point;
}

int Enemy::ReturnLives()
{
    return lives;
}

void Enemy::MinusLives()
{
    lives--;
}
