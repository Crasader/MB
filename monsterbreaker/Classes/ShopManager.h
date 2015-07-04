#pragma once
#ifndef __SHOP_MANAGER_H__
#define __SHOP_MANAGER_H__

#include "cocos2d.h"
#include "Definitions.h"
#include "Hero.h"
#include "MapManager.h"

#include "Item.h"
#include "ItemBomb.h"
#include "ItemHalfHeart.h"
#include "ItemHeart.h"
#include "ItemKey.h"
#include "ItemSoulHeart.h"
#include "ItemHalfSoulHeart.h"

#include "Merchant.h"
#include "ChestItem.h"
#include "SkillItem.h"
#include "ArmorItem.h"

class ShopManager : public cocos2d::Node
{
public:
	ShopManager(cocos2d::Layer * layer, Hero * hero);
	~ShopManager();

	static ShopManager* create(cocos2d::Layer * layer, Hero * hero);

	cocos2d::Layer * layer;
	cocos2d::Vec2 origin;
	cocos2d::Size visibleSize;
	cocos2d::Size contentSize;
	cocos2d::Vec2 startPoint;

	Hero * hero;
	MapManager * mm;
	void createShopItem();
};

#endif // __SHOP_MANAGER_H__
