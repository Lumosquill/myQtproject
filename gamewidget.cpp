#include "gamewidget.h"
#include "ui_gamewidget.h"
#include"gameprogress.h"
#include"enemybase.h"
#include"dementor.h"
#include"bigdementor.h"
Gamewidget* Gamewidget::widget = nullptr;
Gamewidget::Gamewidget(QWidget *parent)
    : QWidget(parent),mAttainedFelixNum(0)
    , ui(new Ui::Gamewidget)
{
    ui->setupUi(this);
    widget =this;//初始化静态指针
    setWindowTitle("Expecto Patronum");
    setWindowIcon(QIcon(":/1/felix felicis.jpg"));
    this->move(350,100);
    setFixedSize(850,629);

    // 初始化QGraphicsView
    mGameView.setParent(this);
    mGameView.setGeometry(0,0,850,629); // 设置视图大小，匹配窗口
    mGameView.setStyleSheet("border: 0px"); // 去掉边框



    this->initstart();
}

Gamewidget::~Gamewidget()
{
    delete ui;
    //qDebug()<<"widget released";
}
void Gamewidget::initstart()
{

    mStartScene.setSceneRect(QRect(0,0,850,629));

    mStartScene.addPixmap(QPixmap(":/1/startscene.jpg"));//设置背景图
    mGameView.setScene(&mStartScene); //先显示开始场景
    mGameView.show();

    MenuBGMplayer = new QMediaPlayer(this);
    MenuBGMOutput = new QAudioOutput(this);
    MenuBGMplayer->setAudioOutput(MenuBGMOutput);
    MenuBGMplayer->setSource(QUrl("qrc:/1/Hedwig's Theme.ogg"));
    QTimer::singleShot(500, this, [this]() {
        MenuBGMplayer->play(); //延迟0.5秒播放音乐
    });
    MenuBGMOutput->setVolume(0.5);

    titlelabel = new QLabel(this);
    titlelabel->setPixmap(QPixmap(":/1/Expecto-Patronum(1).png"));
    titlelabel->setGeometry(200, 28, 500, 200);  // 设置标签的位置和大小

    //按钮音效
    ButtonAudioplayer = new QMediaPlayer(this);
    ButtonAudioOutput = new QAudioOutput(this);
    ButtonAudioplayer->setAudioOutput(ButtonAudioOutput);
    ButtonAudioplayer->setSource(QUrl("qrc:/1/button.mp3"));


    //开始按钮
    startbtn = new QToolButton(this);
    startbtn->setAutoRaise(true);
    startbtn->setFixedSize(133,40);
    startbtn->setIcon(QIcon(":/1/Start.png"));
    startbtn->setIconSize(QSize(133,40));
    startbtn->move(90,220);

    connect(startbtn,&QToolButton::clicked,[this](){
    if (!gameStarted)
    {
    ButtonAudioplayer->play();
    initgame();
    startbtn->hide();
    infobtn->hide();
    quitbtn->hide();
    titlelabel->hide();
    gameStarted = true;
    }
    else restartgame();
    });


    //介绍按钮
    infobtn = new QToolButton(this);
    infobtn->setAutoRaise(true);
    infobtn->setFixedSize(133,40);
    infobtn->setIcon(QIcon(":/1/Info.png"));
    infobtn->setIconSize(QSize(133,40));
    infobtn->move(90,280);
    connect(infobtn,&QToolButton::clicked,[this](){
        ButtonAudioplayer->play();

        QDialog* dialog = new QDialog(this);
        dialog->setWindowTitle("Info");
        dialog->resize(430, 400);
        dialog->setStyleSheet("QDialog { background-color: white; border-radius: 12px; }");
        QScrollArea* scrollArea = new QScrollArea(dialog);
        scrollArea->setWidgetResizable(true);
        scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        scrollArea->verticalScrollBar()->setStyleSheet(R"(
        QScrollBar:vertical {
            background: transparent;
            width: 10px;
            margin: 0px 0px 0px 0px;
        }

        QScrollBar::handle:vertical {
            background: #5CACEE;
            min-height: 20px;
            border-radius: 5px;
        }

        QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {
            height: 0px;
        }

        QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {
            background: none;
        }
    )");
        QLabel* imageLabel = new QLabel;
        QPixmap introImage(":/1/info_page.jpg");
        QPixmap scaled = introImage.scaledToWidth(400, Qt::SmoothTransformation);
        imageLabel->setPixmap(scaled);

        scrollArea->setWidget(imageLabel);

        QVBoxLayout* layout = new QVBoxLayout(dialog);
        layout->addWidget(scrollArea);
        layout->setContentsMargins(10, 10, 10, 10);
        dialog->setLayout(layout);

        dialog->exec(); // 显示为模态对话框
    });


    //退出按钮
    quitbtn = new QToolButton(this);
    quitbtn->setAutoRaise(true);
    quitbtn->setFixedSize(133,40);
    quitbtn->setIcon(QIcon(":/1/Quit.png"));
    quitbtn->setIconSize(QSize(250,327));
    quitbtn->move(90,340);
    connect(quitbtn,&QToolButton::clicked,[this](){
        close();
    });


}
void Gamewidget::initgame()
{
    //显示开始场景
    mGameView.setScene(&mGameScene);
    mGameScene.setSceneRect(QRect(0,0,850,629));
    mGameScene.addPixmap(QPixmap(":/1/background.jpg"));

    //显示玩家
    m_player.setScale(0.03);
    m_player.setPos(200,200);
    m_player.setZValue(1);//在QGraphicsScene里，每个QGraphicsItem都有一个ZValue，值越大，图层越靠前，值越小，图层越靠后。ZValue默认是0。
    mGameScene.addItem(&m_player);

    //开启定时器
    setTimer();
    startTimer();

    MenuBGMplayer->pause();
    BGMplayer = new QMediaPlayer(this);
    BGMOutput = new QAudioOutput(this);
    BGMplayer->setAudioOutput(BGMOutput);
    BGMplayer->setSource(QUrl("qrc:/1/ttk.ogg"));
    QTimer::singleShot(500, this, [this]() {
        BGMplayer->play(); //延迟0.5秒播放音乐
    });
    BGMOutput->setVolume(0.5);

    //设置属性栏
    visualize();

    //连接游戏结束
    connect(&m_player,&Player::isDead,[this](){
        this->GameOver();
        HPBar->hide();
        //QMetaObject::invokeMethod(this, "GameOver", Qt::QueuedConnection);
        //QMetaObject::invokeMethod(HPBar, "hide", Qt::QueuedConnection);
    });



}
void Gamewidget::restartgame()
{
    LoseBGMplayer->pause();
    BGMplayer->play();
    mGameView.setScene(&mGameScene);
    sentence1label->hide();
    GAMEOVERlabel->hide();
    //清除怪物与子弹
    int enemyNum = mEnemyList.size();
    for(int i = enemyNum-1; i >= 0; i--)
    {
        mGameScene.removeItem(mEnemyList[i]);
        if(mEnemyList[i] != nullptr) mEnemyList[i]->deleteLater();
        mEnemyList.removeOne(mEnemyList[i]);
    }
    int enemyBulletNum = mEnemyBulletList.size();
    for(int i = enemyBulletNum-1; i >= 0; i--)
    {
        mGameScene.removeItem(mEnemyBulletList[i]);
        if(mEnemyBulletList[i] != nullptr) mEnemyBulletList[i]->deleteLater();
        mEnemyBulletList.removeOne(mEnemyBulletList[i]);
    }
    int playerBulletNum = mMyBulletList.size();
    for(int i = playerBulletNum-1; i >= 0; i--)
    {
        mGameScene.removeItem(mMyBulletList[i]);
        if(mMyBulletList[i] != nullptr) mMyBulletList[i]->deleteLater();
        mMyBulletList.removeOne(mMyBulletList[i]);
    }
    int chocolatefrogNum=mFrogList.size();
    for(int i=chocolatefrogNum-1;i>=0;i--)
    {
        mGameScene.removeItem(mFrogList[i]);
        if(mFrogList[i] != nullptr) mFrogList[i]->deleteLater();
        mFrogList.removeOne(mFrogList[i]);
    }
    int thoughtbubbleNum=mThoughtBubbleList.size();
    for(int i=thoughtbubbleNum-1;i>=0;i--)
    {
        mGameScene.removeItem(mThoughtBubbleList[i]);
        if(mThoughtBubbleList[i] != nullptr) mThoughtBubbleList[i]->deleteLater();
        mThoughtBubbleList.removeOne(mThoughtBubbleList[i]);
    }
    int timeturnerNum=mTimeturnerList.size();
    for(int i=timeturnerNum-1;i>=0;i--)
    {
        mGameScene.removeItem(mTimeturnerList[i]);
        if(mTimeturnerList[i] != nullptr) mTimeturnerList[i]->deleteLater();
        mTimeturnerList.removeOne(mTimeturnerList[i]);
    }
    int ffNum=mFelixfelicisList.size();
    for(int i=ffNum-1;i>=0;i--)
    {
        mGameScene.removeItem(mFelixfelicisList[i]);
        if(mFelixfelicisList[i] != nullptr) mFelixfelicisList[i]->deleteLater();
        mFelixfelicisList.removeOne(mFelixfelicisList[i]);
    }
    //重置角色
    m_player.resetplayer();
    m_player.setPos(200,200);
    resetproperties();
    startTimer();



}
void Gamewidget::playermove()
{
    qreal speedX = m_player.getSpeed()*(1+m_player.getSpeedRatio()*2);
    if(mKeyList.size() > 1) speedX /= sqrt(2);//斜着走时控制速度
    for(int keyCode : mKeyList)
    {
        switch(keyCode)
        {
        case Qt::Key_W: m_player.moveBy(0,-speedX);break;
        case Qt::Key_S: m_player.moveBy(0,speedX);break;
        case Qt::Key_A:
        {   m_player.moveBy(-speedX,0);
            //m_player.setFaceDir('l');
            break;
        }
        case Qt::Key_D:
        {m_player.moveBy(speedX,0);
            //m_player.setFaceDir('r');
            break;
        }
        }
    }
    if(m_player.pos().x()<0)
        m_player.setX(0);
    if(m_player.pos().y()<100)
        m_player.setY(100);
    if(m_player.pos().x()>850-m_player.scale()*m_player.pixmap().width())
        m_player.setX(850-m_player.scale()*m_player.pixmap().width());
    if(m_player.pos().y()>629-m_player.scale()*m_player.pixmap().height())
        m_player.setY(629-m_player.scale()*m_player.pixmap().height());
}
void Gamewidget::keyPressEvent(QKeyEvent *event)
{
    // if(event->key() == Qt::Key_Escape)
    // {
    //     isStopped = !isStopped;
    //     if(isStopped) stopTimer();
    //     else startTimer();
    //     pauseBTN->click();
    // }

    if (!isRunning) return;
    int key = event->key();
    if ((key == Qt::Key_W || key == Qt::Key_A || key == Qt::Key_S || key == Qt::Key_D)
        && !mKeyList.contains(key)) {
        mKeyList.append(key);

        if (key == Qt::Key_A) m_player.setFaceDir('l');
        if (key == Qt::Key_D) m_player.setFaceDir('r');
    }
    QWidget::keyPressEvent(event);
    playermove();
}
void Gamewidget::GameOver()
{
    stopTimer();
    BGMplayer->pause();
    QTimer::singleShot(1000, this, [=]() {
        LoseBGMplayer = new QMediaPlayer(this);
        LoseBGMOutput = new QAudioOutput(this);
        LoseBGMplayer->setAudioOutput(BGMOutput);
        LoseBGMplayer->setSource(QUrl("qrc:/1/gameover.mp3"));
        LoseBGMplayer->play();
        LoseBGMOutput->setVolume(0.5);
        mOverScene.setSceneRect(QRect(0,0,850,629));
        mOverScene.addPixmap(QPixmap(":/1/gameoverscene.jpg"));
        mGameView.setScene(&mOverScene);
        HPBar->hide();
        ManaBar->hide();
        hplabel->hide();
        manalabel->hide();
        felixLabel->hide();
        felixBtn->hide();
        GAMEOVERlabel = new QLabel(this);
        GAMEOVERlabel->setPixmap(QPixmap(":/1/GAME-OVER.png"));
        GAMEOVERlabel->setGeometry(175, 30, 500, 200);
        GAMEOVERlabel->show();
        sentence1label = new QLabel(this);
        sentence1label->setPixmap(QPixmap(":/1/sentence1.png"));
        sentence1label->setGeometry(100, 220, 686, 33);
        sentence1label->show();

        restartbtn = new QToolButton(this);
        restartbtn->setAutoRaise(true);
        restartbtn->setIcon(QIcon(":/1/Try-Again.png"));
        restartbtn->setIconSize(QSize(190,41));
        restartbtn->move(325,350);
        restartbtn->show();
        connect(restartbtn,&QToolButton::clicked,[this](){
            ButtonAudioplayer->play();
            restartgame();
            restartbtn->hide();
        });
     });
}
void Gamewidget::GameWin()
{
    stopTimer();

    BGMplayer->pause();
    WinBGMplayer = new QMediaPlayer(this);
    WinBGMOutput = new QAudioOutput(this);
    WinBGMplayer->setAudioOutput(WinBGMOutput);
    WinBGMplayer->setSource(QUrl("qrc:/1/gamewin.mp3"));
    QTimer::singleShot(500, this, [this]() {
        WinBGMplayer->play(); //延迟0.5秒播放音乐
        WinBGMOutput->setVolume(0.5);
        HPBar->hide();
        ManaBar->hide();
        hplabel->hide();
        manalabel->hide();
        felixLabel->hide();
        felixBtn->hide();
        mWinScene.setSceneRect(QRect(0,0,850,629));
        mWinScene.addPixmap(QPixmap(":/1/gamewinscene.jpg"));
        mGameView.setScene(&mWinScene);
        victorylabel = new QLabel(this);
        victorylabel->setPixmap(QPixmap(":/1/victory.png"));
        victorylabel->setGeometry(225, 50, 400, 107);
        victorylabel->show();
        sentence2label = new QLabel(this);
        sentence2label->setPixmap(QPixmap(":/1/triumph_sentence.png"));
        sentence2label->setGeometry(100, 200, 686, 32);
        sentence2label->show();

    });

}
void Gamewidget::resetproperties()
{
    HPBar->setValue(m_player.getHP());
    HPBar->show();
    ManaBar->show();
    hplabel->show();
    manalabel->show();
    felixLabel->show();
    felixBtn->show();
}
void Gamewidget::visualize()
{
    hplabel = new QLabel(this);
    hplabel->setPixmap(QPixmap(":/1/HPlabel.png"));
    hplabel->setGeometry(33, 50,32, 19);
    hplabel->show();
    HPBar = new QProgressBar(this);
    HPBar->setMinimum(10);
    HPBar->setMaximum(m_player.getMaxHP());
    HPBar->setValue(m_player.getHP());
    HPBar->move(70,50);
    HPBar->setFixedSize(150,15);
    HPBar->setStyleSheet(
        "QProgressBar {"
        "  border: 2px solid #555;"
        "  border-radius: 5px;"
        "  background-color: #eee;"
        "  text-align: center;"
        "}"

        "QProgressBar::chunk {"
        "  background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #66ff66, stop:1 #009933);"
        "  border-radius: 5px;"
        "}"
        );
    HPBar->show();

    //魔力值条配置
    manalabel = new QLabel(this);
    manalabel->setPixmap(QPixmap(":/1/Manalabel.png"));
    manalabel->setGeometry(15, 80, 50 ,19);
    manalabel->show();
    ManaBar = new QProgressBar(this);
    ManaBar->setMinimum(0);
    ManaBar->setMaximum(m_player.getMaxMana());
    ManaBar->setValue(m_player.getMana());
    ManaBar->move(70,80);
    ManaBar->setFixedSize(150,15);
    ManaBar->setStyleSheet(
        "QProgressBar {"
        "  border: 1px solid #222;"
        "  border-radius: 5px;"
        "  background-color: #111;"
        "  text-align: center;"
        "  color: white;"
        "}"
        "QProgressBar::chunk {"
        "  background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #8e44ad, stop:1 #3498db);"
        "}"
        );
    ManaBar->show();

    felixBtn = new QPushButton(this);
    felixBtn->setIcon(QIcon(":/1/felix felicis.png")); // 改成你实际路径
    felixBtn->setIconSize(QSize(32, 32));
    felixBtn->setStyleSheet("background: transparent; border: none;");
    felixBtn->setGeometry(250, 60, 32, 32); // 放在 ManaBar 下方
    felixBtn->show();

    felixLabel = new QLabel("x0",this);
    felixLabel->setStyleSheet("color: #d4faff; "
                              "font-weight: bold; "
                              "font-size: 14px;"
                              );
    felixLabel->setGeometry(290, 65, 30, 20);
    felixLabel->show();
    connect(felixBtn, &QPushButton::clicked, this, &Gamewidget::onFelixBtnClicked);
}
void Gamewidget::onFelixBtnClicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "使用福灵剂", "是否使用福灵剂？",
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        useFelixFelicis();
    }
}
void Gamewidget::useFelixFelicis()
{
    if (mAttainedFelixNum > 0) {

        mAttainedFelixNum--;
        felixLabel->setText("x" + QString::number(mAttainedFelixNum));
        mIsFelixActive = true;
        QGraphicsDropShadowEffect* glow = new QGraphicsDropShadowEffect;
        glow->setBlurRadius(20);
        glow->setColor(QColor(255, 223, 0));
        glow->setOffset(0, 0);
        m_player.setGraphicsEffect(glow);

        QTimer::singleShot(6000, [&]() {
            m_player.setGraphicsEffect(nullptr);//移除光晕
            mIsFelixActive = false;
        });
        m_player.restoreMana(20);
        m_player.restoreHP(30);
    } else {
        // 如果没有福灵剂，弹出提示
        QMessageBox::information(this, "没有福灵剂", "你没有足够的福灵剂！");
    }
}
void Gamewidget::keyReleaseEvent(QKeyEvent *event)
{
    if(mKeyList.contains(event->key())) {
        mKeyList.removeAll(event->key());
    }
    // if (event->key() == Qt::Key_Space) {
    //     isPressed = false;
    //     playerShootTimer->stop();
    // }
    // QWidget::keyReleaseEvent(event);
    // playermove();
}
void Gamewidget::mousePressEvent(QMouseEvent *event)
{

    if(!isRunning) return;
    isPressed = 1;
    playerShootTimer->start(m_player.getAttackInterval());
    grabMouse();
    QWidget::mousePressEvent(event);
}

void Gamewidget::mouseMoveEvent(QMouseEvent *event)
{
    if(!isPressed) return;

    setMouseTracking(true);
    QPointF moveDir = event->pos() - m_player.getCenterPos();
    qreal _x = moveDir.x();
    qreal _y = moveDir.y();
    _x = QString::number(_x,'f',2).toDouble();
    _y = QString::number(_y,'f',2).toDouble();
    qreal _r = qSqrt(qPow(_x,2) + qPow(_y,2));
    if(_r == 0) return;
    //保留两位小数
    _r = QString::number(_r,'f',2).toDouble();
    qreal dx = _x/_r;
    qreal dy = _y/_r;
    dx = QString::number(dx,'f',2).toDouble();
    dy = QString::number(dy,'f',2).toDouble();
    playerBulletDir = QPointF(dx,dy);

    QWidget::mouseMoveEvent(event);
}

void Gamewidget::mouseReleaseEvent(QMouseEvent *event)
{
    if(!isRunning) return;
    isPressed = 0;
    playerShootTimer->stop();
    releaseMouse();
    QWidget::mouseReleaseEvent(event);
}

void Gamewidget::enemySummon(int _HP, int _Attack, qreal _Speed, int _No)
{
    Enemybase *Enemy = nullptr;
    switch(_No)
    {
    case 1:
    {
        Enemy= new Dementor(Gamewidget::widget->getPlayer(),_HP,_Attack,_Speed);
        break;
    }
    case 2:
    {
        Enemy= new Spider(Gamewidget::widget->getPlayer(),_HP,_Attack,_Speed);
        break;
    }
    case 3:
    {
        Enemy= new Bigdementor(Gamewidget::widget->getPlayer(),_HP,_Attack,_Speed);
        break;
    }
    }

    // 生成随机位置
    QPointF tpos(0,0);
    do {
        QPointF _pos(QRandomGenerator::global()->bounded(0,750), QRandomGenerator::global()->bounded(100,400));
        tpos = _pos + QPointF(Enemy->pixmap().width()*Enemy->scale()/2, Enemy->pixmap().height()*Enemy->scale()/2);
    } while(abs((tpos - m_player.getCenterPos()).x()) < 250 && abs((tpos - m_player.getCenterPos()).y()) < 250);
    //如果 x 方向 和 y 方向 的距离都小于 200，则重新生成 tpos，确保敌人不会太接近玩家
    Enemy->setPos(tpos);
    getGameScene().addItem(Enemy);
    mEnemyList.append(Enemy);
    Enemy->setZValue(2);

    Enemy->startSkill();
}
void Gamewidget::bubbleSummon(QString path,thoughtbubble::EffectType type)
{
    thoughtbubble * bub=new thoughtbubble(path,type);

    connect(bub, &thoughtbubble::bubbleDestroyed, this, [=](thoughtbubble* self){
        mThoughtBubbleList.removeOne(self);
    });

    // 生成随机位置
    QPointF tpos(0,0);
    do {
        QPointF _pos(QRandomGenerator::global()->bounded(0,750), QRandomGenerator::global()->bounded(100,400));
        tpos = _pos + QPointF(bub->pixmap().width()*bub->scale()/2, bub->pixmap().height()*bub->scale()/2);
    } while(abs((tpos - m_player.getCenterPos()).x()) < 50 && abs((tpos - m_player.getCenterPos()).y()) < 50);
    bub->setPos(tpos);

    getGameScene().addItem(bub);
    mThoughtBubbleList.append(bub);
    bub->setZValue(2);
    bub->show();
    bub->floatAround();
}
void Gamewidget::timeturnerSummon()
{
    Timeturner *tt=new Timeturner();
    QPointF tpos(0,0);
    do {
        QPointF _pos(QRandomGenerator::global()->bounded(0,750), QRandomGenerator::global()->bounded(100,400));
        tpos = _pos + QPointF(tt->pixmap().width()*tt->scale()/2, tt->pixmap().height()*tt->scale()/2);
    } while(abs((tpos - m_player.getCenterPos()).x()) < 50 && abs((tpos - m_player.getCenterPos()).y()) < 50);
    tt->setPos(tpos);

    getGameScene().addItem(tt);
    mTimeturnerList.append(tt);
    tt->setZValue(2);
    tt->show();
}
void Gamewidget::felix_felicisSummon()
{
    felix_felicis *ff=new felix_felicis();
    QPointF tpos(0,0);
    do {
        QPointF _pos(QRandomGenerator::global()->bounded(0,750), QRandomGenerator::global()->bounded(100,400));
        tpos = _pos + QPointF(ff->pixmap().width()*ff->scale()/2, ff->pixmap().height()*ff->scale()/2);
    } while(abs((tpos - m_player.getCenterPos()).x()) < 50 && abs((tpos - m_player.getCenterPos()).y()) < 50);
    ff->setPos(tpos);

    getGameScene().addItem(ff);
    mFelixfelicisList.append(ff);
    ff->setZValue(2);
    ff->show();
}
Player *Gamewidget::getPlayer()
{
    return &m_player;
}
QGraphicsScene &Gamewidget::getGameScene()
{
    return mGameScene;
}

void Gamewidget::setTimer()
{
    //设置定时器
    playerMoveTimer = new QTimer(this);
    playerShootTimer = new QTimer(this);
    bulletMoveTimer = new QTimer(this);
    enemyMoveTimer = new QTimer(this);

    connect(playerMoveTimer,&QTimer::timeout,[this](){
        playermove();//玩家移动
        player_enemyCollision();
        player_chocolatefrogCollision();
    });

    connect(playerShootTimer,&QTimer::timeout,[this](){
        m_player.playerShoot(playerBulletDir);
    });

    connect(bulletMoveTimer,&QTimer::timeout,[this](){
        for(auto bullet : mMyBulletList){
            bullet->Bulletbase::BulletMove();
        }
        for(auto enemyBullet : mEnemyBulletList){
            enemyBullet->Bulletbase::BulletMove();
        }
        //检测碰撞
        bullet_enemyCollision();
        bullet_playerCollision();
        bullet_thoughtbubbleCollision();
        player_timeturnerCollision();
        player_felixfelicisCollision();
        //出界检测
        releaseOutPlayerBullet();
        releaseOutEnemyBullet();
    });
    connect(enemyMoveTimer,&QTimer::timeout,[this](){
        for(auto enemy : mEnemyList){
            enemy->setMirrorPixmap(enemy->objectName());//怪物移动与面朝方向
            enemy->enemyMove(1);
            enemy->startSkill();

        }
    });


    // 设置倒计时
    countdownTimer = new QTimer(this);
    connect( countdownTimer, &QTimer::timeout, this, &Gamewidget::onTimeout);

    countdownTimer->start(1000);  // 每秒调用一次
}
int gameTime = 50;
void Gamewidget::onTimeout()
{
    gameTime--;  // 倒计时减1
    if (gameTime <= 0) {
        stopTimer();  //停止定时器
        GameWin();    //游戏胜利逻辑
    } else {
        if(gameTime%3==0)
        Gameprogress::Instance()->EnemyAppearProgress(gameTime);
        if(gameTime%5==0)
        {
            Gameprogress::Instance()->ThoughtBubbleAppear(gameTime);
        }
        if(gameTime==40||gameTime==30||gameTime==20||gameTime==10)
        {
            Gameprogress::Instance()->TimeturnerAppear();
        }
        if(gameTime==38)
        {
            Gameprogress::Instance()->FelixfelicisAppear();
        }
    }
}
void Gamewidget::startTimer()
{
    isRunning=1;

    playerMoveTimer->start(10);
    bulletMoveTimer->start(10);
    enemyMoveTimer->start(10);
}
void Gamewidget::stopTimer()
{
    isRunning = 0;
    //暂停定时器
    playerMoveTimer->stop();
    bulletMoveTimer->stop();
    enemyMoveTimer->stop();
    playerShootTimer->stop();
    countdownTimer->stop();

    //暂停音乐
    //BGMplayer->pause();
}
void Gamewidget::player_enemyCollision()
{
    int enemyNum = mEnemyList.size();
    for(int i=0;i<enemyNum;i++)
    {
        if(m_player.collidesWithItem(mEnemyList[i]))
        {
            m_player.getHurt(mEnemyList[i]->getAttackPoint()/1000);
            emit m_player.isHurt();
            if(m_player.getHP() <= 0)//死亡
            {
                emit m_player.isDead();

            }
        }
    }
}

void Gamewidget::bullet_enemyCollision()
{
    //子弹与敌人碰撞
    int bulletNum = mMyBulletList.size();
    int enemyNum = mEnemyList.size();
    for(int i=0;i< bulletNum;i++)//遍历所有子弹
    {
        for(int j=0;j<enemyNum;j++)//遍历所有敌人
        {
            if(mMyBulletList[i]->collidesWithItem(mEnemyList[j]))//子弹和怪物撞击
            {
                mGameScene.removeItem(mMyBulletList[i]);
                emit mEnemyList[j]->isHurt(); //发出怪物受伤信号
                mEnemyList[j]->getHurt(mMyBulletList[i]->getAttackPoint());
                if(mEnemyList[j]->getHP() <= 0 )
                {
                    emit mEnemyList[j]->isDead();//发出怪物死亡信号

                    //生成巧克力蛙
                    Chocolatefrog* frog = new Chocolatefrog();
                    frog->setPos(mEnemyList[j]->getCenterPos()); //设置为敌人中心位置
                    mGameScene.addItem(frog);
                    mFrogList.append(frog);

                    mGameScene.removeItem(mEnemyList[j]);//从 QList 中移除这个指针（不删除对象）
                    if (mEnemyList[j] != nullptr) mEnemyList[j]->deleteLater();
                    mEnemyList.removeOne(mEnemyList[j]);//deleteLater()：延迟删除对象本身（事件循环后自动 delete）

                }
                if (mMyBulletList[i] != nullptr) mMyBulletList[i]->deleteLater();
                mMyBulletList.removeOne(mMyBulletList[i]);
                return;
            }
        }
    }
}
void Gamewidget::bullet_playerCollision()
{
    int bulletNum = mEnemyBulletList.size();
    for(int i=0;i<bulletNum;i++)
    {
        if(mEnemyBulletList[i]->collidesWithItem(&m_player))
        {
            m_player.getHurt(mEnemyBulletList[i]->getAttackPoint());
            HPBar->setValue(m_player.getHP());
            emit m_player.isHurt();
            if(m_player.getHP() <= 0)//死亡
            {

                emit m_player.isDead();
            }
            if (mEnemyBulletList[i] != nullptr) mEnemyBulletList[i]->deleteLater();
            mEnemyBulletList.removeOne(mEnemyBulletList[i]);

            return;

        }
    }
}
void Gamewidget::player_chocolatefrogCollision()
{
    for(int j = mFrogList.size() - 1; j >= 0; j--)
    {
        if(mFrogList[j]->collidesWithItem(&m_player))
        {
            mGameScene.removeItem(mFrogList[j]);
            if (mFrogList[j] != nullptr) mFrogList[j]->deleteLater();
            mFrogList.removeOne(mFrogList[j]);
            m_player.mhp+=4;
            HPBar->setValue(m_player.getHP());
        }
    }
}
void Gamewidget::player_timeturnerCollision()
{
    int timeturnerNum=mTimeturnerList.size();
    for(int i=0;i<timeturnerNum;i++)
    {
        if(mTimeturnerList[i]->collidesWithItem(&m_player))
        {
            mGameScene.removeItem(mTimeturnerList[i]);
            if (mTimeturnerList[i] != nullptr) mTimeturnerList[i]->deleteLater();
            mTimeturnerList.removeOne(mTimeturnerList[i]);
            for (auto* enemy : mEnemyList)
            {
                enemy->startConfusedVisualEffect();
            }
            return;
        }
    }
}
void Gamewidget::player_felixfelicisCollision()
{
    int ffNum=mFelixfelicisList.size();
    for(int i=0;i<ffNum;i++)
    {
        if(mFelixfelicisList[i]->collidesWithItem(&m_player))
        {
            mAttainedFelixNum++;
            felixLabel->setText("x" + QString::number(mAttainedFelixNum));
            mGameScene.removeItem(mFelixfelicisList[i]);
            if (mFelixfelicisList[i] != nullptr) mFelixfelicisList[i]->deleteLater();
            mFelixfelicisList.removeOne(mFelixfelicisList[i]);
            return;
        }
    }
}
void Gamewidget::bullet_thoughtbubbleCollision()
{
    int bulletNum = mMyBulletList.size();
    int bubbleNum = mThoughtBubbleList.size();
    for(int i=0;i<bulletNum;i++)
    {
        for(int j=0;j<bubbleNum;j++)
        if(mMyBulletList[i]->collidesWithItem(mThoughtBubbleList[j]))
        {
            if (mThoughtBubbleList[j]->effect == thoughtbubble::LoseMana)
            {
                m_player.m_mana -= 10;
                QTimer* shakeTimer = new QTimer;
                int shakeCount = 0;
                int maxShake = 10; // 总共抖动次数（偶数为一个周期）
                qreal originalX = m_player.x();

                connect(shakeTimer, &QTimer::timeout, [=]() mutable {
                    if (shakeCount >= maxShake) {
                        m_player.setX(originalX); //恢复原位
                        shakeTimer->stop();
                        shakeTimer->deleteLater();
                        return;
                    }
                    // 左右切换偏移量
                    qreal offset = (shakeCount % 2 == 0) ? -2.5 : 2.5;
                    m_player.setX(originalX + offset);
                    shakeCount++;
                });
                shakeTimer->start(30); // 每 30ms 抖一次
            }
            else
            {
                QTimer* jumpTimer = new QTimer;
                int jumpCount = 0;
                int maxJump = 4; //总共跳跃次数（偶数为一个周期）
                qreal originalY = m_player.y(); //获取原始位置

                // 创建闪烁效果定时器
                QTimer* blinkTimer = new QTimer;
                int blinkCount = 0;
                bool isBright = false;

                // 创建荧光效果
                QGraphicsDropShadowEffect* glowEffect = new QGraphicsDropShadowEffect;
                glowEffect->setBlurRadius(20);
                glowEffect->setOffset(0, 0);
                //glowEffect->setColor(QColor(150, 180, 250));
                //glowEffect->setColor(QColor(150, 210, 255));
                glowEffect->setColor(QColor(180, 230, 255));
                //glowEffect->setColor(QColor(160, 200, 255));
                m_player.setGraphicsEffect(glowEffect); // 加上光环

                connect(jumpTimer, &QTimer::timeout, [=]() mutable {
                    if (jumpCount >= maxJump) {
                        m_player.setY(originalY); // 恢复原位
                        jumpTimer->stop();
                        jumpTimer->deleteLater();
                        blinkTimer->stop();
                        blinkTimer->deleteLater();
                        m_player.setOpacity(1); // 恢复不透明
                        m_player.setGraphicsEffect(nullptr);
                        return;
                    }
                    qreal offset = (jumpCount % 2 == 0) ? -5 : 5;
                    m_player.setY(originalY + offset);
                    jumpCount++;
                });
                jumpTimer->start(100);

                connect(blinkTimer, &QTimer::timeout, [=]() mutable {
                    if (blinkCount >= 8) {
                        blinkTimer->stop();
                        blinkTimer->deleteLater();
                        m_player.setOpacity(1);
                        return;
                    }

                    m_player.setOpacity(isBright ? 0.8 : 1);
                    isBright = !isBright;
                    blinkCount++;
                });
                blinkTimer->start(100);
            }

            ManaBar->setValue(m_player.getMana());
            mThoughtBubbleList[j]->destroySelf();
            return;

        }
    }
}
void Gamewidget::releaseOutPlayerBullet()
{
    for(int i=0;i<mMyBulletList.size();i++)
    {
        if(mMyBulletList[i]->getCenterPos().x()>950 || mMyBulletList[i]->getCenterPos().x()<-50
            || mMyBulletList[i]->getCenterPos().y()>750 || mMyBulletList[i]->getCenterPos().y()<-50)
        {
            mGameScene.removeItem(mMyBulletList[i]);
            if (mMyBulletList[i] != nullptr) mMyBulletList[i]->deleteLater();
            mMyBulletList.removeOne(mMyBulletList[i]);
            return;
        }
    }
}

void Gamewidget::releaseOutEnemyBullet()
{
    for(int i=0;i<mEnemyBulletList.size();i++)
    {
        if(mEnemyBulletList[i]->getCenterPos().x()>1000 || mEnemyBulletList[i]->getCenterPos().x()<-100
            || mEnemyBulletList[i]->getCenterPos().y()>800 || mEnemyBulletList[i]->getCenterPos().y()<-100)
        {
            mGameScene.removeItem(mEnemyBulletList[i]);
            if (mEnemyBulletList[i] != nullptr) mEnemyBulletList[i]->deleteLater();
            mEnemyBulletList.removeOne(mEnemyBulletList[i]);
            return;
        }
    }
}
