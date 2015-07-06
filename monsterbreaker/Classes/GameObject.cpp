#include"GameObject.h"
#include "Definitions.h"
#include "Utils.h"
USING_NS_CC;

GameObject::GameObject()
{
	Init();
}
GameObject::~GameObject()
{

}
void GameObject::Init()
{
	_name = "NULL";
	_type = "NULL";
	_team = 0;
	_maxHp = 0;
	_currentHp = 0;
	_attackPoint = 0;
	_alive = true;
	_damagedState = false;
	_actionState = myEnum::kAction::kActionStay;
}

void GameObject::IncreaseMaxHp(int i)
{
	if (IsAlive())
	{
		_maxHp += i;
		IncreaseCurrentHp(i);
	}
}
void GameObject::DecreaseMaxHp(int i)
{
	if (IsAlive())
	{
		_maxHp -= i;
		if (_maxHp < 0)
			_maxHp = 0;
		if (_maxHp < _currentHp)
			_currentHp = _maxHp;
	}
	
}
void GameObject::IncreaseCurrentHp(int i)
{
	if (IsAlive())
	{
		_currentHp += i;
		if (_currentHp > _maxHp)
			_currentHp = _maxHp;
	}
}

void GameObject::DecreaseCurrentHp(int i)
{
	_currentHp -= i;
	if (_currentHp <= 0)
	{
		_currentHp = 0;
		_alive = false;
		Die();
	}
}
void GameObject::SetBodyEnable(bool b)
{
	this->getPhysicsBody()->setEnable(b);
}
void GameObject::Die()
{
	Animate("Die", myEnum::kAction::kActionDie);
}

void GameObject::Animate(const char * str, int kAction)
{
	if (!IsDamaged() || !IsAlive())
	{
		kAction = kAction;
		this->stopAllActions();
		auto aniData = GetAniInfo();

		switch (kAction)
		{
		case myEnum::kAction::kActionAttack: Ani(str, (__Dictionary *)aniData->objectForKey("Attack")); break;
		case myEnum::kAction::kActionDie: DieAni(str, (__Dictionary *)aniData->objectForKey("Die")); break;
		case myEnum::kAction::kActionMove: Ani(str, (__Dictionary *)aniData->objectForKey("Move")); break;
		case myEnum::kAction::kActionSkill: Ani(str, (__Dictionary *)aniData->objectForKey("Skill")); break;
		case myEnum::kAction::kActionStay: Ani(str, (__Dictionary *)aniData->objectForKey("Stay")); break;
		case myEnum::kAction::kActionSleep: Ani(str, (__Dictionary *)aniData->objectForKey("Sleep")); break;
		case myEnum::kAction::kActionAwake: Ani(str, (__Dictionary *)aniData->objectForKey("Awake")); break;
		}
	}
}

void GameObject::Ani(const char * str, cocos2d::__Dictionary* dic)
{
	auto cache = SpriteFrameCache::sharedSpriteFrameCache();
	auto ani = Animation::create();
	int frame = dic->valueForKey("Frame")->intValue();
	ani->setDelayPerUnit(dic->valueForKey("AniDelay")->floatValue());
	for (int i = 1; i <= frame; i++) ani->addSpriteFrame(cache->spriteFrameByName(cocos2d::__String::createWithFormat(dic->valueForKey("AniFormat")->getCString(), _name.c_str(), str, i)->getCString()));

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

void GameObject::DieAni(const char * str, cocos2d::__Dictionary* dic)
{
	auto cache = SpriteFrameCache::sharedSpriteFrameCache();
	auto ani = Animation::create();
	int frame = dic->valueForKey("Frame")->intValue();
	ani->setDelayPerUnit(dic->valueForKey("AniDelay")->floatValue());
	for (int i = 1; i <= frame; i++) ani->addSpriteFrame(cache->spriteFrameByName(cocos2d::__String::createWithFormat(dic->valueForKey("AniFormat")->getCString(), _name.c_str(), str, i)->getCString()));

	this->runAction(Sequence::create(Repeat::create(Animate::create(ani), dic->valueForKey("RepeatCount")->intValue())
		, NULL));
}

bool GameObject::IsDamaged() const
{
	return _damagedState;
}

bool GameObject::IsAlive() const
{
	return _alive;
}
void GameObject::update(float dt)
{
}

void GameObject::Damaged(int i)
{
	if (IsAlive())
	{
		if (!IsDamaged())
		{
			_damagedState = true;
			this->getPhysicsBody()->setEnable(false);
			//Animate
			auto color = this->getColor();
			this->runAction(Sequence::create(TintTo::create(0.1f, 255, 0, 0)
				, Blink::create(0.2f, 2)
				, TintTo::create(0.1f, color)
				, CallFunc::create(std::bind(&GameObject::SetBodyEnable, this, true))
				, CallFunc::create(std::bind(&GameObject::setDamagedState, this, false))
				, NULL));

			DecreaseCurrentHp(i);
		}
	}
}

cocos2d::__Dictionary* GameObject::GetAniInfo()
{
	auto data = __Dictionary::createWithContentsOfFile(String::createWithFormat("%s/%s/%sAni.plist", _type.c_str(), _name.c_str(), _name.c_str())->getCString());
	return data;
}
