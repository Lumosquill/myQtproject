#include "player.h"
#include"playerbullet.h"
#include"gamewidget.h"
#include<QDebug>
Player::Player()
{
    setPixmap(QPixmap(":/1/harry.png"));

    mhp = 100;
    m_maxhp=100;
    mDefence = 0;

    m_mana=60;
    m_maxmana=100;

    m_myspeed = 2;
    mSpeedRatio = 0;

    mBulletNum = 5;//子弹个数
}

QPointF Player::getPos()
{
    return pos();
}
void Player::setFaceDir(char x)
{
    QString address = ":/1/harry";
    if(x=='l')
    {
        address += "-mir.png";
        facingright=false;

    }
    else
    {
        address += ".png";
        facingright=true;
    }
    QPixmap pixmap(address);

    this->setPixmap(pixmap);
}
void Player::getHurt(int _attack)
{
    qreal defen = mDefence;
    defen /= 8;
    mhp -= (int)(_attack *  pow(0.5,defen))==0 ? 1 : (int)(_attack *  pow(0.5,defen));
}
void Player::playerShoot(QPointF _dir)
{
    int _attack =  (int)(getMana() * (1+getManaRatio()));//攻击力计算
    if(_attack < 1) _attack = 1;
    qreal defaultSpeed = 8.0; //设定默认子弹速度

    //生成主子弹
    for (int i = 0; i < mBulletNum; i++)
    {
        auto* playerBL = new playerbullet(this, _dir, _attack, defaultSpeed);
        Gamewidget::widget->getGameScene().addItem(playerBL);
        Gamewidget::widget->mMyBulletList.append(playerBL);
        playerBL->setZValue(2);
        for(int j=0;j<5 * i;j++)
        {
            playerBL->BulletMove();
        }
    }
}
int Player::getAttackInterval()
{
    qreal _attackSpeed = mAttackSpeed/80;
    OriginalAttackInterval=800;
    LimitedAttackInterval=200;
    qreal deltaT =OriginalAttackInterval * pow(0.5,_attackSpeed);
    return (int)deltaT < LimitedAttackInterval ? LimitedAttackInterval : (int)deltaT;
    //攻击速度越高，攻击间隔越短，但有下限，不会无限减少
}
void Player::resetplayer()
{
    m_myspeed = 2;
    mhp = 100;
    m_maxhp = 100;
    m_mana = 1;
    mManaRatio = 0;
    mAttackSpeed = 0;//攻击速度
    mSpeedRatio = 0;//移速加成
    mBulletNum = 1;//子弹个数
}
void Player::restoreHP(int num)
{
    mhp+=num;
}
void Player::restoreMana(int num)
{
    m_mana+=num;
}
