#pragma once
#ifndef __ABOUT_SCENE_H__
#define __ABOUT_SCENE_H__

#include "cocos2d.h"
#include "PrologScene.h"
#include "EndingScene.h"
#include "MainMenuScene.h"
#include "CreditScene.h"
#include "cocostudio\CocoStudio.h"
#include "ui\CocosGUI.h"

class AboutScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;

	// implement the "static create()" method manually
	CREATE_FUNC(AboutScene);

	void MoveToScene(cocos2d::Ref * pSender, cocos2d::ui::Widget::TouchEventType type);
	void LockItem(cocos2d::Node * image, cocos2d::Node * lock, cocos2d::ui::Button * btn);
	void UnLockItem(cocos2d::Node * image, cocos2d::Node * lock, cocos2d::ui::Button * btn);
	void AllItemLock();

	cocos2d::Node * node;

	cocos2d::ui::Button * btn1;
	cocos2d::ui::Button * btn2;
	cocos2d::ui::Button * btn3;
	cocos2d::ui::Button * btn4;
	cocos2d::ui::Button * btn5;
	cocos2d::ui::Button * btn6;

	cocos2d::ui::Button * PrologBtn;
	cocos2d::ui::Button * CreditBtn;

	cocos2d::ui::Button * BackBtn;

	cocos2d::Node * lock1;
	cocos2d::Node * lock2;
	cocos2d::Node * lock3;
	cocos2d::Node * lock4;
	cocos2d::Node * lock5;
	cocos2d::Node * lock6;

	cocos2d::Node * image1;
	cocos2d::Node * image2;
	cocos2d::Node * image3;
	cocos2d::Node * image4;
	cocos2d::Node * image5;
	cocos2d::Node * image6;

	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event *event);
};

#endif // __ABOUT_SCENE_H__
 