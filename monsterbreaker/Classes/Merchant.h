#pragma once
#ifndef __MERCHANT_H__
#define __MERCHANT_H__

#include "cocos2d.h"
#include "Definitions.h"
#include "MapManager.h"
#include "ItemCoin.h"
#include "Hero.h"

class Merchant : public cocos2d::Node
{
public :
	Merchant(cocos2d::Layer * layer, Hero * hero);
	static Merchant* create(cocos2d::Layer * layer, Hero * hero);
	void Die();
	void InitSprite();
	cocos2d::Layer * layer;
	Hero * hero;
	cocos2d::Size size;
};

#endif // __MERCHANT_H__
 