#include "MainMenuScene.h"

USING_NS_CC;
using namespace ui;

Scene* MainMenuScene::createScene()
{
    // 'scene' is an autorelease object
	auto scene = Scene::create();
 //   auto scene = Scene::createWithPhysics();
	//scene->getPhysicsWorld()->setGravity(Vec2(0, 0));
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

    // 'layer' is an autorelease object
	auto layer = MainMenuScene::create();
	//layer->SetPhysicsWorld(scene->getPhysicsWorld());

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainMenuScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();

	this->setKeypadEnabled(true);

	//unlockManager = UnlockManager::create(this);
	unlockManager = UnlockManager::getInstace();

	LoadData();
	DrawNode();

	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = CC_CALLBACK_2(MainMenuScene::onTouchBegan, this);
	touchListener->onTouchCancelled = CC_CALLBACK_2(MainMenuScene::onTouchCancelled, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(MainMenuScene::onTouchEnded, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(MainMenuScene::onTouchMoved, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	originalTouchPosition = 0;
	initialTouchPos[0] = 0;
	initialTouchPos[1] = 0;
	currentTouchPos[0] = 0;
	currentTouchPos[1] = 0;

	auto cache = SpriteFrameCache::sharedSpriteFrameCache();
	cache->addSpriteFramesWithFile("Icon/Icon.plist", "Icon/Icon.png");

	for (int i = 0; i < 7; i++)
	{
		auto dotItem = Sprite::createWithSpriteFrameName(String::createWithFormat("Icon/%d.png", i)->getCString());
		if (_currentEndingNumber < i)
		{
			dotItem->setDisplayFrame(cache->getSpriteFrameByName("Icon/Lock.png"));
		}
		dotItem->setTag(i);
		dotItem->setScale(2);
		dotItem->setPosition(visibleSize.width / 8 * (1 + i), visibleSize.height * 0.1f);
		dotMenu[i] = dotItem;
		this->addChild(dotItem, 10000);
	}

	dotMenu[_currentEndingNumber]->setDisplayFrame(cache->spriteFrameByName(String::createWithFormat("Icon/%dc.png", _currentEndingNumber)->getCString()));

	auto def = UserDefault::sharedUserDefault();
	sp = def->getBoolForKey("speaker", true);
	def->setBoolForKey("speaker", sp);

	speaker = Sprite::createWithSpriteFrameName("Icon/speakerO.png");
	speaker->setPosition(visibleSize.width / 8 * 1, visibleSize.height * 0.2f);
	speaker->setScale(2);
	addChild(speaker, 10000);

	if (sp)
	{
		speaker->setDisplayFrame(cache->spriteFrameByName("Icon/speakerO.png"));
	}
	else
	{
		speaker->setDisplayFrame(cache->spriteFrameByName("Icon/speakerX.png"));
	}

	SoundManager::getInstance()->playMyBGLogic("MainBG");
	
	unlockManager->ShowUnlockData(this);

	//CCLOG("%s", (sp) ? "true" : "false");
	return true;
}

void MainMenuScene::clickSpeaker()
{
	auto cache = SpriteFrameCache::sharedSpriteFrameCache();
	auto def = UserDefault::sharedUserDefault();
	sp = !sp;
	def->setBoolForKey("speaker", sp);
	if (sp)
	{
		speaker->setDisplayFrame(cache->spriteFrameByName("Icon/speakerO.png"));
		SoundManager::getInstance()->playMySoundLogic("Select");
		SoundManager::getInstance()->resumeMyBG();
	}
	else
	{
		speaker->setDisplayFrame(cache->spriteFrameByName("Icon/speakerX.png"));
		SoundManager::getInstance()->pauseMyBG();

	}
}

void MainMenuScene::LoadData()
{
	auto def = UserDefault::sharedUserDefault();
	_unlockEnding = def->getIntegerForKey("u_ending", 0);
	_currentEndingNumber = _unlockEnding;
	def->setBoolForKey("isBeginner", false);
}

void MainMenuScene::DeleteNode()
{
	this->removeChild(node);
}


bool MainMenuScene::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
	originalTouchPosition = touch->getLocation().x;

	initialTouchPos[0] = touch->getLocation().x;
	initialTouchPos[1] = touch->getLocation().y;
	currentTouchPos[0] = touch->getLocation().x;
	currentTouchPos[1] = touch->getLocation().y;

	return true;
}
void MainMenuScene::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event)
{
	node->setPosition(node->getPositionX() - (originalTouchPosition - touch->getLocation().x), node->getPositionY());
	originalTouchPosition = touch->getLocation().x;

	currentTouchPos[0] = touch->getLocation().x;
	currentTouchPos[1] = touch->getLocation().y;

}
void MainMenuScene::onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *event)
{
	onTouchEnded(touch, event);
}
void MainMenuScene::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event)
{
	auto cache = SpriteFrameCache::sharedSpriteFrameCache();
	if (initialTouchPos[0] - currentTouchPos[0] > visibleSize.width * 0.4f)
	{
		if (_currentEndingNumber < _unlockEnding)
		{
			dotMenu[_currentEndingNumber]->setDisplayFrame(cache->spriteFrameByName(String::createWithFormat("Icon/%d.png", _currentEndingNumber)->getCString()));
			_currentEndingNumber++;
			dotMenu[_currentEndingNumber]->setDisplayFrame(cache->spriteFrameByName(String::createWithFormat("Icon/%dc.png", _currentEndingNumber)->getCString()));
			DeleteNode();
			DrawNode();
			SoundManager::getInstance()->playMySoundLogic("Swing");
		}
	}
	else if (initialTouchPos[0] - currentTouchPos[0] < -visibleSize.width * 0.4f)
	{
		if (_currentEndingNumber > 0)
		{
			// todo
			dotMenu[_currentEndingNumber]->setDisplayFrame(cache->spriteFrameByName(String::createWithFormat("Icon/%d.png", _currentEndingNumber)->getCString()));
			_currentEndingNumber--;
			dotMenu[_currentEndingNumber]->setDisplayFrame(cache->spriteFrameByName(String::createWithFormat("Icon/%dc.png", _currentEndingNumber)->getCString()));
			DeleteNode();
			DrawNode();
			SoundManager::getInstance()->playMySoundLogic("Swing");
		}
	}

	auto action = EaseCubicActionInOut::create(MoveTo::create(0.5f, Vec2::ZERO));
	node->runAction(action);

	if (speaker->getBoundingBox().containsPoint(touch->getLocation()))
		clickSpeaker();
}

void MainMenuScene::DrawNode()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	struct callBackFunctorCSS
	{
		void operator() (Ref* sender) const
		{
			SoundManager::getInstance()->playMySoundLogic("Select");
			auto scene = CharacterSelectScene::createScene();
			Director::getInstance()->replaceScene(TransitionFade::create(0.5, scene));
		}
	};
	struct callBackFunctorAbout
	{
		void operator() (Ref* sender) const
		{
			SoundManager::getInstance()->playMySoundLogic("Select");
			auto scene = AboutScene::createScene();
			Director::getInstance()->replaceScene(TransitionFade::create(0.5, scene));
		}
	};

	Widget::ccWidgetClickCallback callBackCSS = callBackFunctorCSS();
	Widget::ccWidgetClickCallback callBackAbout = callBackFunctorAbout();

	switch (_currentEndingNumber)
	{

	case myEnum::kEnding::kEndingNone:
	{
		node = CSLoader::createNode("MainMenuScene/Ending0/Ending0.csb");
		this->addChild(node);

		auto ani = CSLoader::createTimeline("MainMenuScene/Ending0/Ending0.csb");
		ani->gotoFrameAndPlay(0, 120, false);
		node->runAction(ani);

		auto b_play = static_cast<cocos2d::ui::Button *>(node->getChildByName("ButtonPlay"));
		b_play->addClickEventListener(callBackCSS);
		//b_play->setTag(myEnum::kMenu::kMenuPlay);
		//b_play->addTouchEventListener(CC_CALLBACK_2(MainMenuScene::MenuClick, this));

		auto b_about = static_cast<cocos2d::ui::Button *>(node->getChildByName("ButtonAbout"));
		b_about->addClickEventListener(callBackAbout);
		//b_about->setTag(myEnum::kMenu::kMenuAbout);
		//b_about->addTouchEventListener(CC_CALLBACK_2(MainMenuScene::MenuClick, this));

		auto treeNode = node->getChildByName("TreeTop_2");
		auto spawn = Spawn::create(RotateBy::create(0.45f, -3), SkewBy::create(0.45f, -3, 3), NULL);
		treeNode->runAction(
			RepeatForever::create(Sequence::create(spawn, spawn->reverse(), NULL))
			);

		// sound
	}
	break;
	case myEnum::kEnding::kEndingMurderer:
	{
		node = CSLoader::createNode("MainMenuScene/Ending1/Ending1.csb");
		this->addChild(node);

		auto ani = CSLoader::createTimeline("MainMenuScene/Ending1/Ending1.csb");
		ani->gotoFrameAndPlay(0, 120, false);
		node->runAction(ani);

		auto b_play = static_cast<cocos2d::ui::Button *>(node->getChildByName("ButtonPlay"));
		b_play->addClickEventListener(callBackCSS);

		//b_play->setTag(myEnum::kMenu::kMenuPlay);
		//b_play->addTouchEventListener(CC_CALLBACK_2(MainMenuScene::MenuClick, this));

		auto b_about = static_cast<cocos2d::ui::Button *>(node->getChildByName("ButtonAbout"));
		b_about->addClickEventListener(callBackAbout);
//		b_about->setTag(myEnum::kMenu::kMenuAbout);
//		b_about->addTouchEventListener(CC_CALLBACK_2(MainMenuScene::MenuClick, this));

		// half Devil
		auto halfDevil = CSLoader::createNode("MainMenuScene/Ending1/HalfDevil.csb");
		node->addChild(halfDevil);
		auto ani_hd = CSLoader::createTimeline("MainMenuScene/Ending1/HalfDevil.csb");
		halfDevil->runAction(ani_hd);
		//ani_hd->pause();
		ani_hd->gotoFrameAndPlay(0, 120, false);
		//halfDevil->runAction(ani_hd);
		
		auto seq = Sequence::create(
			CallFunc::create(std::bind(&MainMenuScene::PlayAnimation, this,ani_hd,0,120,false)),
			DelayTime::create(2.0f),
			CallFunc::create(std::bind(&MainMenuScene::PlayAnimation, this, ani_hd, 121, 180, true)),
			NULL);

		halfDevil->runAction(seq);

		// sound

	}
	break;
	case myEnum::kEnding::kEndingDevil:
	{
		node = CSLoader::createNode("MainMenuScene/Ending2/Ending2.csb");
		this->addChild(node, 0);

		auto ani = CSLoader::createTimeline("MainMenuScene/Ending2/Ending2.csb");
		ani->gotoFrameAndPlay(0, 120, false);
		node->runAction(ani);
		//node->setCameraMask(2);

		auto b_play = static_cast<cocos2d::ui::Button *>(node->getChildByName("ButtonPlay"));
		b_play->addClickEventListener(callBackCSS);
//		b_play->setTag(myEnum::kMenu::kMenuPlay);
//		b_play->addTouchEventListener(CC_CALLBACK_2(MainMenuScene::MenuClick, this));

		auto b_about = static_cast<cocos2d::ui::Button *>(node->getChildByName("ButtonAbout"));
		b_about->addClickEventListener(callBackAbout);
//		b_about->setTag(myEnum::kMenu::kMenuAbout);
//		b_about->addTouchEventListener(CC_CALLBACK_2(MainMenuScene::MenuClick, this));

		// torch
		auto torch = CSLoader::createNode("Torch/Torch.csb");
		torch->setScale(3);
		torch->setPosition(visibleSize.width * 0.4f + origin.x, visibleSize.height * 0.6f + origin.y);
//		torch->setPosition(visibleSize.width / 2, visibleSize.height / 10);
//		torch->setRotation(75);
		//torch->setPosition(0, 180);
		node->addChild(torch, 1000);
		auto ani_torch = CSLoader::createTimeline("Torch/Torch.csb");
		torch->runAction(ani_torch);
		ani_torch->gotoFrameAndPlay(0, 40, true);

		// Light blend
		BlendFunc f1 = { GL_ZERO, GL_ONE_MINUS_SRC_ALPHA };
		BlendFunc f2 = { GL_ONE_MINUS_DST_ALPHA, GL_SRC_ALPHA };
		
		auto mask = Sprite::create("mask.png");
		mask->setBlendFunc(f1);
		mask->setPosition(visibleSize.width / 2, visibleSize.height / 2);
		mask->setScale(1.5);
//		mask->setPosition(torch->getPosition());
		node->addChild(mask, 1);

		auto sh = Sprite::create("Shadow.png");
		sh->setPosition(visibleSize.width / 2, visibleSize.height / 2);
		sh->setBlendFunc(f2);
		sh->setOpacity(180);
		node->addChild(sh, 2);

		auto ft1 = FadeTo::create(0.618f, 120);
		auto ft2 = FadeTo::create(0.618f, 255);
		auto sc1 = ScaleTo::create(0.618f, 0.8f);
		auto sc2 = ScaleTo::create(0.618f, 1.2f);
		auto seq = Sequence::create(ft1, ft2, sc1, sc2, NULL);
		auto r = RepeatForever::create(seq);
		sh->runAction(r);
		//sh->runAction(RepeatForever::create(Sequence::createWithTwoActions(FadeOut::create(0.5f), FadeIn::create(0.5f))));

		// setOpacity(0)Àº Åõ¸í
	}
	break;
	case myEnum::kEnding::kEndingSavior:
	{
		node = CSLoader::createNode("MainMenuScene/Ending3/Ending3.csb");
		this->addChild(node);

		auto ani = CSLoader::createTimeline("MainMenuScene/Ending3/Ending3.csb");
		ani->gotoFrameAndPlay(0, 90, false);
		node->runAction(ani);
		//node->setCameraMask(2);

		auto b_play = static_cast<cocos2d::ui::Button *>(node->getChildByName("ButtonPlay"));
		b_play->addClickEventListener(callBackCSS);
//		b_play->setTag(myEnum::kMenu::kMenuPlay);
//		b_play->addTouchEventListener(CC_CALLBACK_2(MainMenuScene::MenuClick, this));

		auto b_about = static_cast<cocos2d::ui::Button *>(node->getChildByName("ButtonAbout"));
		b_about->addClickEventListener(callBackAbout);
//		b_about->setTag(myEnum::kMenu::kMenuAbout);
//		b_about->addTouchEventListener(CC_CALLBACK_2(MainMenuScene::MenuClick, this));

		// half angel
		auto halfAngel = CSLoader::createNode("MainMenuScene/Ending3/HalfAngel.csb");
		node->addChild(halfAngel);
		auto ani_ha = CSLoader::createTimeline("MainMenuScene/Ending3/HalfAngel.csb");
		halfAngel->runAction(ani_ha);
		ani_ha->gotoFrameAndPlay(0, 120, false);

		auto seq = Sequence::create(
			CallFunc::create(std::bind(&MainMenuScene::PlayAnimation, this, ani_ha, 0, 120, false)),
			DelayTime::create(2.0f),
			CallFunc::create(std::bind(&MainMenuScene::PlayAnimation, this, ani_ha, 121, 180, true)),
			NULL);

		halfAngel->runAction(seq);

		auto fire1 = CSLoader::createNode("Effect/Flame/Flame.csb");
		fire1->setPosition(visibleSize.width * 0.2778, visibleSize.height * 0.2083);
		node->addChild(fire1);

		auto ani_fire1 = CSLoader::createTimeline("Effect/Flame/Flame.csb");
		ani_fire1->gotoFrameAndPlay(0, 63, true);
		fire1->runAction(ani_fire1);

		auto fire2 = CSLoader::createNode("Effect/Flame/Flame.csb");
		fire2->setPosition(visibleSize.width * 0.8333, visibleSize.height * 0.1);
		fire2->setScale(3);
		node->addChild(fire2);

		auto ani_fire2 = CSLoader::createTimeline("Effect/Flame/Flame.csb");
		ani_fire2->gotoFrameAndPlay(0, 63, true);
		fire2->runAction(ani_fire2);

		auto fire3 = CSLoader::createNode("Effect/Flame/Flame.csb");
		fire3->setPosition(visibleSize.width * 0.6481, visibleSize.height * 0.21875);
		fire3->setScale(0.5f);
		node->addChild(fire3);

		auto ani_fire3 = CSLoader::createTimeline("Effect/Flame/Flame.csb");
		ani_fire3->gotoFrameAndPlay(0, 63, true);
		fire3->runAction(ani_fire3);
	}
	break;
	case myEnum::kEnding::kEndingAngel:
	{
		node = CSLoader::createNode("MainMenuScene/Ending4/Ending4.csb");
		this->addChild(node);

		auto ani = CSLoader::createTimeline("MainMenuScene/Ending4/Ending4.csb");
		ani->gotoFrameAndPlay(0, 60, false);
		node->runAction(ani);
		//node->setCameraMask(2);

		auto b_play = static_cast<cocos2d::ui::Button *>(node->getChildByName("ButtonPlay"));
		b_play->addClickEventListener(callBackCSS);
//		b_play->setTag(myEnum::kMenu::kMenuPlay);
//		b_play->addTouchEventListener(CC_CALLBACK_2(MainMenuScene::MenuClick, this));

		auto b_about = static_cast<cocos2d::ui::Button *>(node->getChildByName("ButtonAbout"));
		b_about->addClickEventListener(callBackAbout);
//		b_about->setTag(myEnum::kMenu::kMenuAbout);
//		b_about->addTouchEventListener(CC_CALLBACK_2(MainMenuScene::MenuClick, this));

		// angel
		//auto angel = CSLoader::createNode("MainMenuScene/Ending4/Angel.csb");
		//angel->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height + visibleSize.height / 2);
		//node->addChild(angel);
//		auto ani_a = CSLoader::createTimeline("MainMenuScene/Ending4/Angel.csb");
//		angel->runAction(ani_a);
//		ani_a->gotoFrameAndPlay(0, 120, true);

		auto angel = node->getChildByName("Angel");
		auto wing1 = node->getChildByName("Angel")->getChildByName("wing_4");
		auto wing2 = node->getChildByName("Angel")->getChildByName("wing_3");
		auto body = node->getChildByName("Angel")->getChildByName("body_1");

		

		auto act_wing1 = RepeatForever::create(Sequence::create(
			//			Spawn::create(RotateBy::create(1.0f, 20), SkewBy::create(1.0f, 20, 20), NULL),
			//			Spawn::create(RotateBy::create(1.0f, -20), SkewBy::create(1.0f, -20, -20), NULL),
			RotateBy::create(1.0f, -20),
			RotateBy::create(1.0f, 20),
			NULL));
		auto act_wing2 = RepeatForever::create(Sequence::create(
			//			Spawn::create(RotateBy::create(1.0f, -20), SkewBy::create(1.0f, -20, -20), NULL),
			//			Spawn::create(RotateBy::create(1.0f, 20), SkewBy::create(1.0f, 20, 20), NULL),
			RotateBy::create(1.0f, 20),
			RotateBy::create(1.0f, -20),
			NULL));
		auto act_body = RepeatForever::create(Sequence::create(
			MoveBy::create(1.0f, Vec2(0, 30)),
			MoveBy::create(1.0f, Vec2(0, -30)),
			NULL));

		wing1->runAction(act_wing1);
		wing2->runAction(act_wing2);
		body->runAction(act_body);

		angel->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height + visibleSize.height / 2);

		auto act_moveTo = MoveTo::create(2.0f, Vec2(visibleSize.width / 2 + origin.x, visibleSize.height * 0.4));
		auto seq = Sequence::create(
			DelayTime::create(0.5f),
			act_moveTo,
			NULL);

		angel->runAction(seq);

		// vassal 1
		auto vassal1 = CSLoader::createNode("MainMenuScene/Ending4/Vassal.csb");
		vassal1->setPosition(visibleSize.width *0.2 + origin.x, -visibleSize.height / 3);
		node->addChild(vassal1);

		auto ani_v1 = CSLoader::createTimeline("MainMenuScene/Ending4/Vassal.csb");
		vassal1->runAction(ani_v1);
		//ani_a->gotoFrameAndPlay(0, 120, true);
		auto act_vassal1_moveTo = MoveTo::create(2.0f, Vec2(vassal1->getPositionX(), visibleSize.height / 15));
		//vassal1->runAction(act_vassal1_moveTo);

		auto seq_vassal1 = Sequence::create(
			DelayTime::create(1.5f),
			act_vassal1_moveTo,
			CallFunc::create(std::bind(&MainMenuScene::PlayAnimation, this, ani_v1, 0, 120, true)),
			NULL);

		vassal1->runAction(seq_vassal1);

		// vassal 2
		auto vassal2 = CSLoader::createNode("MainMenuScene/Ending4/Vassal.csb");
		vassal2->setPosition(visibleSize.width * 0.5 + origin.x, -visibleSize.height / 3);
		node->addChild(vassal2);

		auto ani_v2 = CSLoader::createTimeline("MainMenuScene/Ending4/Vassal.csb");
		vassal2->runAction(ani_v2);
		//ani_a->gotoFrameAndPlay(0, 120, true);
		auto act_vassal2_moveTo = MoveTo::create(2.0f, Vec2(vassal2->getPositionX(), visibleSize.height / 20));
		//vassal1->runAction(act_vassal1_moveTo);

		auto seq_vassal2 = Sequence::create(
			DelayTime::create(0.7f),
			act_vassal2_moveTo,
			CallFunc::create(std::bind(&MainMenuScene::PlayAnimation, this, ani_v2, 0, 120, true)),
			NULL);

		vassal2->runAction(seq_vassal2);

		// vassal 3
		auto vassal3 = CSLoader::createNode("MainMenuScene/Ending4/Vassal.csb");
		vassal3->setPosition(visibleSize.width * 0.8 + origin.x, -visibleSize.height / 3);
		vassal3->setScaleX(-1);
		node->addChild(vassal3);

		auto ani_v3 = CSLoader::createTimeline("MainMenuScene/Ending4/Vassal.csb");
		vassal3->runAction(ani_v3);
		//ani_a->gotoFrameAndPlay(0, 120, true);
		auto act_vassal3_moveTo = MoveTo::create(2.0f, Vec2(vassal3->getPositionX(), visibleSize.height / 15));
		//vassal1->runAction(act_vassal1_moveTo);

		auto seq_vassal3 = Sequence::create(
			DelayTime::create(1.0f),
			act_vassal3_moveTo,
			CallFunc::create(std::bind(&MainMenuScene::PlayAnimation, this, ani_v3, 0, 120, true)),
			NULL);

		vassal3->runAction(seq_vassal3);

	}
	break;
	case myEnum::kEnding::kEndingInfinity:
	{
		node = CSLoader::createNode("MainMenuScene/Ending5/Ending5.csb");
		this->addChild(node);

		auto ani = CSLoader::createTimeline("MainMenuScene/Ending5/Ending5.csb");
		ani->gotoFrameAndPlay(0, 60, false);
		node->runAction(ani);
		//node->setCameraMask(2);

		auto b_play = static_cast<cocos2d::ui::Button *>(node->getChildByName("ButtonPlay"));
		b_play->addClickEventListener(callBackCSS);

		auto b_about = static_cast<cocos2d::ui::Button *>(node->getChildByName("ButtonAbout"));
		b_about->addClickEventListener(callBackAbout);

		// infinity 
		auto infi = CSLoader::createNode("MainMenuScene/Ending5/Infinity.csb");
		node->addChild(infi);
		auto ani_infi = CSLoader::createTimeline("MainMenuScene/Ending5/Infinity.csb");
		ani_infi->gotoFrameAndPlay(0, 120, true);
		infi->runAction(ani_infi);

		// hero
		auto hero = CSLoader::createNode("MainMenuScene/Ending5/Hero.csb");
		hero->setPosition(visibleSize.width * 0.5f + origin.x, visibleSize.height * 0.3f);
		node->addChild(hero);

		// half angel
		auto halfAngel = CSLoader::createNode("MainMenuScene/Ending5/HalfAngel.csb");
		node->addChild(halfAngel);
		auto ani_ha = CSLoader::createTimeline("MainMenuScene/Ending5/HalfAngel.csb");
		halfAngel->runAction(ani_ha);
		ani_ha->gotoFrameAndPlay(0, 60, true);
		halfAngel->setPosition(visibleSize.width * 0.35f + origin.x, visibleSize.height * 0.45f);

		// half devil
		auto halfDevil = CSLoader::createNode("MainMenuScene/Ending5/HalfDevil.csb");
		node->addChild(halfDevil);
		auto ani_hd = CSLoader::createTimeline("MainMenuScene/Ending5/HalfDevil.csb");
		halfDevil->runAction(ani_hd);
		ani_hd->gotoFrameAndPlay(0, 60, true);
		halfDevil->setPosition(visibleSize.width*0.7f + origin.x, visibleSize.height * 0.25f);

		// angel
		auto angel = CSLoader::createNode("MainMenuScene/Ending4/Angel.csb");
		angel->setPosition(visibleSize.width * 0.1f + origin.x, visibleSize.height * 0.5f);
		angel->setScale(0.5f);
		node->addChild(angel);
		auto ani_a = CSLoader::createTimeline("MainMenuScene/Ending4/Angel.csb");
		ani_a->gotoFrameAndPlay(0, 120, true);
		angel->runAction(ani_a);

		// devil
		auto devil= CSLoader::createNode("MainMenuScene/Ending5/Devil.csb");
		devil->setPosition(visibleSize.width * 0.9f + origin.x, visibleSize.height * 0.1f);
		node->addChild(devil);

	}
	break;
	case myEnum::kEnding::kEndingForgiver:
	{
		node = CSLoader::createNode("MainMenuScene/Ending6/Ending6.csb");
		this->addChild(node);

		auto ani = CSLoader::createTimeline("MainMenuScene/Ending6/Ending6.csb");
		ani->gotoFrameAndPlay(0, 60, false);
		node->runAction(ani);

		auto b_play = static_cast<cocos2d::ui::Button *>(node->getChildByName("ButtonPlay"));
		b_play->addClickEventListener(callBackCSS);
//		b_play->setTag(myEnum::kMenu::kMenuPlay);
//		b_play->addTouchEventListener(CC_CALLBACK_2(MainMenuScene::MenuClick, this));

		auto b_about = static_cast<cocos2d::ui::Button *>(node->getChildByName("ButtonAbout"));
		b_about->addClickEventListener(callBackAbout);
//		b_about->setTag(myEnum::kMenu::kMenuAbout);
//		b_about->addTouchEventListener(CC_CALLBACK_2(MainMenuScene::MenuClick, this));

		// tree
		auto treeNode = static_cast<cocos2d::Sprite*>(node->getChildByName("TreeTop"));
		auto seq = Sequence::create(RotateBy::create(1.5f, -15.0f), RotateBy::create(1.5f, 15.0f), NULL);
		auto repeat = RepeatForever::create(seq);
		treeNode->runAction(repeat);

		// secret road
		auto roadNode = static_cast<cocos2d::Sprite*>(node->getChildByName("SecretRoad"));
		roadNode->setOpacity(0);
		//auto seq_Road = Sequence::create(FadeIn::create(1.5f), FadeOut::create(1.5f), NULL);
		//auto repeat_road = RepeatForever::create(seq_Road);
		roadNode->runAction(FadeIn::create(1.5f));

		// flower
		auto flower = CSLoader::createNode("MainMenuScene/Ending6/Flower.csb");
		node->addChild(flower);
		auto ani_flower = CSLoader::createTimeline("MainMenuScene/Ending6/Flower.csb");
		flower->runAction(ani_flower);
		ani_flower->gotoFrameAndPlay(0, 120, true);
		flower->setPosition(visibleSize.width * 0.5555f + origin.x, -visibleSize.height * 0.078125f + origin.y);
		auto move = MoveTo::create(1.5f, Vec2(flower->getPositionX(), -flower->getPositionY()));
		flower->runAction(move);
	}
	break;

	}

}

void MainMenuScene::PlayAnimation(cocostudio::timeline::ActionTimeline * ani, int s, int e, bool r)
{
	ani->gotoFrameAndPlay(s, e, r);
	//target->stopAllActions();
	//target->runAction(ani);
}

void MainMenuScene::onKeyReleased(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event *event)
{
	if (keycode == EventKeyboard::KeyCode::KEY_BACK) {
		Director::getInstance()->end();
	}
}
