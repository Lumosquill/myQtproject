#include "playerbullet.h"
#include"gamewidget.h"


playerbullet::playerbullet(Player *_player, QPointF _dir,int _Attack, qreal _speed)
{
    m_player = _player;
    mAttackPoint = _Attack;
    mSpeed = _speed;

    this->setPixmap(QPixmap(":/1/player bullet.png"));
    this->setScale(0.01);
    if (m_player->isFacingRight()) {
        mPos = m_player->getCenterPos()+QPointF(m_player->pixmap().width()*scale(),m_player->pixmap().height()*scale()/2.5);
    } else {
        mPos = m_player->getCenterPos()+QPointF(m_player->pixmap().width()*scale()*(-1.5),m_player->pixmap().height()*scale()/2.5);
    }
    this->setPos(mPos);
    mDir = Bulletbase::MouseDir;
    moveDir = _dir;

}playerbullet::playerbullet(Player *_player, BulletDir _dir, int _Attack, qreal _speed)
{
    m_player = _player;
    mAttackPoint = _Attack;
    mSpeed = _speed;

    this->setPixmap(QPixmap(":/1/player bullet.png"));
    this->setScale(0.01);
    if (m_player->isFacingRight()) {
        mPos = m_player->getCenterPos()+QPointF(m_player->pixmap().width()*scale(),m_player->pixmap().height()*scale()/2.5);
    } else {
        mPos = m_player->getCenterPos()+QPointF(m_player->pixmap().width()*scale()*(-1.5),m_player->pixmap().height()*scale()/2.5);
    }
    this->setPos(mPos);

    mDir = _dir;
}
