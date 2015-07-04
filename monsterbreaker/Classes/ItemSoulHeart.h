#pragma once
#ifndef __ITEM_SOUL_HEART_H__
#define __ITEM_SOUL_HEART_H__

#include "cocos2d.h"
#include "Definitions.h"
#include "Hero.h"
#include "Item.h"

#include "cocostudio\CocoStudio.h"
#include "ui\CocosGUI.h"

class ItemSoulHeart : public Item
{
public :
	ItemSoulHeart(cocos2d::Layer * layer, Hero * hero, bool isShop);

	static ItemSoulHeart* create(cocos2d::Layer * layer, Hero * hero, bool isShop);

	virtual void ClickEvent();
};

#endif // __ITEM_SOUL_HEART_H__
 