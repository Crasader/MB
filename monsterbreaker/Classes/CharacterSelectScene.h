#pragma once
#ifndef __CHARACTER_SELECT_SCENE_H__
#define __CHARACTER_SELECT_SCENE_H__

#include "cocos2d.h"
#include "MainMenuScene.h"
#include "Definitions.h"
#include "LoadingScene.h"
#include "cocostudio\CocoStudio.h"
#include "ui\CocosGUI.h"
#include "HeroData.h"

class CharacterSelectScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
	CREATE_FUNC(CharacterSelectScene);
	cocos2d::Node * node;

	cocos2d::ui::Button * WFBtn;
	cocos2d::ui::Button * MFBtn;
	cocos2d::ui::Button * StartBtn;
	cocos2d::ui::Button * LoadBtn;
	cocos2d::ui::Button * BackBtn;

	cocos2d::Node * WDT;
	cocos2d::Node * MDT;

	cocos2d::Node * WDesc;
	cocos2d::Node * MDesc;

	cocos2d::Node * SelectFrame;
	
	int character = 0;

	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event *event);

private:
};

#endif // __CHARACTER_SELECT_SCENE_H__
