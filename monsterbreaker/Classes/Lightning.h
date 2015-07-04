#pragma once
#ifndef  __LIGHTNING_H__
#define __LIGHTNING_H__

#include "cocos2d.h"
#include "GameObject.h"
#include "cocostudio\CocoStudio.h"
#include "Hero.h"

class Lightning : public cocos2d::Node
{
private:
public:
	float kTimer;
	CC_SYNTHESIZE(int, _attackPoint, AttackPoint);
//	int attackPoint = 2;

	const float kTimerUp= -9999.0f;

	cocos2d::Layer * layer;

	// target node
	cocos2d::Node * t;
	// lightning node
	cocos2d::Node * l;

	Lightning(cocos2d::Layer * layer, int ap);
	~Lightning();
	static Lightning* create(cocos2d::Layer * layer, int ap);

	void InitSprite();

	void boom();

	void RemoveAll();
	virtual cocos2d::Size getContentSize();
	virtual void pause();
	virtual void resume();
};

#endif // __LIGHTNING_H__
 