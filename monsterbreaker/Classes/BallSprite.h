#pragma once
#ifndef  __BALL_SPRITE_H__
#define __BALL_SPRITE_H__

#include "cocos2d.h"
#include "GameObject.h"
#include "Character.h"
class BallSprite : public GameObject
{
private:
	void Init();
protected:

	CC_SYNTHESIZE(float, _velocity, Velocity);
	CC_SYNTHESIZE(float, _ballSize, BallSize);

public:
	BallSprite();
	BallSprite(const Character& obj);
//	BallSprite(cocos2d::Node * node);
	~BallSprite();
//	static BallSprite* create();
	static BallSprite* create(const Character & obj);

	void InitSprite();
	void update(float dt);
};

#endif // __BALL_SPRITE_H__
 