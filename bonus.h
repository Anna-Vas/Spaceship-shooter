#ifndef BONUS_H
#define BONUS_H
#include <QtGui>

class bonus
{
public:
    bonus(int w, int h);
    bool move(int h);
    void draw(QPainter &painter);
    QPoint return_point();
public:
    QPoint point;
    int v = 15;
};

#endif // BONUS_H
