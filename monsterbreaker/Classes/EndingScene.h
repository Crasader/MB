#pragma once
#ifndef __ENDING_SCENE_H__
#define __ENDING_SCENE_H__

#include "cocos2d.h"
#include "cocostudio\CocoStudio.h"
#include "ui\CocosGUI.h"
#include "MainMenuScene.h"

class EndingScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene(int endingNum);

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;

	cocos2d::Vec2 tempVec;

	cocos2d::Node * node;
	cocos2d::Node * frame = nullptr;
	cocos2d::Node * bg1 = nullptr;
	cocos2d::Node * bg2 = nullptr;
	cocos2d::Node * bg3 = nullptr;
	cocos2d::Node * bg4 = nullptr;

	cocos2d::Node * obj1 = nullptr;
	cocos2d::Node * obj2 = nullptr;
	cocos2d::Node * obj3 = nullptr;
	cocos2d::Node * obj4 = nullptr;
	cocos2d::Node * obj5 = nullptr;
	cocos2d::Node * obj6 = nullptr;
	cocos2d::Node * obj7 = nullptr;
	cocos2d::Node * obj8 = nullptr;
	cocos2d::Node * obj9 = nullptr;
	cocos2d::Node * obj10 = nullptr;

	cocos2d::ui::Button * skipBtn;

	int state = 0;

	bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
	void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event);
	void onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *event);
	void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event);

	void animate1();
	void animate2();
	void animate3();
	void animate4();

	void clickAnimate1();
	void clickAnimate2();
	void clickAnimate3();
	void clickAnimate4();

	void moveMainMenu();
	void setState(int state);
	void initOpacity();

	void myStopAllActions();
	// implement the "static create()" method manually
	CREATE_FUNC(EndingScene);

	void saveDataLogic();

};

#endif // __ENDING_SCENE_H__
 