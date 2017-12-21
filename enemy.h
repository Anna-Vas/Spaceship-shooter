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
    int ReturnLives();
    void MinusLives();
protected:
    int speed;
    int lives;
    QPoint point;
   // QPoint b;
};

#endif // ENEMY_H
