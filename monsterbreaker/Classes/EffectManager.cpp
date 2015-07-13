#include "EffectManager.h"
USING_NS_CC;
using namespace ui;

EffectManager::EffectManager(cocos2d::Layer * layer) : layer(layer)
{
	origin = Director::getInstance()->getVisibleOrigin();
	visibleSize = Director::getInstance()->getVisibleSize();	
}
EffectManager::~EffectManager()
{

}

EffectManager* EffectManager::create(cocos2d::Layer * layer)
{
	auto pNode = new EffectManager(layer);
	pNode->autorelease();
	return pNode;
}

void EffectManager::HealEffect(cocos2d::Vec2 target)
{
	auto node = Node::create();
	node->setPosition(target);

	auto spr1 = Sprite::create("Effect/Heal/Heal.png");
	spr1->setPosition(spr1->getContentSize().width * 0.5f, -spr1->getContentSize().height * 0.5f);
	auto spr2 = Sprite::create("Effect/Heal/Heal.png");
	spr2->setScale(0.5f);
	spr2->setPosition(-spr1->getContentSize().width * 0.5f, -spr1->getContentSize().height * 0.5f);
	auto spr3 = Sprite::create("Effect/Heal/Heal.png");
	spr3->setScale(0.3f);
	spr3->setPosition(0, -spr1->getContentSize().height * 0.5f);

	node->addChild(spr1);
	node->addChild(spr2);
	node->addChild(spr3);

	layer->addChild(node, ZINDEX_EFFECT_FRONT);

	spr1->setOpacity(0);
	spr2->setOpacity(0);
	spr3->setOpacity(0);

	spr1->runAction(
		Sequence::create(
		Spawn::create(
		FadeIn::create(0.25f),
		MoveBy::create(0.25f, Vec2(0, spr1->getContentSize().height * 2.0f)),
		NULL),
		FadeOut::create(0.25f),
		NULL));
	spr2->runAction(
		Sequence::create(
		DelayTime::create(0.25f),
		Spawn::create(
		FadeIn::create(0.25f),
		MoveBy::create(0.25f, Vec2(0, spr1->getContentSize().height * 2.0f)),
		NULL),
		FadeOut::create(0.25f),
		NULL));
	spr3->runAction(
		Sequence::create(
		DelayTime::create(0.5f),
		Spawn::create(
		FadeIn::create(0.25f),
		MoveBy::create(0.25f, Vec2(0, spr1->getContentSize().height * 2.0f)),
		NULL),
		FadeOut::create(0.25f),
		CallFunc::create(std::bind(&EffectManager::DestroyNode, this, node)),
		NULL));

	SoundManager::getInstance()->playMySoundLogic("Heal");

	effects.pushBack(node);
}
void EffectManager::FireBallEffect(cocos2d::Vec2 startPosition, cocos2d::Vec2 target)
{
	auto spr = Sprite::create("Effect/FireBall/FireBall.png");
	spr->setPosition(startPosition);
	layer->addChild(spr, ZINDEX_EFFECT_FRONT);

	auto body = PhysicsBody::createCircle(spr->getContentSize().width * 0.5f);
	body->setCollisionBitmask(SKILL_FIRE_BALL_SPRITE_COLLISION_BITMASK);
	body->setDynamic(false);
	body->setContactTestBitmask(true);
	spr->setPhysicsBody(body);

	spr->runAction(
		Sequence::create(
		MoveBy::create(0.3f, Vec2(0, spr->getContentSize().height)),
		DelayTime::create(0.5f),
		MoveTo::create(0.5f, target),
		CallFunc::create(std::bind(&EffectManager::DestroyNode, this, spr)),
		NULL));

	SoundManager::getInstance()->playMySoundLogic("FireBall");

	effects.pushBack(spr);
}

void EffectManager::ShiningEffect(cocos2d::Vec2 target)
{
	auto spr = Sprite::create("Effect/Shining/Shining.png");
	spr->setPosition(target);
	layer->addChild(spr, ZINDEX_EFFECT_FRONT);
	spr->setOpacity(0);
	spr->runAction(
		Sequence::create(
		FadeIn::create(0.2f),
		FadeOut::create(0.1f),
		CallFunc::create(std::bind(&EffectManager::DestroyNode, this, spr)),
		NULL
		));

	effects.pushBack(spr);
}

void EffectManager::ThankyouEffect(cocos2d::Vec2 target)
{
	auto spr = Sprite::create("Effect/Thankyou/Thankyou.png");
	spr->setPosition(target);
	layer->addChild(spr, ZINDEX_EFFECT_FRONT);
	spr->setOpacity(0);
	spr->runAction(
		Sequence::create(
		FadeIn::create(0.5f),
		DelayTime::create(1.0f),
		FadeOut::create(0.5f),
		CallFunc::create(std::bind(&EffectManager::DestroyNode, this, spr)),
		NULL
		));

	effects.pushBack(spr);
}

void EffectManager::ShowItemDes(int itemNumber)
{
	auto node = Node::create();
	node->setPosition(-visibleSize.width * 0.5f, visibleSize.height * 0.7f);
	layer->addChild(node, ZINDEX_EFFECT_FRONT);

	// new Item
	Hero * hero = (Hero *)layer->getChildByName("Hero");
	auto item = ChestItem::create(layer, hero, itemNumber, false);
	node->addChild(item,1);

	// Item Animation 
	auto frame = CSLoader::createNode("Item/ItemFrame.csb");
	//frame->setPosition(origin.x, origin.y);
	node->addChild(frame,0);

	auto nameLabel = dynamic_cast<Text*>(frame->getChildByName("NameLabel"));
	nameLabel->setString(item->getItemName());

	auto descLabel = dynamic_cast<Text*>(frame->getChildByName("DescLabel"));
	descLabel->setString(item->getDesc());

	node->runAction(
		Sequence::create(
		MoveTo::create(0.5f, Vec2(visibleSize.width*0.5f, visibleSize.height*0.7f)),
		DelayTime::create(3.0f),
		MoveTo::create(0.5f, Vec2(visibleSize.width*1.5f, visibleSize.height*0.7f)),
		DelayTime::create(0.5f),
		NULL
		));

	SoundManager::getInstance()->playMySoundLogic("Item");
	
	effects.pushBack(node);
}

void EffectManager::HitEffect(cocos2d::Vec2 target)
{
	auto node = Node::create();
	node->setPosition(target);
	layer->addChild(node, ZINDEX_EFFECT_FRONT);

	auto hitNode = CSLoader::createNode("Effect/Hit/Hit.csb");
	node->addChild(hitNode);

	auto act = CSLoader::createTimeline("Effect/Hit/Hit.csb");
	act->gotoFrameAndPlay(0, 30, false);
	hitNode->runAction(act);

	node->runAction(
		Sequence::create(
		DelayTime::create(0.5f),
		CallFunc::create(std::bind(&EffectManager::DestroyNode, this, node)),
		NULL));

	effects.pushBack(node);
}

void EffectManager::BarrierEffect(cocos2d::Vec2 target)
{
	auto barrier = Sprite::create("Effect/Barrier/Barrier.png");
	barrier->setPosition(target);
	layer->addChild(barrier, ZINDEX_EFFECT_FRONT);
	
	barrier->runAction(Sequence::create(
		Repeat::create(Sequence::create(
		FadeOut::create(0.1f),
		FadeIn::create(0.1f),
		NULL),2),
		CallFunc::create(std::bind(&EffectManager::DestroyNode, this, barrier)),
		NULL));

	effects.pushBack(barrier);
}

void EffectManager::DestroyNode(cocos2d::Node* node)
{
	node->stopAllActions();
	node->removeFromParentAndCleanup(true);
}

void EffectManager::LightningEffect(cocos2d::Vec2 target, int damage)
{
	auto l = Lightning::create(layer, damage);
	l->setPosition(target);
	layer->addChild(l, ZINDEX_EFFECT_FRONT);

	effects.pushBack(l);
}

void EffectManager::PauseAllEffects()
{
	this->pause();
	int size = effects.size();
	for (int i = 0; i < size; i++)
		effects.at(i)->pause();
}
void EffectManager::ResumeAllEffects()
{
	this->resume();
	int size = effects.size();
	for (int i = 0; i < size; i++)
		effects.at(i)->resume();
}


