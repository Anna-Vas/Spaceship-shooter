#ifndef ENEMY_H
#define ENEMY_H
#include <QtGui>
#include <bullet.h>
class Enemy
{
public:
    Enemy(int w,int h);
    void move(int w,int h);
    void shoot();
    void draw(QPainter &painter);
    QPoint getPoint();
private:
    int lives;
    int speed;
    int price;
    QPoint point;
};

#endif // ENEMY_H
