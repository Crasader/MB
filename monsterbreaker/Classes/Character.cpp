#include"Character.h"
#include "BallSprite.h"

#include "Definitions.h"
USING_NS_CC;

Character::Character()
{
	Init();
}
Character::~Character()
{

}
void Character::Init()
{
	_ballCount = 10;
	_ballCurrentCount = 0;
	_ballName = "NormalBall";
	_ballVelocity = 700.0f;
	_ballSize = 1.0f;
}

void Character::Fire(cocos2d::Layer * layer, cocos2d::Vec2 startPoint, cocos2d::Vec2 destPoint, bool isCoin)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();

	if (IsAlive())
	{
		if (_ballCount > _ballCurrentCount)
		{
			_ballCurrentCount++;
			auto ball = BallSprite::create(*this);

			ball->getPhysicsBody()->setVelocity(Vec2(200, 200));
			ball->setUserData(this);

			ball->setPosition(startPoint);
			ball->getPhysicsBody()->setVelocity(destPoint - startPoint);

			ball->runAction(RepeatForever::create(RotateBy::create(1.0f, 360)));
			layer->addChild(ball, ZINDEX_HERO_BALL);

			if (isCoin) ball->getPhysicsBody()->setCollisionBitmask(COIN_BALL_COLLISION_BITMASK);
		}
	}
}



void Character::DecreaseBallCount()
{
	_ballCurrentCount--;
	if (_ballCurrentCount < 0)
		_ballCurrentCount = 0;
}



