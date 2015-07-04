#include "BossHp.h"

USING_NS_CC;
using namespace ui;

BossHp::~BossHp()
{

}
BossHp::BossHp(cocos2d::Layer * layer) : layer(layer)
{
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
}

BossHp* BossHp::create(cocos2d::Layer * layer)
{
	auto pNode = new BossHp(layer);
	pNode->autorelease();
	pNode->Debug();
	return pNode;
}

void BossHp::Debug()
{
	node = CSLoader::createNode("BossHp/BossHp.csb");
	this->addChild(node);

	b = (cocos2d::Sprite*) node->getChildByName("b");
	f = (cocos2d::Sprite*)node->getChildByName("f");
	bossName = (cocos2d::ui::Text*) node->getChildByName("text");
	
}
void BossHp::SetTarget(Monster * target)
{
	this->target = target;
	bossName->setText(target->getBossName().c_str());
}
void BossHp::update(float dt)
{
	if (target->IsAlive())
	{
		float r = (float)(target->getCurrentHp()) / target->getMaxHp();

		if (r != 0)
		{
			f->setScaleX(r);
			auto sp = b->getPositionX() - b->getContentSize().width * 0.5f;
			f->setPositionX(sp + f->getContentSize().width * r * 0.5f);
		}
	}
	else
	{
		f->setVisible(false);
		//SoundManager::getInstance()->changeBG("MainBG");

	}
}



