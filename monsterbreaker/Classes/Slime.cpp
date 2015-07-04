#include"Slime.h"
#include "MyBodyParser.h"
USING_NS_CC;

Slime::Slime()
{
	Init();
}
void Slime::Init()
{
	_name = "Slime";
	_type = "Monster";
}
Slime* Slime::create()
{
	auto pSprite = new Slime();
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


