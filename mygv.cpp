#include "mygv.h"
#include"gamewidget.h"
mygv::mygv() {}
void mygv::mousePressEvent(QMouseEvent *event)
{
    Gamewidget::widget->mousePressEvent(event);
}
void mygv::mouseMoveEvent(QMouseEvent *event)
{
    Gamewidget::widget->mouseMoveEvent(event);
}
void mygv::mouseReleaseEvent(QMouseEvent *event)
{
    Gamewidget::widget->mouseReleaseEvent(event);
}
