#pragma once
#ifndef __SLIMEKING_MIDDLE_H__
#define __SLIMEKING_MIDDLE_H__

#include "cocos2d.h"
#include "Monster.h"
#include "Slime.h"
#include "MonsterManager.h"
class MonsterManager;

class SlimeKingMiddle : public Monster
{
private :
public :
	SlimeKingMiddle();
	static SlimeKingMiddle* create();

	virtual void MoodStay(float dt);
	virtual void MoodMove(float dt);
	virtual void MoodAttack(float dt);
	virtual void Die();
	virtual void InitSprite();
	virtual void MakeTheOtherSelf();

};

#endif // __SLIMEKING_MIDDLE_H__
 