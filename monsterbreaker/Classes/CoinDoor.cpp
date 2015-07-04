#include "CoinDoor.h"
USING_NS_CC;
using namespace ui;

CoinDoor::CoinDoor(const Room & rd, int kDir, Hero * hero, const char * mapType) : Door(rd, kDir, mapType)
{
	this->hero = hero;
}
CoinDoor* CoinDoor::create(const Room & rd, int kDir, Hero * hero, const char * mapType)
{
	auto pSprite = new CoinDoor(rd, kDir, hero, mapType);
	pSprite->autorelease();
	pSprite->InitSprite();
	return pSprite;
}

void CoinDoor::InitSprite()
{
	auto node = (CSLoader::createNode(String::createWithFormat("Door/%s/Door.csb", _mapType.c_str())->getCString()));
	node->setPosition(this->getContentSize().width / 2, this->getContentSize().height / 2);
	this->addChild(node);

	auto typeNode = CSLoader::createNode("Door/Coin.csb");
	typeNode->setPosition(this->getContentSize().width / 2, this->getContentSize().height / 2);
	this->addChild(typeNode);

	auto act = CSLoader::createTimeline(String::createWithFormat("Door/%s/Door.csb", _mapType.c_str())->getCString());
	act->gotoFrameAndPlay(0, 0, false);
	node->runAction(act);

	auto typeAct = CSLoader::createTimeline("Door/Coin.csb");
	typeAct->gotoFrameAndPlay(0, 0, false);
	typeNode->runAction(typeAct);

	btn = dynamic_cast<Button*>(node->getChildByName("btn"));
	btn->setUserData(this);
	//btn->setEnabled(false);
	//btn->addTouchEventListener(CC_CALLBACK_2(Door::onTouchDoor, this));

	auto body = PhysicsBody::createBox(btn->getContentSize());
	body->setCollisionBitmask(DOOR_COLLISION_BITMASK);
	body->setDynamic(false);
	node->setPhysicsBody(body);

	this->setVisible(_roomVisible);
}

void CoinDoor::Open()
{
	Door::Open();

	if (!_lock)
	{
		_isOpen = true;
		auto act = CSLoader::createTimeline("Door/Coin.csb");
		act->gotoFrameAndPlay(0, 60, false);
		this->runAction(act);
		// glow effect
		// open sound
	}
}
bool CoinDoor::ClickOpen()
{
	if (hero->getMoneyCount() > 0)
	{
		hero->DecreaseMoneyCount(1);
		_lock = false;
		return true;
	}

	return false;
}