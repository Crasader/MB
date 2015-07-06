#pragma once
#ifndef  __HELPER_MAN_H__
#define __HELPER_MAN_H__

#include "cocos2d.h"
#include "cocostudio\CocoStudio.h"
#include "ui\CocosGUI.h"
#include "Hero.h"
#include "EffectManager.h"
#include "MapManager.h"
#include "Character.h"

#include "Definitions.h"
#include "SimpleAudioEngine.h"

class HelperMan : public Character
{
private:
public:
	cocos2d::Layer * layer;
	cocos2d::Node * node;
	cocos2d::ui::Button * btn;
	cocos2d::Size visibleSize;

	HelperMan(cocos2d::Layer * layer, Hero * hero, bool cageIn);
	~HelperMan();

	Hero * hero;
	bool clickOk;
	bool isCageIn;

	void InitSprite();
	void ClickHelperMan();
	void RemoveAll();
	void ThankYou();

	virtual void pause();
	virtual void resume();

	virtual void update(float dt);
	virtual void AIBeforeBattle();
	virtual void AIDoingBattle();
	virtual void AIAfterBattle();

	virtual cocos2d::Size getContentSize();

	virtual void Swing();
	virtual void Stay();
};

#endif // __HELPER_MAN_H__
 