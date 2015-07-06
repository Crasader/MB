#include"KeyDoor.h"
USING_NS_CC;
using namespace ui;

KeyDoor::KeyDoor(const Room & rd, int kDir, Hero * hero, const char * mapType) : Door(rd, kDir, mapType)
{
	this->hero = hero;
}
KeyDoor* KeyDoor::create(const Room & rd, int kDir, Hero * hero, const char * mapType)
{
	auto pSprite = new KeyDoor(rd, kDir, hero, mapType);
	pSprite->autorelease();
	pSprite->InitSprite();
	return pSprite;
	
}

void KeyDoor::InitSprite()
{
	auto node = (CSLoader::createNode(String::createWithFormat("Door/%s/Door.csb", _mapType.c_str())->getCString()));
	node->setPosition(this->getContentSize().width / 2, this->getContentSize().height / 2);
	this->addChild(node);

	auto typeNode = CSLoader::createNode("Door/Lock.csb");
	typeNode->setPosition(this->getContentSize().width / 2, this->getContentSize().height / 2);
	this->addChild(typeNode);

	auto act = CSLoader::createTimeline(String::createWithFormat("Door/%s/Door.csb", _mapType.c_str())->getCString());
	act->gotoFrameAndPlay(0, 0, false);
	node->runAction(act);

	auto typeAct = CSLoader::createTimeline("Door/Lock.csb");
	typeAct->gotoFrameAndPlay(0, 0, false);
	typeNode->runAction(typeAct);

	btn = dynamic_cast<Button*>(node->getChildByName("btn"));
	btn->setUserData(this);

	auto body = PhysicsBody::createBox(btn->getContentSize());
	body->setCollisionBitmask(DOOR_COLLISION_BITMASK);
	body->setDynamic(false);
	node->setPhysicsBody(body);

	this->setVisible(_roomVisible);

}

void KeyDoor::Open()
{
	Door::Open();

	if (!_lock)
	{	
		_isOpen = true;
		auto act = CSLoader::createTimeline("Door/Lock.csb");
		act->gotoFrameAndPlay(0, 60, false);
		this->runAction(act);
	}
}
bool KeyDoor::ClickOpen()
{
	if (hero->getKeyCount() > 0)
	{
		hero->DecreaseKeyCount(1);
		_lock = false;
		return true;
	}

	return false;
}