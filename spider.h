#ifndef SPIDER_H
#define SPIDER_H
#include"enemybase.h"
class Spider: public Enemybase
{
    bool hasShot = false;
public:
    Spider(Player* _player, int _HP, int _AttackPoint, qreal _Speed);
    virtual ~Spider();
    void startSkill();
    void setMirrorPixmap(QString name);
    bool isConfused = false;
    void startConfusedVisualEffect();
    void stopConfusedVisualEffect();
    void spidershoot();
private:
    QTimer* mSpinTimer = nullptr;
    qreal mRotationAngle = 0;
    int spinFrame = 0;
};

#endif // SPIDER_H
