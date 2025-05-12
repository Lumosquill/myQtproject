#include "enemybase.h"
#include"gamewidget.h"
Enemybase::Enemybase(Gameobject *parent)
    : Gameobject{parent}
{
    m_player=new Player();

}

Enemybase::~Enemybase()
{

}

Enemybase::Enemybase(Player* _player, int _HP, int _AttackPoint, qreal _Speed)
{
    m_player = _player;
    mHP = _HP;
    mAttackPoint = _AttackPoint;
    mSpeed = _Speed;

}
void Enemybase::enemyMove(bool dir)
{
    //获取玩家位置与敌人当前位置的差值
    QPointF playerPos = m_player->getCenterPos();
    QPointF moveDir = playerPos - this->getCenterPos();

    qreal _x = moveDir.x();
    qreal _y = moveDir.y();

    //根据_x值判断敌人朝向
    if (_x >= 0)
        setDir(1); //玩家在右
    else
        setDir(0); //玩家在左

    // 计算敌人与玩家的距离
    qreal _r = qSqrt(qPow(_x, 2) + qPow(_y, 2));

    // 如果敌人已经在玩家的位置，直接返回
    if (_r == 0)
        return;

    // 计算单位向量 (方向) 并调整速度
    qreal vx = (_x / _r) * mSpeed;
    qreal vy = (_y / _r) * mSpeed;

    if (dir) this->moveBy(vx, vy);//向右移动
    else this->moveBy(-vx, -vy);
}
void Enemybase::setMirrorPixmap(QString name)
{
    QString address = ":/1/"+name;
    if(mMoveDir == mFaceDir) return;//如果当前的面朝方向和移动方向一致，不需要翻转图片，直接返回
    if(mMoveDir && !mFaceDir) //如果不一致，则需要设置图片为镜像，翻转角色
    {
        address += "-mir";
        mFaceDir = 1; //设置面朝方向为右
    }
    else mFaceDir = 0; //否则，保持面朝方向为左
    address += ".png";
    this->setPixmap(QPixmap(address));
}
void Enemybase::getHurt(int _attack)
{
    mHP -= _attack;
}
void Enemybase::startSkill()
{
    //默认啥都不做，由子类重写
}
void Enemybase::startConfusedVisualEffect()
{

}
void Enemybase::stopConfusedVisualEffect()
{

}
