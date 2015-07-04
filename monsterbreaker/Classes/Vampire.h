#pragma once
#ifndef __VAMPIRE_H__
#define __VAMPIRE_H__

#include "cocos2d.h"
#include "Monster.h"

class Vampire: public Monster
{
private :
public :
	Vampire();
	static Vampire* create();

//	virtual void MoodStay(float dt);

	virtual void Die();
	virtual void ChooseMood();
	virtual void MoodMove(float dt);
	virtual void MoodStay(float dt);
	virtual void MoodAttack(float dt);
	virtual void InitSprite();

};

#endif // __VAMPIRE_H__
 