#include "widget.h"
#include "ui_widget.h"
#include <player.h>
#include <QPainter>
#include <QDebug>
#include <QList>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    player = new Player(width(),height());
    for(int i = 0; i<3; i++)
    {
        enemies.push_back(EnemyType1(width(), height()));
        is_enemy = true;
    }
    timer.start(30);
    connect(&timer,SIGNAL(timeout()),this,SLOT(MoveAll()));
}

Widget::~Widget()
{
    delete ui;
    delete player;
}

void Widget::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    player->draw(painter);
    for(eiter = enemies.begin(); eiter != enemies.end(); eiter++)
        eiter->draw(painter);
    if(shooted)
    {
        if(!bullets.empty())
        for (iter = bullets.begin(); iter != bullets.end(); iter++)
        {
            iter->draw(painter);
        }
    }
}

void Widget::keyPressEvent(QKeyEvent *k)
{
    player->move(width(),height(),k);
    if(k->key()==Qt::Key_Space)
    {
       Bullet ammo(player->getPoint(), 1);
       bullets.push_back(ammo);
       shooted = true;
    }

}


void Widget::MoveAll()
{
   if(shooted){
        for (iter = bullets.begin(); iter != bullets.end(); iter++)
        {
            if(!iter->move(width(),height()))
            {
              iter = bullets.erase(iter);
              if(bullets.empty()) shooted = false;
              break;
            }

        }

    }
   if(is_enemy){
       if(shooted){

   for(iter = bullets.begin(); iter != bullets.end(); iter++)
   {
       for(eiter = enemies.begin(); eiter != enemies.end(); eiter++)
       {
           if(iter->getLast()==1)
           {
               int a = iter->getPoint().x();
               int b = iter->getPoint().y();
               int c = eiter->getPoint().x();
               int d = eiter->getPoint().y();
             //  qDebug()<<a<<b<<c<<d;
               if((a - c)*(a - c)+(b - d)*(b - d) <= (35)*(35)) {
                   eiter = enemies.erase(eiter);
                   if(enemies.empty()) {
                       is_enemy = false;
                   }
               //    qDebug()<<"a";
                   iter = bullets.erase(iter);
                   if(bullets.empty()) shooted = false;
                   asd = true;
                   break;
               }

           }
       }
       if(asd) break;
   }
       }
   }
   if(is_enemy)
   {
       for(eiter = enemies.begin(); eiter != enemies.end(); eiter++)
           if(!eiter->move(height()))
           {

               eiter = enemies.erase(eiter);
               if(enemies.empty()) {
                   is_enemy = false;
               }
                   break;
           }

           //qDebug()<<!eiter->move(height());
   }

  // qDebug()<<shooted;
    this->repaint();
}
