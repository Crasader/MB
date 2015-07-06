#pragma once
#ifndef __BOMB_MANAGER_H__
#define __BOMB_MANAGER_H__

#include "cocos2d.h"
#include "Bomb.h"
#include "Hero.h"

class BombManager : public cocos2d::Node
{
public:
	BombManager(cocos2d::Layer * layer, Hero * hero);
	~BombManager();
	
	float countTime;
	float kTimer;
	float kTimerUp = -9999.0f;

	bool SetBomb(cocos2d::Vec2 vec);
	bool IsTimerUp();
	void SetTimer();
	void CanceledTimer();

	virtual void update(float dt);

	static BombManager* create(cocos2d::Layer * layer, Hero * hero);

	cocos2d::Vector<Bomb *> bombes;
	cocos2d::Layer * layer;
	Hero * hero;


};

#endif // __BOMB_MANAGER_H__
