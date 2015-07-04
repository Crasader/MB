#pragma once
#ifndef __SCAVENGER_H__
#define __SCAVENGER_H__

#include "cocos2d.h"
#include "Monster.h"

class Scavenger: public Monster
{
private :
public :
	Scavenger();
	static Scavenger* create();

//	int dir = 0;
	
	float timer2;

	virtual void update(float dt);

//	virtual void Damaged(int i);
	virtual void Die();
	virtual void ChooseMood();
	virtual void MoodMove(float dt);
	virtual void MoodAttack(float dt);
	virtual void InitSprite();

};

#endif // __SCAVENGER_H__
 