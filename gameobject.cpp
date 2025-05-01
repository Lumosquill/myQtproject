#include "gameobject.h"

Gameobject::Gameobject(QObject *parent)
    : QObject{parent}
{}
Gameobject::~Gameobject()
{
    //qDebug()<<"gameobject deleted";
}

 QPointF Gameobject::getCenterPos()
{
    //pos().x()&pos().y()：获取当前对象的左上角坐标
    return QPointF(pos().x()+(pixmap().width()*scale()/2),pos().y()+(pixmap().height()*scale()/2));
}

