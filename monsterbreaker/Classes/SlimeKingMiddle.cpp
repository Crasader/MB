#include"SlimeKingMiddle.h"
USING_NS_CC;

SlimeKingMiddle::SlimeKingMiddle()
{
	_name = "SlimeKingMiddle";
	_type = "Monster";
	stayTime = 1.0f;
	attackTime = 3.0f;
	moveTime = 2.0f;
}
SlimeKingMiddle* SlimeKingMiddle::create()
{
	auto pSprite = new SlimeKingMiddle();
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

void SlimeKingMiddle::MakeTheOtherSelf()
{
	auto s1 = Slime::create();
	auto s2 = Slime::create();
	auto monsterManager = static_cast<MonsterManager*>(layer->getChildByName("MonsterManager"));
	monsterManager->monsters.pushBack(s1);
	monsterManager->monsters.pushBack(s2);
	s1->setPosition(this->getPosition());
	s2->setPosition(this->getPosition());
	s1->Draw(layer);
	s2->Draw(layer);

	auto act = JumpBy::create(0.5f, Vec2(s1->getContentSize().width, 0), s1->getContentSize().height*0.5f, 1);
	s1->runAction(act->clone());
	s2->runAction(act->reverse());
	s1->scheduleUpdate();
	s1->StartAnimation();
	s2->scheduleUpdate();
	s2->StartAnimation();
}


void SlimeKingMiddle::MoodAttack(float dt)
{
	if (timer == kTimerUp)
	{
		timer = AttackTime();
		Animate("Stay", myEnum::kAction::kActionAttack);
		// fire a ball
		auto sp = this->getPosition();
		sp.y -= this->getContentSize().height;
		auto dp1 = Vec2(sp.x - CCRANDOM_MINUS1_1(), sp.y - 1);
		auto dp2 = Vec2(sp.x - CCRANDOM_MINUS1_1(), sp.y - 1);

		Fire(layer, sp, dp1);
		Fire(layer, sp, dp2);
	}
	else if (timer <= 0.0f)
	{
		ChooseMood();
	}
}

void SlimeKingMiddle::MoodMove(float dt)
{
	if (timer == kTimerUp)
	{
		timer = MoveTime();
		dir = rand() % 4;
		cocos2d::JumpBy * jump;
		switch (dir)
		{
		case myEnum::kDir::kDirEast:
			jump = JumpBy::create(0.5f, Vec2(50, 0), this->getContentSize().height*0.5f, 1);
			break;
		case myEnum::kDir::kDirWest:
			jump = JumpBy::create(0.5f, Vec2(-50, 0), this->getContentSize().height*0.5f, 1);
			break;
		case myEnum::kDir::kDirSouth:
			jump = JumpBy::create(0.5f, Vec2(0, -50), this->getContentSize().height*0.5f, 1);
			break;
		case myEnum::kDir::kDirNorth:
			jump = JumpBy::create(0.5f, Vec2(0, +50), this->getContentSize().height*0.5f, 1);
			break;
		}
		auto seq = Sequence::create(jump, jump->clone(), NULL);
		this->runAction(seq);
	}
	else if (timer <= 0.0f)
	{
		ChooseMood();
	}
}


void SlimeKingMiddle::MoodStay(float dt)
{
	if (timer == kTimerUp)
	{
		timer = StayTime();
		Animate("Stay", myEnum::kAction::kActionStay);
		this->runAction(JumpBy::create(1.0f, Vec2::ZERO, this->getContentSize().height*0.5f, 1));
	}

	else if (timer <= 0.0f)
	{
		ChooseMood();
	}

}

void SlimeKingMiddle::Die()
{
	GameObject::Die();
	this->runAction(FadeOut::create(1.0f));
	MakeTheOtherSelf();
	
}

void SlimeKingMiddle::InitSprite()
{
	//	MyBodyParser::getInstance()->parseJsonFile(String::createWithFormat("%s/%s/%s.json", _type.c_str(), _name.c_str(), _name.c_str())->getCString());
	//	auto body = MyBodyParser::getInstance()->bodyFormJson(this, String::createWithFormat("%s.png", _name.c_str())->getCString(), PhysicsMaterial(100, 1, 1));
	//	if (body != nullptr)
	//	{
	auto body = PhysicsBody::createCircle(this->getContentSize().width / 3, PhysicsMaterial(100, 1, 1));
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