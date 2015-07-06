#pragma once
#ifndef __SWORD_H__
#define __SWORD_H__

#include "cocos2d.h"
#include "Definitions.h"
#include "cocostudio\CocoStudio.h"
#include "ui\CocosGUI.h"
#include "SoundManager.h"

class Sword : public cocos2d::Node
{
private :
	cocos2d::Layer * layer;
	cocos2d::Vec2 origin;
	cocos2d::Size visibleSize;

public :
	cocos2d::Node * node;
	cocos2d::Sprite * skill;

	Sword(cocos2d::Layer * layer);

	static Sword* create(cocos2d::Layer * layer);

	virtual void InitSprite();
	void Swing();
	void UseSkill();

	void FadeIn(float t);
	void FadeOut(float t);
};

#endif // __SWORD_H__
 