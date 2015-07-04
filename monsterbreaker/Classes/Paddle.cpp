#include "Paddle.h"
#include "Definitions.h"
#include "MyBodyParser.h"

USING_NS_CC;

Paddle::Paddle()
{

}

Paddle* Paddle::create(float paddleSize, const char * paddleName)
{

	auto pSprite = new Paddle();

	auto cache = SpriteFrameCache::sharedSpriteFrameCache();
	cache->addSpriteFramesWithFile("Paddle/Paddle.plist", "Paddle/Paddle.png");

	if (pSprite->initWithSpriteFrameName(String::createWithFormat("%s.png", paddleName)->getCString()))
	{
		pSprite->autorelease();
		pSprite->SetPaddle(paddleSize, paddleName);
		return pSprite;
	}
	CC_SAFE_DELETE(pSprite);
	return NULL;
}


void Paddle::SetPaddle(float paddleSize, const char * paddleName)
{	
	MyBodyParser::getInstance()->parseJsonFile("Paddle/Paddle.json");
	auto body = MyBodyParser::getInstance()->bodyFormJson(this, String::createWithFormat("%s.png", paddleName)->getCString(), PhysicsMaterial(100, 1, 0));
	if (body != nullptr)
	{
		body->setDynamic(false);
		body->setCollisionBitmask(PADDLE_COLLISION_BITMASK);
		body->setContactTestBitmask(true);
//		body->setCategoryBitmask(1);
		this->setPhysicsBody(body);
	}
	//this->setTag(ZINDEX_HERO_PADDLE);
	//this->setOpacity(200);
	MyBodyParser::getInstance()->freeInstance();

	float scale = this->getScaleX();
	scale *= paddleSize;
	this->setScaleX(scale);

}


