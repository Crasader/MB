#pragma once
#ifndef __SHOOTER_BAT_H__
#define __SHOOTER_BAT_H__

#include "cocos2d.h"
#include "Bat.h"

class ShooterBat : public Bat
{
private :

public :
	ShooterBat();
	void Init();
	static ShooterBat* create();

	virtual void MoodAttack(float dt);
	virtual void SeqFire(cocos2d::Vec2 sp, cocos2d::Vec2 dp);
};

#endif // __SHOOTER_BAT_H__
