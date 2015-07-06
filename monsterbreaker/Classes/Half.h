#pragma once
#ifndef __HALF_H__
#define __HALF_H__

#include "cocos2d.h"
#include "Monster.h"
#include "Definitions.h"
#include "Sword.h"
#include "HalfShadow.h"

class Half : public Monster
{
private :

public :
	Sword * sword;
	cocos2d::Layer * layer;
	Half(cocos2d::Layer * layer);
	cocos2d::Node * fury;

	bool usingSkill;
	bool isFury;
	float skillTime;

	static Half* create(cocos2d::Layer * layer);

	virtual void Damaged(int i);
	virtual void ChooseMood();

	virtual void update(float dt);

	virtual void MoodStay(float dt);
	virtual void MoodHide(float dt);
	virtual void MoodAttack(float dt);
	virtual void MoodAttack2(float dt);
	virtual void MoodSkill(float dt);

	virtual void fadeOut();
	virtual void fadeIn();
	virtual void moveTo(cocos2d::Vec2 vec);
	virtual void StartAnimation();

	virtual void InitSprite();
	virtual void SeqFire(cocos2d::Vec2 sp, cocos2d::Vec2 dp);
	virtual void Die();
	virtual void MakeShadow();

	cocos2d::Vector<Monster*> shadows;

	virtual void pause();
	virtual void resume();

};

#endif // __HALF_H__
 