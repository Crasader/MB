#pragma once
#ifndef __HERO_H__
#define __HERO_H__

#include "cocos2d.h"
#include "Character.h"
#include "Weapon.h"
#include "Paddle.h"
#include "BallSprite.h"
#include "Definitions.h"
#include "Utils.h"
#include "MyBodyParser.h"
#include "HeroData.h"
#include "EffectManager.h"
#include "SkillItem.h"
#include "SoundManager.h"

class Weapon;
class SkillItem;

class Hero : public Character
{
private:
protected:

	CC_SYNTHESIZE(int, _maxSp, MaxSp);
	CC_SYNTHESIZE(int, _currentSp, CurrentSp);

	CC_SYNTHESIZE(int, _keyCount, KeyCount);
	CC_SYNTHESIZE(int, _bombCount, BombCount);
	CC_SYNTHESIZE(int, _moneyCount, MoneyCount);

	CC_SYNTHESIZE(std::string, _bombName, BombName);
	CC_SYNTHESIZE(int, _bombAttackPoint, BombAttackPoint);
	CC_SYNTHESIZE(float, _bombRange, BombRange);
	CC_SYNTHESIZE(float, _bombCountTime, BombCountTime);
	CC_SYNTHESIZE(float, _bombSetCountTime, BombSetCountTime);

	CC_SYNTHESIZE(float, _paddleSize, PaddleSize);
	CC_SYNTHESIZE(std::string, _weaponName, WeaponName);
	CC_SYNTHESIZE(std::string, _weaponType, WeaponType);

	CC_SYNTHESIZE(int, _skillID, SkillID);
	CC_SYNTHESIZE(int, _skillCurrentPoint, SkillCurrentPoint);
	CC_SYNTHESIZE(int, _skillMaxPoint, SkillMaxPoint);

	CC_SYNTHESIZE(bool, _skillUseState, SkillUseState);
	CC_SYNTHESIZE(std::string, _aniName, AniName);

	cocos2d::Layer * layer;
	Weapon * weapon;
	Paddle * paddle;
	
	std::vector<int> itemList;
	std::vector<int> helperList;
public:
	Hero();
	static Hero* create(Hero * hero);
	~Hero();

	virtual void IncreaseMaxHp(int i);
	virtual void DecreaseMaxHp(int i);
	virtual void IncreaseCurrentHp(int i);

	virtual void IncreaseMaxSp(int i);
	virtual void DecreaseMaxSp(int i);
	virtual void IncreaseCurrentSp(int i);
	virtual void DecreaseCurrentSp(int i);

	void IncreaseKeyCount(int num);
	void IncreaseBombCount(int num);
	void IncreaseMoneyCount(int num);
	void DecreaseKeyCount(int num);
	void DecreaseBombCount(int num);
	void DecreaseMoneyCount(int num);

	void SetSkill(int skill);
	void SetSkill(SkillItem * skill);
	void IncreaseSkillPoint(int num);
	void DecreaseSkillPoint(int num);
	void FullSkillPoint();
	void EmptySkillPoint();
	bool IsSkillUse();
	virtual void SkillUse();
	bool IsFullHp();
	virtual void DoSkillEvent(cocos2d::Vec2 touch);

	void InitSprite();

	void SetHeroData();
	void SetHeroData(Hero * hero);
	void SetWeapon(const char * weaponType, const char * weaponName);
	void ChangeWeapon(const char * weaponType, const char * weaponName);
	void RemoveWeapon();

	void Draw(cocos2d::Layer* layer);
	void Move(cocos2d::Vec2 vec);

	void Swing();
	virtual void Die();
	
	bool HasItem(int itemID);
	void SetItem(int itemID);

	virtual void update(float dt);

	void Save();

	void Debug();

	virtual void Ani(const char * str, cocos2d::__Dictionary* dic);
	virtual void DieAni(const char * str, cocos2d::__Dictionary* dic);
	virtual cocos2d::__Dictionary* GetAniInfo();

	virtual void DecreaseCurrentHp(int i);
};

#endif // __HERO_H__
 