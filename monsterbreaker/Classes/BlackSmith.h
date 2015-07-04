#pragma once
#ifndef __BLAKC_SMITH_H__
#define __BLAKC_SMITH_H__

#include "cocos2d.h"
#include "Monster.h"

class BlackSmith: public Monster
{
private :
public :
	BlackSmith();
	static BlackSmith* create();

//	virtual void MoodStay(float dt);

	virtual void Die();
	virtual void ChooseMood();
	virtual void MoodMove(float dt);
	virtual void MoodAttack(float dt);
	virtual void InitSprite();

};

#endif // __BLAKC_SMITH_H__
 