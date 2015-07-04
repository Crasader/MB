#pragma once
#ifndef __PROLOG_SCENE_H__
#define __PROLOG_SCENE_H__

#include "cocos2d.h"
#include "cocostudio\CocoStudio.h"
#include "ui\CocosGUI.h"
#include "MainMenuScene.h"

class PrologScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;

	cocos2d::Node * node;
	cocos2d::Node * frame;
	cocos2d::Node * bg1;
	cocos2d::Node * bg2;
	cocos2d::Node * bg3;
	cocos2d::Node * bg4;

	cocos2d::Node * hero1;
	cocos2d::Node * hero2;
	cocos2d::Node * half1;
	cocos2d::Node * half2;
	cocos2d::Node * heroFace;
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
	void moveMainMenu();
	void setState(int state);

	// implement the "static create()" method manually
	CREATE_FUNC(PrologScene);

};

#endif // __PROLOG_SCENE_H__
 