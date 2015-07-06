#include "EndingDoor.h"
USING_NS_CC;
using namespace ui;

EndingDoor::EndingDoor(const char * type, int endingNum) : _type(type), _endingNum(endingNum)
{

}
EndingDoor* EndingDoor::create(const char * type, int endingNum)
{
	auto pSprite = new EndingDoor(type, endingNum);
	pSprite->autorelease();
	pSprite->InitSprite();
	return pSprite;	
}

EndingDoor* EndingDoor::create(const char * type)
{
	auto pSprite = new EndingDoor(type, 0);
	pSprite->autorelease();
	pSprite->InitSprite();
	return pSprite;
}
void EndingDoor::InitSprite()
{
	auto node = (CSLoader::createNode(String::createWithFormat("EndingDoor/%sDoor.csb", _type.c_str())->getCString()));
	node->setPosition(this->getContentSize().width / 2, this->getContentSize().height / 2);
	this->addChild(node);
	
	if (_type.compare("Ending") == 0)
	{
		auto act = CSLoader::createTimeline(String::createWithFormat("EndingDoor/%sDoor.csb", _type.c_str())->getCString());
		act->gotoFrameAndPlay(0, 60, true);
		node->runAction(act);
	}

	btn = dynamic_cast<Button*>(node->getChildByName("btn"));
	btn->setUserData(this);

}
