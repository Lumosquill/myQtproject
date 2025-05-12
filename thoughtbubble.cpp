#include "thoughtbubble.h"
#include"gamewidget.h"
#include <QRandomGenerator>
#include <QGraphicsScene>
#include<QDebug>
thoughtbubble::thoughtbubble(const QString& imagePath, EffectType type): effect(type)
{
    setPixmap(QPixmap(imagePath));
    setScale(0.06);

    //初始化漂浮方向（小范围随机）
    dx = QRandomGenerator::global()->generateDouble() * 1.0 - 0.5;
    dy = QRandomGenerator::global()->generateDouble() * 1.0 - 0.5;

    //定时器控制“自由漂浮”
    floatTimer = new QTimer(this);
    connect(floatTimer, &QTimer::timeout, this, &thoughtbubble::floatAround);
    floatTimer->start(50);

    //生存时间结束自动销毁
    lifeTimer = new QTimer(this);
    connect(lifeTimer, &QTimer::timeout, this, &thoughtbubble::destroySelf);
    lifeTimer->start(5000);
}
void thoughtbubble::floatAround()
{

    //漂一点点，并且让方向轻微波动
    dx += QRandomGenerator::global()->generateDouble() * 0.2 - 0.1;
    dy += QRandomGenerator::global()->generateDouble() * 0.2 - 0.1;

    //限制最大移动速度
    dx = qBound(-1.0, dx, 1.0);
    dy = qBound(-1.0, dy, 1.0);
    setPos(x() + dx, y() + dy);

    // 更新时间（每次 floatTimer 触发 +50ms）
    elapsedTime += 50;
    currentOpacity -= 0.01;
    // 前两秒不变，后3秒逐渐变淡
    if (elapsedTime > 2000) {
        int fadeTime = elapsedTime - 2000;
        qreal ratio = 1.0 - (fadeTime / 3000.0); //3000ms内从1变到0
        currentOpacity = qMax(0.0, ratio);
        setOpacity(currentOpacity);
    }


}

void thoughtbubble::destroySelf()
{
    emit bubbleDestroyed(this);
    if (scene()) scene()->removeItem(this);
    deleteLater();
}
