#pragma once
#ifndef __SLIMEKING_H__
#define __SLIMEKING_H__

#include "cocos2d.h"
#include "Monster.h"
#include "SlimeKingMiddle.h"
#include "MonsterManager.h"
class MonsterManager;
class SlimeKingMiddle;

class SlimeKing : public Monster
{
private :
public :
	SlimeKing();
	static SlimeKing* create();

	virtual void MoodStay(float dt);
	virtual void MoodMove(float dt);
	virtual void MoodAttack(float dt);
	virtual void Die();
	virtual void InitSprite();
	virtual void MakeTheOtherSelf();
};

#endif // __SLIMEKING_H__
 