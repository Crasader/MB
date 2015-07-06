#pragma once
#ifndef __ARMOR_ITEM_H__
#define __ARMOR_ITEM_H__

#include "cocos2d.h"
#include "Definitions.h"
#include "cocostudio\CocoStudio.h"
#include "ui\CocosGUI.h"
#include "Hero.h"
class Hero;

class ArmorItem: public cocos2d::Node
{
private :
	CC_SYNTHESIZE(int, _armorID, ArmorID);
	CC_SYNTHESIZE(int, _armorPoint, ArmorPoint);
	CC_SYNTHESIZE(bool, _isShop, isShop);
	CC_SYNTHESIZE(int, _cost, Cost);

	Hero * hero;
	cocos2d::Layer * layer;

	cocos2d::Node * node;
	cocos2d::Sprite * image;
	cocos2d::ui::Button * btn;

public :
	ArmorItem(cocos2d::Layer * layer, Hero * hero, int armorID, bool isShop);
	
	static ArmorItem* create(cocos2d::Layer * layer, Hero * hero, int armorID, bool isShop);
	void InitArmorItemData();

	virtual void SetTextLabel();
	virtual void ClickArmorItem();
	virtual void RemoveThis();
};

#endif // __ARMOR_ITEM_H__
 