#pragma once
#ifndef  __BOMB_H__
#define __BOMB_H__

#include "cocos2d.h"
#include "GameObject.h"
#include "cocostudio\CocoStudio.h"
#include "ui\CocosGUI.h"
#include "Hero.h"

class Bomb : public cocos2d::Node
{
private:
	void Init();
protected: 
//	float countTime;
	float kTimer;
	float range;
	int attackPoint;
	std::string bombName;

	bool remoteControll = false;

	const float kTimerUp= -9999.0f;

	cocos2d::Layer * layer;

	cocos2d::Node * bombNode;
	cocos2d::Sprite * spr;
	//cocos2d::Node * AOENode;
	//cocos2d::Node * 	exNode;

public:
	Bomb(cocos2d::Layer * layer, Hero * hero);
//	Bomb(float countTime, int attackPoint, const char * bombName, float range);
	~Bomb();

	//cocos2d::Layer * layer;
	Hero * hero;

	static Bomb* create(cocos2d::Layer * layer, Hero * hero);

	//void SetBombData(const Hero & hero);
	//void SetBomb(cocos2d::Layer * layer, cocos2d::Vec2 vec);
	void BombBomb();
	virtual void update(float dt);
	
	int GetAttackPoint();
	void RemoveAll();
	void InitSprite();

	bool remoteTouch = false;
	
	cocos2d::ui::Button* btn = nullptr;
	
};

#endif // __BOMB_H__
 