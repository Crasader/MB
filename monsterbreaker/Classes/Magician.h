#pragma once
#ifndef __MAGICIAN_H__
#define __MAGICIAN_H__

#include "cocos2d.h"
#include "Hero.h"

class Magician : public Hero
{
public:
	Magician();
	~Magician();
	
	static Magician* create();

	virtual void DecreaseCurrentSp(int i);
	virtual void Damaged(int i);

	virtual void SkillUse();
	bool IsEnoughSp(int needSp);
	virtual void DoSkillEvent(cocos2d::Vec2 touch);
};

#endif // __WARRIOR_H__
 