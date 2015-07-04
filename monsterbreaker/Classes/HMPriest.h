#pragma once
#ifndef  __HM_PRIEST_H__
#define __HM_PRIEST_H__

#include "cocos2d.h"
#include "cocostudio\CocoStudio.h"
#include "ui\CocosGUI.h"
#include "Hero.h"
//#include "EffectManager.h"

#include "Definitions.h"
#include "SimpleAudioEngine.h"

#include "HelperMan.h"

class HMPriest : public HelperMan
{
private:
public:

	HMPriest(cocos2d::Layer * layer, Hero * hero, bool cageIn);
	~HMPriest();

	static HMPriest* create(cocos2d::Layer * layer, Hero * hero, bool cageIn);

//	virtual void update(float dt);
	virtual void AIAfterBattle();

};

#endif // __HM_PRIEST_H__
 