#include "CharacterSelectScene.h"

//#include "SimpleAudioEngine.h"
USING_NS_CC;
using namespace ui;

Scene* CharacterSelectScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
	auto layer = CharacterSelectScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool CharacterSelectScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	node = CSLoader::createNode("CSS/CSS.csb");
	//node->setPosition(origin);
	this->addChild(node);
	
	this->setKeypadEnabled(true);

	// Warrior Frame Button
	WFBtn = static_cast<Button*>(node->getChildByName("WFBtn"));
	WFBtn->setUserData(this);
	struct callBackFunctorWF
	{
		void operator() (Ref* sender) const
		{
			auto scene = static_cast<CharacterSelectScene*>((static_cast<cocos2d::Node*>(sender)->getUserData()));
			scene->character = myEnum::kCharacter::kWarrior;
			auto act = MoveTo::create(0.5f, scene->WFBtn->getPosition());
			scene->SelectFrame->stopAllActions();
			scene->SelectFrame->runAction(act);

			scene->MDT->setVisible(false);
			scene->WDT->setVisible(true);
			scene->MDesc->setVisible(false);
			scene->WDesc->setVisible(true);

			SoundManager::getInstance()->playMySoundLogic("Swing", "mp3");
		}
	};
	Widget::ccWidgetClickCallback callBackWF = callBackFunctorWF();
	WFBtn->addClickEventListener(callBackWF);

	// Magician Frame Button
	MFBtn = static_cast<Button*>(node->getChildByName("MFBtn"));
	MFBtn->setUserData(this);
	struct callBackFunctorMF
	{
		void operator() (Ref* sender) const
		{
			auto scene = static_cast<CharacterSelectScene*>((static_cast<cocos2d::Node*>(sender)->getUserData()));
			scene->character = myEnum::kCharacter::kMagician;
			auto act = MoveTo::create(0.5f, scene->MFBtn->getPosition());
			scene->SelectFrame->stopAllActions();
			scene->SelectFrame->runAction(act);

			scene->MDT->setVisible(true);
			scene->WDT->setVisible(false);
			scene->MDesc->setVisible(true);
			scene->WDesc->setVisible(false);

			SoundManager::getInstance()->playMySoundLogic("Swing", "mp3");
		}
	};
	Widget::ccWidgetClickCallback callBackMF = callBackFunctorMF();
	MFBtn->addClickEventListener(callBackMF);

	// Back Button 
	BackBtn = static_cast<Button*>(node->getChildByName("BackBtn"));
	struct callBackFunctorBB
	{
		void operator() (Ref* sender) const
		{
			SoundManager::getInstance()->playMySoundLogic("Select");
			auto scene = MainMenuScene::createScene();
			Director::getInstance()->replaceScene(TransitionFade::create(0.5, scene));
		}
	};
	Widget::ccWidgetClickCallback callBackBB = callBackFunctorBB();
	BackBtn->addClickEventListener(callBackBB);

	// Start Button
	StartBtn = static_cast<Button*>(node->getChildByName("StartBtn"));
	StartBtn->setUserData(this);
	struct callBackFunctorStart
	{
		void operator() (Ref* sender) const
		{
			auto CSS = static_cast<CharacterSelectScene*>((static_cast<cocos2d::Node*>(sender)->getUserData()));
			HeroData * heroData = HeroData::getInstance();
			if (CSS->character == myEnum::kCharacter::kWarrior)
				heroData->InitWithFile("Hero", "Warrior");
			else
				heroData->InitWithFile("Hero", "Magician");
//			hero->SaveData();

			auto def = UserDefault::getInstance();
			def->setBoolForKey("saveState", false);
			def->flush();

			SoundManager::getInstance()->playMySoundLogic("Select");
			auto scene = LoadingScene::createScene("G");
			Director::getInstance()->replaceScene(TransitionFade::create(0.5f, scene));
		}
	};
	Widget::ccWidgetClickCallback callBackStart = callBackFunctorStart();
	StartBtn->addClickEventListener(callBackStart);

	// Load Button
	LoadBtn = static_cast<Button*>(node->getChildByName("LoadBtn"));
	LoadBtn->setUserData(this);
	auto def = UserDefault::getInstance();
	bool saveState = def->getBoolForKey("saveState", false);
	if (saveState)
	{
		LoadBtn->setEnabled(true);
		LoadBtn->setBright(true);
	}
	else
	{
		LoadBtn->setEnabled(false);
		LoadBtn->setBright(false);
	}
	struct callBackFunctorLoad
	{
		void operator() (Ref* sender) const
		{
			auto CSS = static_cast<CharacterSelectScene*>((static_cast<cocos2d::Node*>(sender)->getUserData()));
			HeroData * heroData = HeroData::getInstance();
			if (CSS->character == myEnum::kCharacter::kWarrior)
				heroData->InitWithFile("Hero", "Warrior");
			else
				heroData->InitWithFile("Hero", "Magician");

			SoundManager::getInstance()->playMySoundLogic("Select");
			auto scene = LoadingScene::createScene("Load");
			Director::getInstance()->replaceScene(TransitionFade::create(0.5f, scene));
		}
	};
	Widget::ccWidgetClickCallback callBackLoad = callBackFunctorLoad();
	LoadBtn->addClickEventListener(callBackLoad);

	WDT = node->getChildByName("WDT");
	MDT = node->getChildByName("MDT");
	MDesc = node->getChildByName("mNode");
	WDesc = node->getChildByName("wNode");
	SelectFrame = node->getChildByName("SelectFrame");

	character = myEnum::kCharacter::kWarrior;
	WDT->setVisible(true);
	WDesc->setVisible(true);
	MDT->setVisible(false);
	MDesc->setVisible(false);
	
	return true;
}

void CharacterSelectScene::onKeyReleased(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event *event)
{
	if (keycode == EventKeyboard::KeyCode::KEY_BACK) {
		SoundManager::getInstance()->playMySoundLogic("Select");
		auto scene = MainMenuScene::createScene();
		Director::getInstance()->replaceScene(TransitionFade::create(0.5, scene));
	}
}



