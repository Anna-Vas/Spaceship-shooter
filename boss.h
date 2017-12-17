#ifndef BOSS_H
#define BOSS_H
#include <QtGui>
#include <QTimer>
#include <bullet.h>

class boss
{
public:
    boss(int w, int h);
    int get_lives();
    void draw(QPainter &painter);
    Bullet attack_1();
private:
    QPoint point;
    int lives;
    int x, y;
    int n = 0;
};

#endif // BOSS_H
