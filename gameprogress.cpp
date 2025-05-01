#include "gameprogress.h"
#include"gamewidget.h"
#include<QDebug>
Gameprogress::Gameprogress() {
    setParent(Gamewidget::widget);//链接对象树，以便正常析构
}
Gameprogress* Gameprogress::instance = nullptr;//instance是静态成员变量，它属于整个类，而不是某个特定的实例，故需要类外初始化
void Gameprogress::EnemyAppearProgress(int _time)
{
    GameTime = _time;
    if(GameTime >35)//摄魂怪出场
    {
        //enemySummon(int _HP, int _Attack, qreal _Speed, int _No)
        for(int i=0;i<QRandomGenerator::global()->bounded(1,3);i++)
            Gamewidget::widget->enemySummon(150,0.1,0.3,1);
    }
    else if(GameTime >20)//蜘蛛出场
    {
        for(int i=0;i<QRandomGenerator::global()->bounded(1,3);i++)
            Gamewidget::widget->enemySummon(1,0.01,0.7,2);
    }
    else if(GameTime >0)//大摄魂怪出场
    {
        Gamewidget::widget->enemySummon(150,0.1,0.3,3);
    }

}
void Gameprogress::TimeturnerAppear()
{
    Gamewidget::widget->timeturnerSummon();
}
void Gameprogress::FelixfelicisAppear()
{
    Gamewidget::widget->felix_felicisSummon();
}
void Gameprogress::ThoughtBubbleAppear(int _time)
{
    GameTime = _time;
    if(GameTime==45)
    {
        Gamewidget::widget->bubbleSummon(":/1/thoughtbubble1.png",thoughtbubble::LoseMana);
    }
    else if(GameTime==40)
        Gamewidget::widget->bubbleSummon(":/1/thoughtbubble6.png",thoughtbubble::GainMana);
    else if(GameTime==35)
    {
        Gamewidget::widget->bubbleSummon(":/1/thoughtbubble10.png",thoughtbubble::GainMana);
        Gamewidget::widget->bubbleSummon(":/1/thoughtbubble3.png",thoughtbubble::LoseMana);
    }
    else if(GameTime==30)
        Gamewidget::widget->bubbleSummon(":/1/thoughtbubble5.png",thoughtbubble::GainMana);
    else if(GameTime==25)
        Gamewidget::widget->bubbleSummon(":/1/thoughtbubble4.png",thoughtbubble::LoseMana);
    else if(GameTime==20)
        Gamewidget::widget->bubbleSummon(":/1/thoughtbubble9.png",thoughtbubble::GainMana);
    else if(GameTime==15)
        Gamewidget::widget->bubbleSummon(":/1/thoughtbubble7.png",thoughtbubble::GainMana);
    else if(GameTime==10)
        Gamewidget::widget->bubbleSummon(":/1/thoughtbubble2.png",thoughtbubble::LoseMana);
    else if(GameTime==5)
        Gamewidget::widget->bubbleSummon(":/1/thoughtbubble8.png",thoughtbubble::GainMana);

}
