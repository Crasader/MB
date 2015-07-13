#include"Bomb.h"
#include "Definitions.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
using namespace ui;

Bomb::Bomb(cocos2d::Layer * layer, Hero * hero) : layer(layer), hero(hero)
{
	this->kTimer = hero->getBombCountTime();
	this->bombName = hero->getBombName().c_str();
	this->attackPoint = hero->getBombAttackPoint();
	this->range = hero->getBombRange();
	if (hero->HasItem(ITEM_REMOTE_BOMB))
		remoteTouch = true;
}

Bomb::~Bomb()
{

}

Bomb* Bomb::create(cocos2d::Layer * layer, Hero * hero)
{
	auto pNode = new Bomb(layer, hero);
	pNode->autorelease();
	pNode->InitSprite();
	return pNode;
}

void Bomb::InitSprite()
{
	bombNode = CSLoader::createNode(String::createWithFormat("Bomb/%s.csb", bombName.c_str())->getCString());

	auto act = CSLoader::createTimeline(String::createWithFormat("Bomb/%s.csb", bombName.c_str())->getCString());
	act->gotoFrameAndPlay(0, 30, true);
	bombNode->runAction(act);

	spr = (Sprite *)bombNode->getChildByName("spr");
	auto body = PhysicsBody::createBox(spr->getContentSize(), PhysicsMaterial(5.0f, 0.3f, 0));
	body->setCollisionBitmask(BOMB_BODY_COLLISION_BITMASK);
	body->setContactTestBitmask(true);
	this->setPhysicsBody(body);

	this->addChild(bombNode);

	if (remoteTouch)
	{
		btn = dynamic_cast<Button*>(bombNode->getChildByName("btn"));
		btn->setUserData(this);
		struct callBackFunctorBomb
		{
			void operator() (Ref* sender) const
			{
				static_cast<Bomb*>(static_cast<Node*>(sender)->getUserData())->BombBomb();
			}
		};
		Widget::ccWidgetClickCallback callBackBomb = callBackFunctorBomb();
		btn->addClickEventListener(callBackBomb);
	}

}

void Bomb::BombBomb()
{
	auto origin = Director::getInstance()->getVisibleOrigin();

	bombNode->stopAllActions();
	bombNode->setVisible(false);
	this->getPhysicsBody()->setEnable(false);

	auto exNode = CSLoader::createNode("Effect/Explore/Explore.csb");
	//exNode->setPosition(origin.x, origin.y);
	this->addChild(exNode);

	auto body = PhysicsBody::createCircle(spr->getContentSize().width);
	body->setDynamic(true);
	body->setContactTestBitmask(true);
	body->setCollisionBitmask(BOMB_RANGE_COLLISION_BITMASK);

	exNode->setPhysicsBody(body);
	body->getNode()->setUserData(this);

	auto act = CSLoader::createTimeline("Effect/Explore/Explore.csb");
	act->gotoFrameAndPlay(0, false);
	exNode->setScale(range);
	exNode->runAction(act);

	auto action = Sequence::create(
		DelayTime::create(0.25),
		CallFunc::create(std::bind(&Bomb::RemoveAll, this)),
		NULL);

	this->runAction(action);

	SoundManager::getInstance()->playMySoundLogic("Bomb");

}
void Bomb::RemoveAll()
{
	this->removeFromParentAndCleanup(true);
}

int Bomb::GetAttackPoint()
{
	return attackPoint;
}

void Bomb::update(float dt)
{
	if (remoteTouch == false)
	{
		if (kTimer != kTimerUp)
			kTimer -= dt;

		if (kTimer != kTimerUp && kTimer <= 0)
		{
			BombBomb();
			kTimer = kTimerUp;
		}
	}

}