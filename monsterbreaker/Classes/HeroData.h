#pragma once
#ifndef __HERO_DATA_H__
#define __HERO_DATA_H__

#include "cocos2d.h"
//#include "Hero.h"

class HeroData
{
private:
	void Init();
	static HeroData * instance;

protected:
	// Game Data
	CC_SYNTHESIZE(int, _team, Team);
	CC_SYNTHESIZE(int, _maxHp, MaxHp);
	CC_SYNTHESIZE(int, _currentHp, CurrentHp);
	CC_SYNTHESIZE(int, _attackPoint, AttackPoint);
	CC_SYNTHESIZE(bool, _alive, Alive);
	CC_SYNTHESIZE(bool, _damagedState, DamagedState);
	CC_SYNTHESIZE(int, _actionState, ActionState);

	CC_SYNTHESIZE(std::string, _name, Name);
	CC_SYNTHESIZE(std::string, _type, Type);

	//std::vector<int> state;
	//std::vector<int> strongState;
	//std::vector<int> weakState;

	// Character Data
	CC_SYNTHESIZE(int, _ballCount, BallCount);
	CC_SYNTHESIZE(int, _ballCurrentCount, BallCurrentCount);
	CC_SYNTHESIZE(std::string, _ballName, BallName);
	CC_SYNTHESIZE(float, _ballVelocity, BallVelocity);
	CC_SYNTHESIZE(float , _ballSize, BallSize);

	// Hero Data
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

	// Skill Data
	CC_SYNTHESIZE(int, _skillID, SkillID);
	CC_SYNTHESIZE(int, _skillCurrentPoint, SkillCurrentPoint);
	CC_SYNTHESIZE(int, _skillMaxPoint, SkillMaxPoint);

	// Animate Data
	CC_SYNTHESIZE(std::string, _aniName, AniName);

	std::vector<int> itemList;
	std::vector<int> helperList;
public:
	HeroData();
	~HeroData();
	static HeroData* getInstance();
	void freeInstance();
	void Debug();
	void InitWithFile(const char * type, const char * name);
//	void InitHeroData(const Hero & hero);
//	void CopyData(const char * type, const char * name);
//	void SaveData() const;
//	void LoadData();
	void SaveData() const;
	void LoadData();
};

#endif // __HERO_H__
 
