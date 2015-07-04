#include"HeroData.h"
#include "Definitions.h"
USING_NS_CC;

HeroData * HeroData ::instance = nullptr;
HeroData::HeroData()
{

}

HeroData::~HeroData()
{

}
HeroData* HeroData::getInstance()
{
	if (instance == nullptr)
		instance = new HeroData();
	return instance;
}
void HeroData::freeInstance()
{
	if (instance != nullptr)
		CC_SAFE_DELETE(instance);
}

void HeroData::Debug()
{
	// Game Data
	CCLOG("team : %d", _team);
	CCLOG("maxHp : %d", _maxHp);
	CCLOG("currentHp : %d", _currentHp);
	CCLOG("attackPoint : %d", _attackPoint);
	CCLOG("alive : %s", _alive ? "true" : "false");
	CCLOG("damagedState : %s", _damagedState? "true" : "false");
	CCLOG("actionState : %d", _actionState);

	CCLOG("name : %s", _name.c_str());
	CCLOG("type : %s", _type.c_str());

	//std::vector<int> state;
	//std::vector<int> strongState;
	//std::vector<int> weakState;

	// Character Data
	CCLOG("ballCount : %d", _ballCount);
	CCLOG("ballCurrentCount : %d", _ballCurrentCount);
	CCLOG("ballName : %s", _ballName.c_str());
	CCLOG("ballVelocity : %d", _ballVelocity);
	CCLOG("ballSize : %d", _ballSize);

	// Hero Data
	CCLOG("maxSp : %d", _maxSp);
	CCLOG("currentSp : %d", _currentSp);

	CCLOG("keyCount : %d", _keyCount);
	CCLOG("bombCount : %d", _bombCount);
	CCLOG("moneyCount : %d", _moneyCount);

	CCLOG("bombName : %s", _bombName.c_str());
	CCLOG("bombAttackPoint : %d", _bombAttackPoint);
	CCLOG("bombRange : %f",_bombRange);
	CCLOG("bombCountTime : %f", _bombCountTime);
	CCLOG("bombSetCountTime : %f", _bombSetCountTime);

	CCLOG("paddleSize : %f", _paddleSize);

	CCLOG("weaponName : %s", _weaponName.c_str());

	int itemSize = itemList.size();
	CCLOG("itemSize : %d", itemSize);
	for (int i = 0; i < itemSize; i++)
	{
		CCLOG("item%d : %d", i, itemList.at(i));
	}
}
void HeroData::InitWithFile(const char * type, const char * name)
{
	_type = type;
	_name = name;
	
	// game object data
	auto dic = cocos2d::__Dictionary::createWithContentsOfFile(String::createWithFormat("%s/%s/%s.plist", _type.c_str(), _name.c_str(), _name.c_str())->getCString());
	_team = dic->valueForKey("Team")->intValue();
	_maxHp = dic->valueForKey("MaxHp")->intValue();
	_currentHp = dic->valueForKey("CurrentHp")->intValue();
	_attackPoint = dic->valueForKey("AttackPoint")->intValue();
	_alive = true;
	_damagedState = false;
	_actionState = myEnum::kAction::kActionStay;


	// character data
	_ballCount = dic->valueForKey("BallCount")->intValue();
	_ballCurrentCount = dic->valueForKey("BallCurrentCount")->intValue();
	_ballName = dic->valueForKey("BallName")->getCString();
	_ballVelocity = dic->valueForKey("BallVelocity")->floatValue();
	_ballSize = dic->valueForKey("BallSize")->floatValue();

	// hero data
	_maxSp = dic->valueForKey("MaxSp")->intValue();
	_currentSp = dic->valueForKey("CurrentSp")->intValue();
	_keyCount = dic->valueForKey("KeyCount")->intValue();
	_bombCount = dic->valueForKey("BombCount")->intValue();
	_moneyCount = dic->valueForKey("MoneyCount")->intValue();

	_bombName = dic->valueForKey("BombName")->getCString();
	_bombAttackPoint = dic->valueForKey("BombAttackPoint")->intValue();
	_bombRange = dic->valueForKey("BombRange")->floatValue();
	_bombCountTime = dic->valueForKey("BombCountTime")->floatValue();
	_bombSetCountTime = dic->valueForKey("BombSetCountTime")->floatValue();

	_paddleSize = dic->valueForKey("PaddleSize")->floatValue();

	_weaponName = dic->valueForKey("WeaponName")->getCString();

	// skill data
	_skillID = dic->valueForKey("Skill")->intValue();
	_skillCurrentPoint = dic->valueForKey("SkillCurrentPoint")->intValue();
	_skillMaxPoint = dic->valueForKey("SkillMaxPoint")->intValue();

	_aniName = dic->valueForKey("AniName")->getCString();

	// init vector data
	itemList.clear();
	helperList.clear();
}

//void HeroData::SaveData()
//{
//	
//}
//void HeroData::LoadData()
//{
//
//}


void HeroData::SaveData() const
{
	auto def = UserDefault::sharedUserDefault();
	// init
	def->setStringForKey("p_name", _name.c_str());
	def->setStringForKey("p_type", _type.c_str());
	def->setIntegerForKey("p_team", _team);
	def->setIntegerForKey("p_maxHp", _maxHp);
	def->setIntegerForKey("p_currentHp", _currentHp);
	def->setIntegerForKey("p_attackPoint", _attackPoint);
	def->setBoolForKey("p_alive", _alive);
	def->setBoolForKey("p_damagedState", _damagedState);

	// ball
	def->setIntegerForKey("p_ballCount", _ballCount);
	def->setIntegerForKey("p_ballCurrentCount", _ballCurrentCount);
	def->setStringForKey("p_ballName", _ballName.c_str());
	def->setFloatForKey("p_ballVelocity", _ballVelocity);
	def->setFloatForKey("p_ballSize", _ballSize);

	// sp & item
	def->setIntegerForKey("p_maxSp", _maxSp);
	def->setIntegerForKey("p_currentSp", _currentSp);
	def->setIntegerForKey("p_keyCount", _keyCount);
	def->setIntegerForKey("p_bombCount", _bombCount);
	def->setIntegerForKey("p_moneyCount", _moneyCount);

	// bomb
	def->setStringForKey("p_bombName", _bombName.c_str());
	def->setIntegerForKey("p_bombAttackPoint", _bombAttackPoint);
	def->setFloatForKey("p_bombRange", _bombRange);
	def->setFloatForKey("p_bombCountTime", _bombCountTime);
	def->setFloatForKey("p_bombSetCountTime", _bombSetCountTime);
	def->setFloatForKey("p_paddleSize", _paddleSize);

	// weapon
	def->setStringForKey("p_weaponName", _weaponName.c_str());

	// item data
	int itemSize = itemList.size();
	def->setIntegerForKey("p_itemSize", itemSize);
	for (int i = 0; i < itemSize; i++)
	{
		def->setIntegerForKey(String::createWithFormat("p_item%d", i)->getCString(), itemList.at(i));
	}

	// skill
	def->setIntegerForKey("p_skillID", _skillID);
	def->setIntegerForKey("p_skillCurrentPoint", _skillCurrentPoint);
	def->setIntegerForKey("p_skillMaxPoint", _skillMaxPoint);

	// helper
	int helperSize = helperList.size();
	def->setIntegerForKey("p_helperSize", helperSize);
	for (int i = 0; i < helperSize; i++)
	{
		def->setIntegerForKey(String::createWithFormat("p_helper%d", i)->getCString(), helperList.at(i));
	}

	// animate data
	def->setStringForKey("p_aniName", _aniName.c_str());

	def->flush();
}
void HeroData::LoadData()
{
	auto def = UserDefault::sharedUserDefault();
	_name = def->getStringForKey("p_name");
	_type = def->getStringForKey("p_type");
	_team = def->getIntegerForKey("p_team");
	_maxHp = def->getIntegerForKey("p_maxHp");
	_currentHp = def->getIntegerForKey("p_currentHp");
	_attackPoint = def->getIntegerForKey("p_attackPoint");
	_alive = def->getBoolForKey("p_alive");
	_damagedState = def->getBoolForKey("p_damagedState");
	_actionState = myEnum::kAction::kActionStay;

	// ball
	_ballCount = def->getIntegerForKey("p_ballCount");
	_ballCurrentCount = def->getIntegerForKey("p_ballCurrentCount");
	_ballName = def->getStringForKey("p_ballName");
	_ballVelocity = def->getFloatForKey("p_ballVelocity");
	_ballSize = def->getFloatForKey("p_ballSize");

	// sp & item
	_maxSp = def->getIntegerForKey("p_maxSp");
	_currentSp = def->getIntegerForKey("p_currentSp");
	_keyCount = def->getIntegerForKey("p_keyCount");
	_bombCount = def->getIntegerForKey("p_bombCount");
	_moneyCount = def->getIntegerForKey("p_moneyCount");

	// bomb
	_bombName = def->getStringForKey("p_bombName");
	_bombAttackPoint = def->getIntegerForKey("p_bombAttackPoint");
	_bombRange = def->getFloatForKey("p_bombRange");
	_bombCountTime = def->getFloatForKey("p_bombCountTime");
	_bombSetCountTime = def->getFloatForKey("p_bombSetCountTime");
	_paddleSize = def->getFloatForKey("p_paddleSize");

	// weapon
	_weaponName = def->getStringForKey("p_weaponName");

	// item data
	itemList.clear();
	int itemSize = def->getIntegerForKey("p_itemSize");
	for (int i = 0; i < itemSize; i++)
	{
		itemList.push_back(def->getIntegerForKey(String::createWithFormat("p_item%d", i)->getCString()));
	}
	
	// skill
	_skillID = def->getIntegerForKey("p_skillID", 0);
	_skillCurrentPoint  = def->getIntegerForKey("p_skillCurrentPoint", 0);
	_skillMaxPoint = def->getIntegerForKey("p_skillMaxPoint", 0);
	
	// helper
	helperList.clear();
	int helperSize = def->getIntegerForKey("p_helperSize", 0);
	for (int i = 0; i < helperSize; i++)
	{
		helperList.push_back(def->getIntegerForKey(String::createWithFormat("p_helper%d", i)->getCString(), 0));
	}
	// animate data
	_aniName = def->getStringForKey("p_aniName", "Warrior");

}

//void HeroData::InitHeroData(const Hero & hero)
//{
//	_name = hero.getName();
//	_type = hero.getType();
//	_team = hero.getTeam();
//	_maxHp = hero.getMaxHp();
//	_currentHp = hero.getCurrentHp();
//	_attackPoint = hero.getAttackPoint();
//	_alive = true;
//	_damagedState = false;
//	_actionState = myEnum::kAction::kActionStay;
//
//	_ballCount = hero.getBallCount();
//	_ballCurrentCount = 0;
//	_ballName = hero.getBallName();
//	_ballVelocity = hero.getBallVelocity();
//	_ballAccel = hero.getBallAccel();
//
//	_maxSp = hero.getMaxSp();
//	_currentSp = hero.getCurrentSp();
//	_keyCount = hero.getKeyCount();
//	_bombCount = hero.getBombCount();
//	_moneyCount = hero.getMoneyCount();
//
//	_bombName = hero.getBombName();
//	_bombAttackPoint = hero.getBombAttackPoint();
//	_bombRange = hero.getBombRange();
//	_bombCountTime = hero.getBombCountTime();
//	_bombSetCountTime = hero.getBombSetCountTime();
//	_paddleSize = hero.getPaddleSize();
//
//	_weaponName = hero.getWeaponName();
//}





