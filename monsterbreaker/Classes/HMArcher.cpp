#include"HMArcher.h"

USING_NS_CC;
using namespace ui;

HMArcher::HMArcher(cocos2d::Layer * layer, Hero * hero, bool cageIn) : HelperMan(layer, hero, cageIn)
{
	_name = "Archer";
	_tag = myEnum::kHelperMan::kHMArcher;
	_ballName = "White";
	_ballCount = 1;
	_ballSize = 1;
	if (hero->HasItem(ITEM_TRINITY)) _ballCount = 3;
	_attackPoint = hero->getAttackPoint() / 2;
	if (_attackPoint <= 0) _attackPoint = 1;
	monsterManager = (MonsterManager *) layer->getChildByName("MonsterManager");
}

HMArcher::~HMArcher()
{

}

HMArcher* HMArcher::create(cocos2d::Layer * layer, Hero * hero, bool cageIn)
{
	auto pNode = new HMArcher(layer, hero, cageIn);
	pNode->autorelease();
	pNode->InitSprite();
	return pNode;
}

void HMArcher::update(float dt)
{
	if (_ballCurrentCount <= 0)
		AIDoingBattle();
}
void HMArcher::AIDoingBattle()
{
	if (hero->IsAlive())
	{
		if (_ballCount > _ballCurrentCount)
		{
			//Fire()
			SoundManager::getInstance()->playMySoundLogic("Arrow");
			auto sp = Vec2(this->getPositionX(), this->getPositionY() + getContentSize().height*0.5f);
			auto dp = Vec2(sp + Vec2(CCRANDOM_MINUS1_1(), 1));

			int size = monsterManager->monsters.size();
			for (int i = 0; i < size; i++)
			{
				auto obj = monsterManager->monsters.at(i);
				if (!obj->IsAlive()) continue;
				else
				{
					dp = obj->getPosition();
					break;
				}
			}

			Fire(layer, sp, dp);
			if (hero->HasItem(ITEM_TRINITY))
			{
				Fire(layer, sp, dp);
				Fire(layer, sp, dp);
			}

			Swing();
		}
	}
}

