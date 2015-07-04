#include "BossDoor.h"
USING_NS_CC;
using namespace ui;

BossDoor::BossDoor(const Room & rd, int kDir, const char * mapType) : Door(rd, kDir, mapType)
{

}
BossDoor* BossDoor::create(const Room & rd, int kDir, const char * mapType)
{
	auto pSprite = new BossDoor(rd, kDir, mapType);
	pSprite->autorelease();
	pSprite->InitSprite();
	return pSprite;
}

void BossDoor::InitSprite()
{
	auto node = (CSLoader::createNode(String::createWithFormat("Door/%s/Door.csb", _mapType.c_str())->getCString()));
	node->setPosition(this->getContentSize().width / 2, this->getContentSize().height / 2);
	this->addChild(node);

	auto typeNode = CSLoader::createNode("Door/Boss.csb");
	typeNode->setPosition(this->getContentSize().width / 2, this->getContentSize().height / 2);
	this->addChild(typeNode);

	auto act = CSLoader::createTimeline(String::createWithFormat("Door/%s/Door.csb", _mapType.c_str())->getCString());
	act->gotoFrameAndPlay(0, 0, false);
	node->runAction(act);

	auto typeAct = CSLoader::createTimeline("Door/Boss.csb");
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

void BossDoor::Open()
{
	Door::Open();

	if (!_lock)
	{
		_isOpen = true;
		auto act = CSLoader::createTimeline("Door/Boss.csb");
		act->gotoFrameAndPlay(0, 60, false);
		this->runAction(act);
		// glow effect
		// open sound
	}
}
bool BossDoor::ClickOpen()
{
	_isOpen = true;
	return true;
}