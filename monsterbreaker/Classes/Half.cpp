#include"Half.h"
USING_NS_CC;

Half::Half(cocos2d::Layer * layer) : layer(layer)
{
	_name = "Half";
	_type = "Monster";
	_bossName = "Half";
	stayTime = 2.1f;
	attackTime = 3.0f;
	skillTime = 5.0f;
	usingSkill = false;
	isFury = false;
}
Half* Half::create(cocos2d::Layer * layer)
{
	auto pSprite = new Half(layer);
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

void Half::InitSprite()
{
	auto body = PhysicsBody::createCircle(this->getContentSize().width * 0.25, PhysicsMaterial(100, 1, 1));
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

	sword = Sword::create(layer);
	sword->setPosition(this->getContentSize().width * 0.33f, this->getContentSize().height * 0.33f);
	this->addChild(sword);

	fury = CSLoader::createNode("Effect/Rage/Rage.csb");
	fury->setPosition(this->getContentSize().width * 0.5f, this->getContentSize().height * 0.5f);
	this->addChild(fury);
	fury->setVisible(false);

	auto hero = (Hero*)layer->getChildByName("Hero");
	_ballName = hero->getBallName();
}


void Half::Damaged(int i)
{
	this->setOpacity(255);
	Monster::Damaged(i);
}

void Half::ChooseMood()
{
	if (IsAlive())
	{
		float r = CCRANDOM_0_1();

		if (!isFury)
		{
			if (r < 0.3f)
				SetMood(myEnum::kMoods::kMoodStay);
			else if (r < 0.5f)
				SetMood(myEnum::kMoods::kMoodAttack);
			else if (r < 0.7f)
				SetMood(myEnum::kMoods::kMoodAttack2);
			else
				SetMood(myEnum::kMoods::kMoodHide);
		}
		else
		{
			if (r < 0.2f)
				SetMood(myEnum::kMoods::kMoodStay);
			else if (r < 0.5f)
				SetMood(myEnum::kMoods::kMoodAttack);
			else if (r < 0.8f)
				SetMood(myEnum::kMoods::kMoodAttack2);
			else 
				SetMood(myEnum::kMoods::kMoodHide);
		}
	}

}

void Half::update(float dt)
{
	if (IsAlive())
	{
		if (isFury == false)
		{
			if (getMaxHp() * 0.5f > getCurrentHp())
			{
				isFury = true;
				fury->setVisible(true);
				auto act = CSLoader::createTimeline("Effect/Rage/Rage.csb");
				act->gotoFrameAndPlay(0, 60, true);
				fury->runAction(act);
				SetMood(myEnum::kMoods::kMoodSkill);
			}
		}

		if (timer != kTimerUp)
			timer -= dt;

		switch (mood)
		{
		case myEnum::kMoods::kMoodStay: MoodStay(dt); break;
		case myEnum::kMoods::kMoodAttack: MoodAttack(dt); break;
		case myEnum::kMoods::kMoodHide: MoodHide(dt); break;
		case myEnum::kMoods::kMoodSkill: MoodSkill(dt); break;
		case myEnum::kMoods::kMoodAttack2: MoodAttack2(dt); break;
		}
	}
}
void Half::Die()
{
	GameObject::Die();
	sword->FadeOut(1.0f);
	fury->runAction(FadeOut::create(1.0f));

	int size = shadows.size();
	for (int i = 0; i < size; i++)
	{
		auto obj = shadows.at(i);
		if (obj->IsAlive())
		{
			obj->stopAllActions();
			obj->pause();
			obj->Damaged(1000);
		}
	}
}

void Half::MoodHide(float dt)
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

		auto seq = Sequence::create(CallFunc::create(std::bind(&Half::fadeOut, this))
			, DelayTime::create(1.0f)
			, CallFunc::create(std::bind(&Half::moveTo, this, dp))
			, CallFunc::create(std::bind(&Half::fadeIn, this))
			, NULL);
		
		this->runAction(seq);

	}

	else if (timer <= 0.0f)
	{
		ChooseMood();
	}
	
}

void Half::moveTo(cocos2d::Vec2 vec)
{
	this->setPosition(vec);
}
void Half::fadeOut()
{
	auto act = FadeOut::create(0.5f);
	this->getPhysicsBody()->setEnable(false);
	this->runAction(act);
	sword->FadeOut(0.5f);
	fury->runAction(act->clone());
}
void Half::fadeIn()
{
	auto act = FadeIn::create(0.5f);
	this->getPhysicsBody()->setEnable(true);
	this->runAction(act);
	sword->FadeIn(0.5f);
	fury->runAction(act->clone());
}


void Half::MoodStay(float dt)
{
	if (timer == kTimerUp)
	{
		if (!isFury)
			timer = StayTime();
		else
			timer = StayTime() * 0.5f;

		Animate("Stay", myEnum::kAction::kActionStay);
	}
	else if (timer <= 0.0f)
	{
		ChooseMood();
	}
}

void Half::MoodAttack(float dt)
{
	if (timer == kTimerUp)
	{
		if (!isFury)
			timer = AttackTime();
		else
			timer = AttackTime() * 0.5f;

		if (getBallCurrentCount() <= getBallCount())
		{
			// swing
			sword->Swing();

			// fire a ball
			auto sp = this->getPosition();
			sp.y -= this->getContentSize().height;
			auto dp1 = Vec2(sp.x + 1, sp.y - 1);
			auto dp2 = Vec2(sp.x - 1, sp.y - 1);
			Fire(layer, sp, dp1);
			Fire(layer, sp, dp2);
		}
	}
	else if (timer <= 0.0f)
	{
		ChooseMood();
	}
}
void Half::MoodAttack2(float dt)
{
	if (timer == kTimerUp)
	{
		if (!isFury)
			timer = AttackTime() * 1.5f;
		else
			timer = AttackTime();

		if (getBallCurrentCount() <= getBallCount())
		{
			// fire a ball
			auto sp = this->getPosition();
			sp.y -= this->getContentSize().height;
			auto dp1 = Vec2(sp.x - 2, sp.y - 1);
			auto dp2 = Vec2(sp.x - 1, sp.y - 1);
			auto dp3 = Vec2(sp.x, sp.y - 1);
			auto dp4 = Vec2(sp.x + 1, sp.y - 1);
			auto dp5 = Vec2(sp.x + 2, sp.y - 1);

			auto seq = Sequence::create(CallFunc::create(std::bind(&Half::SeqFire, this, sp, dp3))
				, DelayTime::create(1.0f)
				, CallFunc::create(std::bind(&Half::SeqFire, this, sp, dp2))
				, DelayTime::create(1.0f)
				, CallFunc::create(std::bind(&Half::SeqFire, this, sp, dp4))
				, NULL);
			this->runAction(seq);
		}
	}
	else if (timer <= 0.0f)
	{
		ChooseMood();
	}

}
void Half::MoodSkill(float dt)
{
	if (timer == kTimerUp)
	{
		timer = skillTime;
		usingSkill = true;
		// swing
		sword->UseSkill();

		auto seq = Sequence::create(
			DelayTime::create(1.0f),
			CallFunc::create(std::bind(&Half::MakeShadow, this)),
			NULL);
		this->runAction(seq);

	}
	else if (timer <= 0.0f)
	{
		usingSkill = false;
		ChooseMood();
	}
}

void Half::MakeShadow()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto sp = Vec2(visibleSize.width / 10, visibleSize.height / 25 * 10);
	auto x = visibleSize.width / 10 * 8;
	auto y = visibleSize.height / 25 * 9;
	auto dp = Vec2(sp.x + x*CCRANDOM_0_1(), sp.y + y*CCRANDOM_0_1());

	auto h1 = HalfShadow::create(layer);
	h1->setPosition(dp);
	this->shadows.pushBack(h1);
	h1->Draw(layer);

	h1->StartAnimation();
	h1->scheduleUpdate();
}



void Half::StartAnimation()
{
	this->Animate("Stay", myEnum::kAction::kActionStay);
}

void Half::SeqFire(cocos2d::Vec2 sp, cocos2d::Vec2 dp)
{
	sword->Swing();
	Fire(layer, sp, dp);
}

void Half::pause()
{
	Node::pause();
	int size = shadows.size();
	for (int i = 0; i < size; i++)
		shadows.at(i)->pause();
}

void Half::resume()
{
	Node::resume();
	int size = shadows.size();
	for (int i = 0; i < size; i++)
		shadows.at(i)->resume();
}






