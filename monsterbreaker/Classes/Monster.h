#pragma once
#ifndef __MONSTER_H__
#define __MONSTER_H__

#include "cocos2d.h"
#include "Character.h"
#include "Hero.h"

#include "ItemBomb.h"
#include "ItemCoin.h"
#include "ItemKey.h"
#include "ItemHalfHeart.h"
#include "ItemHeart.h"
#include "ItemSoulHeart.h"
#include "ItemHalfSoulHeart.h"

class Monster : public Character
{
protected:
	int mood;
	float timer;
	const float kTimerUp = -9999.0f;
	int dir;

	cocos2d::Sprite * hpBgSpr;
	cocos2d::Sprite * hpCurrentSpr;
	CC_SYNTHESIZE(std::string, _bossName, BossName);

	virtual void SetMood(int newMood);
	virtual void ChooseMood();
	virtual float StayTime();
	virtual float MoveTime();
	virtual float AttackTime();
	float stayTime;
	float attackTime;
	float moveTime;

	cocos2d::Layer * layer;

public:
	Monster();
	~Monster();

	cocos2d::Size visibleSize;

	virtual void Damaged(int i);
	virtual void update(float dt);

	virtual void MoodStay(float dt);
	virtual void MoodMove(float dt);
	virtual void MoodAttack(float dt);
	
	virtual void BaseMoveMent(float dt);
	virtual void BaseMoveMent2(float dt);
	void SetMonsterData();
	virtual void InitSprite();
	virtual void Draw(cocos2d::Layer * layer);
	virtual void StartAnimation();

	virtual void Die();

	virtual void DropItem(int itemID);
};

#endif // __MONSTER_H__
 