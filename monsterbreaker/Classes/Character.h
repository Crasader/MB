#pragma once
#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include "cocos2d.h"
#include "GameObject.h"
//#include "Ball.h"

class Character : public GameObject
{
private:
	void Init();
protected:
	CC_SYNTHESIZE(int, _ballCount, BallCount);
	CC_SYNTHESIZE(int, _ballCurrentCount, BallCurrentCount);
	CC_SYNTHESIZE(std::string, _ballName, BallName);
	CC_SYNTHESIZE(int, _ballVelocity, BallVelocity);
	CC_SYNTHESIZE(float, _ballSize, BallSize);

public:
	Character();
	~Character();
	void Fire(cocos2d::Layer * layer, cocos2d::Vec2 startPoint, cocos2d::Vec2 destPoint, bool isCoin = false);

	void DecreaseBallCount();

};

#endif // __CHARACTER_H__
 