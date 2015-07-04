#pragma once
#ifndef __KNIGHT_H__
#define __KNIGHT_H__

#include "cocos2d.h"
#include "Monster.h"

class Knight: public Monster
{
private :
public :
	Knight();
	static Knight* create();

//	virtual void MoodStay(float dt);

	virtual void Die();
	virtual void ChooseMood();
	virtual void MoodMove(float dt);
	virtual void MoodStay(float dt);
	virtual void MoodAttack(float dt);
	virtual void InitSprite();

};

#endif // __KNIGHT_H__
 