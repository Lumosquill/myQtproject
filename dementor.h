#ifndef DEMENTOR_H
#define DEMENTOR_H
#include"enemybase.h"
class Dementor: public Enemybase
{
   // Q_OBJECT
public:
    Dementor(Player* _player, int _HP, int _AttackPoint, qreal _Speed);
    void setMirrorPixmap(QString name);
    void startSkill();
    void dementorshoot();
    QTimer* mShootTimer = nullptr;
    QTimer* confusionSwitchTimer = nullptr;
    QTimer* confusedEffectTimer = nullptr;
    bool currentMirrorState = false; // false = 左, true = 右
    bool isConfused = false;
    void startConfusedVisualEffect();
    void stopConfusedVisualEffect();
    void switchMirrorPixmap();
    int floatFrame = 0; //用于计算上下抖动
};

#endif // DEMENTOR_H
