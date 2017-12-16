#ifndef ENEMY_H
#define ENEMY_H
#include <QtGui>
#include <bullet.h>
class Enemy
{
public:
    Enemy(int w,int h);
    bool move(int h);
    Bullet shoot();
    void draw(QPainter &painter);
    QPoint getPoint();
   // bool isCollided();
protected:
    int lives;
    int speed;
    int price;
    QPoint point;
   // QPoint b;
};

#endif // ENEMY_H
