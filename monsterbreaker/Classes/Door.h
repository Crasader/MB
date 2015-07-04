#pragma once
#ifndef __DOOR_H__
#define __DOOR_H__

#include "cocos2d.h"
#include "Definitions.h"
#include "Room.h"

#include "cocostudio\CocoStudio.h"
#include "ui\CocosGUI.h"

class Door : public cocos2d::Node
{
private :
	CC_SYNTHESIZE(int, _gotoX, GoToX);
	CC_SYNTHESIZE(int, _gotoY, GoToY);
	CC_SYNTHESIZE(bool, _lock,Lock);
	CC_SYNTHESIZE(int, _kDir, Dir);
	CC_SYNTHESIZE(bool, _clickOk, ClickOk);
	CC_SYNTHESIZE(int, _roomType, RoomType);
	CC_SYNTHESIZE(bool, _roomVisible, RoomVisible);
	CC_SYNTHESIZE(std::string, _mapType, MapType);

	bool _isSecret;
	bool _isOpen;

//	Hero * hero;
//	MapManager * mapManager;

public :
	Door(const Room & rd, int kDir, const char * mapType);
	static Door* create(const Room & rd, int kDir, const char * mapType);
	cocos2d::ui::Button* btn = nullptr;

	virtual void Open();
	virtual void InitSprite();
	virtual bool IsOpen() { return _isOpen; }
	virtual bool ClickOpen();
	virtual bool IsDamageDoor() { return false; }

	virtual void bombCrush();

	//virtual void move(int x, int y, int roomType, int dir);
	//virtual void setNextHeroLocationAndSave(int x, int y);
	//virtual void moveScene(int roomType, int dir);

//	virtual void onTouchDoor(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
};

#endif // __SLIME_H__
 