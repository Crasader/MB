#pragma once
#ifndef __HALF_SHADOW_H__
#define __HALF_SHADOW_H__

#include "cocos2d.h"
#include "Monster.h"
#include "Definitions.h"

class HalfShadow : public Monster
{
private :

public :
	cocos2d::Layer * layer;
	HalfShadow(cocos2d::Layer * layer);
	
	static HalfShadow* create(cocos2d::Layer * layer);

	virtual void Damaged(int i);
	virtual void ChooseMood();

	virtual void update(float dt);

	virtual void MoodStay(float dt);
	virtual void MoodHide(float dt);
	virtual void MoodAttack(float dt);

	virtual void fadeOut();
	virtual void fadeIn();
	virtual void moveTo(cocos2d::Vec2 vec);
	virtual void StartAnimation();
//	virtual void Ani(const char * str, cocos2d::__Dictionary* dic);

	virtual void InitSprite();
	virtual void Die();

};

#endif // __HALF_H__
 