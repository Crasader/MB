#pragma once
#ifndef  __DOUBLE_BRICK_H__
#define __DOUBLE_BRICK_H__

#include "cocos2d.h"
#include "Definitions.h"
#include "Brick.h"
#include "SingleBrick.h"
class DoubleBrick : public Brick
{
private:
	cocos2d::Layer * layer;
	bool b;
protected:
public:
	DoubleBrick(const char * mapType, cocos2d::Layer * layer, int brickTypeID);
	~DoubleBrick();
	static DoubleBrick* create(const char * mapType, cocos2d::Layer * layer, int brickTypeID);
//	void InitSprite();
	virtual void DestroyBlock();

};

#endif // __DOUBLE_BRICK_H__
 