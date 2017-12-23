#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <player.h>
#include <QTimer>
#include <QList>
#include <enemy.h>
#include <enemytype1.h>
#include <boss.h>
#include <bonus.h>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT
    Player *player;
    boss *FinalBoss;
    //
    QList<Bullet> GreenBulletsList;
    QList<Bullet>::iterator GreenIter;
    //
    QList<EnemyType1> EnemiesList;
    QList<EnemyType1>::iterator EnemiesIter;
    //
    QList<Bullet> RedBullets;
    QList<Bullet>::iterator RedBulletsIter;
    //
    QList<bonus> BonusList;
    QList<bonus>::iterator BonusIter;

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    void paintEvent(QPaintEvent *e);
    void SwitchButton(QKeyEvent *key);
    void keyPressEvent(QKeyEvent *key);
    void BackToMainScreen();
    void PaintSwitchedButton();
    void LoadMainScreen();
    void LoadScoreScreen();
    void StartNewGame();
    void GreenBulletsMovement();
    void RedBulletsMovement();
    void EnemiesMovement();
    void EnemiesDamage();
    void EnemiesShooting();
    void BossDamage();
    void PlayerDamage();
    void DisplayGameStats();
    void SwitchStage();
    void SpawnBonus();
    void BonusMovement();
    void stage1();
    void stage2();
    void stage3();
    void stage4();
    void stageBoss();
    void EndGame();

private slots:
    void Gameloop();
    void BossAttack();
    void on_NewGameButton_clicked();

    void on_BestScoreButton_clicked();

    void on_ExitButton_clicked();

    void on_BackButton_clicked();

private:
    Ui::Widget *ui;
    bool GameIsStarted = false;
    bool IsScoreboardSelected = false;
    QTimer MainGameLoopTimer;
    QTimer BossAttackTimer;
    int ChosenButton = 1;
    bool PlayerShooted = false;
    bool EnemyShooted = false;
    int PlayerLives = 5;
    int PlayerScore = 0;
    int stage = 1;
    bool IsEnemy = false;
    int LivesStep = 0;
    bool BossIsAlive = false;
    int MaxScore = 0;
    bool IsBonus = false;
};

#endif // WIDGET_H

