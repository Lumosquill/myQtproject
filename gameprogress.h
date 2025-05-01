#ifndef GAMEPROGRESS_H
#define GAMEPROGRESS_H

#include <QObject>
#include<QDebug>
class Gameprogress : public QObject
{
    Q_OBJECT
    Gameprogress();
    static Gameprogress* instance;//实现一个单例模式，确保GameControl全局只有一个实例，并提供一个全局访问点
public:
    static Gameprogress* Instance()
    {
        if(instance == nullptr)
        {
            return instance = new Gameprogress();
        }
        return instance;
    }

    ~Gameprogress()
    {
        qDebug()<<"Gameprogress released";
    }

    void EnemyAppearProgress(int _time);
    void ThoughtBubbleAppear(int _time);
    void TimeturnerAppear();
    void FelixfelicisAppear();

public:
    int GameTime;

};

#endif // GAMEPROGRESS_H
