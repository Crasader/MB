#include"Me.h"
USING_NS_CC;

Me::Me(Hero * hero) : hero(hero)
{
	_name = "Me";
	_type = "Monster";
	_bossName = "Me";
	stayTime = 2.0f;
	attackTime = 1.0f;
	moveTime = 2.0f;
	skillTime = 5.0f;
	onceSkillUsed = false;
}
Me* Me::create(Hero * hero)
{
	auto pSprite = new Me(hero);
	pSprite->SetMonsterData();

	pSprite->setName(hero->getName());
	pSprite->setType(hero->getType());
	auto cache = SpriteFrameCache::sharedSpriteFrameCache();
	cache->addSpriteFramesWithFile(
		String::createWithFormat("%s/%s/%sImage.plist", pSprite->getType().c_str(), pSprite->getName().c_str(), pSprite->getName().c_str())->getCString(),
		String::createWithFormat("%s/%s/%s.png", pSprite->getType().c_str(), pSprite->getName().c_str(), pSprite->getName().c_str())->getCString()
		);
	if (pSprite->initWithSpriteFrameName(String::createWithFormat("%s.png", pSprite->getName().c_str())->getCString()))
	{
		pSprite->autorelease();
		pSprite->InitSprite();
		pSprite->setFlipY(true);
		pSprite->setBallName(hero->getBallName());
		pSprite->setBallSize(hero->getBallSize());
		pSprite->setWeapon();
		pSprite->setBombName(hero->getBombName().c_str());
		pSprite->isWarrior = (hero->getName().compare("Warrior") == 0) ? true : false;

		return pSprite;
	}
	CC_SAFE_DELETE(pSprite);
	return NULL;
}

void Me::MoodAttack(float dt)
{
	if (timer == kTimerUp)
	{
		timer = AttackTime();
		Animate("Attack", myEnum::kAction::kActionAttack);
		// fire a ball
		auto sp = this->getPosition();
		sp.y -= this->getContentSize().height;
		if (hero->HasItem(ITEM_TRINITY))
		{
			auto dp1 = Vec2(sp.x - 1, sp.y - 1);
			auto dp2 = Vec2(sp.x, sp.y - 1);
			auto dp3 = Vec2(sp.x + 1, sp.y - 1);

			Fire(layer, sp, dp1);
			Fire(layer, sp, dp2);
			Fire(layer, sp, dp3);
		}
		else
		{
			auto dp1 = Vec2(sp.x - CCRANDOM_MINUS1_1(), sp.y - 1);

			Fire(layer, sp, dp1);
		}
	}
	else if (timer <= 0.0f)
	{
		ChooseMood();
	}
}

void Me::update(float dt)
{
	if (IsAlive())
	{
		if (!onceSkillUsed)
		{
			if (getCurrentHp() <= getMaxHp() * 0.5f)
			{
				onceSkillUsed = true;
				weapon->Skill();
				createHealEffect(this->getPosition());
				this->runAction(Sequence::create(
					DelayTime::create(1.0f),
					CallFunc::create(std::bind(&Me::heal, this)),
					NULL));
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

void Me::Die()
{
	GameObject::Die();

}

void Me::ChooseMood()
{
	float r = CCRANDOM_0_1();
	if (r < 0.3f)
	{
		SetMood(myEnum::kMoods::kMoodAttack);
	}
	else if (r < 0.5f)
	{
		SetMood(myEnum::kMoods::kMoodSkill);	// Lightning
	}
	else
	{
		SetMood(myEnum::kMoods::kMoodMove);
	}
}
void Me::MoodMove(float dt)
{
	if (timer == kTimerUp)
	{
		timer = MoveTime();
		BaseMoveMent2(dt);
	}
	else if (timer <= 0.0f)
	{
		ChooseMood();
	}
}

void Me::MoodAttack2(float dt)
{
	if (timer == kTimerUp)
	{
		timer = skillTime;

	}
	else if (timer <= 0.0f)
	{
		ChooseMood();
	}
}
void Me::MoodSkill(float dt)
{
	if (timer == kTimerUp)
	{
		timer = skillTime;

		weapon->Skill();

		this->runAction(
			Sequence::create(
			DelayTime::create(1.0f)
			, CallFunc::create(std::bind(&Me::SkillUse, this))
			, NULL));
	}
	else if (timer <= 0.0f)
	{
		ChooseMood();
	}
}
void Me::SkillUse()
{
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

	createLightning(sp1);
	createLightning(sp2);

}

void Me::createLightning(cocos2d::Vec2 p)
{
	auto effectManager = (EffectManager *)layer->getChildByName("EffectManager");
	effectManager->LightningEffect(p, 1);
}

void Me::createHealEffect(cocos2d::Vec2 p)
{
	auto effectManager = (EffectManager *)layer->getChildByName("EffectManager");
	effectManager->HealEffect(p);
}
void Me::heal()
{
	setCurrentHp(getMaxHp());

}

void Me::InitSprite()
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

void Me::setWeapon()
{
	weapon = Weapon::create(layer, hero, hero->getWeaponType().c_str(), hero->getWeaponName().c_str(), false);
	auto _paddleSize = hero->getPaddleSize();
	paddle = Paddle::create(_paddleSize, weapon->getPaddleName().c_str());

	weapon->setPosition(getContentSize() *0.5f);
	paddle->setPosition(Vec2(getContentSize().width *0.5f, 0));

	weapon->Stay();
	weapon->setScaleY(weapon->getScale() * -1);
	paddle->setFlipY(true);
	paddle->getPhysicsBody()->setCollisionBitmask(SOLID_BRICK_COLLISION_BITMASK);

	this->addChild(weapon, -1);
	this->addChild(paddle);
}


void Me::Draw(cocos2d::Layer * layer)
{
	this->layer = layer;
	layer->addChild(this, ZINDEX_MONSTER_SPRITE, "Montser");
}
