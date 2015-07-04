#pragma once
#ifndef __DEVIL_H__
#define __DEVIL_H__

#include "cocos2d.h"
#include "Monster.h"
#include "Dragon.h"

class Devil: public Monster
{
private :
public :
	cocos2d::Layer * layer;
	Devil(cocos2d::Layer * layer);
	static Devil* create(cocos2d::Layer * layer);
	bool isFury;
	cocos2d::Node * fury;

	Dragon * d;

	virtual void ChooseMood();
	virtual void MoodStay(float dt);
	virtual void MoodAttack(float dt);
	virtual void InitSprite();
	virtual void update(float dt);
	virtual void SeqFire(cocos2d::Vec2 sp, cocos2d::Vec2 dp);
	virtual void Die();

	virtual void pause();
	virtual void resume();

};

#endif // __DEVIL_H__
 