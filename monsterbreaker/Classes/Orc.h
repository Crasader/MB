#pragma once
#ifndef __ORC_H__
#define __ORC_H__

#include "cocos2d.h"
#include "Monster.h"

class Orc: public Monster
{
private :
public :
	Orc();
	static Orc* create();

	virtual void MoodStay(float dt);
	virtual void MoodMove(float dt);
	virtual void MoodAttack(float dt);
	virtual void InitSprite();
};

#endif // __GREMLIN_H__
 