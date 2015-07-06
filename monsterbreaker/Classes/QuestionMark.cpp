#include"QuestionMark.h"
USING_NS_CC;

QuestionMark::QuestionMark()
{
	_name = "QuestionMark";
	_type = "Monster";
	stayTime = 1.25f;
	timer2 = kTimerUp;
}
QuestionMark* QuestionMark::create()
{
	auto pSprite = new QuestionMark();
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

void QuestionMark::Die()
{
	Monster::Die();
	this->runAction(FadeOut::create(0.5f));
}

void QuestionMark::update(float dt)
{
	if (IsAlive())
	{
		if (timer != kTimerUp)
			timer -= dt;

		switch (mood)
		{
		case myEnum::kMoods::kMoodStay: MoodStay(dt); break;
		}

		if (timer2 == kTimerUp)
			timer2 = 5.0f;

		if (timer2 != kTimerUp)
			timer2 -= dt;

		if (timer2 <= 0)
		{
			CreateRandomMonster();
			Damaged(100);
			timer2 = kTimerUp;
		}
	}
}

void QuestionMark::CreateRandomMonster()
{
	int r = rand() % MONSTER_SIZE_NUMBER + MONSTER_START_NUMBER;
	auto monsterManager = (MonsterManager*)layer->getChildByName("MonsterManager");
	auto m = monsterManager->CreateMonster(r);
	m->setPosition(this->getPosition());
	m->Draw(layer);
	m->StartAnimation();
	m->scheduleUpdate();
	monsterManager->monsters.pushBack(m);
}

void QuestionMark::ChooseMood()
{
	if (IsAlive())
	{
		SetMood(myEnum::kMoods::kMoodMove);
	}
}


void QuestionMark::InitSprite()
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