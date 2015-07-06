#pragma once
#ifndef  __BRICK_H__
#define __BRICK_H__

#include "cocos2d.h"
#include "Definitions.h"
#include "SoundManager.h"
class Brick : public cocos2d::Sprite
{
private:
	cocos2d::Layer * layer;
protected:
	CC_SYNTHESIZE(std::string, _mapType, MapType);
	CC_SYNTHESIZE(int, _brickTypeID, BrickTypeID)

public:
	Brick(const char * mapType, int brickTypeID);
	~Brick();

	virtual void DestroyBlock();
	virtual void DestroyBody();
	virtual void CleanBlock();
	virtual void InitSprite();
};

#endif // __BRICK_H__
 