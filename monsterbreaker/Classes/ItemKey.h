#pragma once
#ifndef __ITEM_KEY_H__
#define __ITEM_KEY_H__

#include "cocos2d.h"
#include "Definitions.h"
#include "Hero.h"
#include "Item.h"

#include "cocostudio\CocoStudio.h"
#include "ui\CocosGUI.h"

class ItemKey : public Item
{
public :
	ItemKey(cocos2d::Layer * layer, Hero * hero, bool isShop);

	static ItemKey* create(cocos2d::Layer * layer, Hero * hero, bool isShop);

	virtual void ClickEvent();
};

#endif // __ITEM_KEY_H__
 