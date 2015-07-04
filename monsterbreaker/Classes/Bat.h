#pragma once
#ifndef __BAT_H__
#define __BAT_H__

#include "cocos2d.h"
#include "Monster.h"

class Bat : public Monster
{
private :
	bool sleepState = true;

public :
	Bat();

	void Init();
	static Bat* create();

	virtual void Damaged(int i);
	virtual void ChooseMood();

	virtual void update(float dt);

	virtual void MoodStay(float dt);
	virtual void MoodMove(float dt);
	virtual void MoodAttack(float dt);
	virtual void MoodSleep(float dt);
	virtual void StartAnimation();
	virtual void Ani(const char * str, cocos2d::__Dictionary* dic);

	virtual void InitSprite();

};

#endif // __BAT_H__
 