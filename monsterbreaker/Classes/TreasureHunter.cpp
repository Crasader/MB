#include"TreasureHunter.h"
USING_NS_CC;

TreasureHunter::TreasureHunter()
{
	_name = "TreasureHunter";
	_type = "Monster";
	attackTime = 5.0f;
	moveTime = 1.05f;
}
TreasureHunter* TreasureHunter::create()
{
	auto pSprite = new TreasureHunter();
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

void TreasureHunter::MoodAttack(float dt)
{
	if (timer == kTimerUp)
	{
		timer = AttackTime();
		// fire a ball
		auto sp = this->getPosition();
		sp.y -= this->getContentSize().height;
		auto dp1 = Vec2(sp.x - CCRANDOM_MINUS1_1(), sp.y - 1);

		Fire(layer, sp, dp1, true);
	}
	else if (timer <= 0.0f)
	{
		ChooseMood();
	}
}

void TreasureHunter::Die()
{
//	Monster::Die();
	
	for (int i = ITEM_DROP_START_NUM; i < ITEM_DROP_START_NUM + ITEM_DROP_SIZE; i++)
	{
		DropItem(i);
	}

	this->runAction(FadeOut::create(0.5f));
}

void TreasureHunter::Damaged(int i)
{
	Monster::Damaged(i);

}


void TreasureHunter::ChooseMood()
{
	if (IsAlive())
	{
		SetMood(myEnum::kMoods::kMoodAttack);
	}
}


void TreasureHunter::InitSprite()
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