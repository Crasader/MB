#pragma once
#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "Hero.h"
#include "CollisionManager.h"
#include "Warrior.h"
#include "Magician.h"
#include "StatusManager.h"
#include "SystemManager.h"
#include "BombManager.h"
#include "DoorManager.h"
#include "MapManager.h"
#include "MonsterManager.h"
#include "SkillManager.h"
#include "TreasureManager.h"
#include "ShopManager.h"
#include "SecretManager.h"
#include "HelpManager.h"
#include "DataManager.h"
#include "Lightning.h"
#include "TutorialManager.h"
#include "MapDrawManager.h"

#include "Definitions.h"
#include "Utils.h"

class DoorManager;
class MonsterManager;
class ShopManager;
class SecretManager;
class TreasureManager;
class Chest;
class HelpManager;
class DataManager;
class SystemManager;
class TutorialManager;
class MapDrawManager;

class GameScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
	CREATE_FUNC(GameScene);

	void SetPhysicsWorld(cocos2d::PhysicsWorld *world) { sceneWorld = world; };
	cocos2d::PhysicsWorld * GetPhysicsWorld() { return sceneWorld; };
private:
	cocos2d::PhysicsWorld *sceneWorld;
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;
	float rightTick;
	int temp;

	virtual void onExit();
	virtual void onEnter();

	Hero * hero = nullptr;

	// Managers
	StatusManager * statusManager;
	BombManager * bombManager;
	CollisionManager collisionManager;
	SystemManager * systemManager;
	MonsterManager * monsterManager;
	MapManager * mapManager;
	DoorManager * doorManager;
	SkillManager * skillManager;
	EffectManager * effectManager;
	TreasureManager * treasureManager;
	ShopManager * shopManager;
	SecretManager * secretManager;
	HelpManager * helpManager;
	DataManager * dataManager;
	TutorialManager * tutorialManager;
	MapDrawManager * mapDrawManager;

	cocos2d::Node * ball;
	cocos2d::Node * pauseNode;
	cocos2d::Sprite * pauseImage;
	cocos2d::ui::Button * pauseBtn;
	void pauseLogic();

	// test menu
	void test(cocos2d::Ref *pSender);
	void test2(cocos2d::Ref *pSender);
	void test3(cocos2d::Ref *pSender);

	// event
	bool onContactBegin(cocos2d::PhysicsContact &contact);
	void onContactSeperate(cocos2d::PhysicsContact &contact);

	bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
	void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event);
	void onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *event);
	void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event);

	virtual void update(float dt);

	void onPauseBtnClicked(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);

public:
	void SetInit();
	void SetPlay();
	void SetPause();
	void SetResume();
	void SetWin();
	void SetDie();
	void SetMapZoomIn();
	void SetMapZoomOut();
	void Move(cocos2d::Touch * touch);

	void pauseBtnEnable(bool b);
};

#endif // __BOSS_SCENE_H__
