#pragma once
#ifndef __TEST_SCENE_H__
#define __TEST_SCENE_H__

#include "cocos2d.h"
#include "HelperMan.h"
#include "HMWarrior.h"
#include "Hero.h"
#include "HeroData.h"
#include "Warrior.h"

class TestScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
	void SetPhysicsWorld(cocos2d::PhysicsWorld *world) { sceneWorld = world; };
	cocos2d::PhysicsWorld *sceneWorld;
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;

	// implement the "static create()" method manually
	CREATE_FUNC(TestScene);

	cocos2d::Sprite * spr;
	cocos2d::Node * node;
	void readUserInven(std::string pData);

	void GoBack(Ref *pSender);
	void GoBack2(Ref *pSender);
	void GoBack3(Ref *pSender);
	void GoBack4(Ref *pSender);

	virtual void update(float dt);

	bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
	void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event);
	void onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *event);
	void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event);
	int cnt;

	Hero * hero;
	HeroData * heroData;

};

#endif // __TEST_SCENE_H__
 