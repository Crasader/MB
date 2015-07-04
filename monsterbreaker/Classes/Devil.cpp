#include"Devil.h"
USING_NS_CC;

Devil::Devil(cocos2d::Layer * layer) : layer(layer)
{
	_name = "Devil";
	_type = "Monster";
	_bossName = "Devil";
	stayTime = 3.00f;
	attackTime = 3.0f;
	moveTime = 0.0f;
	isFury = false;
}
Devil* Devil::create(cocos2d::Layer * layer)
{
	auto pSprite = new Devil(layer);
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
		//pSprite->scheduleUpdate();

//		pSprite->SetWeapon(pSprite->getWeaponName().c_str());

		return pSprite;
	}
	CC_SAFE_DELETE(pSprite);
	return NULL;
}

void Devil::MoodAttack(float dt)
{
	if (timer == kTimerUp)
	{
		if (!isFury)
			timer = AttackTime();
		else
			timer = AttackTime() * 2;

		if (getBallCurrentCount() <= getBallCount())
		{
			// fire a ball
			auto sp = this->getPosition();
			sp.y -= this->getContentSize().height;
			auto dp1 = Vec2(sp.x - CCRANDOM_MINUS1_1(), sp.y - 1);
			auto dp2 = Vec2(sp.x - CCRANDOM_MINUS1_1(), sp.y - 1);
			auto dp3 = Vec2(sp.x - CCRANDOM_MINUS1_1(), sp.y - 1);
			auto dp4 = Vec2(sp.x - CCRANDOM_MINUS1_1(), sp.y - 1);
			auto dp5 = Vec2(sp.x - CCRANDOM_MINUS1_1(), sp.y - 1);
			auto dp6 = Vec2(sp.x - CCRANDOM_MINUS1_1(), sp.y - 1);
			auto dp7 = Vec2(sp.x - CCRANDOM_MINUS1_1(), sp.y - 1);

			if (!isFury)
			{
				Fire(layer, sp, dp1);
				Fire(layer, sp, dp2);
			}
			else
			{
				auto seq = Sequence::create(CallFunc::create(std::bind(&Devil::SeqFire, this, sp, dp1))
					, DelayTime::create(1.0f)
					, CallFunc::create(std::bind(&Devil::SeqFire, this, sp, dp2))
					, DelayTime::create(1.0f)
					, CallFunc::create(std::bind(&Devil::SeqFire, this, sp, dp3))
					, DelayTime::create(1.0f)
					, CallFunc::create(std::bind(&Devil::SeqFire, this, sp, dp4))
					, DelayTime::create(1.0f)
					, CallFunc::create(std::bind(&Devil::SeqFire, this, sp, dp5))
					, DelayTime::create(1.0f)
					, CallFunc::create(std::bind(&Devil::SeqFire, this, sp, dp6))
					, NULL);
				this->runAction(seq);
			}
		}

	}
	else if (timer <= 0.0f)
	{
		ChooseMood();
	}
}
void Devil::SeqFire(cocos2d::Vec2 sp, cocos2d::Vec2 dp)
{
	Fire(layer, sp, dp);
}

void Devil::ChooseMood()
{
	float r = CCRANDOM_0_1();
	if (!isFury)
	{
		if (r < 0.5f)
			SetMood(myEnum::kMoods::kMoodAttack);
		else
			SetMood(myEnum::kMoods::kMoodStay);
	}
	else
	{
		if (r < 0.8f)
			SetMood(myEnum::kMoods::kMoodAttack);
		else
			SetMood(myEnum::kMoods::kMoodStay);
	}
}

void Devil::MoodStay(float dt)
{
	if (timer == kTimerUp)
	{
		if (!isFury)
			timer = StayTime();
		else
			timer = StayTime() * 2;

		Animate("Stay", myEnum::kAction::kActionStay);
	}
	else if (timer <= 0.0f)
	{
		ChooseMood();
	}
}
void Devil::update(float dt)
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
				d->setFury(true);
				SoundManager::getInstance()->playMySoundLogic("Fury");
			}
		}

		if (timer != kTimerUp)
			timer -= dt;

		switch (mood)
		{
		case myEnum::kMoods::kMoodStay: MoodStay(dt); break;
		case myEnum::kMoods::kMoodAttack: MoodAttack(dt); break;
		}
	}
}

void Devil::InitSprite()
{
	auto body = PhysicsBody::createBox(this->getContentSize(), PhysicsMaterial(100, 1, 1));
	body->setDynamic(true);
	body->setGravityEnable(false);
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

	fury = CSLoader::createNode("Effect/Rage/Rage.csb");
	fury->setPosition(this->getContentSize().width * 0.5f, this->getContentSize().height * 0.5f);
	this->addChild(fury);
	fury->setVisible(false);

	auto visibleSize = Director::getInstance()->getVisibleSize();
	d = Dragon::create(layer);
	d->setPosition(visibleSize.width*0.7f, visibleSize.height*0.7f);
	layer->addChild(d, ZINDEX_MONSTER_SPRITE);
	d->scheduleUpdate();

}

void Devil::Die()
{
	GameObject::Die();
	//	this->runAction(FadeOut::create(1.0f));
	fury->runAction(FadeOut::create(1.0f));
	d->Die();
}

void Devil::pause()
{
	Node::pause();
	d->pause();
}

void Devil::resume()
{
	Node::resume();
	d->resume();
}

