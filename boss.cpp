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
    painter.drawImage(0, point.y(), QImage(":/img/boos4.png").scaled(2*260, 2*50));
}

void boss::BossMinusLives()
{
    lives--;
}

Bullet boss::attack_1()
{
    Bullet bul(point+QPoint(n,0),2);
    n+=75;
    if(n>x/2) n = -x/2;
    return bul;
}
