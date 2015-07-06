#pragma once
#ifndef  __SINGLE_BRICK_H__
#define __SINGLE_BRICK_H__

#include "cocos2d.h"
#include "Definitions.h"
#include "Brick.h"
class SingleBrick : public Brick
{
private:
protected:
public:
	SingleBrick(const char * mapType, int brickTypeID);
	~SingleBrick();
	static SingleBrick* create(const char * mapType, int brickTypeID);
};

#endif // __SINGLE_BRICK_H__
 