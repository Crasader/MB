#pragma once
#ifndef __PADDLE_H__
#define __PADDLE_H__

#include "cocos2d.h"

class Paddle : public cocos2d::Sprite
{
public:
	// default constructor
	Paddle();
	
	// set the paddle
	void SetPaddle(float paddleSize, const char * paddleName);
	// create paddle sprite
	static Paddle* create(float paddleSize, const char * paddleName);
private:

};

#endif // __PADDLE_H__
