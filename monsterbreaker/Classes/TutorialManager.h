#pragma once
#ifndef __TUTORIAL_MANAGER_H__
#define __TUTORIAL_MANAGER_H__

#include "cocos2d.h"
#include "Definitions.h"

#include "MapManager.h"
#include "Hero.h"

#include "TutorialBtn.h"
#include "FingerPointer.h"

#include "Bomb.h"
#include "Slime.h"

#include "DoorManager.h"

class TutorialManager : public cocos2d::Node
{
public:
	TutorialManager(cocos2d::Layer * layer, Hero * hero);
	~TutorialManager();

	static TutorialManager* create(cocos2d::Layer * layer, Hero * hero);

	cocos2d::Layer * layer;
	cocos2d::Vec2 origin;
	cocos2d::Size visibleSize;

	MapManager * mapManager;
	Hero * hero;

	CC_SYNTHESIZE(bool, isClicked, IsClicked);

	TutorialBtn * aBtn;
	TutorialBtn * mBtn;
	TutorialBtn * bBtn;
	TutorialBtn * dBtn;
	TutorialBtn * sBtn;

	virtual void createTutorialBtn();

	virtual void update(float dt);
	virtual void pause();
	virtual void resume();

	void onTutorialBtnTouch(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
	
	void doWork(int btnType);
	void removeNode(cocos2d::Node * target);
	
	Vector <cocos2d::Node * > vec;

	void playAttackSound(const char * soundName, const char * soundType = "wav");

	void HideBtn();
	void EndAnimation();
};

#endif // __TUTORIAL_MANAGER_H__
