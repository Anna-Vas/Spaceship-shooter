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
    bool is_expld = false;
    void draw(QPainter &painter);
    QPoint getPoint();
    void explode(QPainter &painter);
   
    int lives;
protected:
    int speed;
    int price;

    QPoint point;
   // QPoint b;
};

#endif // ENEMY_H
