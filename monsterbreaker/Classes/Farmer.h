#pragma once
#ifndef __FARMER_H__
#define __FARMER_H__

#include "cocos2d.h"
#include "Monster.h"

class Farmer : public Monster
{
private :

public :
	Farmer();

	void Init();
	static Farmer* create();

	virtual void MoodStay(float dt);
	virtual void MoodMove(float dt);
	virtual void MoodAttack(float dt);
	virtual void InitSprite();

};

#endif // __FARMER_H__
 