#include "spider.h"
#include"gamewidget.h"
Spider::Spider(Player *_player, int _HP, int _AttackPoint, qreal _Speed)
    :Enemybase(_player,_HP,_AttackPoint,_Speed)
{
    this->setPixmap(QPixmap(":/1/spider.png"));
    this->setScale(1);
    setTransformOriginPoint(boundingRect().center());
    mNo = 2;
}
Spider::~Spider() {
    //qDebug() << "Spider destroyed ";
}
void Spider::startSkill()
{
    spidershoot();
}
void Spider::setMirrorPixmap(QString name)
{
    Enemybase::setMirrorPixmap("spider");
}

void Spider::spidershoot()
{
    if (hasShot) return;
    hasShot = true;
    qDebug() << "spider at" << this->pos();

    QTimer* shootTimer = new QTimer(this);
    int* count = new int(0); // 用指针包住，因为 lambda 捕获变量是值

    connect(shootTimer, &QTimer::timeout, this, [=]() mutable {
        if (*count >= 2) { //射3轮就停
            shootTimer->stop();
            shootTimer->deleteLater();
            delete count;
            return;
        }
        (*count)++;

        for (int i = 0; i < 4; i++) {
            auto* spiderBL = new Enemybullet(this, Bulletbase::BulletDir(i), 0.05,1, 0);
            Gamewidget::widget->getGameScene().addItem(spiderBL);
            Gamewidget::widget->mEnemyBulletList.append(spiderBL);
            spiderBL->setZValue(2);
        }
    });
    shootTimer->start(1000);
}
void Spider::startConfusedVisualEffect()
{
    if (mSpinTimer) return;
    isConfused=true;
    spinFrame = 0;
    mSpinTimer = new QTimer(this);
    connect(mSpinTimer, &QTimer::timeout, this, [=]() mutable {
        //旋转
        mRotationAngle += 10;
        if (mRotationAngle >= 360) mRotationAngle = 0;
        setRotation(mRotationAngle);

        //原地小幅抖动（漂浮）
        mSpeed=0;
        qreal dx = 2 * sin(spinFrame * 0.3);  //左右
        qreal dy = 2 * cos(spinFrame * 0.3);  //上下
        moveBy(dx, dy);

        spinFrame++;
        QTimer::singleShot(8000, this, [=]() {
            stopConfusedVisualEffect();
            isConfused=false;
        });
    });
    mSpinTimer->start(50);
}

void Spider::stopConfusedVisualEffect()
{
    if (mSpinTimer)
    {
        mSpinTimer->stop();
        mSpinTimer->deleteLater();
        mSpinTimer = nullptr;
    }
    setRotation(0);  // 恢复正常角度
    mSpeed=0.7;
}
