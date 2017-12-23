#include "bonus.h"

bonus::bonus(int w, int h)
{
    point.setX(rand()%w);
    point.setY(10);
}

bool bonus::move(int h)
{
    point+=QPoint(0,v);
    if(point.y()+2*15>=h)
        return false;
    return true;
}

void bonus::draw(QPainter &painter)
{
    painter.drawImage(point.x(), point.y(), QImage(":/images/plus_lives.png").scaled(2*15, 2*15));
}

QPoint bonus::return_point()
{
    return point;
}
