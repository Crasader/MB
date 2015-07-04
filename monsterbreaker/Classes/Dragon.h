#pragma once
#ifndef __DRAGON_H__
#define __DRAGON_H__

#include "cocos2d.h"
#include "Monster.h"
#include "cocostudio\CocoStudio.h"
#include "ui\CocosGUI.h"

class Dragon: public cocos2d::Node
{
private :
public :
	float timer;
	const float kTimerUp = -9999.0f;

	CC_SYNTHESIZE(bool, isFury, Fury);
	CC_SYNTHESIZE(bool, usingSkill, UsingSkill);
	cocos2d::Layer * layer;
	Dragon(cocos2d::Layer * layer);
	static Dragon* create(cocos2d::Layer * layer);

	cocos2d::Node * node;
	cocos2d::Node * mNode;
	cocos2d::Sprite * m1;
	cocos2d::Sprite * m2;
	cocos2d::Sprite * f1;
	cocos2d::Sprite * f2;
	cocos2d::Node * size;

	cocos2d::Sprite * flame;

	virtual void InitSprite();
	virtual void FireLeft();
	virtual void FireRight();
	virtual void Fire();
	virtual void setMyVisibile(cocos2d::Sprite * spr, bool b);
	virtual void Die();
	virtual cocos2d::Size getContentSize();
	virtual cocos2d::Vec2 getMousePosition();
	virtual void update(float dt);
	virtual void setFlameVisible(bool b);

	virtual void pause();
	virtual void resume();

};

#endif // __DRAGON_H__
 