#pragma once
#ifndef __CREDIT_SCENE_H__
#define __CREDIT_SCENE_H__

#include "cocos2d.h"
#include "AboutScene.h"
#include "MainMenuScene.h"
#include "cocostudio\CocoStudio.h"
#include "ui\CocosGUI.h"

class CreditScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;

	// implement the "static create()" method manually
	CREATE_FUNC(CreditScene);

	void openWeb(cocos2d::Ref * pSender, cocos2d::ui::Widget::TouchEventType type);

	cocos2d::Node * node;

	cocos2d::ui::Button * backBtn;
	cocos2d::ui::Button * tumblrBtn;
	cocos2d::ui::Button * meBtn;
	cocos2d::ui::Button * isaacBtn;

	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event *event);

};

#endif // __CREDIT_SCENE_H__
 