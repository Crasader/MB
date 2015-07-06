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
	float kTimer;
	float range;
	int attackPoint;
	std::string bombName;

	bool remoteControll = false;

	const float kTimerUp= -9999.0f;

	cocos2d::Layer * layer;

	cocos2d::Node * bombNode;
	cocos2d::Sprite * spr;

public:
	Bomb(cocos2d::Layer * layer, Hero * hero);
	~Bomb();

	Hero * hero;

	static Bomb* create(cocos2d::Layer * layer, Hero * hero);

	void BombBomb();
	virtual void update(float dt);
	
	int GetAttackPoint();
	void RemoveAll();
	void InitSprite();

	bool remoteTouch = false;
	
	cocos2d::ui::Button* btn = nullptr;
	
};

#endif // __BOMB_H__
 