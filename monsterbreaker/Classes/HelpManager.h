#pragma once
#ifndef __HELP_MANAGER_H__
#define __HELP_MANAGER_H__

#include "cocos2d.h"
#include "Definitions.h"
#include "Hero.h"
#include "MapManager.h"

#include "Item.h"
#include "ItemCoin.h"
#include "ItemBomb.h"
#include "ItemHalfHeart.h"
#include "ItemHeart.h"
#include "ItemHalfSoulHeart.h"
#include "ItemSoulHeart.h"
#include "ItemKey.h"

#include "Cage.h"

#include "HelperMan.h"

#include "HMWarrior.h"
#include "HMArcher.h"
#include "HMPriest.h"
#include "HMRifleMan.h"

#include "Weapon.h"

class HelpManager : public cocos2d::Node
{
public:
	HelpManager(cocos2d::Layer * layer, Hero * hero);
	~HelpManager();

	static HelpManager* create(cocos2d::Layer * layer, Hero * hero);

	cocos2d::Layer * layer;
	cocos2d::Vec2 origin;
	cocos2d::Size visibleSize;
	MapManager * mapManager;

	Cage * c1 = nullptr;
	Cage * c2 = nullptr;
	Cage * c3 = nullptr;

	Hero * hero;
	void createCageAndData();
	void createCageInCoin();
	void createCageInBomb();
	void createCageInHeart();

	void createHeroHelperMan();

	vector<HelperMan*> helpermans;
	virtual void update(float dt);
	virtual void pause();
	virtual void resume();

	virtual void startHelperUpdateAI();
	virtual void startAIBeforeBattle();
	virtual void startAIDoingBattle();
	virtual void startAIAfterBattle();

	virtual HelperMan * createHelperMan(int hmID);
};

#endif // __HELP_MANAGER_H__
