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
	auto body = PhysicsBody::createCircle(this->getContentSize().width / 2, PhysicsMaterial(1, 1, 0));
	if (body != nullptr)
	{
		body->setDynamic(true);
		body->setRotationEnable(true);
		if (getTeam() == 1)
		{
			body->setCollisionBitmask(HERO_BALL_COLLISION_BITMASK);
		}
		else
		{
			body->setCollisionBitmask(MONSTER_BALL_COLLISION_BITMASK);
		}
		body->setContactTestBitmask(true);
		this->setPhysicsBody(body);
	}
	this->setScale(_ballSize);
}
void BallSprite::update(float dt)
{
	Vec2 vec = this->getPhysicsBody()->getVelocity();
	vec.normalize();
	vec = vec * _velocity;
	this->getPhysicsBody()->setVelocity(vec);
	
}