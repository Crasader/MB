#pragma once
#ifndef __ARCHER_H__
#define __ARCHER_H__

#include "cocos2d.h"
#include "Monster.h"

class Archer: public Monster
{
private :
public :
	Archer();
	static Archer* create();

//	virtual void MoodStay(float dt);

	virtual void Die();
	virtual void ChooseMood();
	virtual void MoodMove(float dt);
	virtual void MoodAttack(float dt);
	virtual void InitSprite();

};

#endif // __ARCHER_H__
 