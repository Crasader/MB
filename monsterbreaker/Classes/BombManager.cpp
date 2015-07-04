#include "BombManager.h"
#include "Bomb.h"
USING_NS_CC;

BombManager::BombManager(cocos2d::Layer * layer, Hero * hero) : layer(layer), hero(hero)
{
	countTime = hero->getBombSetCountTime();
	kTimer = kTimerUp;
}
BombManager::~BombManager()
{

}

//void BombManager::InitBombManagerData(float countTime)
//{
//	this->countTime = countTime;
//	this->kTimer = kTimerUp;
//}
void BombManager::CanceledTimer()
{
	kTimer = kTimerUp;
}
bool BombManager::SetBomb(cocos2d::Vec2 vec)
{
	if (IsTimerUp())
	{
		auto bomb = Bomb::create(layer, hero);
		bomb->setPosition(vec);
//		bomb->SetBomb(layer, vec);
		layer->addChild(bomb, ZINDEX_HERO_BOMB);
		bombes.pushBack(bomb);
		kTimer = kTimerUp;
		return true;
	}
	kTimer = kTimerUp;
	return false;
}
bool BombManager::IsTimerUp()
{
	return (kTimer != kTimerUp && kTimer <= 0) ? true : false;
}
void BombManager::SetTimer()
{
	kTimer = countTime;
//	auto node = Node::create();
}

BombManager* BombManager::create(cocos2d::Layer * layer, Hero * hero)
{
	auto pNode = new BombManager(layer, hero);
	pNode->autorelease();
	return pNode;
}

void BombManager::update(float dt)
{
	if (kTimer != kTimerUp)
		kTimer -= dt;

	int size = bombes.size();
	for (int i = 0; i < size; i++)
	{
		bombes.at(i)->update(dt);
	}

}

