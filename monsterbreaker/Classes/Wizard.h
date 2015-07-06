#pragma once
#ifndef __WIZARD_H__
#define __WIZARD_H__

#include "cocos2d.h"
#include "Monster.h"
#include "MonsterManager.h"

class Wizard: public Monster
{
private :
public :
	Wizard();
	static Wizard* create();

	cocos2d::Node * charge;

	virtual void Die();
	virtual void ChooseMood();
	virtual void MoodMove(float dt);
	virtual void MoodCharge(float dt);
	virtual void MoodCharge2(float dt);
	virtual void MoodAttack(float dt);
	virtual void MoodStay(float dt);
	virtual void InitSprite();

	virtual void fadeOut();
	virtual void fadeIn();
	virtual void moveTo(cocos2d::Vec2 vec);
	virtual void SeqFire(cocos2d::Vec2 sp, cocos2d::Vec2 dp);

	virtual void update(float dt);

};

#endif // __WIZARD_H__
 