#include "bigdementor.h"
#include"gamewidget.h"
Bigdementor::Bigdementor(Player *_player, int _HP, int _AttackPoint, qreal _Speed): Enemybase(_player, _HP, _AttackPoint, _Speed)

{
    this->setPixmap(QPixmap(":/1/bigdementor.png"));
    this->setScale(1);
    mNo = 3;
}
void Bigdementor::setMirrorPixmap(QString name)
{
    Enemybase::setMirrorPixmap("bigdementor");
}
void Bigdementor::bigdementorshoot()
{
    // 避免重复开启多个 timer
    if (mShootTimer && mShootTimer->isActive())
        return;
    if (isConfused) return;
    int mShootCount = 0;

    mShootTimer = new QTimer(this);

    connect(mShootTimer, &QTimer::timeout, this, [=]() mutable {
        if (mShootCount >= 2) {
            mShootTimer->stop();
            mShootTimer->deleteLater();
            mShootTimer = nullptr;
            return;
        }

        mShootCount++;
        //Enemybullet(Enemybase *_owner,BulletDir _dir,int _Attack, qreal _speed = 8,int _type = 0);
        auto* dementorBL = new Enemybullet(this, Bulletbase::BulletDir(5), 0.1, 5, 2);
        Gamewidget::widget->getGameScene().addItem(dementorBL);
        Gamewidget::widget->mEnemyBulletList.append(dementorBL);
        dementorBL->setZValue(2);
    });
    mShootTimer->start(100);

}

void Bigdementor::startSkill()
{
    bigdementorshoot();
}

void Bigdementor::startConfusedVisualEffect()
{
    if (confusionSwitchTimer) return; //避免重复
    isConfused = true;
    mSpeed = 0;
    //镜像快速翻转
    confusionSwitchTimer = new QTimer(this);
    connect(confusionSwitchTimer, &QTimer::timeout, this, &Bigdementor::switchMirrorPixmap);
    confusionSwitchTimer->start(250); //每200ms切一次图

    //漂浮抖动
    floatFrame = 0;
    confusedEffectTimer = new QTimer(this);
    connect(confusedEffectTimer, &QTimer::timeout, this, [=]() mutable {
        //让摄魂怪上下抖动：-1到+1的像素移动
        qreal dy = qSin(floatFrame * 0.3) * 1.5;
        this->moveBy(0, dy);
        floatFrame++;
    });
    confusedEffectTimer->start(50); //每50ms抖一下

    QTimer::singleShot(10000, this, [=]() {
        stopConfusedVisualEffect();
        isConfused = false;
    });
}
void Bigdementor::switchMirrorPixmap()
{
    currentMirrorState = !currentMirrorState;//改变方向

    if (currentMirrorState)//右
        setPixmap(QPixmap(":/1/bigdementor-mir.png"));
    else
        setPixmap(QPixmap(":/1/bigdementor.png"));
}

void Bigdementor::stopConfusedVisualEffect()
{
    //停止镜像切换
    if (confusionSwitchTimer) {
        confusionSwitchTimer->stop();
        confusionSwitchTimer->deleteLater();
        confusionSwitchTimer = nullptr;
    }

    //停止抖动
    if (confusedEffectTimer) {
        confusedEffectTimer->stop();
        confusedEffectTimer->deleteLater();
        confusedEffectTimer = nullptr;
    }
    //设置回默认图片
    setPixmap(QPixmap(":/1/bigdementor.png"));
    mSpeed = 0.3;
}
