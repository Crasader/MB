#pragma once
#ifndef __TREASURE_MANAGER_H__
#define __TREASURE_MANAGER_H__

#include "cocos2d.h"
#include "Definitions.h"
#include "Chest.h"
#include "Hero.h"
#include "MapManager.h"

class TreasureManager : public cocos2d::Node
{
public:
	TreasureManager(cocos2d::Layer * layer, Hero * hero);
	~TreasureManager();

	static TreasureManager* create(cocos2d::Layer * layer, Hero * hero);

	cocos2d::Layer * layer;
	cocos2d::Vec2 origin;
	cocos2d::Size visibleSize;
	cocos2d::Size contentSize;
	cocos2d::Vec2 startPoint;

	Hero * hero;
	void createTreasure();
};

#endif // __TREASURE_MANAGER_H__
