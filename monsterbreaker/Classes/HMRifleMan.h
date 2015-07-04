#pragma once
#ifndef  __HM_RIFLE_MAN_H__
#define __HM_RIFLE_MAN_H__

#include "cocos2d.h"
#include "cocostudio\CocoStudio.h"
#include "ui\CocosGUI.h"
#include "Hero.h"
#include "MonsterManager.h"
//#include "EffectManager.h"

#include "Definitions.h"
#include "SimpleAudioEngine.h"

#include "HelperMan.h"

class HMRifleMan : public HelperMan
{
private:
public:
	const float kTimeUp = -9999.0f;
	float kTimer;
	float setTime;
	//int _attackPoint;
	HMRifleMan(cocos2d::Layer * layer, Hero * hero, bool cageIn);
	~HMRifleMan();

	static HMRifleMan* create(cocos2d::Layer * layer, Hero * hero, bool cageIn);

	MonsterManager * monsterManager;
	EffectManager * effectManager;

	virtual void update(float dt);
	virtual void AIDoingBattle();
	
	
};

#endif // __HM_RIFLE_MAN_H__
 