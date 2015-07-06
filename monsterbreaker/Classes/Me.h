#pragma once
#ifndef __ME_H__
#define __ME_H__

#include "cocos2d.h"
#include "Monster.h"

class Me: public Monster
{
private :
public :
	Me(Hero * hero);
	static Me* create(Hero * hero);

	Hero * hero;
	Weapon * weapon;
	Paddle * paddle;

	float skillTime;
	bool isWarrior;
	bool onceSkillUsed;
	CC_SYNTHESIZE(std::string, _bombName, BombName);


	virtual void update(float dt);
	virtual void Die();


	virtual void ChooseMood();
	virtual void MoodMove(float dt);
	virtual void MoodAttack(float dt);
	virtual void MoodAttack2(float dt);
	virtual void MoodSkill(float dt);
	virtual void InitSprite();
	
	virtual void SkillUse();
	virtual void createLightning(cocos2d::Vec2 p);
	virtual void createHealEffect(cocos2d::Vec2 p);
	virtual void heal();

	virtual void Draw(cocos2d::Layer * layer);
	
	virtual void setWeapon();
};

#endif // __ME_H__
 