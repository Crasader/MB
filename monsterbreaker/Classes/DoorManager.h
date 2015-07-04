#pragma once
#ifndef __DOOR_MANAGER_H__
#define __DOOR_MANAGER_H__

#include "cocos2d.h"
#include "MapManager.h"
#include "cocostudio\CocoStudio.h"
#include "ui\CocosGUI.h"
#include "Utils.h"
#include "Hero.h"
#include "Definitions.h"

#include "Definitions\DOOR DEFINITIONS.h"
#include "GameScene.h"
#include "LoadingScene.h"
//#include "Definitions\SCENE DEFINITIONS.h"

#include "EndingDoor.h"
#include "EndingScene.h"

class DoorManager : public cocos2d::Node
{
private:
	CC_SYNTHESIZE(std::string, _mapType, MapType);
	CC_SYNTHESIZE(bool, _currentSecretRoom, CurrentSecretRoom);
	CC_SYNTHESIZE(bool, _secretView, SecretView);
	CC_SYNTHESIZE(bool, _secretViewLockOpen, SecretViewLockOpen);
	CC_SYNTHESIZE(bool, _isMovingLoadingScene, IsMovindLoadingScene);
	cocos2d::Vec2 startPoint;
	cocos2d::Size contentSize;
	cocos2d::Layer * layer;
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;
	void SetTileFence(int x, int y);
	void SetTileFenceLine(int kDir, bool hasDoor);
	void SetTileDoor(cocos2d::Vec2 vec, float scale, float rotate, const Room & rd, int kDir);

	Hero * hero;
	MapManager * mapManager;
public:

	DoorManager(Hero * hero);
	~DoorManager();

	static DoorManager* create(Hero * hero);

	cocos2d::Vector <Door*> doors;
	cocos2d::Vector <EndingDoor*> BAWKeyDoors;
	cocos2d::Vector <EndingDoor*> TKeyDoors;

//	void InitMapTypeData(MapManager * mapManager, Hero * hero, MonsterManager * monsterManager);
	void Draw(cocos2d::Layer * layer);

	void OpenDoors();
	void SetDoorClickEnable(bool b);
	void ShowEndingDoor();
	
	// door 
	void onTouchDoor(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
	virtual void move(int x, int y, int dir);
	virtual void setNextHeroLocationAndSave(int x, int y);
	virtual void moveScene(int dir);
	virtual void moveLoadingScene(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
	virtual void moveEndingScene(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
	//cocos2d::Vec2 getMyGridPosition(int x, int y);
	
	void update(float dt);
	void visibleAllSecretDoor(bool b);
	void OpenAllSecretDoor();
};

#endif // __DOOR_MANAGER_H__
