#include "HMRifleMan.h"

USING_NS_CC;
using namespace ui;

HMRifleMan::HMRifleMan(cocos2d::Layer * layer, Hero * hero, bool cageIn) : HelperMan(layer, hero, cageIn)
{
	_name = "RifleMan";
	_tag = myEnum::kHelperMan::kHMRifleMan;
	kTimer = kTimeUp;
	_attackPoint = hero->getAttackPoint() / 2;
	if (_attackPoint <= 0) _attackPoint = 1;
	monsterManager = (MonsterManager *)layer->getChildByName("MonsterManager");
	effectManager = (EffectManager *)layer->getChildByName("EffectManager");
	setTime = 5.0f;
}

HMRifleMan::~HMRifleMan()
{

}

HMRifleMan* HMRifleMan::create(cocos2d::Layer * layer, Hero * hero, bool cageIn)
{
	auto pNode = new HMRifleMan(layer, hero, cageIn);
	pNode->autorelease();
	pNode->InitSprite();
	return pNode;
}

void HMRifleMan::update(float dt)
{
	if (kTimer == kTimeUp)
	{
		kTimer = setTime;
	}
	else
	{
		kTimer -= dt;

		if (kTimer <= 0.0f)
		{
			AIDoingBattle();
			kTimer = kTimeUp;
		}
	}
	
}
void HMRifleMan::AIDoingBattle()
{


	int size = monsterManager->monsters.size();
	for (int i = 0; i < size; i++)
	{
		auto obj = monsterManager->monsters.at(i);
		if (!obj->IsAlive()) continue;
		else
		{
			// fire sound
			SoundManager::getInstance()->playMySoundLogic("FireBall");
			Swing();
			effectManager->HitEffect(obj->getPosition());
			obj->Damaged(this->_attackPoint);
			break;
		}
	}

}