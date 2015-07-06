#pragma once
#ifndef __CHEST_ITEM_H__
#define __CHEST_ITEM_H__

#include "cocos2d.h"
#include "Definitions.h"
#include "cocostudio\CocoStudio.h"
#include "ui\CocosGUI.h"
#include "Hero.h"
class Hero;

class ChestItem : public cocos2d::Node
{
private :
	CC_SYNTHESIZE(std::string, _itemName, ItemName);
	CC_SYNTHESIZE(std::string, _desc, Desc);
	CC_SYNTHESIZE(int, _itemID, ItemID);
	CC_SYNTHESIZE(bool, _isShop, isShop);
	CC_SYNTHESIZE(int, _cost, Cost);
	Hero * hero;
	cocos2d::Layer * layer;

	cocos2d::Node * node;
	cocos2d::Sprite * image;
	cocos2d::ui::Button * btn;

public :
	ChestItem(cocos2d::Layer * layer, Hero * hero, int itemID, bool isShop);
	
	static ChestItem* create(cocos2d::Layer * layer, Hero * hero, int itemID, bool isShop);
	void InitChestItemData();

	virtual void SetTextLabel();
	virtual void ClickChestItem();
	virtual void RemoveThis();
};

#endif // __CHEST_ITEM_H__
 