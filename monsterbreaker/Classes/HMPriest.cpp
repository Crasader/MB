#include"HMPriest.h"

USING_NS_CC;
using namespace ui;

HMPriest::HMPriest(cocos2d::Layer * layer, Hero * hero, bool cageIn) : HelperMan(layer, hero, cageIn)
{
	_name = "Priest";
	_tag = myEnum::kHelperMan::kHMPriest;
}

HMPriest::~HMPriest()
{

}

HMPriest* HMPriest::create(cocos2d::Layer * layer, Hero * hero, bool cageIn)
{
	auto pNode = new HMPriest(layer, hero, cageIn);
	pNode->autorelease();
	pNode->InitSprite();
	return pNode;
}

void HMPriest::AIAfterBattle()
{
	if (!hero->IsFullHp())
	{
		Swing();
		hero->IncreaseCurrentHp(1);	// only First Aid
		// effect & sound
		auto effectManager = static_cast<EffectManager*>(layer->getChildByName("EffectManager"));
		effectManager->HealEffect(hero->getPosition());
		SoundManager::getInstance()->playMySoundLogic("Skill");

	}
}

