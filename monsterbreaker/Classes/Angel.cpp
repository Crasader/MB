#include"Angel.h"
USING_NS_CC;

Angel::Angel(cocos2d::Layer * layer) : layer(layer)
{
	_name = "Angel";
	_type = "Monster";
	_bossName = "Angel";
	stayTime = 2.1f;
	attackTime = 3.0f;
	skillTime = 5.0f;
	moveTime = 2.0f;
	usingSkill = false;
	isFury = false;
}
Angel* Angel::create(cocos2d::Layer * layer)
{
	auto pSprite = new Angel(layer);
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

void Angel::InitSprite()
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

	lightning= CSLoader::createNode("Effect/Lightning/Lightning.csb");
	lightning->setPosition(this->getContentSize().width * 0.5f, this->getContentSize().height * 0.5f);
	this->addChild(lightning,-1);
	lightning->setVisible(false);

	fury = CSLoader::createNode("Effect/Rage/Rage.csb");
	fury->setPosition(this->getContentSize().width * 0.5f, this->getContentSize().height * 0.5f);
	this->addChild(fury);
	fury->setVisible(false);
}


void Angel::ChooseMood()
{
	if (IsAlive())
	{
		float r = CCRANDOM_0_1();
		CCLOG("r :: %f", r);
		if (!isFury)
		{
			if (r < 0.25f)
				SetMood(myEnum::kMoods::kMoodStay);
			else if (r < 0.5f)
				SetMood(myEnum::kMoods::kMoodAttack);
			else if (r < 0.8f)
				SetMood(myEnum::kMoods::kMoodSkill);
			else
				SetMood(myEnum::kMoods::kMoodMove);
		}
		else
		{
			if (r < 0.15f)
				SetMood(myEnum::kMoods::kMoodStay);
			else if (r < 0.45f)
				SetMood(myEnum::kMoods::kMoodAttack);
			else if (r < 0.80f)
				SetMood(myEnum::kMoods::kMoodSkill);
			else
				SetMood(myEnum::kMoods::kMoodMove);
		}
	}
}

void Angel::update(float dt)
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
			}
		}

		if (timer != kTimerUp)
			timer -= dt;

		switch (mood)
		{
		case myEnum::kMoods::kMoodStay: MoodStay(dt); break;
		case myEnum::kMoods::kMoodAttack: MoodAttack(dt); break;
		case myEnum::kMoods::kMoodSkill: MoodSkill(dt); break;
		case myEnum::kMoods::kMoodMove: MoodMove(dt); break;
		}
	}
}
void Angel::Die()
{
	GameObject::Die();
	fury->runAction(FadeOut::create(1.0f));

}
void Angel::MoodMove(float dt)
{
	if (timer == kTimerUp)
	{
		CCLOG("Move");
		timer = MoveTime();
		dir = rand() % 2;
		cocos2d::MoveBy * move;
		switch (dir)
		{
		case myEnum::kDir::kDirEast:
			move = MoveBy::create(2.0f, Vec2(this->getContentSize().width, 0));
			break;
		case myEnum::kDir::kDirWest:
			move = MoveBy::create(2.0f, Vec2(-this->getContentSize().width, 0));
			break;
		}
		this->runAction(move);
	}
	else if (timer <= 0.0f)
	{
		ChooseMood();
	}
}

void Angel::MoodStay(float dt)
{
	if (timer == kTimerUp)
	{
		CCLOG("stay");
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

void Angel::MoodAttack(float dt)
{
	if (timer == kTimerUp)
	{
		CCLOG("attack");
		if (!isFury)
			timer = AttackTime();
		else
			timer = AttackTime() * 0.5f;

		if (getBallCurrentCount() <= getBallCount())
		{
			// fire a ball
			auto sp = Vec2(Director::getInstance()->getVisibleSize().width*0.5f, this->getPositionY());
			sp.y -= this->getContentSize().height;
			auto dp1 = Vec2(sp.x - 2, sp.y - 1);
			auto dp2 = Vec2(sp.x - 1, sp.y - 1);
			auto dp3 = Vec2(sp.x, sp.y - 1);
			auto dp4 = Vec2(sp.x + 1, sp.y - 1);
			auto dp5 = Vec2(sp.x + 2, sp.y - 1);

			auto visibleSize = Director::getInstance()->getVisibleSize();
			auto seq = Sequence::create(
				MoveTo::create(0.5f, Vec2(visibleSize.width*0.5f, this->getPositionY()))
				, CallFunc::create(std::bind(&Angel::SeqFire, this, sp, dp3))
				, DelayTime::create(0.25f)
				, CallFunc::create(std::bind(&Angel::SeqFire, this, sp, dp2))
				, DelayTime::create(0.25f)
				, CallFunc::create(std::bind(&Angel::SeqFire, this, sp, dp4))
				, DelayTime::create(0.25f)
				, CallFunc::create(std::bind(&Angel::SeqFire, this, sp, dp1))
				, DelayTime::create(0.25f)
				, CallFunc::create(std::bind(&Angel::SeqFire, this, sp, dp5))
				, NULL);
			this->runAction(seq);
		}
	}
	else if (timer <= 0.0f)
	{
		ChooseMood();
	}
}

void Angel::MoodSkill(float dt)
{
	if (timer == kTimerUp)
	{
		timer = skillTime;
		// Todo
		lightning->setVisible(true);
		auto act = CSLoader::createTimeline("Effect/Lightning/Lightning.csb");
		act->gotoFrameAndPlay(0, 60, false);
		lightning->runAction(act);
		lightning->runAction(
			Sequence::create(
			DelayTime::create(1.0f)
			, CallFunc::create(std::bind(&Angel::Lightning, this))
			, CallFunc::create(std::bind(&Angel::setVisibleLightning, this, false))
//			, DelayTime::create(1.0f)
			, NULL));
	}
	else if (timer <= 0.0f)
	{
		ChooseMood();
	}
}

void Angel::Lightning()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto hero = layer->getChildByName("Hero");

	auto spX = visibleSize.width * 0.1f;
	auto gapX = visibleSize.width * 0.8f / 3;

	int r1 = 0;
	int r2 = 0;
	r1 = rand() % 3;
	while (true){
		r2 = rand() % 3;
		if (r1 != r2) break;
	}


	auto sp1 = Vec2(spX + r1 * gapX + gapX * 0.5f, hero->getPositionY());
	auto sp2 = Vec2(spX + r2 * gapX + gapX * 0.5f, hero->getPositionY());

	if (!isFury)
	{
		createLightning(sp1);
	}
	else
	{
		//auto seq = Sequence::create(CallFunc::create(std::bind(&Angel::createLightning, this, sp1))
		//	, DelayTime::create(1.5f)
		//	, CallFunc::create(std::bind(&Angel::createLightning, this, sp2))
		//	, NULL);
		//this->runAction(seq);
		createLightning(sp1);
		createLightning(sp2);
	}

}

void Angel::createLightning(cocos2d::Vec2 p)
{	
	//auto l = Lightning::create(layer, 1);
	//p.x += l->getContentSize().width * 0.5f;
	//l->setPosition(p);
	//layer->addChild(l, ZINDEX_EFFECT_FRONT);

	auto effectManager = (EffectManager *)layer->getChildByName("EffectManager");
	effectManager->LightningEffect(p, 1);
}

void Angel::setVisibleLightning(bool b)
{
	lightning->setVisible(b);
}

void Angel::StartAnimation()
{
	this->Animate("Stay", myEnum::kAction::kActionStay);

}

void Angel::SeqFire(cocos2d::Vec2 sp, cocos2d::Vec2 dp)
{
	Fire(layer, sp, dp);
}



