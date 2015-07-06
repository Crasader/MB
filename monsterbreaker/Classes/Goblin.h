#pragma once
#ifndef __GOBLIN_H__
#define __GOBLIN_H__

#include "cocos2d.h"
#include "Monster.h"

class Goblin: public Monster
{
private :
public :
	Goblin();
	static Goblin* create();

	virtual void Damaged(int i);
	virtual void Die();
	virtual void ChooseMood();
	virtual void MoodMove(float dt);
	virtual void MoodAttack(float dt);
	virtual void InitSprite();

};

#endif // __GOBLIN_H__
 