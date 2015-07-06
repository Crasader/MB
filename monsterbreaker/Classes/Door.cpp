#include"Door.h"
USING_NS_CC;
using namespace ui;

Door::Door(const Room & rd, int kDir, const char * mapType)
{
	this->_kDir = kDir;
	_gotoX = rd.x;
	_gotoY = rd.y;
	_lock = rd.lock;
	_roomType = rd.type;
	_roomVisible = rd.visible;
	_mapType = mapType;

	_clickOk = false;
	_isOpen = false;
	_isSecret = false;
}

Door* Door::create(const Room & rd, int kDir, const char * mapType)
{
	auto pSprite = new Door(rd, kDir, mapType);
	pSprite->autorelease();
	pSprite->InitSprite();
	return pSprite;
}

void Door::InitSprite()
{
	auto node = (CSLoader::createNode(String::createWithFormat("Door/%s/Door.csb", _mapType.c_str())->getCString()));
	node->setPosition(this->getContentSize().width / 2, this->getContentSize().height / 2);
	this->addChild(node);

	auto act = CSLoader::createTimeline(String::createWithFormat("Door/%s/Door.csb", _mapType.c_str())->getCString());
	act->gotoFrameAndPlay(0, 0, false);
	node->runAction(act);

	btn = dynamic_cast<Button*>(node->getChildByName("btn"));
	btn->setUserData(this);

	auto body = PhysicsBody::createBox(btn->getContentSize());
	body->setCollisionBitmask(DOOR_COLLISION_BITMASK);
	body->setDynamic(false);
	node->setPhysicsBody(body);

	this->setVisible(_roomVisible);
}

void Door::Open()
{
	if (!_lock)
	{
		_isOpen = true;
		auto act = CSLoader::createTimeline(String::createWithFormat("Door/%s/Door.csb", _mapType.c_str())->getCString());
		act->gotoFrameAndPlay(0, 60, false);
		this->runAction(act);
	}
}

bool Door::ClickOpen()
{
	_isOpen = true;
	return true;
}

void Door::bombCrush()
{

}

