#include "SecretDoor.h"
USING_NS_CC;
using namespace ui;

SecretDoor::SecretDoor(const Room & rd, int kDir, const char * mapType) : Door(rd, kDir, mapType)
{
	_clickOk = false;
	_isSecret = true;
}
SecretDoor* SecretDoor::create(const Room & rd, int kDir, const char * mapType)
{
	auto pSprite = new SecretDoor(rd, kDir, mapType);

	pSprite->autorelease();
	pSprite->InitSprite();
	return pSprite;
}

void SecretDoor::InitSprite()
{	
	auto node = (CSLoader::createNode(String::createWithFormat("Door/%s/Door.csb", _mapType.c_str())->getCString()));
	node->setPosition(this->getContentSize().width / 2, this->getContentSize().height / 2);
	this->addChild(node);

	auto typeNode = CSLoader::createNode("Door/Secret.csb");
	typeNode->setPosition(this->getContentSize().width / 2, this->getContentSize().height / 2);
	this->addChild(typeNode);

	auto act = CSLoader::createTimeline(String::createWithFormat("Door/%s/Door.csb", _mapType.c_str())->getCString());
	act->gotoFrameAndPlay(0, 0, false);
	node->runAction(act);

	auto typeAct = CSLoader::createTimeline("Door/Secret.csb");
	typeAct->gotoFrameAndPlay(0, 0, false);
	typeNode->runAction(typeAct);

	btn = dynamic_cast<Button*>(node->getChildByName("btn"));
	btn->setUserData(this);

	auto body = PhysicsBody::createBox(btn->getContentSize());
	body->setCollisionBitmask(SECRET_DOOR_COLLISION_BITMASK);
	body->setDynamic(false);
	body->setContactTestBitmask(true);
	node->setPhysicsBody(body);
	body->getNode()->setUserData(this);

	this->setVisible(_roomVisible);
}

void SecretDoor::Open()
{
	Door::Open();

	if (!_lock)
	{
		_isOpen = true;
		auto act = CSLoader::createTimeline("Door/Secret.csb");
		act->gotoFrameAndPlay(0, 60, true);
		this->runAction(act);
	}
}
bool SecretDoor::ClickOpen()
{
	return false;
}