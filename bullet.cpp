#include "bullet.h"


Bullet::Bullet(QPoint SpPoint,int lastAction)
{
    point = SpPoint;
    r = 5;
    last = lastAction;
}

void Bullet::draw(QPainter &painter)
{
    painter.drawEllipse(point,r,r);
}

bool Bullet::move(int w, int h)
{
    switch (last) {
    case 1:
            point -= QPoint(v,0);
            break;
        case 2:
            point += QPoint(0,v);
            break;
        case 3:
            point += QPoint(v,0);
            break;
        case 4:
            point -= QPoint(0,v);
            break;
        default:
            break;
    }
    if(point.x()+r>=w)
    {
        return false;
    }
    if(point.y()+r>=h)
    {
         return false;
    }
    if(point.x()-r<=0)
    {
         return false;
    }
    if(point.y()-r<=0)
    {
        return false;
    }
    return true;
}
