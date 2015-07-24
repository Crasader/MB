#include "EndingScene.h"

USING_NS_CC;
using namespace ui;

int ESendingNum = 0;
Scene* EndingScene::createScene(int endingNum)
{
	ESendingNum = endingNum;
    // 'scene' is an autorelease object
	auto scene = Scene::create();
    
    // 'layer' is an autorelease object
	auto layer = EndingScene::create();
	
    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool EndingScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
	
	SoundManager::getInstance()->changeBG("EndingBG");

	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = CC_CALLBACK_2(EndingScene::onTouchBegan, this);
	touchListener->onTouchCancelled = CC_CALLBACK_2(EndingScene::onTouchCancelled, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(EndingScene::onTouchEnded, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(EndingScene::onTouchMoved, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	node = CSLoader::createNode(String::createWithFormat("EndingScene/Ending%d/Ending.csb", ESendingNum)->getCString());
	//node->setPosition(origin);
	addChild(node);

	switch (ESendingNum)
	{
	case 1 :
		frame = node->getChildByName("frame");
		bg1 = node->getChildByName("bg1");
		bg2 = node->getChildByName("bg2");
		bg3 = node->getChildByName("bg3");

		obj1 = node->getChildByName("hero1");
		obj2 = node->getChildByName("hero1arms");
		obj3 = node->getChildByName("half2");
		obj4 = node->getChildByName("half3");
		obj5 = node->getChildByName("half4");
		obj6 = node->getChildByName("hero4");
		obj7 = node->getChildByName("mark");

		initOpacity();
		break;
	case 2 :
		frame = node->getChildByName("frame");
		bg1 = node->getChildByName("bg1");
		bg2 = node->getChildByName("bg2");

		obj1 = node->getChildByName("hand1");
		obj2 = node->getChildByName("text");

		obj3 = node->getChildByName("hand2");
		obj4 = node->getChildByName("hero");
		obj5 = node->getChildByName("wing");
		obj6 = node->getChildByName("mark");

		initOpacity();
		break;
	case 3:
		frame = node->getChildByName("frame");
		bg1 = node->getChildByName("bg1");
		bg2 = node->getChildByName("bg2");
		bg3 = node->getChildByName("bg3");

		obj1 = node->getChildByName("etc");
		obj2 = node->getChildByName("half1");

		obj3 = node->getChildByName("sword2");
		obj4 = node->getChildByName("effect");

		obj5 = node->getChildByName("orc");
		obj6 = node->getChildByName("half2");

		initOpacity();
		break;
	case 4:
		frame = node->getChildByName("frame");
		bg1 = node->getChildByName("bg1");
		bg2 = node->getChildByName("bg2");

		obj1 = node->getChildByName("angel");
		obj2 = node->getChildByName("crown1");
		obj3 = node->getChildByName("hero1");

		obj4 = node->getChildByName("wing");
		obj5 = node->getChildByName("hero2");
		obj6 = node->getChildByName("hero3");

		obj7 = node->getChildByName("crown2b");
		obj8 = node->getChildByName("crown2f");

		initOpacity();
		break;
	case 5:
		frame = node->getChildByName("frame");

		bg1 = node->getChildByName("bg1");
		bg2 = node->getChildByName("bg2");
		bg3 = node->getChildByName("bg3");

		obj1 = node->getChildByName("etc1");
		obj2 = node->getChildByName("half1");
		obj3 = node->getChildByName("kid1");

		obj4 = node->getChildByName("etc2");
		obj5 = node->getChildByName("half2");
		obj6 = node->getChildByName("kid2");

		obj7 = node->getChildByName("frame2");
		obj8 = node->getChildByName("half3");
		obj9 = node->getChildByName("wing");
		obj10 = node->getChildByName("mark");

		initOpacity();
		break;
	case 6:
		frame = node->getChildByName("frame");

		bg1 = node->getChildByName("bg1");
		bg2 = node->getChildByName("bg2");

		obj1 = node->getChildByName("half1");
		obj2 = node->getChildByName("half2");
		obj3 = node->getChildByName("es");
		obj4 = node->getChildByName("hs");
		obj5 = node->getChildByName("H");


		obj6 = node->getChildByName("hero");
		obj7 = node->getChildByName("hf");
		obj8 = node->getChildByName("orc");

		obj9 = node->getChildByName("kid1");
		obj10 = node->getChildByName("kid2");

		initOpacity();
		break;
	}

	animate1();

	// skip button add click event listener
	skipBtn = static_cast<cocos2d::ui::Button*>(node->getChildByName("skipBtn"));
	skipBtn->setUserData(this);
	struct callBackFunctorSkip
	{
		void operator() (Ref* sender) const
		{
			auto obj = (EndingScene*)((Button*)(sender))->getUserData();
			obj->saveDataLogic();

			auto scene = MainMenuScene::createScene();
			Director::getInstance()->replaceScene(TransitionFade::create(0.5, scene));
		}
	};
	Widget::ccWidgetClickCallback callBackSkip = callBackFunctorSkip();
	skipBtn->addClickEventListener(callBackSkip);

	return true;
}
void EndingScene::initOpacity()
{
	if (bg1 != nullptr) bg1->setOpacity(0);
	if (bg2 != nullptr) bg2->setOpacity(0);
	if (bg3 != nullptr) bg3->setOpacity(0);
	if (obj1 != nullptr) obj1->setOpacity(0);
	if (obj2 != nullptr) obj2->setOpacity(0);
	if (obj3 != nullptr) obj3->setOpacity(0);
	if (obj4 != nullptr) obj4->setOpacity(0);
	if (obj5 != nullptr) obj5->setOpacity(0);
	if (obj6 != nullptr) obj6->setOpacity(0);
	if (obj7 != nullptr) obj7->setOpacity(0);
	if (obj8 != nullptr) obj8->setOpacity(0);
	if (obj9 != nullptr) obj9->setOpacity(0);
	if (obj10 != nullptr) obj10->setOpacity(0);
}

bool EndingScene::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
	return true;
}
void EndingScene::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event)
{

}
void EndingScene::onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *event)
{

}
void EndingScene::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event)
{
	switch (state)
	{
	case 0:
		clickAnimate1();
		break;
	case 1:
		clickAnimate2();
		break;
	case 2:
		clickAnimate3();
		break;
	case 3:
		clickAnimate4();
		break;
	case 4:
		moveMainMenu();
		break;
	}
}

void EndingScene::animate1()
{
	switch (ESendingNum)
	{
	case 1:
		bg1->runAction(
			Sequence::create(
			DelayTime::create(1.0f),
			FadeIn::create(0.5f),
			NULL
			));

		obj1->runAction(
			Sequence::create(
			DelayTime::create(1.5f),
			FadeIn::create(0.5f),
			NULL
			));

		obj2->runAction(
			Sequence::create(
			DelayTime::create(1.5f),
			FadeIn::create(0.5f),
			DelayTime::create(1.0f),
			CallFunc::create(std::bind(&EndingScene::setState, this, 1)),
			CallFunc::create(std::bind(&EndingScene::animate2, this)),
			NULL
			));
		break;
	case 2:
		bg1->runAction(
			Sequence::create(
			DelayTime::create(1.0f),
			FadeIn::create(0.5f),
			NULL
			));
		obj1->setPosition(Vec2(visibleSize.width + obj1->getContentSize().width, obj1->getPositionY()));
		obj1->setOpacity(255);
		obj1->runAction(
			Sequence::create(
			DelayTime::create(1.0f),
			MoveBy::create(0.5f, Vec2(-obj1->getContentSize().width, 0)),
			FadeIn::create(0.5f),
			NULL
			));

		obj2->runAction(
			Sequence::create(
			DelayTime::create(1.5f),
			FadeIn::create(0.5f),
			DelayTime::create(1.0f),
			CallFunc::create(std::bind(&EndingScene::setState, this, 1)),
			CallFunc::create(std::bind(&EndingScene::animate2, this)),
			NULL
			));
		break;
	case 3:
	{
		bg1->runAction(
			Sequence::create(
			DelayTime::create(1.0f),
			FadeIn::create(0.5f),
			NULL
			));

		obj1->runAction(
			Sequence::create(
			DelayTime::create(1.0f),
			FadeIn::create(0.5f),
			NULL
			));

		auto s = obj2->getChildByName("sword");
		auto h = obj2->getChildByName("half1_body")->getChildByName("hero");
		h->setOpacity(0);
		s->setOpacity(0);

		obj2->setPosition(Vec2(-visibleSize.width * 0.5f, 0));

		obj2->runAction(
			Sequence::create(
			DelayTime::create(1.5f),
			FadeIn::create(0.5f),
			MoveTo::create(1.0f, Vec2::ZERO),
			NULL
			));

		h->runAction(
			Sequence::create(
			DelayTime::create(2.5f),
			FadeIn::create(0.5f),
			DelayTime::create(0.25f),
			FadeOut::create(0.25f),
			DelayTime::create(0.25f),
			FadeIn::create(0.5f),
			FadeOut::create(0.5f),
			DelayTime::create(0.25f),
			FadeIn::create(0.5f),
			FadeOut::create(0.25f),
			NULL
			));

		s->runAction(
			Sequence::create(
			DelayTime::create(6.25f),
			FadeIn::create(0.5f),
			DelayTime::create(1.0f),
			CallFunc::create(std::bind(&EndingScene::setState, this, 1)),
			CallFunc::create(std::bind(&EndingScene::animate2, this)),
			NULL
			));
	}
		break;
	case 4:
	{
		bg1->runAction(
			Sequence::create(
			DelayTime::create(1.0f),
			FadeIn::create(0.5f),
			NULL
			));

		obj1->runAction(
			Sequence::create(
			DelayTime::create(1.5f),
			FadeIn::create(0.5f),
			NULL
			));


		tempVec = obj2->getPosition();
		obj2->setPosition(obj1->getPosition());
		obj2->runAction(
			Sequence::create(
			DelayTime::create(1.5f),
			Spawn::create(FadeIn::create(0.5f),
			MoveTo::create(0.5f, tempVec),
			RotateBy::create(0.5f,-360),
			NULL
			),
			NULL
			));

		obj3->runAction(
			Sequence::create(
			DelayTime::create(2.5f),
			FadeIn::create(0.5f),
			DelayTime::create(1.0f),
			CallFunc::create(std::bind(&EndingScene::setState, this, 1)),
			CallFunc::create(std::bind(&EndingScene::animate2, this)),
			NULL
			));
	}
		break;
	case 5:
	{
		bg1->runAction(
			Sequence::create(
			DelayTime::create(1.0f),
			FadeIn::create(0.5f),
			NULL
			));

		obj1->runAction(
			Sequence::create(
			DelayTime::create(1.0f),
			FadeIn::create(0.5f),
			NULL
			));

		tempVec = obj2->getPosition();
		obj2->setPosition(0, obj2->getPositionY());
		obj2->runAction(
			Sequence::create(
			DelayTime::create(1.5f),
			Spawn::create(FadeIn::create(0.5f),
			MoveTo::create(1.0f, tempVec),
			NULL),
			NULL
			));


		obj3->runAction(
			Sequence::create(
			DelayTime::create(3.0f),
			FadeIn::create(1.0f),
			DelayTime::create(1.0f),
			CallFunc::create(std::bind(&EndingScene::setState, this, 1)),
			CallFunc::create(std::bind(&EndingScene::animate2, this)),
			NULL
			));
	}
		break;
	case 6:
		bg1->runAction(
			Sequence::create(
			DelayTime::create(1.0f),
			FadeIn::create(0.5f),
			NULL
			));

		obj1->runAction(
			Sequence::create(
			DelayTime::create(1.0f),
			FadeIn::create(0.5f),
			NULL
			));
		obj4->runAction(
			Sequence::create(
			DelayTime::create(2.0f),
			FadeIn::create(1.0f),
			NULL
			));
		obj5->runAction(
			Sequence::create(
			DelayTime::create(1.0f),
			FadeIn::create(0.5f),
			NULL
			));


		obj2->runAction(
			Sequence::create(
			DelayTime::create(2.5f),
			FadeIn::create(0.5f),
			NULL
			));
		obj3->runAction(
			Sequence::create(
			DelayTime::create(3.5f),
			FadeIn::create(1.0f),
			DelayTime::create(1.0f),
			CallFunc::create(std::bind(&EndingScene::setState, this, 1)),
			CallFunc::create(std::bind(&EndingScene::animate2, this)),
			NULL
			));

		break;
	}

}
void EndingScene::animate2()
{
	switch (ESendingNum)
	{
	case 1:
		bg2->runAction(
			Sequence::create(
			DelayTime::create(0.5f),
			FadeIn::create(0.5f),
			NULL
			));

		obj3->runAction(
			Sequence::create(
			DelayTime::create(1.5f),
			FadeIn::create(1.0f),
			DelayTime::create(1.5f),
			CallFunc::create(std::bind(&EndingScene::setState, this, 2)),
			CallFunc::create(std::bind(&EndingScene::animate3, this)),
			NULL
			));
		break;
	case 2:
		bg2->runAction(
			Sequence::create(
			DelayTime::create(0.5f),
			FadeIn::create(0.5f),
			NULL
			));
		// hand
		obj3->setPosition(Vec2(visibleSize.width + obj1->getContentSize().width, obj3->getPositionY()));
		obj3->setOpacity(255);
		obj3->runAction(
			Sequence::create(
			DelayTime::create(0.5f),
			MoveBy::create(0.5f, Vec2(-obj3->getContentSize().width, 0)),
			NULL
			));
		// hero
		obj4->runAction(
			Sequence::create(
			DelayTime::create(1.5f),
			FadeIn::create(0.5f),
			NULL
			));
		// wing
		obj5->runAction(
			Sequence::create(
			DelayTime::create(1.5f),
			FadeIn::create(0.5f),
			NULL
			));
		obj5->runAction(RepeatForever::create(Sequence::create(MoveBy::create(1.0f, Vec2(0, visibleSize.height * 0.05f)), MoveBy::create(1.0f, Vec2(0, -visibleSize.height * 0.05f)), NULL)));
		// mark
		obj6->runAction(
			Sequence::create(
			DelayTime::create(2.0f),
			FadeIn::create(0.5f),
			DelayTime::create(1.0f),
			CallFunc::create(std::bind(&EndingScene::setState, this, 4)),
			NULL
			));
		break;
	case 3:
		bg2->runAction(
			Sequence::create(
			DelayTime::create(0.5f),
			FadeIn::create(0.5f),
			NULL
			));

		obj3->runAction(
			Sequence::create(
			DelayTime::create(1.0f),
			FadeIn::create(0.5f),
			NULL
			));

		obj4->runAction(
			Sequence::create(
			DelayTime::create(1.5f),
			FadeIn::create(0.5f),
			DelayTime::create(1.5f),
			CallFunc::create(std::bind(&EndingScene::setState, this, 2)),
			CallFunc::create(std::bind(&EndingScene::animate3, this)),
			NULL
			));
		break;
	case 4:
	{
		bg2->runAction(
			Sequence::create(
			DelayTime::create(0.5f),
			FadeIn::create(0.5f),
			NULL
			));

		obj5->runAction(
			Sequence::create(
			DelayTime::create(1.0f),
			FadeIn::create(0.5f),
			DelayTime::create(1.5f),
			FadeOut::create(1.0f),
			NULL
			));

		obj4->runAction(
			Sequence::create(
			DelayTime::create(1.0f),
			FadeIn::create(0.5f),
			NULL
			));

		obj4->runAction(RepeatForever::create(Sequence::create(MoveBy::create(1.0f, Vec2(0, visibleSize.height * 0.05f)), MoveBy::create(1.0f, Vec2(0, -visibleSize.height * 0.05f)), NULL)));

		obj7->runAction(
			Sequence::create(
			DelayTime::create(2.0f),
			FadeIn::create(0.5f),
			NULL
			));

		obj8->runAction(
			Sequence::create(
			DelayTime::create(2.0f),
			FadeIn::create(0.5f),
			NULL
			));

		obj6->runAction(
			Sequence::create(
			DelayTime::create(3.0f),
			FadeIn::create(1.0f),
			DelayTime::create(1.5f),
			CallFunc::create(std::bind(&EndingScene::setState, this, 4)),
			NULL
			));
	}
		break;
	case 5:
	{
		bg2->runAction(
			Sequence::create(
			DelayTime::create(1.0f),
			FadeIn::create(0.5f),
			NULL
			));

		obj4->runAction(
			Sequence::create(
			DelayTime::create(1.0f),
			FadeIn::create(0.5f),
			NULL
			));

		tempVec = obj5->getPosition();
		obj5->setPosition(0, obj5->getPositionY());
		obj5->runAction(
			Sequence::create(
			DelayTime::create(1.5f),
			Spawn::create(FadeIn::create(0.5f),
			MoveTo::create(1.0f, tempVec),
			NULL),
			NULL
			));


		obj6->runAction(
			Sequence::create(
			DelayTime::create(3.0f),
			FadeIn::create(1.0f),
			DelayTime::create(1.0f),
			CallFunc::create(std::bind(&EndingScene::setState, this, 2)),
			CallFunc::create(std::bind(&EndingScene::animate3, this)),
			NULL
			));
	}
		break;
	case 6:
	{
		// fade out
		obj1->runAction(
			Sequence::create(
			DelayTime::create(0.5f),
			FadeOut::create(1.0f),
			NULL
			));
		obj5->runAction(
			Sequence::create(
			DelayTime::create(0.5f),
			FadeOut::create(1.0f),
			NULL
			));

		// fade in
		obj6->runAction(
			Sequence::create(
			DelayTime::create(0.5f),
			FadeIn::create(1.0f),
			NULL
			));
		obj7->runAction(
			Sequence::create(
			DelayTime::create(0.5f),
			FadeIn::create(1.0f),
			DelayTime::create(3.5f),
			FadeOut::create(1.0f),
			NULL
			));

		// fade out
		obj2->runAction(
			Sequence::create(
			DelayTime::create(2.0f),
			FadeOut::create(1.0f),
			NULL
			));
		// fade in
		obj8->runAction(
			Sequence::create(
			DelayTime::create(2.0f),
			FadeIn::create(1.0f),
			NULL
			));

		// 3, 4, 7
		obj3->runAction(
			Sequence::create(
			DelayTime::create(4.0f),
			FadeOut::create(1.0f),
			NULL
			));
		obj4->runAction(
			Sequence::create(
			DelayTime::create(5.0f),
			FadeOut::create(1.0f),
			NULL
			));

		bg2->runAction(
			Sequence::create(
			DelayTime::create(6.0f),
			FadeIn::create(1.0f),
			DelayTime::create(1.0f),
			CallFunc::create(std::bind(&EndingScene::setState, this, 2)),
			CallFunc::create(std::bind(&EndingScene::animate3, this)),
			NULL
			));

	}
		break;
	}
}
void EndingScene::animate3()
{
	switch (ESendingNum)
	{
	case 1:
		bg3->runAction(
			Sequence::create(
			DelayTime::create(0.5f),
			FadeIn::create(0.5f),
			NULL
			));
		obj4->runAction(
			Sequence::create(
			DelayTime::create(1.5f),
			FadeIn::create(1.0f),
			DelayTime::create(1.5f),
			CallFunc::create(std::bind(&EndingScene::setState, this, 3)),
			CallFunc::create(std::bind(&EndingScene::animate4, this)),
			NULL
			));
		break;
	case 2:
		break;
	case 3:
	{
		bg3->runAction(
			Sequence::create(
			DelayTime::create(0.5f),
			FadeIn::create(0.5f),
			NULL
			));

		// moveTo
		obj6->setPosition(visibleSize.width *0.5f, obj6->getPositionY());
		obj6->runAction(
			Sequence::create(
			DelayTime::create(1.0f),
			FadeIn::create(0.5f),
			MoveTo::create(1.5f, Vec2(visibleSize.width, obj6->getPositionY())),
			NULL
			));

		auto a1 = obj5->getChildByName("orc_arm1");
		auto a2 = obj5->getChildByName("orc_arm2");
		auto f = obj5->getChildByName("orc_face");

		f->setOpacity(0);
		a2->setOpacity(0);

		obj5->setPosition(Vec2(-visibleSize.width * 0.5f, 0));

		obj5->runAction(
			Sequence::create(
			DelayTime::create(3.0f),
			FadeIn::create(0.5f),
			MoveTo::create(1.0f, Vec2::ZERO),
			NULL
			));


		a1->runAction(
			Sequence::create(
			DelayTime::create(5.0f),
			FadeOut::create(0.5f),
			NULL
			));

		a2->runAction(
			Sequence::create(
			DelayTime::create(5.0f),
			FadeIn::create(0.5f),
			NULL
			));

		f->runAction(
			Sequence::create(
			DelayTime::create(5.0f),
			FadeIn::create(0.5f),
			DelayTime::create(1.0f),
			CallFunc::create(std::bind(&EndingScene::setState, this, 4)),
			NULL
			));
	}
		break;
	case 4:
		break;
	case 5:
	{
		bg3->runAction(
			Sequence::create(
			DelayTime::create(0.5f),
			FadeIn::create(0.5f),
			NULL
			));
		obj7->runAction(
			Sequence::create(
			DelayTime::create(0.5f),
			FadeIn::create(0.5f),
			NULL
			));
		// half
		obj8->runAction(
			Sequence::create(
			DelayTime::create(1.5f),
			FadeIn::create(0.5f),
			NULL
			));
		// wing
		obj9->runAction(
			Sequence::create(
			DelayTime::create(1.5f),
			FadeIn::create(0.5f),
			NULL
			));
		obj9->runAction(RepeatForever::create(Sequence::create(MoveBy::create(1.0f, Vec2(0, visibleSize.height * 0.05f)), MoveBy::create(1.0f, Vec2(0, -visibleSize.height * 0.05f)), NULL)));
		// mark
		obj10->runAction(
			Sequence::create(
			DelayTime::create(2.0f),
			FadeIn::create(0.5f),
			DelayTime::create(1.0f),
			CallFunc::create(std::bind(&EndingScene::setState, this, 4)),
			NULL
			));
	}
		break;
	case 6:
	{
		// 6, 8
		obj6->runAction(
			Sequence::create(
			DelayTime::create(1.0f),
			FadeOut::create(1.0f),
			NULL
			));
		obj8->runAction(
			Sequence::create(
			DelayTime::create(2.0f),
			FadeOut::create(1.0f),
			NULL
			));

		// 9, 10
		obj9->runAction(
			Sequence::create(
			DelayTime::create(1.0f),
			FadeIn::create(1.0f),
			NULL
			));
		obj10->runAction(
			Sequence::create(
			DelayTime::create(2.0f),
			FadeIn::create(1.0f),
			NULL
			));

		auto k1f1 = obj9->getChildByName("k1f1");
		auto k1f2 = obj9->getChildByName("k1f2");
		auto k1a = obj9->getChildByName("k1a");

		auto k2f1 = obj10->getChildByName("k2f1");
		auto k2f2 = obj10->getChildByName("k2f2");
		auto k2a = obj10->getChildByName("k2a");

		k1f2->setOpacity(0);
		k1a->setOpacity(0);

		k2f2->setOpacity(0);
		k2a->setOpacity(0);

		// face & arm
		k1f1->runAction(
			Sequence::create(
			DelayTime::create(4.0f),
			FadeOut::create(1.0f),
			NULL
			));
		k1f2->runAction(
			Sequence::create(
			DelayTime::create(5.0f),
			FadeIn::create(1.0f),
			NULL
			));
		k1a->runAction(
			Sequence::create(
			DelayTime::create(5.0f),
			FadeIn::create(1.0f),
			NULL
			));

		k2f1->runAction(
			Sequence::create(
			DelayTime::create(6.0f),
			FadeOut::create(1.0f),
			NULL
			));
		k2f2->runAction(
			Sequence::create(
			DelayTime::create(7.0f),
			FadeIn::create(1.0f),
			NULL
			));
		k2a->runAction(
			Sequence::create(
			DelayTime::create(7.0f),
			FadeIn::create(1.0f),
			DelayTime::create(1.0f),
			CallFunc::create(std::bind(&EndingScene::setState, this, 4)),
			NULL
			));
	}
		break;
	}

}
void EndingScene::animate4()
{
	switch (ESendingNum)
	{
	case 1:
		// half
		obj5->runAction(
			Sequence::create(
			DelayTime::create(0.5f),
			FadeIn::create(0.5f),
			NULL
			));
		obj5->runAction(RepeatForever::create(Sequence::create(RotateBy::create(1.0f, -15.0f), RotateBy::create(1.0f, 15.0f), NULL)));
		// hero
		obj6->runAction(
			Sequence::create(
			DelayTime::create(1.0f),
			FadeIn::create(0.5f),
			NULL
			));
		obj6->runAction(RepeatForever::create(Sequence::create(RotateBy::create(1.0f, 15.0f), RotateBy::create(1.0f, -15.0f), NULL)));
		// mark
		obj7->runAction(
			Sequence::create(
			DelayTime::create(1.5f),
			FadeIn::create(0.5f),
			CallFunc::create(std::bind(&EndingScene::setState, this, 4)),
			NULL
			));
		break;
	case 2:
		break;
	case 3:
		break;
	case 4:
		break;
	case 5:
		break;
	case 6:
		break;
	}
}
void EndingScene::moveMainMenu()
{
	saveDataLogic();

	auto scene = MainMenuScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(0.5, scene));
}

void EndingScene::setState(int state)
{
	this->state = state;
}

void EndingScene::clickAnimate1()
{
	switch (ESendingNum)
	{
	case 1:
		myStopAllActions();
		bg1->setOpacity(255);
		obj1->setOpacity(255);
		obj2->setOpacity(255);
		state = 1;
		animate2();
		break;
	case 2:
		myStopAllActions();
		bg1->setOpacity(255);
		obj1->setOpacity(255);
		obj2->setOpacity(255);
		obj1->setPosition(Vec2(visibleSize.width, obj1->getPositionY()));
		state = 1;
		animate2();
		break;
	case 3:
	{
		myStopAllActions();
		bg1->setOpacity(255);
		obj1->setOpacity(255);
		obj2->setPosition(Vec2::ZERO);
		obj2->setOpacity(255);

		auto s = obj2->getChildByName("sword");
		auto h = obj2->getChildByName("half1_body")->getChildByName("hero");
		s->stopAllActions();
		h->stopAllActions();
		s->setOpacity(255);
		h->setOpacity(0);		

		state = 1;
		animate2();
	}
		break;
	case 4:
	{
		myStopAllActions();
		bg1->setOpacity(255);
		obj1->setOpacity(255);
		obj2->setOpacity(255);
		obj3->setOpacity(255);
		obj2->setPosition(Vec2::ZERO);
		obj2->setPosition(tempVec);
		obj2->setRotation(0);

		state = 1;
		animate2();
	}
		break;
	case 5:
	{
		myStopAllActions();
		bg1->setOpacity(255);
		obj1->setOpacity(255);
		obj2->setOpacity(255);
		obj3->setOpacity(255);

		obj2->setPosition(tempVec);

		state = 1;
		animate2();
	}
		break;
	case 6:
	{
		myStopAllActions();
		bg1->setOpacity(255);

		obj1->setOpacity(255);
		obj2->setOpacity(255);
		obj3->setOpacity(255);
		obj4->setOpacity(255);
		obj5->setOpacity(255);

		state = 1;
		animate2();
	}
		break;
	}

}
void EndingScene::clickAnimate2()
{
	switch (ESendingNum)
	{
	case 1:
		myStopAllActions();
		bg2->setOpacity(255);
		obj3->setOpacity(255);
		state = 2;
		animate3();
		break;
	case 2:
		myStopAllActions();
		bg2->setOpacity(255);
		obj3->setOpacity(255);
		obj4->setOpacity(255);
		obj5->setOpacity(255);
		obj6->setOpacity(255);
		obj3->setPosition(Vec2(visibleSize.width, obj3->getPositionY()));

		state = 4;
		break;
	case 3:
		myStopAllActions();
		bg2->setOpacity(255);
		obj3->setOpacity(255);
		obj4->setOpacity(255);
		state = 2;
		animate3();
		break;
	case 4:
	{
		myStopAllActions();
		bg2->setOpacity(255);
		obj4->setOpacity(255);
		obj5->setOpacity(0);
		obj6->setOpacity(255);
		obj7->setOpacity(255);
		obj8->setOpacity(255);

		state = 4;
	}
		break;
	case 5:
	{
		myStopAllActions();
		bg2->setOpacity(255);
		obj4->setOpacity(255);
		obj5->setOpacity(255);
		obj6->setOpacity(255);

		obj5->setPosition(tempVec);

		state = 2;
		animate3();
	}
		break;
	case 6:
	{
		myStopAllActions();
		bg2->setOpacity(255);

		obj1->setOpacity(0);
		obj2->setOpacity(0);
		obj3->setOpacity(0);
		obj4->setOpacity(0);
		obj5->setOpacity(0);
		obj6->setOpacity(255);
		obj7->setOpacity(0);
		obj8->setOpacity(255);

		state = 2;
		animate3();
	}
		break;
	}
}
void EndingScene::clickAnimate3()
{
	switch (ESendingNum)
	{
	case 1:
		myStopAllActions();
		bg3->setOpacity(255);
		obj4->setOpacity(255);
		state = 3;
		animate4();
		break;
	case 2:
		break;
	case 3:
	{
		myStopAllActions();
		bg3->setOpacity(255);
		obj5->setOpacity(255);
		obj6->setOpacity(255);
		obj6->setPosition(visibleSize.width, obj6->getPositionY());

		auto a1 = obj5->getChildByName("orc_arm1");
		auto a2 = obj5->getChildByName("orc_arm2");
		auto f = obj5->getChildByName("orc_face");
		a1->stopAllActions();
		a2->stopAllActions();
		f->stopAllActions();

		f->setOpacity(255);
		a1->setOpacity(0);
		a2->setOpacity(255);

		obj5->setPosition(Vec2::ZERO);

		state = 4;
	}
		break;
	case 4:
		break;
	case 5:
		myStopAllActions();
		bg3->setOpacity(255);
		obj7->setOpacity(255);
		obj8->setOpacity(255);
		obj9->setOpacity(255);
		obj10->setOpacity(255);

		state = 4;
		break;
	case 6:
	{
		myStopAllActions();

		obj6->setOpacity(0);
		obj8->setOpacity(0);
		obj9->setOpacity(255);
		obj10->setOpacity(255);

		auto k1f1 = obj9->getChildByName("k1f1");
		auto k1f2 = obj9->getChildByName("k1f2");
		auto k1a = obj9->getChildByName("k1a");

		auto k2f1 = obj10->getChildByName("k2f1");
		auto k2f2 = obj10->getChildByName("k2f2");
		auto k2a = obj10->getChildByName("k2a");

		k1f1->stopAllActions();
		k1f2->stopAllActions();
		k1a->stopAllActions();

		k2f1->stopAllActions();
		k2f2->stopAllActions();
		k2a->stopAllActions();

		k1f1->setOpacity(0);
		k1f2->setOpacity(255);
		k1a->setOpacity(255);

		k2f1->setOpacity(0);
		k2f2->setOpacity(255);
		k2a->setOpacity(255);

		state = 4;
	}
		break;
	}
}
void EndingScene::clickAnimate4()
{
	switch (ESendingNum)
	{
	case 1:
		myStopAllActions();
		obj5->setOpacity(255);
		obj6->setOpacity(255);
		obj7->setOpacity(255);
		state = 4;
		break;
	case 2:
		break;
	case 3:
		break;
	case 4:
		break;
	case 5:
		break;
	case 6:
		break;
	}
}

void EndingScene::myStopAllActions()
{
	if (bg1 != nullptr) bg1->stopAllActions();
	if (bg2 != nullptr) bg2->stopAllActions();
	if (bg3 != nullptr) bg3->stopAllActions();
	if (obj1 != nullptr) obj1->stopAllActions();
	if (obj2 != nullptr) obj2->stopAllActions();
	if (obj3 != nullptr) obj3->stopAllActions();
	if (obj4 != nullptr) obj4->stopAllActions();
	if (obj5 != nullptr) obj5->stopAllActions();
	if (obj6 != nullptr) obj6->stopAllActions();
	if (obj7 != nullptr) obj7->stopAllActions();
	if (obj8 != nullptr) obj8->stopAllActions();
	if (obj9 != nullptr) obj9->stopAllActions();
	if (obj10 != nullptr) obj10->stopAllActions();
}

void EndingScene::saveDataLogic()
{
	auto def = UserDefault::sharedUserDefault();
	int temp = def->getIntegerForKey("u_ending");
	if (temp < ESendingNum)
	{
		def->setIntegerForKey("u_ending", ESendingNum);
		def->setBoolForKey("saveState", false);
		auto um = UnlockManager::getInstace();
		if (ESendingNum == 1)
		{
			um->addUnlockData(UNLOCK_ENDING_1);
			um->addUnlockData(UNLOCK_MC);
			um->addUnlockData(UNLOCK_BLACK_AND_WHITE);
		}else if (ESendingNum == 2)
		{
			um->addUnlockData(UNLOCK_ENDING_2);
			um->addUnlockData(UNLOCK_HV);
		}else if (ESendingNum == 3)
		{
			um->addUnlockData(UNLOCK_ENDING_3);
			um->addUnlockData(UNLOCK_HC);
		}else if (ESendingNum == 4)
		{
			um->addUnlockData(UNLOCK_ENDING_4);
		}
		else if (ESendingNum == 5)
		{
			um->addUnlockData(UNLOCK_ENDING_5);
			um->addUnlockData(UNLOCK_MM);
			um->addUnlockData(UNLOCK_TRUTH);
		}
		else if (ESendingNum == 6)
		{
			um->addUnlockData(UNLOCK_ENDING_6);
		}

		def->flush();
	}

}

