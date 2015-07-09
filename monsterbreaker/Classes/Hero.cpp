#include"Hero.h"

USING_NS_CC;

Hero::Hero()
{
	_type = "Hero";
	_skillUseState = false;

	auto cache = SpriteFrameCache::sharedSpriteFrameCache();
	cache->addSpriteFramesWithFile("Hero/HalfHero/HalfHeroImage.plist", "Hero/HalfHero/HalfHero.png");
}
Hero::~Hero()
{

}
void Hero::update(float dt)
{
}

// i is only multiples of two
void Hero::IncreaseMaxHp(int i)
{
	if (IsAlive())
	{
		if (Utils::GetInstance()->IsMultiplesOfTwo(i)) {
			_maxHp += i;
			if (_maxHp > 10)
				_maxHp = 10;
			IncreaseCurrentHp(i);
			SoundManager::getInstance()->playMySoundLogic("HpUp");
		}
		else{
			CCLOG("Warning :: IncreaseMaxHp(int i) method called :: parameter i is not multiples of two");
		}
		Utils::GetInstance()->FreeInstance();
	}

}

// i is only multiples of two
void Hero::DecreaseMaxHp(int i)
{
	if (IsAlive())
	{
		// is i power of two?
		if (Utils::GetInstance()->IsMultiplesOfTwo(i)) {
			GameObject::DecreaseMaxHp(i);
		}
		else
		{
			CCLOG("Warning :: DecreaseMaxHp(int i) method called :: parameter i is not multiples of two");
		}
		Utils::GetInstance()->FreeInstance();
	}
}

void Hero::IncreaseCurrentHp(int i)
{
	GameObject::IncreaseCurrentHp(i);
	if (IsAlive())
	{
		SoundManager::getInstance()->playMySoundLogic("HpUp");
	}
}

void Hero::IncreaseMaxSp(int i)
{
	if (IsAlive())
	{
		// is i power of two?
		if (Utils::GetInstance()->IsMultiplesOfTwo(i)) {
			_maxSp += i;
			if (_maxSp > 10)
				_maxSp = 10;
			IncreaseCurrentSp(i);
			SoundManager::getInstance()->playMySoundLogic("HpUp");
		}
		else
		{
			CCLOG("Warning :: IncreaseMaxSp(int i) method called :: parameter i is not multiples of two");
		}
		Utils::GetInstance()->FreeInstance();
	}
}
void Hero::DecreaseMaxSp(int i)
{
	if (IsAlive())
	{
		// is i power of two?
		if (Utils::GetInstance()->IsMultiplesOfTwo(i)) {
			_maxSp -= i;
			if (_maxSp < 0)
				_maxSp = 0;
			if (_maxSp < _currentSp)
				_currentSp = _maxSp;
		}
		else
		{
			CCLOG("Warning :: IncreaseMaxSp(int i) method called :: parameter i is not multiples of two");
		}
		Utils::GetInstance()->FreeInstance();
	}
}
void Hero::IncreaseCurrentSp(int i)
{
	if (IsAlive())
	{
		_currentSp += i;
		if (_maxSp < _currentSp)
			_currentSp = _maxSp;
		SoundManager::getInstance()->playMySoundLogic("HpUp");
	}
}
void Hero::DecreaseCurrentSp(int i)
{
	if (IsAlive())
	{
		_currentSp -= i;
		if (_currentSp < 0)
			_currentSp = 0;
	}
}

void Hero::IncreaseKeyCount(int num)
{
	if (IsAlive())
	{
		_keyCount += num;
		if (_keyCount >= 100) _keyCount = 99;
		SoundManager::getInstance()->playMySoundLogic("PickUpCoin");
	}
}
void Hero::IncreaseBombCount(int num)
{
	if (IsAlive())
	{
		_bombCount += num;
		if (_bombCount >= 100) _bombCount = 99;
		SoundManager::getInstance()->playMySoundLogic("PickUpCoin");
	}
}
void Hero::IncreaseMoneyCount(int num)
{
	if (IsAlive())
	{
		_moneyCount += num;
		if (_moneyCount >= 100) _moneyCount = 99;

		SoundManager::getInstance()->playMySoundLogic("PickUpCoin");
	}
}
void Hero::DecreaseKeyCount(int num)
{
	if (IsAlive())
	{
		_keyCount -= num;
		if (_keyCount < 0) _keyCount = 0;
	}
}
void Hero::DecreaseBombCount(int num)
{
	if (IsAlive())
	{
		_bombCount -= num;
		if (_bombCount < 0) _bombCount = 0;
	}
}
void Hero::DecreaseMoneyCount(int num)
{
	if (IsAlive())
	{
		_moneyCount -= num;
		if (_moneyCount < 0) _moneyCount = 0;
	}
}

Hero* Hero::create(Hero * hero)
{
	auto pSprite = new Hero();
	pSprite->SetHeroData(hero);

	auto cache = SpriteFrameCache::sharedSpriteFrameCache();
	cache->addSpriteFramesWithFile(
		String::createWithFormat("%s/%s/%sImage.plist", pSprite->getType().c_str(), pSprite->getName().c_str(), pSprite->getName().c_str())->getCString(),
		String::createWithFormat("%s/%s/%s.png", pSprite->getType().c_str(), pSprite->getName().c_str(), pSprite->getName().c_str())->getCString()
		);

	if (pSprite->initWithSpriteFrameName(String::createWithFormat("%s.png", pSprite->getName().c_str())->getCString()))
	{
		pSprite->autorelease();
		pSprite->Animate("Stay", myEnum::kAction::kActionStay);
		return pSprite;
	}
	CC_SAFE_DELETE(pSprite);
	return NULL;
}
void Hero::SetHeroData(Hero * hero)
{
	_type = hero->getType();
	_name = hero->getName();
	_team = hero->getTeam();
	_maxHp = hero->getMaxHp();
	_currentHp = hero->getCurrentHp();
	_attackPoint = hero->getAttackPoint();
	_alive = hero->getAlive();
	_damagedState = hero->getDamagedState();

	_ballCount = hero->getBallCount();
	_ballCurrentCount = hero->getBallCurrentCount();
	_ballName = hero->getBallName();
	_ballVelocity = hero->getBallVelocity();
	_ballSize = hero->getBallSize();

	_maxSp = hero->getMaxSp();
	_currentSp = hero->getCurrentSp();
	_keyCount = hero->getKeyCount();
	_bombCount = hero->getBombCount();
	_moneyCount = hero->getMoneyCount();

	_bombName = hero->getBombName();
	_bombAttackPoint = hero->getBombAttackPoint();
	_bombRange = hero->getBombRange();
	_bombCountTime = hero->getBombCountTime();
	_bombSetCountTime = hero->getBombSetCountTime();
	_paddleSize = hero->getPaddleSize();

	_weaponName = hero->getWeaponName();

	_skillID = hero->getSkillID();
	_skillCurrentPoint = hero->getSkillCurrentPoint();
	_skillMaxPoint = hero->getSkillMaxPoint();

	_aniName = hero->getAniName();

	itemList = hero->itemList;
	helperList = hero->helperList;
}


void Hero::SetHeroData()
{
	auto heroData = HeroData::getInstance();
	_type = heroData->getType();
	_name = heroData->getName();
	_team = heroData->getTeam();
	_maxHp = heroData->getMaxHp();
	_currentHp = heroData->getCurrentHp();
	_attackPoint = heroData->getAttackPoint();
	_alive = heroData->getAlive();
	_damagedState = heroData->getDamagedState();

	_ballCount = heroData->getBallCount();
	_ballCurrentCount = heroData->getBallCurrentCount();
	_ballName = heroData->getBallName();
	_ballVelocity = heroData->getBallVelocity();
	_ballSize = heroData->getBallSize();

	_maxSp = heroData->getMaxSp();
	_currentSp = heroData->getCurrentSp();
	_keyCount = heroData->getKeyCount();
	_bombCount = heroData->getBombCount();
	_moneyCount = heroData->getMoneyCount();

	_bombName = heroData->getBombName();
	_bombAttackPoint = heroData->getBombAttackPoint();
	_bombRange = heroData->getBombRange();
	_bombCountTime = heroData->getBombCountTime();
	_bombSetCountTime = heroData->getBombSetCountTime();
	_paddleSize = heroData->getPaddleSize();

	_weaponName = heroData->getWeaponName();

	_skillID = heroData->getSkillID();
	_skillCurrentPoint = heroData->getSkillCurrentPoint();
	_skillMaxPoint = heroData->getSkillMaxPoint();

	_aniName = heroData->getAniName();

	itemList = heroData->itemList;
	helperList = heroData->helperList;
}

void Hero::InitSprite()
{
	MyBodyParser::getInstance()->parseJsonFile(String::createWithFormat("%s/%s/%s.json", _type.c_str(), _name.c_str(), _name.c_str())->getCString());
	auto body = MyBodyParser::getInstance()->bodyFormJson(this, String::createWithFormat("%s.png", _name.c_str())->getCString(), PhysicsMaterial(100, 1, 0));
	if (body != nullptr)
	{
		body->setDynamic(true);
		body->setGravityEnable(false);
		body->setRotationEnable(false);
		body->setCollisionBitmask(HERO_BODY_COLLISION_BITMASK);
		body->setContactTestBitmask(true);
		this->setPhysicsBody(body);
	}
	this->setUserData(this);
	this->Animate("Stay", myEnum::kAction::kActionStay);
	MyBodyParser::getInstance()->freeInstance();

}

void Hero::SetWeapon(const char * weaponType, const char * weaponName)
{
	weapon = Weapon::create(layer, this, weaponType, weaponName, false);
	_weaponName = weaponName;
	// weapon ++
	_attackPoint += weapon->getAttackPoint();
	_paddleSize += weapon->getpaddleSize();
	// weapon setposition
	weapon->setPosition(this->getPosition());
	weapon->Stay();
	// paddle set
	paddle = Paddle::create(_paddleSize, weapon->getPaddleName().c_str());
	paddle->setPosition(this->getPosition().x, this->getPosition().y + paddle->getContentSize().height *1.5);

}

void Hero::ChangeWeapon(const char * weaponType, const char * weaponName)
{
	RemoveWeapon();
	SetWeapon(weaponType, weaponName);
	layer->addChild(weapon, ZINDEX_HERO_WEAPON);
	layer->addChild(paddle, ZINDEX_HERO_PADDLE);
}
void Hero::RemoveWeapon()
{
	_attackPoint -= weapon->getAttackPoint();
	_paddleSize -= weapon->getpaddleSize();
	weapon->stopAllActions();
	layer->removeChild(weapon);
	layer->removeChild(paddle);

}

void Hero::Move(cocos2d::Vec2 vec)
{
	this->setPosition(vec);
	weapon->setPosition(vec);
	paddle->setPosition(vec.x, vec.y + paddle->getContentSize().height*2);
}
void Hero::Draw(cocos2d::Layer* layer)
{
	layer->addChild(this, ZINDEX_HERO_SPRITE, "Hero");
	layer->addChild(weapon, ZINDEX_HERO_WEAPON);
	layer->addChild(paddle, ZINDEX_HERO_PADDLE);
	this->layer = layer;
}

void Hero::Swing()
{
	if (IsAlive())
	{
		Animate("Attack", myEnum::kAction::kActionAttack);
		weapon->Swing();
	}
}
void Hero::Die()
{
	Animate("Die", myEnum::kAction::kActionDie);
	weapon->Die();
	SoundManager::getInstance()->playMySoundLogic("Die");
}

void Hero::Debug()
{
	// Game Data
	CCLOG("team : %d", _team);
	CCLOG("maxHp : %d", _maxHp);
	CCLOG("currentHp : %d", _currentHp);
	CCLOG("attackPoint : %d", _attackPoint);
	CCLOG("alive : %s", _alive ? "true" : "false");
	CCLOG("damagedState : %s", _damagedState ? "true" : "false");
	CCLOG("actionState : %d", _actionState);

	CCLOG("name : %s", _name.c_str());
	CCLOG("type : %s", _type.c_str());

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
	CCLOG("bombRange : %f", _bombRange);
	CCLOG("bombCountTime : %f", _bombCountTime);
	CCLOG("bombSetCountTime : %f", _bombSetCountTime);

	CCLOG("paddleSize : %f", _paddleSize);

	CCLOG("WeaponName : %s", _weaponName.c_str());

	CCLOG("Skill : %d", _skillID);
	CCLOG("SkillCurrentPoint : %d", _skillCurrentPoint);
	CCLOG("SkillMaxPoint : %d", _skillMaxPoint);

	for (int i = 0; i < itemList.size(); i++)
		CCLOG("item : %d", itemList.at(i));

}

void Hero::Save()
{
	auto heroData = HeroData::getInstance();
	heroData->setName(_name);
	heroData->setType(_type);
	heroData->setTeam(_team);

	heroData->setMaxHp(_maxHp);
	heroData->setCurrentHp(_currentHp);
	heroData->setAttackPoint(_attackPoint - weapon->getAttackPoint());
	heroData->setAlive(true);
	heroData->setDamagedState(false);
	heroData->setActionState(myEnum::kAction::kActionStay);

	//
	heroData->setBallCount(_ballCount);
	heroData->setBallCurrentCount(0);
	heroData->setBallName(_ballName);
	heroData->setBallVelocity(_ballVelocity);
	heroData->setBallSize(_ballSize);
	//
	heroData->setMaxSp(_maxSp);
	heroData->setCurrentSp(_currentSp);
	heroData->setKeyCount(_keyCount);
	heroData->setBombCount(_bombCount);
	heroData->setMoneyCount(_moneyCount);

	heroData->setBombName(_bombName);
	heroData->setBombAttackPoint(_bombAttackPoint);
	heroData->setBombRange(_bombRange);
	heroData->setBombCountTime(_bombCountTime);
	heroData->setBombSetCountTime(_bombSetCountTime);
	heroData->setPaddleSize(_paddleSize - weapon->getpaddleSize());
	heroData->setWeaponName(_weaponName);

	heroData->itemList = itemList;

	heroData->setSkillID(_skillID);
	heroData->setSkillCurrentPoint(_skillCurrentPoint);
	heroData->setSkillMaxPoint(_skillMaxPoint);

	heroData->setAniName(_aniName);
	heroData->helperList = helperList;
}

bool Hero::HasItem(int itemID)
{
	return (std::find(itemList.begin(), itemList.end(), itemID) != itemList.end());
}

void Hero::SetItem(int itemID)
{
	itemList.push_back(itemID);
	switch (itemID)
	{
	case ITEM_BEAUTY_GLASS_BEAD:
		_attackPoint += 1;
		_ballSize += 1.0f;
		_ballName = "GlassBead";
		break;
	case ITEM_BLACK_AND_WHITE:
	{
		_attackPoint += 1;
		IncreaseMaxHp(2);
		IncreaseMaxSp(2);

		// change hero image
		auto cache = SpriteFrameCache::sharedSpriteFrameCache();
		cache->addSpriteFramesWithFile("Hero/HalfHero/HalfHeroImage.plist", "Hero/HalfHero/HalfHero.png");
		this->setTexture(cache->getSpriteFrameByName("HalfHero.png")->getTexture());
		_aniName = "HalfHero";
		this->Animate("Stay", myEnum::kAction::kActionStay);
		weapon->Stay();
	}
		break;
	case ITEM_BOMBER:
		_bombAttackPoint += 5;
		_bombCount += 5;
		_bombSetCountTime -= 0.5f;
		_bombCountTime -= 0.5f;
		_bombRange += 1;
		break;
	case ITEM_BOMB_PACKAGE:
		_bombCount += 5;
		break;
	case ITEM_CHAKRAM:
		_attackPoint += 1;
		// change ball image
		_ballName = "Chakram";
		break;
	case ITEM_DANCING_TOY:
		_attackPoint += 1;
		_ballVelocity += 250;
		// change ball image
		_ballName = "DancingToy";
		break;
	case ITEM_DYNAMITE:
		_bombCountTime += 1.0f;
		_bombAttackPoint += 5;
		_bombRange += 1;
		// change bomb image
		_bombName = "Dynamite";
		break;
	case ITEM_FRESH_MEAT:
		IncreaseMaxHp(2);
		setScaleX(3.0f);
		break;
	case ITEM_GOLD:
		IncreaseMoneyCount(10);
		break;
	case ITEM_LOL:
		IncreaseMaxHp(2);
		IncreaseMaxSp(2);
		_attackPoint += 1;
		break;
	case ITEM_SOUL_EATER:
		IncreaseMaxSp(2);
		break;
	case ITEM_STONE_OF_DAVID:
		_attackPoint += 2;
		_paddleSize = 0.7f;
		// change ball image
		_ballName = "StoneOfDavid";
		break;
	case ITEM_REMOTE_BOMB:
		_bombSetCountTime += 0.5f;
		// change bomb image
		_bombName = "RemoteBomb";
		break;
	case ITEM_TRINITY:
		_ballCount = 3;
		break;
	case ITEM_TRUTH:
		_attackPoint += 1;
		IncreaseMaxHp(2);
		IncreaseMaxSp(2);
		break;
	case ITEM_SCAVENGER:
		break;
	case ITEM_SECRET_MASTER:
		break;
	case ITEM_THE_MAP:
		break;
	case ITEM_THE_COMPASS:
		break;
	}
}

void Hero::SetSkill(SkillItem * skill)
{
	_skillID = skill->getSkillID();
	_skillMaxPoint = skill->getMaxPoint();
	_skillCurrentPoint = skill->getCurrentPoint();
}

void Hero::SetSkill(int skill)
{
	_skillID = skill;

	auto dic = __Dictionary::createWithContentsOfFile("Skill/SkillData.plist");
	auto item = (cocos2d::__Dictionary *)dic->objectForKey(String::createWithFormat("%d", _skillID)->getCString());

	_skillMaxPoint = item->valueForKey("MaxPoint")->intValue();
	_skillCurrentPoint = _skillMaxPoint;
}

void Hero::IncreaseSkillPoint(int num)
{
	_skillCurrentPoint += num;
	if (_skillCurrentPoint > _skillMaxPoint)
		_skillCurrentPoint = _skillMaxPoint;
}

void Hero::DecreaseSkillPoint(int num)
{
	_skillCurrentPoint -= num;
	if (_skillCurrentPoint < 0)
		_skillCurrentPoint = 0;
}
void Hero::FullSkillPoint()
{
	_skillCurrentPoint = _skillMaxPoint;
}
void Hero::EmptySkillPoint()
{
	_skillCurrentPoint = 0;
}

bool Hero::IsSkillUse()
{
	bool result = false;
	if (_skillCurrentPoint == _skillMaxPoint)
		result = true;
	return result;
}
void Hero::SkillUse()
{
	if (IsSkillUse())
	{
		EmptySkillPoint();
	}
}

bool Hero::IsFullHp()
{
	bool result = false;
	if (getMaxHp() == getCurrentHp())
		result = true;
	return result;
}
void Hero::DoSkillEvent(cocos2d::Vec2 touch)
{
	// nothing
}

void Hero::Ani(const char * str, cocos2d::__Dictionary* dic)
{
	auto cache = SpriteFrameCache::sharedSpriteFrameCache();
	auto ani = Animation::create();
	int frame = dic->valueForKey("Frame")->intValue();
	ani->setDelayPerUnit(dic->valueForKey("AniDelay")->floatValue());
	for (int i = 1; i <= frame; i++) ani->addSpriteFrame(cache->spriteFrameByName(cocos2d::__String::createWithFormat(dic->valueForKey("AniFormat")->getCString(), _aniName.c_str(), str, i)->getCString()));

	if (dic->valueForKey("RepeatForever")->boolValue())
	{
		this->runAction(RepeatForever::create(Animate::create(ani)));
	}
	else
	{
		this->runAction(Sequence::create(Repeat::create(Animate::create(ani), dic->valueForKey("RepeatCount")->intValue())
			, CallFunc::create(std::bind(&GameObject::Animate, this, "Stay", myEnum::kAction::kActionStay))
			, NULL));
	}
}

void Hero::DieAni(const char * str, cocos2d::__Dictionary* dic)
{
	auto cache = SpriteFrameCache::sharedSpriteFrameCache();
	auto ani = Animation::create();
	int frame = dic->valueForKey("Frame")->intValue();
	ani->setDelayPerUnit(dic->valueForKey("AniDelay")->floatValue());
	for (int i = 1; i <= frame; i++) ani->addSpriteFrame(cache->spriteFrameByName(cocos2d::__String::createWithFormat(dic->valueForKey("AniFormat")->getCString(), _aniName.c_str(), str, i)->getCString()));

	this->runAction(Sequence::create(Repeat::create(Animate::create(ani), dic->valueForKey("RepeatCount")->intValue())
		, NULL));
}

cocos2d::__Dictionary* Hero::GetAniInfo()
{
	auto data = __Dictionary::createWithContentsOfFile(String::createWithFormat("%s/%s/%sAni.plist", _type.c_str(), _aniName.c_str(), _aniName.c_str())->getCString());
	return data;
}

void Hero::DecreaseCurrentHp(int i)
{
	GameObject::DecreaseCurrentHp(i);
	SoundManager::getInstance()->playMySoundLogic("HeroDamaged");
}

