#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include <QGraphicsPixmapItem>
#include <QObject>
#include<QDebug>
#include <QPointF>
class Gameobject : public QObject,public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Gameobject(QObject *parent = nullptr);
    ~Gameobject();

    QPointF getCenterPos();//获取中心位置
signals:
};

#endif // GAMEOBJECT_H
