#pragma once

#ifndef __MAINMENU_SCENE_H__
#define __MAINMENU_SCENE_H__

#include "cocos2d.h"
#include "CharacterSelectScene.h"
#include "AboutScene.h"

#include "Definitions.h"
#include "SimpleAudioEngine.h"
#include "cocostudio\CocoStudio.h"
#include "ui\CocosGUI.h"

#include "UnlockManager.h"

class MainMenuScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
	CREATE_FUNC(MainMenuScene);
	
private:
	int _unlockEnding;
	int _currentEndingNumber = 0;
	UnlockManager * unlockManager;

	void LoadData();
	void DeleteNode();
	void DrawNode();

	cocos2d::Node * node;
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;
	cocos2d::Sprite * dotMenu[7];
	cocos2d::Sprite * speaker;
	bool sp;

	void PlayAnimation(cocostudio::timeline::ActionTimeline * ani, int s, int e, bool r);

	bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
	void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event);
	void onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *event);
	void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event);

	float originalTouchPosition;
	float initialTouchPos[2];
	float currentTouchPos[2];

	void clickSpeaker();

	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event *event);
	
};

#endif // __MAINMENU_SCENE_H__
