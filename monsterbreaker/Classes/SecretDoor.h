#pragma once
#ifndef __SECRET_DOOR_H__
#define __SECRET_DOOR_H__

#include "cocos2d.h"
#include "Door.h"
#include "cocostudio\CocoStudio.h"
#include "ui\CocosGUI.h"

class SecretDoor : public Door
{
public:
	SecretDoor(const Room & rd, int kDir, const char * mapType);
	static SecretDoor* create(const Room & rd, int kDir, const char * mapType);
	void InitSprite();

	void Open();
	virtual bool ClickOpen();
};

#endif // __SECRET_DOOR_H__
 