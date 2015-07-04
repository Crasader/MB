#pragma once
#ifndef __SKILL_MANAGER_H__
#define __SKILL_MANAGER_H__

#include "cocos2d.h"
#include "Hero.h"
#include "cocostudio\CocoStudio.h"
#include "ui\CocosGUI.h"

class SkillManager : public cocos2d::Node
{
public:
	SkillManager(Hero * hero);
	~SkillManager();
	
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;
	cocos2d::Layer * layer;

	Hero * hero;
	cocos2d::Node * node;
	cocos2d::Sprite * gaugeFrame;
	cocos2d::Node * gaugeCurrent;
	cocos2d::Node * gaugeMax;
	cocos2d::Sprite * skillImage;
	cocos2d::ui::Button * btn;
	
//	CC_SYNTHESIZE(bool, _changedSkill, ChangedSkill);
	CC_SYNTHESIZE(bool, _clickEnabled, ClickEnabled);

	virtual void update(float dt);

	static SkillManager* create(Hero * hero);

	void InitSkill();
	void DrawAndSetPosition(cocos2d::Layer* layer);
	void ClickSkillBtn(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
	void SetSkillImage();
//	void ChangedSkill();
	cocos2d::SpriteFrame * GetSkillSpriteFrame(int skillID);
};

#endif // __SKILL_MANAGER_H__
