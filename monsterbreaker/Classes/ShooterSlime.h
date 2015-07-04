#pragma once
#ifndef __SHOOTER_SLIME_H__
#define __SHOOTER_SLIME_H__

#include "cocos2d.h"
#include "Slime.h"

class ShooterSlime : public Slime
{
private :

public :
	ShooterSlime();
	void Init();
	static ShooterSlime* create();

	virtual void MoodAttack(float dt);

};

#endif // __SHOOTER_SLIME_H__
 