#include"HalfShadow.h"
USING_NS_CC;

HalfShadow::HalfShadow(cocos2d::Layer * layer) : layer(layer)
{
	_name = "HalfShadow";
	_type = "Monster";
	stayTime = 1.0f;
	attackTime = 3.0f;
}
HalfShadow* HalfShadow::create(cocos2d::Layer * layer)
{
	auto pSprite = new HalfShadow(layer);
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

void HalfShadow::InitSprite()
{
	auto body = PhysicsBody::createCircle(this->getContentSize().width * 0.25, PhysicsMaterial(100, 1, 1));
	body->setDynamic(true);
	body->setRotationEnable(false);
	body->setCollisionBitmask(MONSTER_BODY_COLLISION_BITMASK);
	body->setContactTestBitmask(true);
	this->setPhysicsBody(body);
	//	}
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

	auto hero = (Hero*)layer->getChildByName("Hero");
	_ballName = hero->getBallName();
//	_ballSize = hero->getBallSize();
//	_ballVelocity = hero->getBallVelocity();

}


void HalfShadow::Damaged(int i)
{
	this->setOpacity(255);
	Monster::Damaged(i);
	if (IsAlive())
	{
		SetMood(myEnum::kMoods::kMoodHide);
	}
}

void HalfShadow::ChooseMood()
{
	if (IsAlive())
	{
		float r = CCRANDOM_0_1();

		if (r < 0.3f)
			SetMood(myEnum::kMoods::kMoodStay);
		else if (r < 0.5f)
			SetMood(myEnum::kMoods::kMoodAttack);
		else
			SetMood(myEnum::kMoods::kMoodHide);
	}
}

void HalfShadow::update(float dt)
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
void HalfShadow::Die()
{
//	GameObject::Die();
	stopAllActions();
	this->runAction(FadeOut::create(1.0f));
	this->pause();
	//CCLOG("DIE SHADOW");
}

void HalfShadow::MoodHide(float dt)
{
	if (timer == kTimerUp)
	{
		timer = 2.0f;

		auto visibleSize = Director::getInstance()->getVisibleSize();
		auto gapX = visibleSize.width * 0.1f;
		auto gapY = visibleSize.width * 0.04f;

		auto sp = Vec2(gapX * 0.5f, visibleSize.height - gapY * 0.5f - gapY * 10);
		int x = rand() % 6 + 2; // 2 to 7
		int y = rand() % 6 + 2; // 2 to 7
		auto dp = Vec2(sp.x + gapX * x, sp.y - gapY * y);
		
//		auto sp = Vec2(visibleSize.width / 10, visibleSize.height / 25 * 10);
//		auto x = visibleSize.width / 10 * 8;
//		auto y = visibleSize.height / 25 * 9;
//		auto dp = Vec2(sp.x + x*CCRANDOM_0_1(), sp.y + y*CCRANDOM_0_1());

		auto seq = Sequence::create(CallFunc::create(std::bind(&HalfShadow::fadeOut, this))
			, DelayTime::create(1.0f)
			, CallFunc::create(std::bind(&HalfShadow::moveTo, this, dp))
			, CallFunc::create(std::bind(&HalfShadow::fadeIn, this))
			, NULL);
		
		this->runAction(seq);
	}
	else if (timer <= 0.0f)
	{
		ChooseMood();
	}
	
}

void HalfShadow::moveTo(cocos2d::Vec2 vec)
{
	this->setPosition(vec);
}
void HalfShadow::fadeOut()
{
	auto act = FadeOut::create(0.5f);
	this->getPhysicsBody()->setEnable(false);
	this->runAction(act);
}
void HalfShadow::fadeIn()
{
	auto act = FadeIn::create(0.5f);
	this->getPhysicsBody()->setEnable(true);
	this->runAction(act);
}


void HalfShadow::MoodStay(float dt)
{
	if (timer == kTimerUp)
	{
		timer = StayTime();
		Animate("Stay", myEnum::kAction::kActionStay);
	}
	else if (timer <= 0.0f)
	{
		ChooseMood();
	}
}

void HalfShadow::MoodAttack(float dt)
{
	if (timer == kTimerUp)
	{
		timer = AttackTime();

		if (getBallCurrentCount() <= getBallCount())
		{
			// fire a ball
			auto sp = this->getPosition();
			sp.y -= this->getContentSize().height;
			auto dp1 = Vec2(sp.x - CCRANDOM_MINUS1_1(), sp.y - 1);
//			auto dp1 = Vec2(sp.x + 1, sp.y - 1);
			Fire(layer, sp, dp1);
		}
	}
	else if (timer <= 0.0f)
	{
		ChooseMood();
	}
}

void HalfShadow::StartAnimation()
{
	this->Animate("Stay", myEnum::kAction::kActionStay);
}



