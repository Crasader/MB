#include"Guard.h"
USING_NS_CC;

Guard::Guard()
{
	_name = "Guard";
	_type = "Monster";
	stayTime = 3.00f;
	attackTime = 2.00f;
//	moveTime = 1.05f;
}
Guard* Guard::create()
{
	auto pSprite = new Guard();
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

void Guard::MoodAttack(float dt)
{
	if (timer == kTimerUp)
	{
		timer = AttackTime();
		//Animate("Attack", myEnum::kAction::kActionAttack);
		// fire a ball
		auto sp = this->getPosition();
		sp.y -= this->getContentSize().height;
		auto dp1 = Vec2(sp.x - CCRANDOM_MINUS1_1(), sp.y - 1);
//		auto dp2 = Vec2(sp.x - CCRANDOM_MINUS1_1(), sp.y - 1);
//		auto target = layer->getChildByName("Hero");
//		auto dp1 = target->getPosition();

		Fire(layer, sp, dp1);
	}
	else if (timer <= 0.0f)
	{
		ChooseMood();
	}
}

void Guard::Die()
{
	Monster::Die();
	this->runAction(FadeOut::create(0.5f));
}

void Guard::MoodStay(float dt)
{
	if (timer == kTimerUp)
	{
		timer = MoveTime();
	}
	else if (timer <= 0.0f)
	{
		ChooseMood();
	}
}


//void Guard::MoodStay(float dt)
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

void Guard::ChooseMood()
{
	if (IsAlive())
	{
		float r = CCRANDOM_0_1();
		if (r < 0.5f)
		{
			SetMood(myEnum::kMoods::kMoodAttack);
		}
		else
		{
			SetMood(myEnum::kMoods::kMoodStay);
		}
	}
}


void Guard::InitSprite()
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