#pragma once
#ifndef __WOLF_H__
#define __WOLF_H__

#include "cocos2d.h"
#include "Monster.h"

class Wolf: public Monster
{
private :
public :
	Wolf();
	static Wolf* create();

//	virtual void MoodStay(float dt);

	virtual void Die();
	virtual void ChooseMood();
	virtual void MoodMove(float dt);
	virtual void MoodAttack(float dt);
	virtual void InitSprite();

};

#endif // __WOLF_H__
 