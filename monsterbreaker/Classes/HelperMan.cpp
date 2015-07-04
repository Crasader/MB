#include"HelperMan.h"

USING_NS_CC;
using namespace ui;

HelperMan::HelperMan(cocos2d::Layer * layer, Hero * hero, bool cageIn) : layer(layer), hero(hero), isCageIn(cageIn)
{
	if (isCageIn)
		clickOk = true;
	else
		clickOk = false;
	visibleSize = Director::getInstance()->getVisibleSize();
	setAlive(true);
	_team = 1;
}

HelperMan::~HelperMan()
{

}

//HelperMan* HelperMan::create(cocos2d::Layer * layer, Hero * hero, bool cageIn)
//{
//	auto pNode = new HelperMan(layer, hero, cageIn);
//	pNode->autorelease();
//	pNode->InitSprite();
//	return pNode;
//}

void HelperMan::InitSprite()
{

	node = CSLoader::createNode(String::createWithFormat("HelperMan/%s/%s.csb", _name.c_str(), _name.c_str())->getCString());
	this->addChild(node);
	Stay();
	//auto act = CSLoader::createTimeline(String::createWithFormat("HelperMan/%s/%s.csb", _name.c_str(), _name.c_str())->getCString());
	//act->gotoFrameAndPlay(0, 60, true);
	//node->runAction(act);

	//l1 = node->getChildByName("l1");
	//l2 = node->getChildByName("l2");
	//l3 = node->getChildByName("l3");

	//for (int i = 3; i > 0 + lockCnt; i--)
	//{
	//	auto obj = node->getChildByName(String::createWithFormat("l%d", i)->getCString());
	//	obj->setVisible(false);
	//}

	btn = dynamic_cast<Button*>(node->getChildByName("btn"));
	btn->setUserData(this);
	struct callBackFunctorHelperMan
	{
		void operator() (Ref* sender) const
		{
			static_cast<HelperMan*>(static_cast<Node*>(sender)->getUserData())->ClickHelperMan();
		}
	};
	Widget::ccWidgetClickCallback callBackHelperMan = callBackFunctorHelperMan();
	btn->addClickEventListener(callBackHelperMan);
	btn->setEnabled(clickOk);

	this->initWithSpriteFrameName(String::createWithFormat("HelperMan/%s/alpha.png", _name.c_str())->getCString());
	node->setPosition(getContentSize().width*0.5f, getContentSize().height*0.5f);
}

cocos2d::Size HelperMan::getContentSize()
{
	return btn->getContentSize();
}

void HelperMan::ClickHelperMan()
{
	int size = hero->helperList.size();
	if (clickOk && size < 2)
	{
//		CCLOG("Clicked");
		ThankYou();
		clickOk = false;

		// hero
		if (size < 2)
			hero->helperList.push_back(getTag());

		auto mm = MapManager::getInstance();
		int x = mm->GetCurrentRoomData().x;
		int y = mm->GetCurrentRoomData().y;
		mm->map[x][y].data["HMClicked"] = 1;

		Vec2 vec;
		if (size == 0)
			vec = Vec2(visibleSize.width*0.7f, hero->getPositionY());
		else if(size == 1)
			vec = Vec2(visibleSize.width*0.3f, hero->getPositionY());

		this->runAction(Sequence::create(
			DelayTime::create(2.0f),
			MoveTo::create(1.0f, vec),
		NULL));
		SoundManager::getInstance()->playMySoundLogic("ThankYou");

	}
	else
	{
		// beep sound
		SoundManager::getInstance()->playMySoundLogic("X");
	}
}

void HelperMan::ThankYou()
{
	auto effectManager = (EffectManager*) layer->getChildByName("EffectManager");
	float tempSize = visibleSize.height*0.078125;
	auto vec = Vec2(tempSize, tempSize);
	effectManager->ThankyouEffect(this->getPosition() + vec);
}

void HelperMan::pause()
{
	Node::pause();
}
void HelperMan::resume()
{
	Node::resume();
}

void HelperMan::update(float dt)
{

}

void HelperMan::RemoveAll()
{
	//this->removeAllChildrenWithCleanup(true);
	this->removeFromParentAndCleanup(true);
//	layer->removeChild(this);
}

void HelperMan::AIBeforeBattle()
{

}
void HelperMan::AIDoingBattle()
{

}
void HelperMan::AIAfterBattle()
{

}

void HelperMan::Swing()
{
	auto act = CSLoader::createTimeline(String::createWithFormat("HelperMan/%s/%s.csb", _name.c_str(), _name.c_str())->getCString());
	act->gotoFrameAndPlay(60, 120, false);
	node->runAction(act);

	this->runAction(Sequence::create(
		DelayTime::create(1.0f),
		CallFunc::create(std::bind(&HelperMan::Stay, this)),
		NULL));
}

void HelperMan::Stay()
{
	auto act = CSLoader::createTimeline(String::createWithFormat("HelperMan/%s/%s.csb", _name.c_str(), _name.c_str())->getCString());
	act->gotoFrameAndPlay(0, 60, true);
	node->runAction(act);
}
