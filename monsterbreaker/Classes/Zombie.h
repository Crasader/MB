#pragma once
#ifndef __ZOMBIE_H__
#define __ZOMBIE_H__

#include "cocos2d.h"
#include "Monster.h"
//#include "MonsterManager.h"
//class MonsterManager;
//class SlimeKingMiddle;

class Zombie: public Monster
{
private :
public :
	Zombie();
	static Zombie* create();

	virtual void ChooseMood();
	virtual void MoodMove(float dt);
	virtual void MoodAttack(float dt);
	virtual void InitSprite();
};

#endif // __ZOMBIE_H__
 