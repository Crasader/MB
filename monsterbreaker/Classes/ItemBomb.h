#pragma once
#ifndef __ITEM_BOMB_H__
#define __ITEM_BOMB_H__

#include "cocos2d.h"
#include "Definitions.h"
#include "Hero.h"
#include "Item.h"

#include "cocostudio\CocoStudio.h"
#include "ui\CocosGUI.h"

class ItemBomb : public Item
{
public :
	ItemBomb(cocos2d::Layer * layer, Hero * hero, bool isShop);
	
	static ItemBomb* create(cocos2d::Layer * layer, Hero * hero, bool isShop);
	
	virtual void ClickEvent();


};

#endif // __ITEM_BOMB_H__
 