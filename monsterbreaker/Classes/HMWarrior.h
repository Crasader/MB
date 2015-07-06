#pragma once
#ifndef  __HM_WARRIOR_H__
#define __HM_WARRIOR_H__

#include "cocos2d.h"
#include "cocostudio\CocoStudio.h"
#include "ui\CocosGUI.h"
#include "Hero.h"
#include "MonsterManager.h"

#include "Definitions.h"
#include "SimpleAudioEngine.h"

#include "HelperMan.h"

class HMWarrior : public HelperMan
{
private:
public:

	HMWarrior(cocos2d::Layer * layer, Hero * hero, bool cageIn);
	~HMWarrior();

	static HMWarrior* create(cocos2d::Layer * layer, Hero * hero, bool cageIn);

	virtual void AIBeforeBattle();

};

#endif // __HM_WARRIOR_H__
 