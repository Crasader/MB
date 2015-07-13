#include "PrologScene.h"

USING_NS_CC;
using namespace ui;

Scene* PrologScene::createScene()
{

    // 'scene' is an autorelease object
	auto scene = Scene::create();
    
    // 'layer' is an autorelease object
	auto layer = PrologScene::create();
	
    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool PrologScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
	
	SoundManager::getInstance()->changeBG("PrologBG");

	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = CC_CALLBACK_2(PrologScene::onTouchBegan, this);
	touchListener->onTouchCancelled = CC_CALLBACK_2(PrologScene::onTouchCancelled, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(PrologScene::onTouchEnded, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(PrologScene::onTouchMoved, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	node = CSLoader::createNode("Prolog/Prolog.csb");
	addChild(node);

	frame = node->getChildByName("frame");
	bg1 = node->getChildByName("bg1");
	bg2 = node->getChildByName("bg2");
	bg3 = node->getChildByName("bg3");
	bg4 = node->getChildByName("bg4");

	hero1 = node->getChildByName("hero1");
	hero2 = node->getChildByName("hero2");
	half1 = node->getChildByName("half1");
	half2 = node->getChildByName("half2");
	heroFace = node->getChildByName("heroFace");
	skipBtn = static_cast<cocos2d::ui::Button*>(node->getChildByName("skipBtn"));

	bg1->setOpacity(0);
	bg2->setOpacity(0);
	bg3->setOpacity(0);
	bg4->setOpacity(0);
	hero1->setOpacity(0);
	hero2->setOpacity(0);
	half1->setOpacity(0);
	half2->setOpacity(0);
	heroFace->setOpacity(0);

	animate1();

	// skip button add click event listener
	struct callBackFunctorSkip
	{
		void operator() (Ref* sender) const
		{
			auto scene = MainMenuScene::createScene();
			Director::getInstance()->replaceScene(TransitionFade::create(0.5, scene));
		}
	};
	Widget::ccWidgetClickCallback callBackSkip = callBackFunctorSkip();
	skipBtn->addClickEventListener(callBackSkip);

	node->setPosition(origin);
	return true;
}

bool PrologScene::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
	return true;
}
void PrologScene::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event)
{

}
void PrologScene::onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *event)
{

}
void PrologScene::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event)
{
	switch (state)
	{
	case 0:
		node->stopAllActions();
		bg1->setOpacity(255);
		hero1->setOpacity(255);
		state = 1;
		animate2();
		break;
	case 1:
		node->stopAllActions();
		bg2->setOpacity(255);
		half1->setOpacity(255);
		state = 2;
		animate3();
		break;
	case 2:
		node->stopAllActions();
		half2->stopAllActions();
		bg3->setOpacity(255);
		half2->setOpacity(255);
		state = 3;
		animate4();
		break;
	case 3:
		node->stopAllActions();
		bg4->setOpacity(255);
		hero2->setOpacity(255);
		heroFace->setOpacity(255);
		state = 4;
		break;
	case 4:
		moveMainMenu();
		break;
	}
}

void PrologScene::animate1()
{
	// bg1
	bg1->runAction(
		Sequence::create(
		DelayTime::create(1.0f),
		FadeIn::create(0.5f),
		NULL
		));

	hero1->runAction(
		Sequence::create(
		DelayTime::create(1.5f),
		FadeIn::create(0.5f),
		DelayTime::create(1.0f),
		CallFunc::create(std::bind(&PrologScene::setState, this, 1)),
		CallFunc::create(std::bind(&PrologScene::animate2, this)),
		NULL
		));
}
void PrologScene::animate2()
{
	// bg2
	bg2->runAction(
		Sequence::create(
		DelayTime::create(0.5f),
		FadeIn::create(0.5f),
		NULL
		));

	half1->runAction(
		Sequence::create(
		DelayTime::create(3.0f),
		FadeIn::create(1.0f),
		DelayTime::create(2.0f),
		CallFunc::create(std::bind(&PrologScene::setState, this, 2)),
		CallFunc::create(std::bind(&PrologScene::animate3, this)),
		NULL
		));
}
void PrologScene::animate3()
{
	// bg3
	bg3->runAction(
		Sequence::create(
		DelayTime::create(0.5f),
		FadeIn::create(0.5f),
		NULL
		));
	auto spawn = Spawn::create(MoveTo::create(2.0f, Vec2(visibleSize.width*0.3f, visibleSize.height*0.25f)), ScaleTo::create(2.0f, 0.5f), NULL);
	half2->runAction(
		Sequence::create(
		DelayTime::create(1.0f),
		FadeIn::create(1.0f),
		spawn,
		DelayTime::create(1.0f),
		CallFunc::create(std::bind(&PrologScene::setState, this, 3)),
		CallFunc::create(std::bind(&PrologScene::animate4, this)),
		NULL
		));
}
void PrologScene::animate4()
{
	// bg4
	bg4->runAction(
		Sequence::create(
		DelayTime::create(0.5f),
		FadeIn::create(0.5f),
		NULL
		));

	hero2->runAction(
		Sequence::create(
		DelayTime::create(1.0f),
		FadeIn::create(1.0f),
		NULL
		));

	heroFace->runAction(
		Sequence::create(
		DelayTime::create(2.0f),
		FadeIn::create(0.5f),
		CallFunc::create(std::bind(&PrologScene::setState, this, 4)),
		NULL
		));
}
void PrologScene::moveMainMenu()
{
	auto scene = MainMenuScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(0.5, scene));
}

void PrologScene::setState(int state)
{
	this->state = state;
}
