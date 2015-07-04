#pragma once
#ifndef __BOSS_DOOR_H__
#define __BOSS_DOOR_H__

#include "cocos2d.h"
#include "Door.h"
#include "cocostudio\CocoStudio.h"
#include "ui\CocosGUI.h"

class BossDoor : public Door
{
public :
	BossDoor(const Room & rd, int kDir, const char * mapType);
	static BossDoor* create(const Room & rd, int kDir, const char * mapType);
	void InitSprite();

	void Open();
	bool ClickOpen();
};

#endif // __BOSS_DOOR_H__
 