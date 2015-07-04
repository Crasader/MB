#pragma once
#ifndef __DATA_MANAGER_H__
#define __DATA_MANAGER_H__

#include "cocos2d.h"
#include "Definitions.h"
#include "Hero.h"
#include "MapManager.h"

#include "Item.h"
#include "ItemBomb.h"
#include "ItemHalfHeart.h"
#include "ItemHeart.h"
#include "ItemHalfSoulHeart.h"
#include "ItemSoulHeart.h"
#include "ItemKey.h"
#include "ItemCoin.h"

#include "SkillItem.h"
#include "ArmorItem.h"

#include "Brick.h"
#include "DoubleBrick.h"
#include "SingleBrick.h"
#include "SolidBrick.h"

class DataManager : public cocos2d::Node
{
public:
	DataManager(cocos2d::Layer * layer, Hero * hero);
	~DataManager();

	static DataManager* create(cocos2d::Layer * layer, Hero * hero);

	cocos2d::Layer * layer;
	cocos2d::Vec2 origin;
	cocos2d::Size visibleSize;
	MapManager * mapManager;

	Hero * hero;
	int x;
	int y;

	void ClearData();
	void SaveData();
	void LoadData();
	void CreateItems(const char * n, float x, float y, bool isShop);
	void CreateChestItems(int cID, float x, float y, bool isShop);
	void CreateSkillItems(int sID, float x, float y, bool isShop, int currentPoint);
	void CreateArmorItems(int aID, float x, float y, bool isShop);
	void CreateBricks(int brickID, float x, float y);
};

#endif // __ITEM_MANAGER_H__
