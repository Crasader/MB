#pragma once
#ifndef __SLIME_H__
#define __SLIME_H__

#include "cocos2d.h"
#include "Monster.h"

class Slime : public Monster
{
private :

public :
	Slime();
	void Init();
	static Slime* create();

//	virtual void MoodStay(float dt);
//	virtual void MoodMove(float dt, char * dir, int kAction);
//	virtual void MoodAttack(float dt);
};

#endif // __SLIME_H__
 