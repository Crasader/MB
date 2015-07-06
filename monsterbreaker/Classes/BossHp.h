#pragma once
#ifndef __BOSS_HP_H__
#define __BOSS_HP_H__

#include "cocos2d.h"
#include "Definitions.h"
#include "cocostudio\CocoStudio.h"
#include "ui\CocosGUI.h"
#include "Monster.h"

class BossHp : public cocos2d::Node
{
public:
	BossHp(cocos2d::Layer * layer);
	~BossHp();

	static BossHp* create(cocos2d::Layer * layer);

	cocos2d::Layer * layer;
	cocos2d::Vec2 origin;
	cocos2d::Size visibleSize;

	cocos2d::Node * node;
	cocos2d::Sprite * f;
	cocos2d::Sprite * b;
	cocos2d::ui::Text * bossName;
	
	Monster * target;

	void Debug();
	void update(float dt);
	void SetTarget(Monster * target);
};

#endif // __BOSS_HP_H__
