#include"Scavenger.h"
USING_NS_CC;

Scavenger::Scavenger()
{
	_name = "Scavenger";
	_type = "Monster";
	stayTime = 1.25f;
	attackTime = 0.5f;
	moveTime = 2.00f;
	timer2 = kTimerUp;
	dir = rand() % 4;
}
Scavenger* Scavenger::create()
{
	auto pSprite = new Scavenger();
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

void Scavenger::MoodAttack(float dt)
{
	auto sp = this->getPosition();
	sp.y -= this->getContentSize().height;
	auto dp1 = Vec2(sp.x - CCRANDOM_MINUS1_1(), sp.y - 1);

	Damaged(1);
	Fire(layer, sp, dp1, true);
}

void Scavenger::Die()
{
	Monster::Die();
	this->runAction(FadeOut::create(0.5f));
}

void Scavenger::MoodMove(float dt)
{
	if (timer == kTimerUp)
	{
		timer = MoveTime();
		dir++;
		if (dir >= 4) dir = 0;

		auto visibleSize = Director::getInstance()->getVisibleSize();
		auto gapX = visibleSize.width * 0.1f;
		auto gapY = visibleSize.width * 0.04f;

		auto sp = Vec2(gapX * 0.5f, visibleSize.height - gapY * 0.5f - gapY * 10);
		auto dp1 = Vec2(sp.x + gapX * 2, sp.y - gapY * 2); // left up
		auto dp2 = Vec2(sp.x + gapX * 2, sp.y - gapY * 7); // right up
		auto dp3 = Vec2(sp.x + gapX * 7, sp.y - gapY * 2); // left down
		auto dp4 = Vec2(sp.x + gapX * 7, sp.y - gapY * 7); // right down

		cocos2d::MoveTo * move;
		switch (dir)
		{
		case myEnum::kDir::kDirEast:
			move = MoveTo::create(moveTime, dp1);
			break;
		case myEnum::kDir::kDirWest:
			move = MoveTo::create(moveTime, dp2);
			break;
		case myEnum::kDir::kDirSouth:
			move = MoveTo::create(moveTime, dp3);
			break;
		case myEnum::kDir::kDirNorth:
			move = MoveTo::create(moveTime, dp4);
			break;
		}
		this->runAction(move);
	}
	else if (timer <= 0.0f)
	{
		ChooseMood();
	}
}

void Scavenger::update(float dt)
{
	if (IsAlive())
	{
		if (timer != kTimerUp)
			timer -= dt;

		switch (mood)
		{
		case myEnum::kMoods::kMoodMove: MoodMove(dt); break;
		case myEnum::kMoods::kMoodStay: MoodStay(dt); break;
		}

		if (timer2 == kTimerUp)
			timer2 = 2.0f;

		if (timer2 != kTimerUp)
			timer2 -= dt;

		if (timer2 <= 0)
		{
			MoodAttack(0);
			timer2 = kTimerUp;
		}
	}
}

void Scavenger::ChooseMood()
{
	if (IsAlive())
	{
		SetMood(myEnum::kMoods::kMoodMove);
	}
}

void Scavenger::InitSprite()
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

}

