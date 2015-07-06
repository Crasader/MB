#include"Dragon.h"
USING_NS_CC;
using namespace ui;

Dragon::Dragon(cocos2d::Layer * layer) : layer(layer)
{
	isFury = false;
	usingSkill = false;
	timer = kTimerUp;
}
Dragon* Dragon::create(cocos2d::Layer * layer)
{
	auto pSprite = new Dragon(layer);
	pSprite->autorelease();
	pSprite->InitSprite();
	return pSprite;
}

void Dragon::InitSprite()
{
	node = CSLoader::createNode("Monster/Dragon/Dragon.csb");
	this->addChild(node);

	auto act = CSLoader::createTimeline("Monster/Dragon/Dragon.csb");
	act->gotoFrameAndPlay(0, 60, true);
	node->runAction(act);
	
	mNode = node->getChildByName("mNode");
	m1 = (Sprite *)(mNode->getChildByName("m1"));
	m2 = (Sprite *)(mNode->getChildByName("m2"));
	f1 = (Sprite *)(mNode->getChildByName("f1"));
	f2 = (Sprite *)(mNode->getChildByName("f2"));
	m2->setVisible(false);
	f2->setVisible(false);

	// flame & flame body
	flame= (Sprite *)(mNode->getChildByName("dbNode")->getChildByName("f"));
	auto flameBody = PhysicsBody::createBox(flame->getContentSize());
	flameBody->setDynamic(false);
	flameBody->setCollisionBitmask(DRAGON_BREATH_COLLISION_BITMASK);
	flameBody->setContactTestBitmask(true);
	flame->setPhysicsBody(flameBody);

	setFlameVisible(false);

	// dragon body
	size = node->getChildByName("size");
	
	auto body = PhysicsBody::createBox(size->getContentSize());
	body->setDynamic(false);
	body->setRotationEnable(false);
	body->setCollisionBitmask(SOLID_BRICK_COLLISION_BITMASK);
	body->setContactTestBitmask(true);
	this->setPhysicsBody(body);
	this->setUserData(this);
	
}

cocos2d::Size Dragon::getContentSize()
{
	return size->getContentSize();
}
cocos2d::Vec2 Dragon::getMousePosition()
{
	return m2->getPosition();
}


void Dragon::Fire()
{
	int r = rand() % 2;
	usingSkill = true;

	if (!isFury)
	{
		if (r == 0)
		{
			this->runAction(Sequence::create(
				CallFunc::create(std::bind(&Dragon::FireLeft, this)),
				DelayTime::create(5.0f),
				CallFunc::create(std::bind(&Dragon::setUsingSkill, this, false)),
				NULL));
		}
		else
		{
			this->runAction(Sequence::create(
				CallFunc::create(std::bind(&Dragon::FireRight, this)),
				DelayTime::create(5.0f),
				CallFunc::create(std::bind(&Dragon::setUsingSkill, this, false)),
				NULL));
		}
	}
	else
	{
		if (r == 0)
		{
			this->runAction(Sequence::create(
				CallFunc::create(std::bind(&Dragon::FireLeft, this)),
				DelayTime::create(5.0f),
				CallFunc::create(std::bind(&Dragon::FireRight, this)),
				DelayTime::create(5.0f),
				CallFunc::create(std::bind(&Dragon::setUsingSkill, this, false)),
				NULL));
		}
		else
		{
			this->runAction(Sequence::create(
				CallFunc::create(std::bind(&Dragon::FireRight, this)),
				DelayTime::create(5.0f),
				CallFunc::create(std::bind(&Dragon::FireLeft, this)),
				DelayTime::create(5.0f),
				CallFunc::create(std::bind(&Dragon::setUsingSkill, this, false)),
				NULL));
		}
	}

	
}

void Dragon::FireLeft()
{
	auto act = CSLoader::createTimeline("Monster/Dragon/Dragon.csb");
	act->gotoFrameAndPlay(60, 360, false);
	node->runAction(act);
	
	this->runAction(Sequence::create(
		DelayTime::create(1.0f),
		CallFunc::create(std::bind(&Dragon::setMyVisibile, this, m2, true)),
		DelayTime::create(3.0f),
		CallFunc::create(std::bind(&Dragon::setMyVisibile, this, m2, false)),
		NULL));
	
	this->runAction(Sequence::create(
		DelayTime::create(1.0f),
		CallFunc::create(std::bind(&Dragon::setFlameVisible, this, true)),
		DelayTime::create(3.0f),
		CallFunc::create(std::bind(&Dragon::setFlameVisible, this, false)),
		NULL));
	
	SoundManager::getInstance()->playMySoundLogic("DragonFlame");
}

void Dragon::FireRight()
{
	auto act = CSLoader::createTimeline("Monster/Dragon/Dragon.csb");
	act->gotoFrameAndPlay(360, 660, false);
	node->runAction(act);

	this->runAction(Sequence::create(
		DelayTime::create(1.0f),
		CallFunc::create(std::bind(&Dragon::setMyVisibile, this, m2, true)),
		DelayTime::create(3.0f),
		CallFunc::create(std::bind(&Dragon::setMyVisibile, this, m2, false)),
		NULL));
	
	this->runAction(Sequence::create(
		DelayTime::create(1.0f),
		CallFunc::create(std::bind(&Dragon::setFlameVisible, this, true)),
		DelayTime::create(3.0f),
		CallFunc::create(std::bind(&Dragon::setFlameVisible, this, false)),
		NULL));

	SoundManager::getInstance()->playMySoundLogic("DragonFlame");

}

void Dragon::setMyVisibile(cocos2d::Sprite * spr, bool b)
{
	spr->setVisible(b);
}

void Dragon::Die()
{
	node->stopAllActions();
	this->stopAllActions();
	this->pause();
	this->getPhysicsBody()->setEnable(false);
	SoundManager::getInstance()->pauseAllSound();

	// flame disappear
	flame->stopAllActions();
	setFlameVisible(false);
		
	auto act = CSLoader::createTimeline("Monster/Dragon/Dragon.csb");
	act->gotoFrameAndPlay(660, 720, false);
	node->runAction(act);
	m2->setVisible(false);
	f2->setVisible(true);
}

void Dragon::update(float dt)
{

	if (timer == kTimerUp)	// timer set
	{
		if (!isFury)
			timer = 5.0f;
		else
			timer = 2.5f;
	}
	else
	{
		if (!usingSkill)
			timer -= dt;
	}
	if (timer <= 0)
	{
		Fire();
		timer = kTimerUp;
	}
}

void Dragon::setFlameVisible(bool b)
{
	flame->setVisible(b);
	flame->getPhysicsBody()->setEnable(b);
}

void Dragon::pause()
{
	Node::pause();
	node->pause();
}

void Dragon::resume()
{
	Node::resume();
	node->resume();
}



