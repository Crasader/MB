#pragma once
#ifndef __CHEST_H__
#define __CHEST_H__

#include "cocos2d.h"
#include "Definitions.h"
#include "cocostudio\CocoStudio.h"
#include "ui\CocosGUI.h"
#include "ChestItem.h"
#include "Hero.h"
//#include "MapManager.h"
#include "DoorManager.h"
#include "MapDrawManager.h"

class Chest : public cocos2d::Node
{
private :
	bool clicked = false;
	Hero * hero = nullptr;
	cocos2d::Layer * layer;
	int r = 0;
public :
	Chest(Hero * hero, cocos2d::Layer * layer);

	static Chest* create(Hero * hero, cocos2d::Layer * layer);

	virtual void InitSprite();
	virtual void Open();
	virtual void Opened();
	virtual void OpenFail();

	void SetItem(int itemNum);

	void onTouch(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
};

#endif // __CHEST_H__
 