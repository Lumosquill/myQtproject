#ifndef MYGV_H
#define MYGV_H
#include<QGraphicsView>
#include<QMouseEvent>
class mygv: public QGraphicsView
{
    Q_OBJECT
public:
    explicit mygv();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
};

#endif // MYGV_H
