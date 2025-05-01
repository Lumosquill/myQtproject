#include "bulletbase.h"
#include"gamewidget.h"
Bulletbase::Bulletbase() {}
Bulletbase::Bulletbase(Gameobject* _owner)
{
    mOwner = _owner;
}
void Bulletbase::BulletMove()
{
    switch(mDir)
    {
    case DirN:this->moveBy(0,-getSpeed());break;
    case DirS:this->moveBy(0,getSpeed());break;
    case DirW:this->moveBy(-getSpeed(),0);break;
    case DirE:this->moveBy(getSpeed(),0);break;
    case MouseDir:
    {
        this->moveBy(getSpeed()*getbMoveDir().x(),getSpeed()*getbMoveDir().y());
        //QPointF moveDir = QPointF(1,0);// 方向向量，默认向右
    }
    case PlayerDir:this->moveBy(getSpeed()*getbMoveDir().x(),getSpeed()*getbMoveDir().y());
    this->show();
    }
}

