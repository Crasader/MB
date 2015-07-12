#include"ShooterSlime.h"
#include "Definitions.h"
USING_NS_CC;

ShooterSlime::ShooterSlime()
{
	Init();
}
void ShooterSlime::Init()
{
	_name = "ShooterSlime";
	_type = "Monster";
	attackTime = 3.0f;
}
ShooterSlime* ShooterSlime::create()
{
	auto pSprite = new ShooterSlime();
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

void ShooterSlime::MoodAttack(float dt)
{
	if (timer == kTimerUp)
	{
		timer = AttackTime();
		Animate("Attack", myEnum::kAction::kActionAttack);
		// fire a ball
		auto sp = this->getPosition();
		sp.y -= this->getContentSize().height;
		auto dp = Vec2(sp.x - CCRANDOM_MINUS1_1(), sp.y - 1);

		Fire(layer, sp, dp);
		Fire(layer, sp, dp);
		Fire(layer, sp, dp);
	}
	else if (timer <= 0.0f)
	{
		ChooseMood();
	}
}


