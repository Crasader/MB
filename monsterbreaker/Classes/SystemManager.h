#pragma once
#ifndef __SYSTEM_MANAGER_H__
#define __SYSTEM_MANAGER_H__

#include "cocos2d.h"
#include "Definitions.h"
#include "Hero.h"
#include "cocostudio\CocoStudio.h"
#include "ui\CocosGUI.h"

#include "Bomb.h"
#include "ChestItem.h"
#include "HelperMan.h"
#include "HelpManager.h"

#include "MainMenuScene.h"
#include "GameScene.h"


class SystemManager : public cocos2d::Node
{
public:
	SystemManager(cocos2d::Layer * layer, Hero * hero);
	~SystemManager();

	// local pointer of the physics world
	cocos2d::PhysicsWorld * physicsWorld;
	cocos2d::Layer * layer;
	cocos2d::Size visibleSize;
	Hero * hero;

	static SystemManager * create(cocos2d::Layer * layer, Hero * hero);
	int systemState;
	void InitSystemData();
	void SetSystemState(int systemState);

	HelpManager * helpManager = nullptr;

	// pause data
	cocos2d::Node * node;

	cocos2d::Node * bg;
	cocos2d::Node * dead;
	cocos2d::Node * pause;

	cocos2d::Node * you;
	
	cocos2d::Node * ball1;
	cocos2d::Node * ball2;
	cocos2d::Node * ball3;

	cocos2d::Node * bomb;
	cocos2d::Node * weapon;

	Vector<cocos2d::Node*> itemList;
	Vector<cocos2d::Node*> buddiesList;
	CC_SYNTHESIZE(bool, _clickOk, ClickOk);
	void ShowPause();
	void HidePause();
	
	void SetAndStartAllPauseData();
	void RemoveAllPauseData();
	void RemoveMethod(cocos2d::Node * target);
	void RemoveMethod(cocos2d::Vector<cocos2d::Node *> * target);

	cocos2d::ui::Button * btnResume;
	cocos2d::ui::Button * btnSave;
	cocos2d::ui::Button * btnHome;

	void ResumeClicked();
	void SaveClicked();
	void HomeClicked();

	void SaveBtnEnabled(bool b);
};

#endif // __SYSTEM_MANAGER_H__
