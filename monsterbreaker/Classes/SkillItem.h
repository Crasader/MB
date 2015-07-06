#pragma once
#ifndef __SKILL_ITEM_H__
#define __SKILL_ITEM_H__

#include "cocos2d.h"
#include "Definitions.h"
#include "cocostudio\CocoStudio.h"
#include "ui\CocosGUI.h"
#include "Hero.h"
#include "SkillManager.h"
class Hero;

class SkillItem : public cocos2d::Node
{
private :
	CC_SYNTHESIZE(int, maxPoint, MaxPoint);
	CC_SYNTHESIZE(int, currentPoint, CurrentPoint);
	CC_SYNTHESIZE(int, _skillID, SkillID);
	CC_SYNTHESIZE(bool, _isShop, isShop);
	CC_SYNTHESIZE(int, _cost, Cost);
	Hero * hero;
	cocos2d::Layer * layer;

	cocos2d::Node * node;
	cocos2d::Sprite * image;
	cocos2d::ui::Button * btn;

public :
	SkillItem(cocos2d::Layer * layer, Hero * hero, int skillID, bool isShop, int currentPoint);
	
	static SkillItem* create(cocos2d::Layer * layer, Hero * hero, int skillID, bool isShop, int currentPoint = 0);
	void InitSkillItemData();

	virtual void SetTextLabel();
	virtual void ClickSkillItem();
	virtual void RemoveThis();

};

#endif // __SKILL_ITEM_H__
 