#pragma once
#ifndef __WEAPON_H__
#define __WEAPON_H__

#include "cocos2d.h"
#include "Definitions.h"
#include "SimpleAudioEngine.h"
#include "cocostudio\CocoStudio.h"
#include "ui\CocosGUI.h"
#include "Hero.h"
#include "MapManager.h"

class Hero;
//#include "GameObject.h"
class Weapon : public cocos2d::Node
{
public:
	cocos2d::Layer * layer;
	cocos2d::Size visibleSize;
	cocos2d::Node * node;
	cocos2d::Node * skillNode;
	cocos2d::ui::Button * btn;
	MapManager * mm;
	Hero * hero;
	
	CC_SYNTHESIZE(int, _attackPoint, AttackPoint);
	CC_SYNTHESIZE(float, _paddleSize, paddleSize);
	CC_SYNTHESIZE(std::string, _paddleName, PaddleName);
	CC_SYNTHESIZE(std::string, _weaponName, WeaponName);
	CC_SYNTHESIZE(std::string, _weaponType, WeaponType);
//	bool cageIn;
	bool clickOk;
	//CC_SYNTHESIZE(std::string, _useClass, UseClass);

	static Weapon * create(cocos2d::Layer * layer, Hero * hero, const char * weaponType, const char * weaponName, bool clickOk);
	void InitSprite();

//	std::vector<int> specialEffect;
//	enum SpecialEffect{ first = 0, none = 0, bleed, burn, freeze, poison, holy, lightning, sleep ,stun, last = stun };

public:
	Weapon(cocos2d::Layer * layer, Hero * hero, const char * weaponType, const char * weaponName, bool clickOk);
	~Weapon();

	void ClickWeapon();
	void RemoveAll();

	void SetWeaponData();
	void Swing();
	void Skill();
	void Stay();
	void Die();
	void SetSkillVisible(bool b);
//	void setFilpY(bool b);
};

#endif // __WEAPON_H__
 