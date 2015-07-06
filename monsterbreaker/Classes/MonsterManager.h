#pragma once
#ifndef __MONSTER_MANAGER_H__
#define __MONSTER_MANAGER_H__

#include "cocos2d.h"
#include "Monster.h"
#include "Definitions.h"
#include "Definitions\MONSTER DEFINITIONS.h"
#include "Brick.h"
#include "SingleBrick.h"
#include "DoubleBrick.h"
#include "SolidBrick.h"
#include "BossHp.h"
#include "Hero.h"

class MonsterManager : public cocos2d::Node
{
public:
	MonsterManager(cocos2d::Layer * layer, const char * mapType);
	~MonsterManager();

	static MonsterManager* create(cocos2d::Layer * layer, const char * mapType);

	cocos2d::Layer * layer;
	cocos2d::Vec2 origin;
	cocos2d::Size visibleSize;
	cocos2d::Size contentSize;
	cocos2d::Vec2 startPoint;

	cocos2d::Vector<Monster*> monsters;

	CC_SYNTHESIZE(bool, _monsterClear, MonsterClear);
	CC_SYNTHESIZE(std::string, _mapType, MapType);

	void DrawMonsters();
	void Debug2();
	void CreateBossMonster();
	void update(float dt);
	void PauseMonsters();
	void ResumeMonsters();

	void CreateHeroBrick();

	Monster * CreateMonster(int mID);
	std::vector<Point> tp;
};

#endif // __MONSTER_MANAGER_H__
