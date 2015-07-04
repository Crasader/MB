#include "DoubleBrick.h"
USING_NS_CC;

DoubleBrick::DoubleBrick(const char * mapType, cocos2d::Layer * layer, int brickTypeID) : Brick(mapType, brickTypeID)
{
	this->layer = layer;
//	setType(type);
	b = false;
}

DoubleBrick::~DoubleBrick()
{
}
DoubleBrick* DoubleBrick::create(const char * mapType, cocos2d::Layer * layer, int brickTypeID)
{
	auto pSprite = new DoubleBrick(mapType, layer, brickTypeID);
	SpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Block/Block.plist", "Block/Block.png");
	if (pSprite->initWithSpriteFrameName(String::createWithFormat("Block/Block%s2.png", mapType, brickTypeID)->getCString()))
	{
		pSprite->autorelease();
		pSprite->InitSprite();
		return pSprite;
	}
	CC_SAFE_DELETE(pSprite);
	return NULL;
}

//void DoubleBrick::InitSprite()
//{
//	auto body = PhysicsBody::createBox(this->getContentSize(), PhysicsMaterial(100, 1, 1));
//	body->setDynamic(false);
//	body->setRotationEnable(false);
//	body->setCollisionBitmask(DOUBLE_BRICK_COLLISION_BITMASK);
//	body->setContactTestBitmask(true);
////	body->setCategoryBitmask(2);
//	this->setPhysicsBody(body);
//}

void DoubleBrick::DestroyBlock()
{
	if (!b)
	{
		b = true;
		auto sBrick = SingleBrick::create(getMapType().c_str(), BRICK_SINGLE_ID);
		sBrick->setPosition(this->getPosition());
		layer->addChild(sBrick, ZINDEX_BRICK_SPRITE, myEnum::kMyTag::kBlockTag);
		Brick::DestroyBlock();
	}
}

