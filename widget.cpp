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
    Boss = new boss(width(), height());
    boss_lives = 20;
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
    if(boss_exist)
    {
        Boss->draw(painter);
    }
    if(shooted)
    {
        if(!bullets.empty())
        for (iter = bullets.begin(); iter != bullets.end(); iter++)
        {
            iter->draw(painter);
        }
    }
    if(rshooted)
    {
        if(!rbullets.empty())
        for (riter = rbullets.begin(); riter != rbullets.end(); riter++)
        {
            riter->draw(painter);
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

void Widget::stage1()
{
    for(int i = 0; i<2; i++)
    {
        enemies.push_back(EnemyType1(width(), height(),livesStep));
        is_enemy = true;
    }
}

void Widget::stage2()
{
    for(int i = 0; i<3; i++)
    {
        enemies.push_back(EnemyType1(width(), height(),livesStep));
        is_enemy = true;
    }
}

void Widget::stage3()
{
    for(int i = 0; i<4; i++)
    {
        enemies.push_back(EnemyType1(width(), height(),livesStep));
        is_enemy = true;
    }
}

void Widget::stage4()
{
    for(int i = 0; i<5; i++)
    {
        enemies.push_back(EnemyType1(width(), height(),livesStep));
        is_enemy = true;
    }
}

void Widget::stageBoss()
{
    timerer.start(1000);
    connect(&timerer,SIGNAL(timeout()),this,SLOT(moverect()));
    qDebug()<<"aa";
    boss_exist = true;
}

void Widget::moverect()
{
   rbullets.push_back(Boss->attack_1());
   qDebug()<<"bb";
}


void Widget::MoveAll()
{
   switch (stage) {
    case 1:

        if(!is_enemy && !boss_exist)
        {
            stage1();
            stage++;
            livesStep+=1;
            qDebug()<<livesStep;
            timerer.stop();
            boss_lives = 20 + livesStep;

        }
        break;
    case 2:
        if(!is_enemy)
        {
            stage2();
            stage++;
        }
        break;
    case 3:
        if(!is_enemy)
        {
            stage3();
            stage++;
        }
        break;
    case 4:
        if(!is_enemy)
        {
            stage4();
            stage++;
        }
        break;
    case 5:
        if(!is_enemy)
        {
            if(!boss_exist)
            {
                stageBoss();
                stage++;
            }
        }
        break;
    default:
        break;
    }
   if(stage>5) stage = 1;
   if(rshooted)
   {
       for (riter = rbullets.begin(); riter != rbullets.end(); riter++)
       {
           if(!riter->move(width(),height()))
           {
             riter = rbullets.erase(riter);
             if(rbullets.empty()) rshooted = false;
             break;
           }

       }
   }
   if(rshooted)
   {
       for(riter = rbullets.begin();riter!=rbullets.end();riter++)
       {
           int a = riter->getPoint().x();
           int b = riter->getPoint().y();
           int c = player->getPoint().x();
           int d = player->getPoint().y();
         //  qDebug()<<a<<b<<c<<d;
           if((a - c)*(a - c)+(b - d)*(b - d) <= (35)*(35)) {
               lives--;
               riter = rbullets.erase(riter);
               if(rbullets.empty()) rshooted = false;
               break;
           }
           if(lives<=0) {
               game_is_started = false;
               this->close();
           }
       }
   }
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
                   eiter->lives--;
                   if(eiter->lives<=0)
                   {
                       eiter = enemies.erase(eiter);
                       if(enemies.empty()) {
                           is_enemy = false;
                       }
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
       for(eiter = enemies.begin(); eiter != enemies.end(); eiter++){
           if(rand()%1000<7)
           {
               rbullets.push_back(eiter->shoot());
               rshooted = true;
           }
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
   }
  if(boss_exist)
   {
       for(iter = bullets.begin(); iter != bullets.end(); iter++)
       {
           if(iter->getLast() == 1){
               int b = iter->getPoint().y();
               if(b <= 100)
               {
                   iter = bullets.erase(iter);
                   boss_lives--;
                   break;
               }
           }
           if(boss_lives <= 0)
           {
               qDebug()<<"aa";
               boss_exist = false;
               delete Boss;
               break;
           }
       }
       /*if(((player->getPoint().x()+20 <= Boss->returnX()+35)and(player->getPoint().x()-20 >= Boss->returnX()-35)) and ((player->getPoint().y()+20 <= Boss->returnY()+35)and(player->getPoint().y()-20 >= Boss->returnY()-35)))
           lives--;
       else lives = 0;*/
   }
  // qDebug()<<shooted;
    this->repaint();
}

