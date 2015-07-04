#include"Brick.h"
USING_NS_CC;

Brick::Brick(const char * mapType, int brickTypeID) : _mapType(mapType), _brickTypeID(brickTypeID)
{
}

Brick::~Brick()
{
}

//Brick* Brick::create(const char * mapType, int brickTypeID)
//{
//	auto pSprite = new Brick(mapType, brickTypeID);
//	SpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Block/Block.plist", "Block/Block.png");
//	if (pSprite->initWithSpriteFrameName(String::createWithFormat("Block/Block%s%d.png", mapType, brickTypeID)->getCString()))
//	{
//		pSprite->autorelease();
//		pSprite->InitSprite();
//		return pSprite;
//	}
//	CC_SAFE_DELETE(pSprite);
//	return NULL;
////	return nullptr;
//}

void Brick::DestroyBlock()
{
	SoundManager::getInstance()->playMySoundLogic("Brick");
	auto ac_fade = FadeOut::create(0.3f);

	auto seq = Sequence::create(
		CallFunc::create(std::bind(&Brick::DestroyBody, this))
		, ac_fade
		, CallFunc::create(std::bind(&Brick::CleanBlock, this))
		, NULL);
	this->runAction(seq);

}

void Brick::CleanBlock()
{
	this->removeFromParentAndCleanup(true);
}
void Brick::DestroyBody()
{
	this->getPhysicsBody()->setEnable(false);
}

void Brick::InitSprite()
{
	auto body = PhysicsBody::createBox(this->getContentSize(), PhysicsMaterial(100, 1, 1));
	body->setDynamic(false);
	body->setRotationEnable(false);
	
	switch (_brickTypeID)
	{
	case BRICK_SINGLE_ID:
		body->setCollisionBitmask(SINGLE_BRICK_COLLISION_BITMASK);
		break;
	case BRICK_DOUBLE_ID:
		body->setCollisionBitmask(DOUBLE_BRICK_COLLISION_BITMASK);
		break;
	case BRICK_SOLID_ID:
		body->setCollisionBitmask(SOLID_BRICK_COLLISION_BITMASK);
		break;
	}	
	body->setContactTestBitmask(true);
	this->setPhysicsBody(body);
}

