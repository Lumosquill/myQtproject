#include "enemybullet.h"
#include"gamewidget.h"
Enemybullet::Enemybullet(Enemybase *_owner, BulletDir _dir, int _Attack, qreal _speed,int _type)
{
    mOwner = _owner;
    mAttackPoint = _Attack;
    mSpeed = _speed;
    type = _type;
    if(type == 0)//四处散射的子弹（蜘蛛用）
    {
        this->setPixmap(QPixmap(":/1/spider bullet.png"));
        this->setScale(0.008);
        // 计算散射方向
        static QVector<QPointF> scatterDirs = {
            QPointF(1, 0), QPointF(-1, 0), QPointF(0, 1), QPointF(0, -1),
            QPointF(0.7, 0.7), QPointF(-0.7, 0.7), QPointF(0.7, -0.7), QPointF(-0.7, -0.7)
        };
        moveDir = scatterDirs[_dir]; //让每颗子弹对应一个方向
    }
    else if(type == 1)//朝玩家发射的子弹（摄魂怪用）
    {
        QPointF _Dir = Gamewidget::widget->getPlayer()->getCenterPos() - mOwner->getCenterPos();//子弹的方向向量
        qreal _x = _Dir.x();//提取向量的x和y分量
        qreal _y = _Dir.y();
        qreal _r = qSqrt(qPow(_x,2) + qPow(_y,2));//归一化方向向量
        if(_r == 0) return;

        qreal dx = _x/_r;
        qreal dy = _y/_r;
        moveDir = QPointF(dx,dy);
        this->setPixmap(QPixmap(":/1/dementor bullet.png"));
        this->setScale(0.01);
    }
    else if(type == 2)//朝玩家发射的子弹（大摄魂怪用）
    {
        QPointF _Dir = Gamewidget::widget->getPlayer()->getCenterPos() - mOwner->getCenterPos();//子弹的方向向量
        qreal _x = _Dir.x();//提取向量的x和y分量
        qreal _y = _Dir.y();
        qreal _r = qSqrt(qPow(_x,2) + qPow(_y,2));//归一化方向向量
        if(_r == 0) return;

        qreal dx = _x/_r;
        qreal dy = _y/_r;
        moveDir = QPointF(dx,dy);
        this->setPixmap(QPixmap(":/1/dementor bullet.png"));
        this->setScale(0.04);
    }
    if(type==0||type==1)
    {
        if(mOwner->getFaceDir())//朝右
            mPos = mOwner->getCenterPos() - QPointF(this->pixmap().width()*scale()/(-0.45),this->pixmap().height()*scale()/0.3);
        else//朝左
            mPos = mOwner->getCenterPos() - QPointF(this->pixmap().width()*scale()/0.4,this->pixmap().height()*scale()/0.25);
    }
    else
    {
        if(mOwner->getFaceDir())//朝右
            mPos = mOwner->getCenterPos() - QPointF(this->pixmap().width()*scale()/(-0.45),this->pixmap().height()*scale()/0.5);

        else//朝左
            mPos = mOwner->getCenterPos() - QPointF(this->pixmap().width()*scale()/0.4,this->pixmap().height()*scale()/0.5);

    }
    this->setPos(mPos);//设置子弹初始位置
    mDir = _dir;

    QTimer* moveTimer = new QTimer(this);
    moveTimer->start(300);
    connect(moveTimer, &QTimer::timeout, this, [=]() {
        this->BulletMove();
    });


}
