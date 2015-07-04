#include"Sword.h"
USING_NS_CC;
using namespace ui;

Sword::Sword(cocos2d::Layer * layer) : layer(layer)
{
}
Sword* Sword::create(cocos2d::Layer * layer)
{
	auto pSprite = new Sword(layer);
	pSprite->autorelease();
	pSprite->InitSprite();
	return pSprite;
}

void Sword::InitSprite()
{
	origin = Director::getInstance()->getVisibleOrigin();
	visibleSize = Director::getInstance()->getVisibleSize();

	node = CSLoader::createNode("Sword/Sword.csb");
	this->addChild(node);

	skill = (cocos2d::Sprite *) node->getChildByName("skill");
	skill->setOpacity(0);

	auto act = CSLoader::createTimeline("Sword/Sword.csb");
	act->gotoFrameAndPause(0);
	
}

void Sword::Swing()
{
	auto act = CSLoader::createTimeline("Sword/Sword.csb");
	act->gotoFrameAndPlay(0, 30, false);
	node->runAction(act);
	SoundManager::getInstance()->playMySoundLogic("Swing", "mp3");

}

void Sword::UseSkill()
{
	auto act = CSLoader::createTimeline("Sword/Sword.csb");
	act->gotoFrameAndPlay(30, 90, false);
	node->runAction(act);

//	skill->stopAllActions();
	skill->setOpacity(0);

	skill->runAction(Sequence::create(
		FadeIn::create(0.25f),
		DelayTime::create(0.5f),
		FadeOut::create(0.25f),
		NULL));
	SoundManager::getInstance()->playMySoundLogic("Skill");

}

void Sword::FadeIn(float t)
{
	node->runAction(FadeIn::create(t));
}
void Sword::FadeOut(float t)
{
	node->runAction(FadeOut::create(t));
}

