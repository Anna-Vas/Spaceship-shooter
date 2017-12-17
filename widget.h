#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <player.h>
#include <QPainter>
#include <QTimer>
#include <bullet.h>
#include <boss.h>
#include <enemy.h>
#include <enemytype1.h>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT
    Player *player;
    boss *Boss;
    QList <Bullet> bullets;
    QList <Bullet>::iterator iter;
    QList <Bullet> rbullets;
    QList <Bullet>::iterator riter;
    QList <EnemyType1> enemies;
    QList <EnemyType1>::iterator eiter;
public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    void paintEvent(QPaintEvent *e);
    void keyPressEvent(QKeyEvent *k);
    void stage1();
    void stage2();
    void stage3();
    void stage4();
    void stageBoss();

public slots:
    void MoveAll();
    bool moverect();
private:
    bool is_enemy = false;
    Ui::Widget *ui;
    QTimer timer;
    QTimer timerer;
    QTimer pause;
    bool shooted = false;
    bool rshooted = false;
    bool asd = false;
    int stage = 1;
    bool boss_exist = false;
    int boss_lives = 20;
    int lives;
protected:
    bool s = true;
};

#endif // WIDGET_H
