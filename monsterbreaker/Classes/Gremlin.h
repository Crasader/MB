#pragma once
#ifndef __GREMLIN_H__
#define __GREMLIN_H__

#include "cocos2d.h"
#include "Monster.h"
//#include "MonsterManager.h"
//class MonsterManager;
//class SlimeKingMiddle;

class Gremlin: public Monster
{
private :
public :
	Gremlin();
	static Gremlin* create();

	virtual void MoodStay(float dt);
	virtual void MoodMove(float dt);
	virtual void MoodAttack(float dt);
	virtual void InitSprite();
};

#endif // __GREMLIN_H__
 