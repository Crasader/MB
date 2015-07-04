#pragma once
#ifndef __DAMAGE_DOOR_H__
#define __DAMAGE_DOOR_H__

#include "cocos2d.h"
#include "Door.h"
#include "cocostudio\CocoStudio.h"
#include "ui\CocosGUI.h"
#include "Hero.h"
class DamageDoor : public Door
{
private:
	Hero * hero;
public:
	DamageDoor(const Room & rd, int kDir, Hero * hero, const char * mapType);
	static DamageDoor* create(const Room & rd, int kDir, Hero * hero, const char * mapType);
	void InitSprite();

	void Open();
	bool ClickOpen();
	virtual bool IsDamageDoor() { return true; }
};

#endif // __DAMAGE_DOOR_H__
 