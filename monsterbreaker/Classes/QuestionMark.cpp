#include"QuestionMark.h"
USING_NS_CC;

QuestionMark::QuestionMark()
{
	_name = "QuestionMark";
	_type = "Monster";
	stayTime = 1.25f;
//	attackTime = 0.5f;
//	moveTime = 1.05f;
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

//void QuestionMark::MoodAttack(float dt)
//{
//	if (timer == kTimerUp)
//	{
//		timer = AttackTime();
//		//Animate("Attack", myEnum::kAction::kActionAttack);
//		// fire a ball
//		auto sp = this->getPosition();
//		sp.y -= this->getContentSize().height;
//		auto dp1 = Vec2(sp.x - CCRANDOM_MINUS1_1(), sp.y - 1);
////		auto dp2 = Vec2(sp.x - CCRANDOM_MINUS1_1(), sp.y - 1);
////		auto dp3 = Vec2(sp.x - CCRANDOM_MINUS1_1(), sp.y - 1);
////		auto dp4 = Vec2(sp.x - CCRANDOM_MINUS1_1(), sp.y - 1);
//
//		Fire(layer, sp, dp1, true);
////		Fire(layer, sp, dp2, true);
////		Fire(layer, sp, dp3, true);
////		Fire(layer, sp, dp4, true);
//	}
//	else if (timer <= 0.0f)
//	{
//		ChooseMood();
//	}
//}

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


//void QuestionMark::MoodMove(float dt)
//{
//	if (timer == kTimerUp)
//	{
//		timer = MoveTime();
//		dir = rand() % 4;
//		cocos2d::MoveBy * move;
//		switch (dir)
//		{
//		case myEnum::kDir::kDirEast:
//			move = MoveBy::create(0.5f, Vec2(this->getContentSize().width * 0.5f, 0));
//			break;
//		case myEnum::kDir::kDirWest:
//			move = MoveBy::create(0.5f, Vec2(-this->getContentSize().width * 0.5f, 0));
//			break;
//		case myEnum::kDir::kDirSouth:
//			move = MoveBy::create(0.5f, Vec2(0, -this->getContentSize().height * 0.5f));
//			break;
//		case myEnum::kDir::kDirNorth:
//			move = MoveBy::create(0.5f, Vec2(0, this->getContentSize().height * 0.5f));
//			break;
//		}
//		auto seq = Sequence::create(move, move->clone(), NULL);
//		this->runAction(seq);
//	}
//	else if (timer <= 0.0f)
//	{
//		ChooseMood();
//	}
//}


//void QuestionMark::MoodStay(float dt)
//{
//	if (timer == kTimerUp)
//	{
//		timer = StayTime();
//		Animate("Stay", myEnum::kAction::kActionStay);
////		this->runAction(JumpBy::create(1.0f, Vec2::ZERO, this->getContentSize().height*0.5f, 1));
//	}
//
//	else if (timer <= 0.0f)
//	{
//		ChooseMood();
//	}
//
//}

//void QuestionMark::Damaged(int i)
//{
//	Monster::Damaged(i);
//	//if (IsAlive())
//	//{
//	//	SetMood(myEnum::kMoods::kMoodAttack);
//	//}
//
//}


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

//	this->setScale(2);
}