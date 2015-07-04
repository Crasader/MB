#pragma once
#ifndef __COIN_DOOR_H__
#define __COIN_DOOR_H__

#include "cocos2d.h"
#include "Door.h"
#include "cocostudio\CocoStudio.h"
#include "ui\CocosGUI.h"

#include "Hero.h"

class CoinDoor : public Door
{
private :
	Hero * hero;
public :
	CoinDoor(const Room & rd, int kDir, Hero * hero, const char * mapType);
	static CoinDoor* create(const Room & rd, int kDir, Hero * hero, const char * mapType);
	void InitSprite();

	void Open();
	bool ClickOpen();
};

#endif // __COIN_DOOR_H__
 