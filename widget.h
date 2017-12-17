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
    void switch_choose(QKeyEvent *k);
public slots:
    void MoveAll();
    bool moverect();
    void stop();
private:
    bool is_enemy = false;
    Ui::Widget *ui;
    QTimer timer;
    QTimer timerer;
    bool shooted = false;
    bool rshooted = false;
    bool asd = false;
    int stage = 1;
    bool boss_exist = false;
    int boss_lives = 20;
    int lives = 5;
    int livesStep = 0;
    bool game_is_started = false;
    int score = 0;
    int choose = 1;
    bool expld = false;
    int MaxScore = 0;

protected:
    bool s = true;
private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_lcdNumber_overflow();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
};

#endif // WIDGET_H
