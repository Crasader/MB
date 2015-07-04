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

//	virtual void MoodStay(float dt);

//	virtual void Damaged(int i);
	virtual void Die();
	virtual void ChooseMood();
	virtual void update(float dt);
//	virtual void MoodMove(float dt);
//	virtual void MoodAttack(float dt);
	virtual void InitSprite();

	virtual void CreateRandomMonster();
};

#endif // __QUESTION_MARK_H__
 