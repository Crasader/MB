#include "SingleBrick.h"
USING_NS_CC;

SingleBrick::SingleBrick(const char * mapType, int brickTypeID) : Brick(mapType, brickTypeID)
{
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

