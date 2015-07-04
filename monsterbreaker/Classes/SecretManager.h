#pragma once
#ifndef __SECRET_MANAGER_H__
#define __SECRET_MANAGER_H__

#include "cocos2d.h"
#include "Definitions.h"
#include "Chest.h"
#include "Hero.h"
#include "MapManager.h"

#include "Item.h"
#include "ItemBomb.h"
#include "ItemHalfHeart.h"
#include "ItemHeart.h"
#include "ItemKey.h"

#include "Merchant.h"

class SecretManager : public cocos2d::Node
{
public:
	SecretManager(cocos2d::Layer * layer, Hero * hero);
	~SecretManager();

	static SecretManager* create(cocos2d::Layer * layer, Hero * hero);

	cocos2d::Layer * layer;
	cocos2d::Vec2 origin;
	cocos2d::Size visibleSize;
	cocos2d::Size contentSize;
	cocos2d::Vec2 startPoint;

	Hero * hero;
	void createSecretItem();
};

#endif // __SECRET_MANAGER_H__
