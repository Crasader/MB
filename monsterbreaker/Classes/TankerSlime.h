#pragma once
#ifndef __TANKER_SLIME_H__
#define __TANKER_SLIME_H__

#include "cocos2d.h"
#include "Slime.h"

class TankerSlime : public Slime
{
private :

public :
	TankerSlime();
	void Init();
	static TankerSlime * create();

};

#endif // __TANKER_SLIME_H__
 