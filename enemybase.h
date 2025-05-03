#ifndef ENEMYBASE_H
#define ENEMYBASE_H
#include "gameobject.h"
#include "player.h"
#include<QTimer>
#include<QString>
#include<QRandomGenerator>

class Enemybase: public Gameobject
{
    Q_OBJECT
    //如果一个类继承自QObject或其子类（如QWidget)，并且需要使用信号和槽机制，那么必须在类的声明部分添加 Q_OBJECT宏，否则Qt的元对象系统无法正确解析该类。
public:
    explicit Enemybase(Gameobject *parent = nullptr);
    //如果一个类有可能被继承，并且可能通过基类指针删除对象，那么它应该有 virtual析构函数
    //否则通过基类指针删除派生类对象时，只会调用基类的析构函数，而不会调用派生类的析构函数，导致派生类的资源（比如new分配的内存）无法正确释放。
    virtual ~Enemybase();

    Enemybase(Player* _player, int _HP, int _AttackPoint, qreal _Speed);
    void setDir(bool right){mMoveDir = right;}
    int getAttackPoint(){return mAttackPoint;}
    bool getFaceDir(){return mFaceDir;}
    int getHP(){return mHP;}
    virtual void startSkill();//虚函数，让子类可以重写，调用时会自动用子类的版本
    virtual void getHurt(int _attack);
    virtual void enemyMove(bool dir = 0);
    virtual void setMirrorPixmap(QString);
    virtual void startConfusedVisualEffect();
    virtual void stopConfusedVisualEffect();



signals:
    void isHurt();
    void isDead();

protected:
    int mHP;
    qreal mSpeed;
    int mAttackPoint;
    Player* m_player;
    bool mMoveDir = 0;
    bool mFaceDir = 1;
    int mNo;//编号 1：小摄魂怪 2：蜘蛛 3：大摄魂怪

};

#endif // ENEMYBASE_H
