#ifndef BULLETBASE_H
#define BULLETBASE_H
#include "gameobject.h"


class Bulletbase: public Gameobject
{
    //Q_OBJECT
public:
    Bulletbase();
    Bulletbase(Gameobject* _owner);
    virtual ~Bulletbase(){}

    qreal getSpeed(){return mSpeed;}
    QPointF getbMoveDir(){return moveDir;}
    int getAttackPoint(){return mAttackPoint;}

    void BulletMove();

    enum BulletDir{
        DirN,
        DirS,
        DirW,
        DirE,
        MouseDir,
        PlayerDir};
    qreal mSpeed;//子弹发射速度
protected:
    Gameobject* mOwner;

    int mAttackPoint;
    QPointF mPos;//子弹的初始位置
    BulletDir mDir;//子弹的位移方向
    QPointF moveDir = QPointF(1,0);//方向向量，默认向右

};

#endif // BULLETBASE_H
