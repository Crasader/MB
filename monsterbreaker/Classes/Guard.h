#pragma once
#ifndef __GUARD_H__
#define __GUARD_H__

#include "cocos2d.h"
#include "Monster.h"

class Guard: public Monster
{
private :
public :
	Guard();
	static Guard* create();

//	virtual void MoodStay(float dt);

	virtual void Die();
	virtual void ChooseMood();
//	virtual void MoodMove(float dt);
	virtual void MoodStay(float dt);
	virtual void MoodAttack(float dt);
	virtual void InitSprite();

};

#endif // __GUARD_H__
 