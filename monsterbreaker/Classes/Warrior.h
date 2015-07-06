#pragma once
#ifndef __WARRIOR_H__
#define __WARRIOR_H__

#include "cocos2d.h"
#include "Hero.h"
#include "EffectManager.h"

class Warrior : public Hero
{
private:
public:

	Warrior();
	~Warrior();

	static Warrior* create();

	virtual void DecreaseCurrentSp(int i);
	virtual void Damaged(int i);

	virtual void SkillUse();
};

#endif // __WARRIOR_H__
 