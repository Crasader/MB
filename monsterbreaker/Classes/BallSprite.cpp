#include"BallSprite.h"
#include "Definitions.h"
#include "SimpleAudioEngine.h"
#include "MyBodyParser.h"
USING_NS_CC;

BallSprite::BallSprite()
{
	Init();
}
BallSprite::BallSprite(const Character& obj)
{
	setType("Ball");
	setName(obj.getBallName());
	setTeam(obj.getTeam());
	setAttackPoint(obj.getAttackPoint());
	setVelocity(obj.getBallVelocity());
	setBallSize(obj.getBallSize());
}

BallSprite::~BallSprite()
{
}

void BallSprite::Init()
{
	setType("Ball");
	setName("NormalBall");

	setVelocity(0.5f);
	setBallSize(1.0f);
}
BallSprite* BallSprite::create(const Character & obj)
{
	auto pSprite = new BallSprite(obj);

	auto cache = SpriteFrameCache::sharedSpriteFrameCache();
	cache->addSpriteFramesWithFile("Ball/Ball.plist", "Ball/Ball.png");
	//cache->addSpriteFramesWithFile(
	//	String::createWithFormat("%s/%s/%sImage.plist", pSprite->getType().c_str(), pSprite->getName().c_str(), pSprite->getName().c_str())->getCString(),
	//	String::createWithFormat("%s/%s/%s.png", pSprite->getType().c_str(), pSprite->getName().c_str(), pSprite->getName().c_str())->getCString()
	//	);

	if (pSprite->initWithSpriteFrameName(String::createWithFormat("Ball/%s.png", pSprite->getName().c_str() )->getCString()))
	{
		pSprite->autorelease();

		pSprite->InitSprite();
		pSprite->scheduleUpdate();

		return pSprite;
	}

	CC_SAFE_DELETE(pSprite);
	return NULL;
}



void BallSprite::InitSprite()
{
	//this->initWithSpriteFrameName(String::createWithFormat("%s.png", _name.c_str())->getCString());

	//MyBodyParser::getInstance()->parseJsonFile(String::createWithFormat("%s/%s/%s.json", _type.c_str(), _name.c_str(), _name.c_str())->getCString());
	//auto body = MyBodyParser::getInstance()->bodyFormJson(this, String::createWithFormat("%s.png", _name.c_str())->getCString(), PhysicsMaterial(1, 1, 0));
	auto body = PhysicsBody::createCircle(this->getContentSize().width / 2, PhysicsMaterial(1, 1, 0));
	if (body != nullptr)
	{
		body->setDynamic(true);
		body->setRotationEnable(true);
		if (getTeam() == 1)
		{
			body->setCollisionBitmask(HERO_BALL_COLLISION_BITMASK);
//			body->setCategoryBitmask(1);
		}
		else
		{
			body->setCollisionBitmask(MONSTER_BALL_COLLISION_BITMASK);
//			body->setCategoryBitmask(2);
		}
		body->setContactTestBitmask(true);
		this->setPhysicsBody(body);
	}
//	MyBodyParser::getInstance()->freeInstance();
	this->setScale(_ballSize);
}
void BallSprite::update(float dt)
{
	Vec2 vec = this->getPhysicsBody()->getVelocity();
	vec.normalize();
	vec = vec * _velocity;
	this->getPhysicsBody()->setVelocity(vec);
	
}