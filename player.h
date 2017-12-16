#ifndef PLAYER_H
#define PLAYER_H
#include <QtGui>
class Player
{
public:
    Player(int w,int h);
    void move(int w,int h,QKeyEvent *k);
    //void attack(QKeyEvent *k);
    void draw(QPainter &painter);
    QPoint getPoint();
private:
    QPoint point;
    int vx,vy;
    int r = 20;
};

#endif // PLAYER_H
