#include"Gremlin.h"
USING_NS_CC;

Gremlin::Gremlin()
{
	_name = "Gremlin";
	_type = "Monster";
	stayTime = 1.0f;
	attackTime = 1.75f;
	moveTime = 2.0f;
}
Gremlin* Gremlin::create()
{
	auto pSprite = new Gremlin();
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

void Gremlin::MoodAttack(float dt)
{
	if (timer == kTimerUp)
	{
		timer = AttackTime();
		Animate("Attack", myEnum::kAction::kActionAttack);
		// fire a ball
		auto sp = this->getPosition();
		sp.y -= this->getContentSize().height;
//		auto dp1 = Vec2(sp.x - CCRANDOM_MINUS1_1(), sp.y - 1);
//		auto dp2 = Vec2(sp.x - CCRANDOM_MINUS1_1(), sp.y - 1);

		auto dp1 = Vec2(sp.x - 2, sp.y - 1);
		auto dp2 = Vec2(sp.x - 1, sp.y - 1);
		auto dp3 = Vec2(sp.x, sp.y - 1);
		auto dp4 = Vec2(sp.x + 1, sp.y - 1);
		auto dp5 = Vec2(sp.x + 2, sp.y - 1);

		Fire(layer, sp, dp1);
		Fire(layer, sp, dp2);
		Fire(layer, sp, dp3);
		Fire(layer, sp, dp4);
		Fire(layer, sp, dp5);
	}
	else if (timer <= 0.0f)
	{
		ChooseMood();
	}
}

void Gremlin::MoodMove(float dt)
{
	if (timer == kTimerUp)
	{
		timer = MoveTime();
		BaseMoveMent(dt);

	}
	else if (timer <= 0.0f)
	{
		ChooseMood();
	}
}


void Gremlin::MoodStay(float dt)
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

void Gremlin::InitSprite()
{
	auto body = PhysicsBody::createCircle(this->getContentSize().width / 3, PhysicsMaterial(100, 1, 1));
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