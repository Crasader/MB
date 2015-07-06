#pragma once
#ifndef __EFFECT_MANAGER_H__
#define __EFFECT_MANAGER_H__

#include "cocos2d.h"
#include "cocostudio\CocoStudio.h"
#include "ui\CocosGUI.h"
#include "Definitions.h"

#include "ChestItem.h"
#include "Lightning.h"

#include "SoundManager.h"

class EffectManager : public cocos2d::Node
{
public:
	EffectManager(cocos2d::Layer * layer);
	~EffectManager();

	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;
	cocos2d::Layer * layer;

	static EffectManager* create(cocos2d::Layer * layer);

	void HealEffect(cocos2d::Vec2 target);
	void FireBallEffect(cocos2d::Vec2 startPosition, cocos2d::Vec2 target);
	void ShiningEffect(cocos2d::Vec2 target);
	void LightningEffect(cocos2d::Vec2 target, int damage);
	void ShowItemDes(int itemNumber);
	void ThankyouEffect(cocos2d::Vec2 target);
	void HitEffect(cocos2d::Vec2 target);

	void DestroyNode(cocos2d::Node* node);

	void PauseAllEffects();
	void ResumeAllEffects();
	cocos2d::Vector<cocos2d::Node*> effects;
	
};

#endif // __EFFECT_MANAGER_H__
