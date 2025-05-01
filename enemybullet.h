#ifndef ENEMYBULLET_H
#define ENEMYBULLET_H
#include"bulletbase.h"
#include"dementor.h"
#include"bigdementor.h"
#include"spider.h"
#include"player.h"

class Enemybullet: public Bulletbase
{
public:
    Enemybullet(Enemybase *_owner,BulletDir _dir,int _Attack, qreal _speed = 8,int _type = 0);
private:
    Enemybase* mOwner;
    int type = 0;

};

#endif // ENEMYBULLET_H
