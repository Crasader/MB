#pragma once
#ifndef __ITEM_COIN_H__
#define __ITEM_COIN_H__

#include "cocos2d.h"
#include "Definitions.h"
#include "Hero.h"
#include "Item.h"

#include "cocostudio\CocoStudio.h"
#include "ui\CocosGUI.h"

class ItemCoin : public Item
{
public :
	ItemCoin(cocos2d::Layer * layer, Hero * hero);

	static ItemCoin* create(cocos2d::Layer * layer, Hero * hero);

	virtual void ClickEvent();
	virtual void SetTextLabel();

};

#endif // __ITEM_COIN_H__
 