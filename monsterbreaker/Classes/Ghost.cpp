#include"Ghost.h"
#include "Definitions.h"
USING_NS_CC;

Ghost::Ghost()
{
	Init();
}
void Ghost::Init()
{
	_name = "Ghost";
	_type = "Monster";
//	sleepState = true;
}
Ghost* Ghost::create()
{
	auto pSprite = new Ghost();
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

void Ghost::InitSprite()
{
	//	MyBodyParser::getInstance()->parseJsonFile(String::createWithFormat("%s/%s/%s.json", _type.c_str(), _name.c_str(), _name.c_str())->getCString());
	//	auto body = MyBodyParser::getInstance()->bodyFormJson(this, String::createWithFormat("%s.png", _name.c_str())->getCString(), PhysicsMaterial(100, 1, 1));
	//	if (body != nullptr)
	//	{
	auto body = PhysicsBody::createCircle(this->getContentSize().width / 2, PhysicsMaterial(100, 1, 1));
	body->setDynamic(true);
	body->setRotationEnable(false);
	body->setCollisionBitmask(MONSTER_BODY_COLLISION_BITMASK);
	body->setContactTestBitmask(true);
	this->setPhysicsBody(body);
	//	}
	this->setUserData(this);
	//	this->Animate("Stay", myEnum::kAction::kActionStay);
	//	MyBodyParser::getInstance()->freeInstance();

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


void Ghost::Damaged(int i)
{
//	stopAllActions();
	this->setOpacity(255);
	Monster::Damaged(i);
	if (IsAlive())
	{
		SetMood(myEnum::kMoods::kMoodHide);
	}

}

void Ghost::ChooseMood()
{
	if (IsAlive())
	{
		float r = CCRANDOM_0_1();
		if (r < 0.3f)
		{
			SetMood(myEnum::kMoods::kMoodStay);
		}
		else if (r > 0.7f)
		{
			SetMood(myEnum::kMoods::kMoodAttack);
		}
		else
		{
			SetMood(myEnum::kMoods::kMoodHide);
		}
	}

}

void Ghost::update(float dt)
{
	if (IsAlive())
	{
		if (timer != kTimerUp)
			timer -= dt;

		switch (mood)
		{
		case myEnum::kMoods::kMoodStay: MoodStay(dt); break;
		case myEnum::kMoods::kMoodAttack: MoodAttack(dt); break;
		case myEnum::kMoods::kMoodHide: MoodHide(dt); break;
		}
	}
}

void Ghost::MoodHide(float dt)
{
	if (timer == kTimerUp)
	{
		timer = 2.0f;
		Animate("Attack", myEnum::kAction::kActionAttack);

		// TODO
		//		timer = MoveTime() + MoveTime() * CCRANDOM_0_1();
		//		Animate("Fly", myEnum::kAction::kActionMove);
		//auto visibleSize = Director::getInstance()->getVisibleSize();
		//auto sp = Vec2(visibleSize.width / 10, visibleSize.height / 25 * 10);
		//auto x = visibleSize.width / 10 * 8;
		//auto y = visibleSize.height / 25 * 9;
		//auto dp = Vec2(sp.x + x*CCRANDOM_0_1(), sp.y + y*CCRANDOM_0_1());

		auto gapX = visibleSize.width * 0.1f;
		auto gapY = visibleSize.width * 0.04f;

		auto sp = Vec2(gapX * 0.5f, visibleSize.height - gapY * 0.5f - gapY * 10);

		auto mm = (MonsterManager*)layer->getChildByName("MonsterManager");
		int size = mm->tp.size();
		int r = 0;
		int x = 0;
		int y = 0;
		Vec2 dp = getPosition();
		if (size != 0)
		{
			r = rand() % size;
			auto p = mm->tp.at(r);
			x = p.x;
			y = p.y;
			dp = Vec2(sp.x + gapX * x, sp.y - gapY * y);
		}



		auto seq = Sequence::create(CallFunc::create(std::bind(&Ghost::fadeOut, this))
			, DelayTime::create(1.0f)
			, CallFunc::create(std::bind(&Ghost::moveTo, this, dp))
			, CallFunc::create(std::bind(&Ghost::fadeIn, this))
			, NULL);
		
		this->runAction(seq);


	}

	else if (timer <= 0.0f)
	{
		ChooseMood();
	}
	
}

void Ghost::moveTo(cocos2d::Vec2 vec)
{
	this->setPosition(vec);
}
void Ghost::fadeOut()
{
	auto act = FadeOut::create(1.0f);
	this->getPhysicsBody()->setEnable(false);
	this->runAction(act);
}
void Ghost::fadeIn()
{
	auto act = FadeIn::create(1.0f);
	this->getPhysicsBody()->setEnable(true);
	this->runAction(act);
}


void Ghost::MoodStay(float dt)
{
	if (timer == kTimerUp)
	{
		timer = StayTime() + StayTime() * CCRANDOM_0_1();
		Animate("Stay", myEnum::kAction::kActionStay);
	}

	else if (timer <= 0.0f)
	{
		ChooseMood();
	}

}
//
//void Ghost::MoodMove(float dt)
//{
//	if (timer == kTimerUp)
//	{
//		timer = MoveTime() + MoveTime() * CCRANDOM_0_1();
//		Animate("Fly", myEnum::kAction::kActionMove);
//		auto visibleSize = Director::getInstance()->getVisibleSize();
//		auto sp = Vec2(visibleSize.width / 10, visibleSize.height / 25 * 10);
//		auto x = visibleSize.width / 10 * 8;
//		auto y = visibleSize.height / 25 * 9;
//		auto dp = Vec2(sp.x + x*CCRANDOM_0_1(), sp.y + y*CCRANDOM_0_1());
//		this->runAction(MoveTo::create(timer, dp));
//	}
//	else if (timer <= 0.0f)
//	{
//		ChooseMood();
//	}
//}

void Ghost::MoodAttack(float dt)
{
	if (timer == kTimerUp)
	{
		timer = AttackTime() + AttackTime() * CCRANDOM_0_1();
		Animate("Attack", myEnum::kAction::kActionAttack);
		// fire a ball
		auto sp = this->getPosition();
		sp.y -= this->getContentSize().height;
		//auto destPoint = Vec2(0, Director::getInstance()->getVisibleSize().width * CCRANDOM_0_1());
		auto dp1 = Vec2(sp.x - 1 * CCRANDOM_MINUS1_1(), sp.y - 1);

		Fire(layer, sp, dp1);
	}
	else if (timer <= 0.0f)
	{
		ChooseMood();
	}
}

void Ghost::StartAnimation()
{
	//this->setColor(cocos2d::Color3B(255, 0, 0));
	this->Animate("Stay", myEnum::kAction::kActionStay);
}


void Ghost::Ani(const char * str, cocos2d::__Dictionary* dic)
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
			, CallFunc::create(std::bind(&Ghost::Animate, this, "Stay", myEnum::kAction::kActionStay))
			, NULL));
	}
}