#include"ShooterBat.h"
#include "Definitions.h"
USING_NS_CC;

ShooterBat::ShooterBat()
{
	Init();
}
void ShooterBat::Init()
{
	_name = "ShooterBat";
	_type = "Monster";
	attackTime = 2.0f;
}
ShooterBat* ShooterBat::create()
{
	auto pSprite = new ShooterBat();
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

void ShooterBat::MoodAttack(float dt)
{
	if (timer == kTimerUp)
	{
		timer = AttackTime();
		Animate("Attack", myEnum::kAction::kActionAttack);
		// fire a ball
		auto sp = this->getPosition();
		sp.y -= this->getContentSize().height;
		auto dp1 = Vec2(sp.x - 2, sp.y - 1);
		auto dp2 = Vec2(sp.x - 1, sp.y - 1);
		auto dp3 = Vec2(sp.x, sp.y - 1);
		auto dp4 = Vec2(sp.x + 1, sp.y - 1);
		auto dp5 = Vec2(sp.x + 2, sp.y - 1);

		auto seq = Sequence::create(CallFunc::create(std::bind(&ShooterBat::SeqFire, this, sp, dp1))
			, DelayTime::create(0.5f)
			, CallFunc::create(std::bind(&ShooterBat::SeqFire, this, sp, dp2))
			, DelayTime::create(0.5f)
			, CallFunc::create(std::bind(&ShooterBat::SeqFire, this, sp, dp3))
			, DelayTime::create(0.5f)
			, CallFunc::create(std::bind(&ShooterBat::SeqFire, this, sp, dp4))
			, DelayTime::create(0.5f)
			, CallFunc::create(std::bind(&ShooterBat::SeqFire, this, sp, dp5))
			, NULL);
		this->runAction(seq);

//		Fire(layer, sp, dp1);
	}
	else if (timer <= 0.0f)
	{
		ChooseMood();
	}

}

void ShooterBat::SeqFire(cocos2d::Vec2 sp, cocos2d::Vec2 dp)
{
	Fire(layer, sp, dp);
}

