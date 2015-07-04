#include "HMWarrior.h"

USING_NS_CC;
using namespace ui;

HMWarrior::HMWarrior(cocos2d::Layer * layer, Hero * hero, bool cageIn) : HelperMan(layer, hero, cageIn)
{
	_name = "Warrior";
	_tag = myEnum::kHelperMan::kHMWarrior;
}

HMWarrior::~HMWarrior()
{

}

HMWarrior* HMWarrior::create(cocos2d::Layer * layer, Hero * hero, bool cageIn)
{
	auto pNode = new HMWarrior(layer, hero, cageIn);
	pNode->autorelease();
	pNode->InitSprite();
	return pNode;
}

void HMWarrior::AIBeforeBattle()
{
	auto mm = (MonsterManager*)layer->getChildByName("MonsterManager");
	mm->CreateHeroBrick();
	SoundManager::getInstance()->playMySoundLogic("Skill");
}

