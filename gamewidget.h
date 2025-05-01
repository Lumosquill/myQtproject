#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QWidget>
#include<QKeyEvent>
#include<QMouseEvent>
#include<QList>
#include<QProgressBar>
#include<QLabel>
#include<QCursor>
#include<QApplication>
#include<QIcon>
#include<QDebug>
#include<QString>
#include<QGraphicsScene>
#include<QGraphicsView>
#include <QRandomGenerator>
#include<QToolButton>
#include<QPushButton>
#include"player.h"
#include"enemybase.h"
#include"dementor.h"
#include"bigdementor.h"
#include"spider.h"
#include"bulletbase.h"
#include"playerbullet.h"
#include"gameprogress.h"
#include"chocolatefrog.h"
#include"timeturner.h"
#include"enemybullet.h"
#include"thoughtbubble.h"
#include"felix_felicis.h"
#include<QMessageBox>
#include<QPropertyAnimation>
#include <QGraphicsDropShadowEffect>

//#include<QMediaPlayer>
//#include<QAudioOutput>

QT_BEGIN_NAMESPACE
namespace Ui {
class Gamewidget;
}
QT_END_NAMESPACE

class Gamewidget : public QWidget
{
    Q_OBJECT

public:
    Gamewidget(QWidget *parent = nullptr);
    ~Gamewidget();
    static Gamewidget* widget;//静态指针，所有Gamewidget的实例都共享这一个指针。
    void initstart();
    void initgame();
    void restartgame();
    void setTimer();
    void startTimer();
    void stopTimer();
    void resetproperties();
    void GameWin();
    void GameOver();
    void onTimeout();
    void visualize();

    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent* event);

    Player* getPlayer();
    void playermove();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

    QPointF playerBulletDir = QPointF(1,0);

    bool isRunning = 0;//游戏是否进行中
    bool isChoosing = 0;//是否在选择物品
    bool isStopped = 0;//是否按暂停
    bool isPressed = 0;//鼠标是否按住



    QGraphicsScene &getGameScene();

    //生成怪物
    void enemySummon(int _HP, int _Attack, qreal _Speed,int _No);
    //生成思想泡泡
    void bubbleSummon(QString name,thoughtbubble::EffectType type);
    //生成时间转换器
    void timeturnerSummon();
    void felix_felicisSummon();

    //各种碰撞检测
    void player_enemyCollision();
    void bullet_enemyCollision();
    void bullet_playerCollision();
    void player_chocolatefrogCollision();
    void player_timeturnerCollision();
    void bullet_thoughtbubbleCollision();
    void player_felixfelicisCollision();

    //清除出界子弹
    void releaseOutPlayerBullet();
    void releaseOutEnemyBullet();


    void getExp();//玩家获取经验

    QList<Enemybase*> mEnemyList;//怪物列表
    QList<Bulletbase*> mMyBulletList;//玩家子弹列表
    QList<Enemybullet*> mEnemyBulletList;//怪物子弹列表
    QList<Chocolatefrog*> mFrogList;//巧克力蛙列表
    QList<thoughtbubble*>mThoughtBubbleList;//思想泡泡列表
    QList<Timeturner*> mTimeturnerList;//时间转转换器列表
    QList<felix_felicis*> mFelixfelicisList;//时间转换器列表
    int mAttainedFelixNum;
    void onFelixBtnClicked();
    void useFelixFelicis();
private:
    Ui::Gamewidget *ui;

    QGraphicsView mGameView; //视图
    QGraphicsScene mStartScene;//开始场景
    QGraphicsScene mGameScene;//游戏场景
    QGraphicsScene mWinScene;//胜利场景
    QGraphicsScene mOverScene;//结束场景

    QToolButton *startbtn=nullptr;
    QToolButton *quitbtn=nullptr;
    QToolButton *infobtn=nullptr;
    QToolButton *restartbtn=nullptr;
    QPushButton* felixBtn=nullptr;
    QLabel*titlelabel;
    QLabel*GAMEOVERlabel;
    QLabel*sentence1label;
    QLabel*victorylabel;
    QLabel*sentence2label;
    QLabel*sentence3label;
    QLabel*hplabel;
    QLabel*manalabel;
    QLabel*felixLabel;

    QProgressBar* HPBar;
    QProgressBar* ManaBar;

    Player m_player;

    bool gameStarted = false;
    QList<int> mKeyList;//QList是Qt提供的一个模板类，它是一个容器类，可以存储任意类型的数据

    //定时器
    QTimer* playerMoveTimer;
    QTimer* enemyMoveTimer;
    QTimer* playerShootTimer;
    QTimer* bulletMoveTimer;
    QTimer* countdownTimer;//倒计时
    int countdowntime;


};
#endif // GAMEWIDGET_H
