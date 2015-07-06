#pragma once
#ifndef __QUESTION_MARK_H__
#define __QUESTION_MARK_H__

#include "cocos2d.h"
#include "Monster.h"
#include "MonsterManager.h"

class QuestionMark: public Monster
{
private :
public :
	QuestionMark();
	static QuestionMark* create();

	float timer2;

	virtual void Die();
	virtual void ChooseMood();
	virtual void update(float dt);
	virtual void InitSprite();

	virtual void CreateRandomMonster();
};

#endif // __QUESTION_MARK_H__
 