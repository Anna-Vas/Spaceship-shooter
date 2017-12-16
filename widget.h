#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <player.h>
#include <QPainter>
#include <QTimer>
#include <bullet.h>
#include <enemy.h>
#include <enemytype1.h>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT
    Player *player;
    QList <Bullet> bullets;
    QList <Bullet>::iterator iter;
    QList <EnemyType1> enemies;
    QList <EnemyType1>::iterator eiter;
public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    void paintEvent(QPaintEvent *e);
    void keyPressEvent(QKeyEvent *k);

public slots:
    void MoveAll();

private:
    bool is_enemy = false;
    Ui::Widget *ui;
    QTimer timer;
    bool shooted = false;
    bool asd = false;

};

#endif // WIDGET_H
