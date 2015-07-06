#include"Cage.h"
#include "Definitions.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
using namespace ui;

Cage::Cage(cocos2d::Layer * layer, Hero * hero, int lockCnt) : layer(layer), hero(hero), lockCnt(lockCnt)
{
	clickOk = true;
}

Cage::~Cage()
{

}

Cage* Cage::create(cocos2d::Layer * layer, Hero * hero, int lockCnt)
{
	auto pNode = new Cage(layer, hero, lockCnt);
	pNode->autorelease();
	pNode->InitSprite();
	return pNode;
}

void Cage::InitSprite()
{
	node = CSLoader::createNode("Cage/Cage.csb");
	this->addChild(node);

	l1 = node->getChildByName("l1");
	l2 = node->getChildByName("l2");
	l3 = node->getChildByName("l3");

	for (int i = 3; i > 0 + lockCnt; i--)
	{
		auto obj = node->getChildByName(String::createWithFormat("l%d", i)->getCString());
		obj->setVisible(false);
	}

	btn = dynamic_cast<Button*>(node->getChildByName("btn"));
	btn->setUserData(this);
	struct callBackFunctorCage
	{
		void operator() (Ref* sender) const
		{
			static_cast<Cage*>(static_cast<Node*>(sender)->getUserData())->ClickCage();
		}
	};
	Widget::ccWidgetClickCallback callBackCage = callBackFunctorCage();
	btn->addClickEventListener(callBackCage);
}

void Cage::ClickCage()
{
	if (clickOk)
	{
		if (hero->getKeyCount() >= lockCnt)
		{
			auto mm = MapManager::getInstance();
			int x = mm->GetCurrentRoomData().x;
			int y = mm->GetCurrentRoomData().y;

			mm->map[x][y].data[String::createWithFormat("c%d", this->getTag())->getCString()] = 1;

			clickOk = false;
			hero->DecreaseKeyCount(lockCnt);

			auto effectManager = (EffectManager*) layer->getChildByName("EffectManager");
			effectManager->ShiningEffect(l1->getPosition() + this->getPosition());

			auto act = FadeOut::create(1.0f);
			l1->runAction(act->clone());
			l2->runAction(act->clone());
			l3->runAction(act->clone());

			this->runAction(Sequence::create(
				DelayTime::create(1.5f),
				CallFunc::create(std::bind(&Cage::RemoveAll, this)),
				NULL));
			SoundManager::getInstance()->playMySoundLogic("Shining");
		}
		else
		{
			// beep sound
			SoundManager::getInstance()->playMySoundLogic("X");
		}

	}
}

void Cage::RemoveAll()
{
	this->removeFromParentAndCleanup(true);
}