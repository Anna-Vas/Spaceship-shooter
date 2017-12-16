#ifndef BOSS_H
#define BOSS_H
#include <QtGui>
#include <QTimer>

class boss
{
public:
    boss(int w, int h);
    int get_lives();
    void draw(QPainter &painter);
    void attack_1(QPainter &painter);
private:
    QPoint point;
    int lives;
    int x, y;
};

#endif // BOSS_H
