#include "SingleBrick.h"
USING_NS_CC;

SingleBrick::SingleBrick(const char * mapType, int brickTypeID) : Brick(mapType, brickTypeID)
{
//	setType(type);
}

SingleBrick::~SingleBrick()
{
}
SingleBrick* SingleBrick::create(const char * mapType, int brickTypeID)
{
	auto pSprite = new SingleBrick(mapType, brickTypeID);
	SpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Block/Block.plist", "Block/Block.png");
	if (pSprite->initWithSpriteFrameName(String::createWithFormat("Block/Block%s%d.png", mapType, brickTypeID)->getCString()))
	{
		pSprite->autorelease();
		pSprite->InitSprite();
		return pSprite;
	}
	CC_SAFE_DELETE(pSprite);
	return NULL;
}

//void SingleBrick::InitSprite()
//{
//	auto body = PhysicsBody::createBox(this->getContentSize(), PhysicsMaterial(100, 1, 1));
//	body->setDynamic(false);
//	body->setRotationEnable(false);
//	body->setCollisionBitmask(SINGLE_BRICK_COLLISION_BITMASK);
//	body->setContactTestBitmask(true);
////	body->setCategoryBitmask(2);
//	this->setPhysicsBody(body);
//}
