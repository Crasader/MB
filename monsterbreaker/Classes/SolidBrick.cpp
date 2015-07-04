#include "SolidBrick.h"
USING_NS_CC;

SolidBrick::SolidBrick(const char * mapType, int brickTypeID) : Brick(mapType, brickTypeID)
{
//	setMapType(type);
}

SolidBrick::~SolidBrick()
{
}
SolidBrick* SolidBrick::create(const char * mapType, int brickTypeID)
{
	auto pSprite = new SolidBrick(mapType, brickTypeID);
	SpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Block/Block.plist", "Block/Block.png");
	if (pSprite->initWithSpriteFrameName(String::createWithFormat("Block/Block%s%d.png", mapType,brickTypeID)->getCString()))
	{
		pSprite->autorelease();
		pSprite->InitSprite();
		return pSprite;
	}
	CC_SAFE_DELETE(pSprite);
	return NULL;
}

//void SolidBrick::InitSprite()
//{
//	auto body = PhysicsBody::createBox(this->getContentSize(), PhysicsMaterial(100, 1, 1));
//	body->setDynamic(false);
//	body->setRotationEnable(false);
//	body->setCollisionBitmask(SOLID_BRICK_COLLISION_BITMASK);
//	body->setContactTestBitmask(true);
////	body->setCategoryBitmask(2);
//	this->setPhysicsBody(body);
//}
void SolidBrick::DestroyBlock()
{
	// sound
}

