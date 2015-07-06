#pragma once
#ifndef __TREASURE_HUNTER_H__
#define __TREASURE_HUNTER_H__

#include "cocos2d.h"
#include "Monster.h"

class TreasureHunter: public Monster
{
private :
public :
	TreasureHunter();
	static TreasureHunter* create();

	virtual void Damaged(int i);
	virtual void Die();
	virtual void ChooseMood();
	virtual void MoodAttack(float dt);
	virtual void InitSprite();

};

#endif // __TREASURE_HUNTER_H__
 