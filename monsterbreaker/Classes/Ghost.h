#pragma once
#ifndef __GHOST_H__
#define __GHOST_H__

#include "cocos2d.h"
#include "Monster.h"
#include "MonsterManager.h"

class Ghost : public Monster
{
private :

public :
	Ghost();

	void Init();
	static Ghost* create();

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
	virtual void Ani(const char * str, cocos2d::__Dictionary* dic);

	virtual void InitSprite();

};

#endif // __GHOST_H__
 