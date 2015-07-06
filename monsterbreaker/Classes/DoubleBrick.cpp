#include "DoubleBrick.h"
USING_NS_CC;

DoubleBrick::DoubleBrick(const char * mapType, cocos2d::Layer * layer, int brickTypeID) : Brick(mapType, brickTypeID)
{
	this->layer = layer;
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

