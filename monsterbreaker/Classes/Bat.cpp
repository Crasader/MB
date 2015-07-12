#include"Bat.h"
//#include "MyBodyParser.h"
#include "Definitions.h"
USING_NS_CC;

Bat::Bat()
{
	Init();
}
void Bat::Init()
{
	_name = "Bat";
	_type = "Monster";
	sleepState = true;
	attackTime = 3.0f;
	stayTime = 2.0f;
	moveTime = 1.5f;
}
Bat* Bat::create()
{
	auto pSprite = new Bat();
	pSprite->SetMonsterData();

	auto cache = SpriteFrameCache::sharedSpriteFrameCache();
	cache->addSpriteFramesWithFile(
		String::createWithFormat("%s/%s/%sImage.plist", pSprite->getType().c_str(), pSprite->getName().c_str(), pSprite->getName().c_str())->getCString(),
		String::createWithFormat("%s/%s/%s.png", pSprite->getType().c_str(), pSprite->getName().c_str(), pSprite->getName().c_str())->getCString()
		);
	if (pSprite->initWithSpriteFrameName(String::createWithFormat("%s.png", pSprite->getName().c_str())->getCString()))
	{
		pSprite->autorelease();
		pSprite->InitSprite();

		return pSprite;
	}
	CC_SAFE_DELETE(pSprite);
	return NULL;
	
}

void Bat::InitSprite()
{
	auto body = PhysicsBody::createCircle(this->getContentSize().width / 2, PhysicsMaterial(100, 1, 1));
	body->setDynamic(true);
	body->setRotationEnable(false);
	body->setCollisionBitmask(MONSTER_BODY_COLLISION_BITMASK);
	body->setContactTestBitmask(true);
	this->setPhysicsBody(body);

	this->setUserData(this);

	hpBgSpr = Sprite::create("Monster/hpBg.png");
	this->addChild(hpBgSpr, ZINDEX_MONSTER_HP);
	hpCurrentSpr = Sprite::create("Monster/hpCurrent.png");
	this->addChild(hpCurrentSpr, ZINDEX_MONSTER_HP);
	auto origin = Director::getInstance()->getVisibleOrigin();
	hpBgSpr->setPosition(Vec2(this->getContentSize().width / 2, this->getPosition().y + this->getContentSize().height + hpBgSpr->getContentSize().height / 2));
	hpCurrentSpr->setPosition(hpBgSpr->getPosition());
	hpBgSpr->setOpacity(0);
	hpCurrentSpr->setOpacity(0);

}


void Bat::Damaged(int i)
{
	Monster::Damaged(i);
	if (IsAlive())
	{
		if (sleepState == true)
		{
			sleepState = false;
			Animate("Awake", myEnum::kAction::kActionAwake);
		}
	}

}

void Bat::ChooseMood()
{
	if (IsAlive())
	{
		if (sleepState == true)
		{
			SetMood(myEnum::kMoods::kMoodSleep);
		}
		else
		{
			float r = CCRANDOM_0_1();
			if (r < 0.2f)
			{
				SetMood(myEnum::kMoods::kMoodStay);
			}
			else if (r > 0.5f)
			{
				SetMood(myEnum::kMoods::kMoodAttack);
			}
			else
			{
				SetMood(myEnum::kMoods::kMoodMove);
			}
		}
	}

}

void Bat::update(float dt)
{
	if (IsAlive())
	{
		if (timer != kTimerUp)
			timer -= dt;

		switch (mood)
		{
		case myEnum::kMoods::kMoodStay: MoodStay(dt); break;
		case myEnum::kMoods::kMoodMove: MoodMove(dt); break;
		case myEnum::kMoods::kMoodAttack: MoodAttack(dt); break;
		case myEnum::kMoods::kMoodSleep: MoodSleep(dt); break;
		}
	}
}

void Bat::MoodSleep(float dt)
{
	if (timer == kTimerUp)
	{
		timer = 2.25f;
		Animate("Sleep", myEnum::kAction::kActionSleep);
	}

	else if (timer <= 0.0f)
	{
		ChooseMood();
	}
	
}


void Bat::MoodStay(float dt)
{
	if (timer == kTimerUp)
	{
		timer = StayTime();
		Animate("Fly", myEnum::kAction::kActionStay);
	}

	else if (timer <= 0.0f)
	{
		ChooseMood();
	}

}

void Bat::MoodMove(float dt)
{
	if (timer == kTimerUp)
	{
		timer = MoveTime();
		Animate("Fly", myEnum::kAction::kActionMove);
		auto visibleSize = Director::getInstance()->getVisibleSize();
		auto sp = Vec2(visibleSize.width / 10, visibleSize.height / 25 * 10);
		auto x = visibleSize.width / 10 * 8;
		auto y = visibleSize.height / 25 * 9;
		auto dp = Vec2(sp.x + x*CCRANDOM_0_1(), sp.y + y*CCRANDOM_0_1());
		this->runAction(MoveTo::create(timer, dp));
	}
	else if (timer <= 0.0f)
	{
		ChooseMood();
	}
}

void Bat::MoodAttack(float dt)
{
	if (timer == kTimerUp)
	{
		timer = AttackTime();
		Animate("Attack", myEnum::kAction::kActionAttack);
		// fire a ball
		auto sp = this->getPosition();
		sp.y -= this->getContentSize().height;
		auto dp1 = Vec2(sp.x - 1, sp.y - 1);
		auto dp2 = Vec2(sp.x, sp.y - 1);
		auto dp3 = Vec2(sp.x + 1, sp.y - 1);

		Fire(layer, sp, dp1);
		Fire(layer, sp, dp2);
		Fire(layer, sp, dp3);
	}
	else if (timer <= 0.0f)
	{
		ChooseMood();
	}
}

void Bat::StartAnimation()
{
	this->Animate("Sleep", myEnum::kAction::kActionSleep);
}


void Bat::Ani(const char * str, cocos2d::__Dictionary* dic)
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
			, CallFunc::create(std::bind(&Bat::Animate, this, "Fly", myEnum::kAction::kActionStay))
			, NULL));
	}
}