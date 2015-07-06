#include"Wizard.h"
USING_NS_CC;

Wizard::Wizard()
{
	_name = "Wizard";
	_type = "Monster";
	stayTime = 3.00f;
	attackTime = 3.00f;
	moveTime = 1.05f;
}
Wizard* Wizard::create()
{
	auto pSprite = new Wizard();
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

void Wizard::MoodAttack(float dt)
{
	if (timer == kTimerUp)
	{
		timer = AttackTime();

		charge->stopAllActions();
		charge->setVisible(false);
		// fire a ball

		auto sp = this->getPosition();
		sp.y -= this->getContentSize().height;
		auto dp1 = Vec2(sp.x - 2, sp.y - 1);
		auto dp2 = Vec2(sp.x - 1, sp.y - 1);
		auto dp3 = Vec2(sp.x, sp.y - 1);
		auto dp4 = Vec2(sp.x + 1, sp.y - 1);
		auto dp5 = Vec2(sp.x + 2, sp.y - 1);

		auto visibleSize = Director::getInstance()->getVisibleSize();
		auto seq = Sequence::create(
			CallFunc::create(std::bind(&Wizard::SeqFire, this, sp, dp3))
			, DelayTime::create(1.0f)
			, CallFunc::create(std::bind(&Wizard::SeqFire, this, sp, dp2))
			, CallFunc::create(std::bind(&Wizard::SeqFire, this, sp, dp4))
			, DelayTime::create(1.0f)
			, CallFunc::create(std::bind(&Wizard::SeqFire, this, sp, dp1))
			, CallFunc::create(std::bind(&Wizard::SeqFire, this, sp, dp5))
			, NULL);
		this->runAction(seq);
	}
	else if (timer <= 0.0f)
	{
		SetMood(myEnum::kMoods::kMoodMove);
	}
}

void Wizard::SeqFire(cocos2d::Vec2 sp, cocos2d::Vec2 dp)
{
	Fire(layer, sp, dp);
}


void Wizard::Die()
{
	Monster::Die();
	this->runAction(FadeOut::create(0.5f));
	charge->stopAllActions();
	charge->runAction(FadeOut::create(0.5f));

}

void Wizard::MoodCharge(float dt)
{
	if (timer == kTimerUp)
	{
		timer = 5.0f;
		charge->setVisible(true);
		
		auto act = CSLoader::createTimeline("Effect/Charge/Charge.csb");
		act->gotoFrameAndPlay(0, 60, true);
		charge->runAction(act);
	}
	else if (timer <= 0.0f)
	{
		SetMood(myEnum::kMoods::kMoodCharge2);
	}
}

void Wizard::MoodCharge2(float dt)
{
	if (timer == kTimerUp)
	{
		timer = 2.0f;

		charge->stopAllActions();
		auto act = CSLoader::createTimeline("Effect/Charge/Charge.csb");
		act->gotoFrameAndPlay(61, 120, true);
		charge->runAction(act);
	}
	else if (timer <= 0.0f)
	{
		SetMood(myEnum::kMoods::kMoodAttack);
	}
}



void Wizard::MoodStay(float dt)
{
	if (timer == kTimerUp)
	{
		timer = StayTime();
	}

	else if (timer <= 0.0f)
	{
		ChooseMood();
	}

}

void Wizard::MoodMove(float dt)
{
	if (timer == kTimerUp)
	{
		timer = MoveTime();

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


		auto seq = Sequence::create(CallFunc::create(std::bind(&Wizard::fadeOut, this))
			, DelayTime::create(1.0f)
			, CallFunc::create(std::bind(&Wizard::moveTo, this, dp))
			, CallFunc::create(std::bind(&Wizard::fadeIn, this))
			, NULL);

		this->runAction(seq);
	}
	else if (timer <= 0.0f)
	{
		ChooseMood();
	}
}

void Wizard::moveTo(cocos2d::Vec2 vec)
{
	this->setPosition(vec);
}
void Wizard::fadeOut()
{
	auto act = FadeOut::create(0.2f);
	this->getPhysicsBody()->setEnable(false);
	this->runAction(act);
}
void Wizard::fadeIn()
{
	auto act = FadeIn::create(0.2f);
	this->getPhysicsBody()->setEnable(true);
	this->runAction(act);
}

void Wizard::update(float dt)
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
		case myEnum::kMoods::kMoodCharge1: MoodCharge(dt); break;
		case myEnum::kMoods::kMoodCharge2: MoodCharge2(dt); break;
		}
	}
}

void Wizard::ChooseMood()
{
	if (IsAlive())
	{
		float r = CCRANDOM_0_1();
		if (r < 0.7f)
		{
			SetMood(myEnum::kMoods::kMoodStay);
		}
		else
		{
			SetMood(myEnum::kMoods::kMoodCharge1);
		}
	}
}


void Wizard::InitSprite()
{
	auto body = PhysicsBody::createBox(this->getContentSize(), PhysicsMaterial(100, 1, 1));
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

	charge = CSLoader::createNode("Effect/Charge/Charge.csb");
	charge->setPosition(this->getContentSize().width * 0.5f, this->getContentSize().height * 0.5f);
	this->addChild(charge, -1);
	charge->setVisible(false);

}