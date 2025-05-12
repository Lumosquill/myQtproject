#ifndef PLAYER_H
#define PLAYER_H
#include"gameobject.h"
#include<QPointF>
#include<QGraphicsPixmapItem>
class Player : public Gameobject {
    Q_OBJECT
public:
    Player();
    int getHP(){return mhp;}
    int getMaxHP(){return m_maxhp;}
    void restoreHP(int num);

    qreal getSpeed(){return m_myspeed;}
    qreal getSpeedRatio(){return mSpeedRatio;}

    int getMana(){return m_mana;}
    int getMaxMana(){return m_maxmana;}
    qreal getManaRatio(){return mManaRatio;}
    int getAttackSpeed(){return mAttackSpeed;}
    int getAttackInterval();
    void restoreMana(int num);

    QPointF getPos();
    void setFaceDir(char x);
    bool getFaceDir(){return faceDir;}
    bool isFacingRight() const { return facingright; }

    int mBulletNum = 1;//子弹个数
    void getHurt(int _attack);
    void playerShoot(QPointF _dir);
    void resetplayer();

    qreal m_myspeed;//移动速度 代码跟Qt图形系统（如 QPointF, QRectF, QTransform）相关，用qreal浮点数
    qreal mSpeedRatio;//速度调整因子

    int mhp;//生命值
    int m_maxhp;//生命值上限
    int mDefence;

    int m_mana;//魔力值（攻击）
    int m_maxmana;
    int mAttackSpeed;//攻击速度
    qreal mManaRatio;//魔力值提升倍率
    int OriginalAttackInterval;//初始攻击间隔
    int LimitedAttackInterval;//最短攻击间隔

    bool faceDir;//0->left 1->right
    bool facingright=true;

signals:
    void isHurt();
    void isDead();

};

#endif // PLAYER_H
