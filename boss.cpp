#include "boss.h"
#include <widget.h>
#include <bullet.h>

boss::boss(int w, int h)
{
    point.setX(w/2);
    point.setY(0);
    lives = 20;
    x = w;

}

int boss::get_lives()
{
    return lives;
}

void boss::draw(QPainter &painter)
{
    painter.drawImage(0, point.y(), QImage(":/images/boos4.png").scaled(2*260, 2*50));
}

Bullet boss::attack_1()
{
    /*x = rand()%300;
    y = rand()%200;
    painter.drawRect(x, y, 70, 70);
    //painter.drawRect(point.x()+100, point.y()+100, 200, 100);
    painter.setBrush(QBrush(QColor::fromRgb(255, 255, 255)));*/

    Bullet bul(point+QPoint(n,0),2);
    n+=75;
    if(n>x/2) n = -x/2;
    return bul;
}
