#pragma once
#ifndef __ANGEL_H__
#define __ANGEL_H__

#include "cocos2d.h"
#include "Monster.h"
#include "Definitions.h"
#include "Lightning.h"

class Angel : public Monster
{
private :

public :
	cocos2d::Layer * layer;
	Angel(cocos2d::Layer * layer);
	cocos2d::Node * fury;
	cocos2d::Node * lightning;

	bool usingSkill;
	bool isFury;
	float skillTime;

	static Angel* create(cocos2d::Layer * layer);

	virtual void ChooseMood();

	virtual void update(float dt);

	virtual void MoodStay(float dt);
	virtual void MoodMove(float dt);
	virtual void MoodAttack(float dt);
	virtual void MoodSkill(float dt);

	virtual void StartAnimation();

	virtual void InitSprite();
	virtual void SeqFire(cocos2d::Vec2 sp, cocos2d::Vec2 dp);
	virtual void Die();

	virtual void Lightning();
	virtual void setVisibleLightning(bool b);
	virtual void createLightning(cocos2d::Vec2 p);
};

#endif // __ANGEL_H__
 