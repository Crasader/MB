#pragma once
#ifndef __KEY_DOOR_H__
#define __KEY_DOOR_H__

#include "cocos2d.h"
#include "Door.h"
#include "Hero.h"

class KeyDoor : public Door
{
private:
	Hero * hero;
public :
	KeyDoor(const Room & rd, int kDir, Hero * hero, const char * mapType);
	static KeyDoor* create(const Room & rd, int kDir, Hero * hero, const char * mapType);
	void InitSprite();

	void Open();
	bool ClickOpen();
};

#endif // __KEY_DOOR_H__
 