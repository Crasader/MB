#include"Lightning.h"
#include "Definitions.h"
#include "SimpleAudioEngine.h"
//#include "MyBodyParser.h"
USING_NS_CC;

Lightning::Lightning(cocos2d::Layer * layer, int ap) : layer(layer), _attackPoint(ap)
{

}

Lightning::~Lightning()
{

}

//void Lightning::SetLightningData(float countTime, int attackPoint, const char * LightningName, float range)
//{
//	this->kTimer = countTime;
//	this->LightningName = LightningName;
//	this->attackPoint = attackPoint;
//	this->range = range;
//}

Lightning* Lightning::create(cocos2d::Layer * layer, int ap)
{
	auto pNode = new Lightning(layer, ap);
	pNode->autorelease();
//	pNode->SetLightningData(hero.getLightningCountTime(), hero.getLightningAttackPoint(), hero.getLightningName().c_str(), hero.getLightningRange());
	pNode->InitSprite();
	return pNode;
}

void Lightning::InitSprite()
{
	t = CSLoader::createNode("Effect/Lightning/LightningT.csb");
	l = CSLoader::createNode("Effect/Lightning/Lightning.csb");
	this->addChild(t, 0);
	this->addChild(l, 1);
	l->setVisible(false);
	auto act = CSLoader::createTimeline("Effect/Lightning/LightningT.csb");
	act->gotoFrameAndPlay(0, 180, true);
	t->runAction(act);

	this->runAction(Sequence::create(
		DelayTime::create(3.0f),
		CallFunc::create(std::bind(&Lightning::boom, this)),
		DelayTime::create(1.0f),
		CallFunc::create(std::bind(&Lightning::RemoveAll, this)),
		NULL));
}
void Lightning::boom()
{
	t->setVisible(false);
	t->stopAllActions();

	l->setVisible(true);
	auto act = CSLoader::createTimeline("Effect/Lightning/Lightning.csb");
	act->gotoFrameAndPlay(0, 60, false);
	l->runAction(act);
	
	auto spr = l->getChildByName("skill10_1");
//	auto body = PhysicsBody::createBox(spr->getContentSize());
	auto body = PhysicsBody::createCircle(spr->getContentSize().height * 0.5f);
	body->setCollisionBitmask(SKILL_LIGHTNING_COLLISION_BITMASK);
	body->setContactTestBitmask(true);
	body->setDynamic(false);
//	body->setGravityEnable(false);
	this->setPhysicsBody(body);
	body->getNode()->setUserData(this);

	SoundManager::getInstance()->playMySoundLogic("Lightning");

}
void Lightning::RemoveAll()
{
	this->removeFromParentAndCleanup(true);
}

cocos2d::Size Lightning::getContentSize()
{
	auto spr = l->getChildByName("skill10_1");
	return spr->getContentSize();
}

void Lightning::pause()
{
	Node::pause();
	l->pause();
	t->pause();
}

void Lightning::resume()
{
	Node::resume();
	l->resume();
	t->resume();
}


//int Lightning::GetAttackPoint()
//{
//	return attackPoint;
//}
