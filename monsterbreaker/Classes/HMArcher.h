#pragma once
#ifndef  __HM_ARCHER_H__
#define __HM_ARCHER_H__

#include "cocos2d.h"
#include "cocostudio\CocoStudio.h"
#include "ui\CocosGUI.h"
#include "Hero.h"
#include "MonsterManager.h"
//#include "EffectManager.h"

#include "Definitions.h"
#include "SimpleAudioEngine.h"

#include "HelperMan.h"

class HMArcher : public HelperMan
{
private:
public:
	//std::string  _ballName;
	//int _ballCount;
	//int _ballCurrentCount;
	//int _team;
	//int _attackPoint;


	HMArcher(cocos2d::Layer * layer, Hero * hero, bool cageIn);
	~HMArcher();

	static HMArcher* create(cocos2d::Layer * layer, Hero * hero, bool cageIn);

	MonsterManager * monsterManager;

	virtual void update(float dt);
	virtual void AIDoingBattle();

};

#endif // __HM_ARCHER_H__
 