#pragma once
#ifndef  __CAGE_H__
#define __CAGE_H__

#include "cocos2d.h"
#include "GameObject.h"
#include "cocostudio\CocoStudio.h"
#include "ui\CocosGUI.h"
#include "Hero.h"
#include "EffectManager.h"
#include "MapManager.h"

class Cage : public cocos2d::Node
{
public:
	cocos2d::Layer * layer;

	cocos2d::Node * node;
	cocos2d::ui::Button * btn;
	cocos2d::Node * l1;
	cocos2d::Node * l2;
	cocos2d::Node * l3;

	Cage(cocos2d::Layer * layer, Hero * hero, int lockCnt);
	~Cage();

	Hero * hero;
	int lockCnt;
	bool clickOk;

	static Cage* create(cocos2d::Layer * layer, Hero * hero, int lockCnt);

	void InitSprite();
	void ClickCage();
	void RemoveAll();

	
};

#endif // __CAGE_H__
 