#pragma once
#ifndef __SOUL_H__
#define __SOUL_H__

#include "cocos2d.h"
#include "Monster.h"

class Soul: public Monster
{
private :
public :
	Soul();
	static Soul* create();
	
	virtual void Die();
	virtual void ChooseMood();
	virtual void MoodMove(float dt);
	virtual void MoodStay(float dt);
	virtual void MoodAttack(float dt);
	virtual void InitSprite();

};

#endif // __SOUL_H__
 