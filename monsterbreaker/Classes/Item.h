#pragma once
#ifndef __ITEM_H__
#define __ITEM_H__

#include "cocos2d.h"
#include "Definitions.h"
#include "Hero.h"

#include "cocostudio\CocoStudio.h"
#include "ui\CocosGUI.h"

class Item : public cocos2d::Node
{
private :
public :
	cocos2d::Layer * layer;
	Hero * hero;
	Item(cocos2d::Layer * layer, Hero * hero ,int cost, int isShop);

	cocos2d::Node * node = nullptr;
	cocos2d::ui::Button * btn = nullptr;

	CC_SYNTHESIZE(int, _cost, Cost);
	CC_SYNTHESIZE(bool, _isShop, IsShop);

	virtual void RemoveThis();
	virtual void InitSprite();
	virtual void onTouch(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);

	virtual cocos2d::Size getContentSize();

	virtual void SetTextLabel();
	virtual void ClickEvent();
//	virtual void SaveShopItem1ClickedData();

};

#endif // __ITEM_H__
 