#pragma once
#ifndef __ENDING_DOOR_H__
#define __ENDING_DOOR_H__

#include "cocos2d.h"
#include "Hero.h"

#include "cocostudio\CocoStudio.h"
#include "ui\CocosGUI.h"
class EndingDoor : public cocos2d::Node
{
private:
	Hero * hero;
	CC_SYNTHESIZE(std::string, _type, Type);
	CC_SYNTHESIZE(int, _endingNum, EndingNum);
public :
	cocos2d::ui::Button* btn = nullptr;
	
	EndingDoor(const char * type, int endingNum);
	static EndingDoor* create(const char * type);
	static EndingDoor* create(const char * type, int endingNum);

	void InitSprite();
};

#endif // __ENDING_DOOR_H__
 