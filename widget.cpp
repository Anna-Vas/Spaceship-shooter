#include "widget.h"
#include "ui_widget.h"
#include <QKeyEvent>
#include <QPainter>

#include <QDebug>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    LoadMainScreen();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    if(GameIsStarted)
    {
        painter.drawImage(0,0, QImage(":/images/space.jpg").scaled(width(), height()));
        player->draw(painter);
        if(PlayerShooted)
        {
            for(GreenIter = GreenBulletsList.begin();GreenIter!=GreenBulletsList.end();GreenIter++)
                GreenIter->draw(painter);
        }
        if(IsEnemy)
        {
            for(EnemiesIter = EnemiesList.begin();EnemiesIter!=EnemiesList.end();EnemiesIter++)
            {
                EnemiesIter->draw(painter);
            }
        }
        if(EnemyShooted)
        {
            for(RedBulletsIter = RedBullets.begin();RedBulletsIter!=RedBullets.end();RedBulletsIter++)
            {
                RedBulletsIter->draw(painter);
            }
        }
        if(BossIsAlive)
        {
            FinalBoss->draw(painter);
        }
        if(IsBonus)
        {
            for(BonusIter = BonusList.begin();BonusIter != BonusList.end();BonusIter++)
            {
                BonusIter->draw(painter);
            }
        }
    }
}

void Widget::SwitchButton(QKeyEvent *key)
{
    if(IsScoreboardSelected)
    {
        if(key->key()==Qt::Key_E)
        {
            on_BackButton_clicked();
        }
    }
    else
         {
            switch (key->key()) {
            case Qt::Key_W:
                ChosenButton--;
                break;
            case Qt::Key_S:
                ChosenButton++;
                break;
            case Qt::Key_E:
                qDebug()<<ChosenButton;
                switch (ChosenButton) {
                case 1:
                    on_NewGameButton_clicked();
                    break;
                case 2:
                    on_BestScoreButton_clicked();
                    break;
                case 3:
                    on_ExitButton_clicked();
                    break;
                default:
                    break;
                }
                break;
            default:
                break;
            }
            if(ChosenButton>3) ChosenButton = 1;
            if(ChosenButton<1) ChosenButton = 3;
        }
    PaintSwitchedButton();
}

void Widget::Gameloop()
{
    if(!IsEnemy && !BossIsAlive) SwitchStage();
    else EnemiesMovement();
    if(PlayerShooted) GreenBulletsMovement();
    if(IsEnemy) EnemiesShooting();
    if(EnemyShooted) RedBulletsMovement();
    if(EnemyShooted) PlayerDamage();
    if(IsEnemy && PlayerShooted) EnemiesDamage();
    if(BossIsAlive && PlayerShooted) BossDamage();
    if(IsBonus) BonusMovement();
    DisplayGameStats();
    if(PlayerLives<=0) EndGame();
    this->repaint();
}

void Widget::keyPressEvent(QKeyEvent *key)
{
    if(!GameIsStarted)
        SwitchButton(key);
    else
    {
        player->move(width(),height(),key);
        if(key->key()==Qt::Key_E)
        {
            GreenBulletsList.push_back(player->shoot());
            PlayerShooted = true;
        }
    }
}

void Widget::PaintSwitchedButton()
{
    ui->NewGameButton->setStyleSheet("color:black");
    ui->BestScoreButton->setStyleSheet("color:black");
    ui->ExitButton->setStyleSheet("color:black");
    switch (ChosenButton) {
    case 1:
        ui->NewGameButton->setStyleSheet("color:red");
        break;
    case 2:
        ui->BestScoreButton->setStyleSheet("color:red");
        break;
    case 3:
        ui->ExitButton->setStyleSheet("color:red");
        break;
    default:
        break;
    }
}

void Widget::LoadMainScreen()
{
    ui->BackButton->hide();
    ui->LivesDisplay->hide();
    ui->LivesLabes->hide();
    ui->ScoreDisplay->hide();
    ui->ScoreLabel->hide();
    ui->BestScoreLabel->hide();
    ui->BestScoreButton->show();
    ui->NewGameButton->show();
    ui->ExitButton->show();
    ui->NewGameButton->setStyleSheet("color:red");
    ChosenButton = 1;
    GameIsStarted = false;
    IsScoreboardSelected = false;
}

void Widget::LoadScoreScreen()
{
    ui->BackButton->show();
    ui->BestScoreButton->hide();
    ui->NewGameButton->hide();
    ui->ExitButton->hide();
    ui->BestScoreLabel->show();
    ui->BestScoreLabel->setText(QString::number(MaxScore));
}

void Widget::StartNewGame()
{
    ui->LivesDisplay->show();
    ui->LivesLabes->show();
    ui->ScoreDisplay->show();
    ui->ScoreLabel->show();
    ui->BestScoreButton->hide();
    ui->NewGameButton->hide();
    ui->ExitButton->hide();
    player = new Player(width(),height());
    MainGameLoopTimer.start(30);
    connect(&MainGameLoopTimer,SIGNAL(timeout()),this,SLOT(Gameloop()));
    PlayerLives = 5;
    PlayerScore = 0;
    LivesStep = 0;
    stage = 1;
}

void Widget::GreenBulletsMovement()
{
    for(GreenIter = GreenBulletsList.begin();GreenIter!=GreenBulletsList.end();GreenIter++)
    {
        if(!GreenIter->move(width(),height()))
        {
            GreenIter = GreenBulletsList.erase(GreenIter);
            if(GreenBulletsList.empty())
            {
                PlayerShooted = false;
                break;
            }
        }
    }
}

void Widget::RedBulletsMovement()
{
    for(RedBulletsIter = RedBullets.begin();RedBulletsIter!=RedBullets.end();RedBulletsIter++)
    {
        if(!RedBulletsIter->move(width(),height()))
        {
           RedBulletsIter = RedBullets.erase(RedBulletsIter);
            if(RedBullets.empty())
            {
                EnemyShooted = false;
                break;
            }
        }
    }
}

void Widget::EnemiesMovement()
{
    for(EnemiesIter = EnemiesList.begin();EnemiesIter!=EnemiesList.end();EnemiesIter++)
    {
        if(!EnemiesIter->move(height()))
        {
            EnemiesIter = EnemiesList.erase(EnemiesIter);
            if(EnemiesList.empty())
            {
                IsEnemy = false;

            }
            break;
        }
    }
}

void Widget::EnemiesDamage()
{
    bool end = false;
    for(EnemiesIter = EnemiesList.begin();EnemiesIter!=EnemiesList.end();EnemiesIter++)
    {
        for(GreenIter = GreenBulletsList.begin();GreenIter!=GreenBulletsList.end();GreenIter++)
        {
            int a = GreenIter->getPoint().x();
            int b = GreenIter->getPoint().y();
            int c = EnemiesIter->getPoint().x();
            int d = EnemiesIter->getPoint().y();
            if((a - c)*(a - c)+(b - d)*(b - d) <= (35)*(35))
            {
                EnemiesIter->MinusLives();
                if(EnemiesIter->ReturnLives()<=0)
                {
                    EnemiesIter = EnemiesList.erase(EnemiesIter);
                    PlayerScore+=10;
                    if(EnemiesList.empty())
                    {
                        IsEnemy = false;
                    }
                }
                GreenIter = GreenBulletsList.erase(GreenIter);
                if(GreenBulletsList.empty())
                {
                    PlayerShooted = false;
                }
                end = true;
                break;
            }
        }
        if(end) break;
    }
}

void Widget::EnemiesShooting()
{
    for(EnemiesIter=EnemiesList.begin();EnemiesIter!=EnemiesList.end();EnemiesIter++)
    {
        if(rand()%100<1)
        {
            RedBullets.push_back(EnemiesIter->shoot());
            EnemyShooted = true;
        }
    }
}

void Widget::BossAttack()
{
    RedBullets.push_back(FinalBoss->attack_1());
    EnemyShooted = true;
}

void Widget::BossDamage()
{
    for(GreenIter = GreenBulletsList.begin();GreenIter != GreenBulletsList.end();GreenIter++)
    {
        if(GreenIter->getPoint().y()<100)
        {
            FinalBoss->BossMinusLives();
            if(FinalBoss->get_lives()<=0)
            {
                BossIsAlive = false;
                delete FinalBoss;
                BossAttackTimer.stop();
                disconnect(&BossAttackTimer,SIGNAL(timeout()),this,SLOT(BossAttack()));
                PlayerScore+=100;
            }
            GreenIter = GreenBulletsList.erase(GreenIter);
            if(GreenBulletsList.empty())
            {
                PlayerShooted = false;
            }
            break;
        }
    }
}

void Widget::PlayerDamage()
{
    for(RedBulletsIter = RedBullets.begin();RedBulletsIter!=RedBullets.end();RedBulletsIter++)
    {
        int a = player->getPoint().x();
        int b = player->getPoint().y();
        int c = RedBulletsIter->getPoint().x();
        int d = RedBulletsIter->getPoint().y();
        if((a - c)*(a - c)+(b - d)*(b - d) <= (35)*(35))
        {
            PlayerLives--;
            RedBulletsIter = RedBullets.erase(RedBulletsIter);
            if(RedBullets.empty())
            {
                EnemyShooted = false;
            }
            break;
        }
    }
}

void Widget::DisplayGameStats()
{
    ui->LivesDisplay->display(PlayerLives);
    ui->ScoreDisplay->display(PlayerScore);
}

void Widget::SwitchStage()
{
    switch (stage) {
    case 1:
        stage1();
        stage++;
        break;
    case 2:
        stage2();
        stage++;
        break;
    case 3:
        stage3();
        stage++;
        break;
    case 4:
        stage4();
        stage++;
        break;
    case 5:
        stageBoss();
        stage++;
        break;
    default:
        break;
    }
    if(stage>5){
        stage = 1;
        LivesStep++;
    }
}

void Widget::BonusMovement()
{
    for(BonusIter = BonusList.begin();BonusIter != BonusList.end();BonusIter++)
    {
        int a = player->getPoint().x();
        int b = player->getPoint().y();
        int c = BonusIter->return_point().x();
        int d = BonusIter->return_point().y();
        if((a - c)*(a - c)+(b - d)*(b - d) <= (35)*(35))
        {
            if(PlayerLives < 10) PlayerLives++;
            BonusIter = BonusList.erase(BonusIter);
            IsBonus = false;
            break;
        }
        if(!BonusIter->move(height()))
        {
            BonusIter = BonusList.erase(BonusIter);
            if(BonusList.empty()) IsBonus = false;
            break;
        }
    }
}

void Widget::stage1()
{
    for(int i = 0;i<3;i++)
    {
        EnemiesList.push_back(EnemyType1(width(),height(),LivesStep));

    }
    BonusList.push_back(bonus(width(),height()));
    IsEnemy = true;
    IsBonus = true;
}

void Widget::stage2()
{
    for(int i = 0;i<4;i++)
    {
        EnemiesList.push_back(EnemyType1(width(),height(),LivesStep));
    }
    BonusList.push_back(bonus(width(),height()));
    IsBonus = true;
    IsEnemy = true;
}

void Widget::stage3()
{
    for(int i = 0;i<5;i++)
    {
        EnemiesList.push_back(EnemyType1(width(),height(),LivesStep));
    }
    BonusList.push_back(bonus(width(),height()));
    IsBonus = true;
    IsEnemy = true;
}

void Widget::stage4()
{
    for(int i = 0;i<6;i++)
    {
        EnemiesList.push_back(EnemyType1(width(),height(),LivesStep));
    }
    BonusList.push_back(bonus(width(),height()));
    IsBonus = true;
    IsEnemy = true;
}

void Widget::stageBoss()
{
   BossAttackTimer.start(600);
   FinalBoss = new boss(width(),height());
   connect(&BossAttackTimer,SIGNAL(timeout()),this,SLOT(BossAttack()));
   BossIsAlive = true;
   BonusList.push_back(bonus(width(),height()));
   IsBonus = true;
}

void Widget::EndGame()
{
    delete player;
    if(IsEnemy) EnemiesList.clear();
    if(PlayerShooted) GreenBulletsList.clear();
    if(EnemyShooted) RedBullets.clear();
    MainGameLoopTimer.stop();
    PlayerShooted = false;
    EnemyShooted = false;
    IsEnemy = false;
    IsBonus = false;
    if(PlayerScore > MaxScore) MaxScore = PlayerScore;
    LoadMainScreen();
}

void Widget::on_NewGameButton_clicked()
{
    GameIsStarted = true;
    StartNewGame();
}

void Widget::on_BestScoreButton_clicked()
{
    IsScoreboardSelected = true;
    LoadScoreScreen();
}

void Widget::on_ExitButton_clicked()
{
    this->close();
}

void Widget::on_BackButton_clicked()
{
     LoadMainScreen();
}
