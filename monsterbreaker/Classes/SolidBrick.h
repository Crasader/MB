#pragma once
#ifndef  __SOLID_BRICK_H__
#define __SOLID_BRICK_H__

#include "cocos2d.h"
#include "Definitions.h"
#include "Brick.h"
class SolidBrick : public Brick
{
private:
protected:
public:
	SolidBrick(const char * mapType, int brickTypeID);
	~SolidBrick();
	static SolidBrick* create(const char * mapType, int brickTypeID);
	//void InitSprite();
	virtual void DestroyBlock();
};

#endif // __SOLID_BRICK_H__
 