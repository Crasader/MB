#pragma once
#ifndef __SLIME_H__
#define __SLIME_H__

#include "cocos2d.h"
#include "Monster.h"

class Slime : public Monster
{
private :

public :
	Slime();
	void Init();
	static Slime* create();

};

#endif // __SLIME_H__
 