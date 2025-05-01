#ifndef THOUGHTBUBBLE_H
#define THOUGHTBUBBLE_H
#include "gameobject.h"
#include <QGraphicsPixmapItem>
#include <QTimer>
class thoughtbubble: public Gameobject
{
    Q_OBJECT
public:
    enum EffectType { GainMana, LoseMana }; //魔力效果类型（增加/减少）
    EffectType effect; //暴露出去，方便外部读取

    thoughtbubble(const QString& imagePath, EffectType type);

public slots:
    void floatAround();   //自由漂浮
    void destroySelf();   //自动销毁

signals:
    void bubbleDestroyed(thoughtbubble* self);

private:
    QTimer* floatTimer;
    QTimer* lifeTimer;
    qreal dx;
    qreal dy;
    qreal currentOpacity = 1.0;
    int elapsedTime; // 毫秒
};

#endif // THOUGHTBUBBLE_H
