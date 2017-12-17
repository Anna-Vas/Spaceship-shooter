#include "widget.h"
#include "ui_widget.h"
#include <player.h>
#include <QPainter>
#include <QDebug>
#include <QList>
#include <QMessageBox>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);


    ui->label->hide();
    ui->label_2->hide();
    ui->lcdNumber->hide();
    ui->lcdNumber_2->hide();

}

Widget::~Widget()
{
    delete ui;
    delete player;
}

void Widget::paintEvent(QPaintEvent *e)
{
    if(game_is_started) {
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
}

void Widget::keyPressEvent(QKeyEvent *k)
{
    if(game_is_started) {
        player->move(width(),height(),k);
        if(k->key()==Qt::Key_Space)
        {
            Bullet ammo(player->getPoint(), 1);
            bullets.push_back(ammo);
            shooted = true;
        }
    }

}

void Widget::stage1()
{
    if(game_is_started) {
        for(int i = 0; i<2; i++)
            {
                enemies.push_back(EnemyType1(width(), height(),livesStep));
                is_enemy = true;
            }
    }
}

void Widget::stage2()
{
    if(game_is_started) {
        for(int i = 0; i<3; i++)
            {
                enemies.push_back(EnemyType1(width(), height(),livesStep));
                is_enemy = true;
            }
    }
}

void Widget::stage3()
{
    if(game_is_started) {
        for(int i = 0; i<4; i++)
            {
                enemies.push_back(EnemyType1(width(), height(),livesStep));
                is_enemy = true;
            }
    }
}

void Widget::stage4()
{
    if(game_is_started) {
        for(int i = 0; i<5; i++)
            {
                enemies.push_back(EnemyType1(width(), height(),livesStep));
                is_enemy = true;
            }
    }
}

void Widget::stageBoss()
{
    if(game_is_started) {
        timerer.start(1000);
            connect(&timerer,SIGNAL(timeout()),this,SLOT(moverect()));
            qDebug()<<"aa";
            boss_exist = true;
    }
}

bool Widget::moverect()
{
    rbullets.push_back(Boss->attack_1());
    rshooted = true;
       qDebug()<<"bb";
}

void Widget::stop()
{
    if(!game_is_started)
    {
        disconnect(&timer, SIGNAL(timeout()), this, SLOT(MoveAll()));
        disconnect(&timerer, SIGNAL(timeout()), this, SLOT(moverect()));
        timer.stop();
        timerer.stop();
        QMessageBox::warning(this, "Balls", "Игра окончена! Вы набрали - "+QString::number(score) + " очков.");
        ui->pushButton->show();
        ui->pushButton_2->show();
        ui->pushButton_3->show();
        ui->lcdNumber->hide();
        ui->lcdNumber_2->hide();
        ui->label->hide();
        ui->label_2->hide();
        lives = 5;
        score = 0;
        delete player;
        delete Boss;
        if(!enemies.empty())
            enemies.clear();
        if(!bullets.empty())
        bullets.clear();
        if(!rbullets.empty())
        rbullets.clear();
        rshooted = false;
        shooted = false;
        is_enemy = false;
        boss_exist = false;
    }
}

void Widget::MoveAll()
{
    if(game_is_started) {
        if(lives<=0) {
            game_is_started = false;
            stop();
        }
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
                               score += 10;
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
                       score+=100;
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
           ui->lcdNumber->display(lives);
           ui->lcdNumber_2->display(score);
            this->repaint();
    }


void Widget::on_pushButton_clicked()
{
    ui->pushButton->hide();
    ui->pushButton_2->hide();
    ui->pushButton_3->hide();
    ui->label->show();
    ui->label_2->show();
    ui->lcdNumber->show();
    ui->lcdNumber_2->show();
    player = new Player(width(),height());
    Boss = new boss(width(), height());
    boss_lives = 20;
    game_is_started = true;
    timer.start(30);
    connect(&timer,SIGNAL(timeout()),this,SLOT(MoveAll()));
    stage = 1;

}

void Widget::on_pushButton_2_clicked()
{
    this->close();
}

void Widget::on_lcdNumber_overflow()
{

}

void Widget::on_pushButton_3_clicked()
{
    ui->pushButton->hide();
    ui->pushButton_2->hide();
    ui->pushButton_3->hide();
    ui->label->hide();
    ui->label_2->hide();
    ui->lcdNumber->hide();
    ui->lcdNumber_2->hide();
}
