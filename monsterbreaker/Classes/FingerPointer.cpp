#include"FingerPointer.h"
#include "Definitions.h"
#include "SimpleAudioEngine.h"
//#include "MyBodyParser.h"
USING_NS_CC;

FingerPointer::FingerPointer(cocos2d::Layer * layer) : layer(layer)
{

}

FingerPointer::~FingerPointer()
{

}

FingerPointer* FingerPointer::create(cocos2d::Layer * layer)
{
	auto pNode = new FingerPointer(layer);
	pNode->autorelease();
	pNode->InitSprite();
	return pNode;
}

void FingerPointer::InitSprite()
{
	node = CSLoader::createNode("Tutorial/Pointer.csb");
	spr = (Sprite*)node->getChildByName("ptr");
	c = node->getChildByName("click");
	
	addChild(node);
	c->setVisible(false);
	
}
void FingerPointer::RemoveAll()
{
	this->removeFromParentAndCleanup(true);
}

cocos2d::Size FingerPointer::getContentSize()
{
//	auto spr = l->getChildByName("skill10_1");
	return spr->getContentSize();
}

void FingerPointer::pause()
{
	Node::pause();
	node->pause();
	c->pause();
}

void FingerPointer::resume()
{
	Node::resume();
	node->resume();
	c->resume();
}

void FingerPointer::setClickVisible(bool b)
{
	c->setVisible(b);
}

void FingerPointer::setOpacity(float op)
{
	node->setOpacity(op);
}

void FingerPointer::clickHold(float dt)
{
	c->setVisible(true);
	c->stopAllActions();
	c->runAction(FadeIn::create(dt));
}
void FingerPointer::clickCancle(float dt)
{
	c->stopAllActions();
	c->runAction(FadeIn::create(dt));
}

void FingerPointer::fadeIn(float dt)
{
	node->stopAllActions();
	node->runAction(FadeIn::create(dt));
}
void FingerPointer::fadeOut(float dt)
{
	node->stopAllActions();
	node->runAction(FadeOut::create(dt));
}




