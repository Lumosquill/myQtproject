#include "gamewidget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Gamewidget w;
    w.show();
    return a.exec();
    QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
}
//组件	作用
//QGraphicsScene	逻辑场景，管理所有图形元素 比如作为游戏地图
//QGraphicsView	视图窗口，显示 QGraphicsScene 的一部分，并支持缩放、平移等操作 让玩家看到整个场景的某个部分，并提供交互功能
//QGraphicsItem	具体的图形元素（比如角色、道具）

//QGraphicsScene 只是一个逻辑场景，不能直接显示内容，而 QGraphicsView 是一个可视化窗口，用来显示 QGraphicsScene
