#pragma once
#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__

#include "cocos2d.h"

class GameObject : public cocos2d::Sprite
{
private:
	void Init();
protected:

	CC_SYNTHESIZE(int, _team, Team);
	CC_SYNTHESIZE(int, _maxHp, MaxHp);
	CC_SYNTHESIZE(int, _currentHp, CurrentHp);
	CC_SYNTHESIZE(int, _attackPoint, AttackPoint);
	CC_SYNTHESIZE(bool, _alive, Alive);
	CC_SYNTHESIZE(int, _damagedState, DamagedState);
	CC_SYNTHESIZE(int, _actionState, ActionState);

	CC_SYNTHESIZE(std::string, _name, Name);
	CC_SYNTHESIZE(std::string, _type, Type);

public:
	GameObject();
	~GameObject();

	virtual void IncreaseMaxHp(int i);
	virtual void DecreaseMaxHp(int i);
	virtual void IncreaseCurrentHp(int i);
	virtual void DecreaseCurrentHp(int i);
	virtual void Damaged(int i);
	
	virtual void Animate(const char * str, int kAction);
	virtual void Ani(const char * str, cocos2d::__Dictionary* dic);
	virtual void DieAni(const char * str, cocos2d::__Dictionary* dic);

	virtual void update(float dt);

	virtual cocos2d::__Dictionary* GetAniInfo();

	void SetBodyEnable(bool b);
	bool IsAlive() const;
	bool IsDamaged() const;
	virtual void Die();

};

#endif // __GAMEOBJECT_H__
 