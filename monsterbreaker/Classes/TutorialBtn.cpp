#include"TutorialBtn.h"
#include "Definitions.h"
#include "SimpleAudioEngine.h"
//#include "MyBodyParser.h"
USING_NS_CC;
using namespace ui;

TutorialBtn::TutorialBtn(cocos2d::Layer * layer, int btnType) : layer(layer), btnType(btnType)
{
	switch (btnType)
	{
	case myEnum::kTutorial::kAttack:
		btnTypeStr = "a";
		break;
	case myEnum::kTutorial::kMove:
		btnTypeStr = "m";
		break;
	case myEnum::kTutorial::kBomb:
		btnTypeStr = "b";
		break;
	case myEnum::kTutorial::kDamaged:
		btnTypeStr = "d";
		break;
	case myEnum::kTutorial::kSkill:
		btnTypeStr = "s";
		break;
	}
}

TutorialBtn::~TutorialBtn()
{

}

TutorialBtn* TutorialBtn::create(cocos2d::Layer * layer, int btnType)
{
	auto pNode = new TutorialBtn(layer, btnType);
	pNode->autorelease();
	pNode->InitSprite();
	return pNode;
}

void TutorialBtn::InitSprite()
{
	node = CSLoader::createNode("Tutorial/Btn.csb");
	img = (Sprite*)node->getChildByName("img");
	btn = (Button*)node->getChildByName("btn");
	
	btn->setUserData(this);
	auto cache = SpriteFrameCache::getInstance();
	img->setDisplayFrame(cache->getSpriteFrameByName(String::createWithFormat("Tutorial/%s.png", btnTypeStr.c_str())->getCString()));

	addChild(node);
//	c->setVisible(false);
	
}
void TutorialBtn::RemoveAll()
{
	this->removeFromParentAndCleanup(true);
}

cocos2d::Size TutorialBtn::getContentSize()
{
//	auto spr = l->getChildByName("skill10_1");
	return btn->getContentSize();
}

void TutorialBtn::pause()
{
	Node::pause();
	node->pause();
	//c->pause();
}

void TutorialBtn::resume()
{
	Node::resume();
	node->resume();
	//c->resume();
}

