#pragma once
#ifndef  __FINGER_POINTER_H__
#define __FINGER_POINTER_H__

#include "cocos2d.h"
#include "GameObject.h"
#include "cocostudio\CocoStudio.h"

class FingerPointer : public cocos2d::Node
{
private:
public:
	cocos2d::Layer * layer;

	// node
	cocos2d::Node * node;
	cocos2d::Sprite * spr;
	cocos2d::Node * c;

	FingerPointer(cocos2d::Layer * layer);
	~FingerPointer();
	static FingerPointer* create(cocos2d::Layer * layer);

	void InitSprite();

	void RemoveAll();
	virtual cocos2d::Size getContentSize();
	virtual void pause();
	virtual void resume();
	virtual void setClickVisible(bool b);

	virtual void setOpacity(float op);
	
	void clickHold(float dt);
	void clickCancle(float dt);

	void fadeIn(float dt);
	void fadeOut(float dt);

	void mySetPosition(cocos2d::Vec2 vec);

};

#endif // __FINGER_POINTER_H__
 