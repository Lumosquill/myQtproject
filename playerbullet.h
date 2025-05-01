#ifndef PLAYERBULLET_H
#define PLAYERBULLET_H
#include"bulletbase.h"
#include"player.h"
class playerbullet: public Bulletbase
{
public:
    playerbullet(Player *_player, QPointF _dir, int _Attack, qreal _speed = 8);
    playerbullet(Player *_player,BulletDir _dir,int _Attack, qreal _speed = 8);

private:
    Player* m_player;

};

#endif // PLAYERBULLET_H
