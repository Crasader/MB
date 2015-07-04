#pragma once
#ifndef __UNLOCK_MANAGER_H__
#define __UNLOCK_MANAGER_H__

#include "cocos2d.h"
#include "cocostudio\CocoStudio.h"
#include "ui\CocosGUI.h"
#include "Definitions.h"

#include "SoundManager.h"
//#include "Monster.h"

class UnlockManager
{
private:
	static UnlockManager * instance;
	UnlockManager();
	~UnlockManager();

public:
	static UnlockManager* getInstace();
	void freeInstance();

	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;
	//cocos2d::Layer * layer;

	//static UnlockManager* create(cocos2d::Layer * layer);

	void ShowUnlockData(cocos2d::Layer * layer);
	void GetUnlockData();
	void GetUnlockImageAndText(cocos2d::Sprite* img, cocos2d::ui::Text * text1, cocos2d::ui::Text * text2, int id);

	void DestroyNode(cocos2d::Node* node);

	void PauseAllEffects();
	void ResumeAllEffects();

	cocos2d::Vector<cocos2d::Node*> nodes;
	std::vector<int> unlockData;

	void addUnlockData(int unlockID);
	void playSound(const char * soundName, const char * soundType = "wav");
	
};

#endif // __UNLOCK_MANAGER_H__
