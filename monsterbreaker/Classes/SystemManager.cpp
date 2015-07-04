#include "SystemManager.h"
USING_NS_CC;
using namespace ui;

SystemManager::SystemManager(cocos2d::Layer * layer, Hero * hero) : layer(layer), hero(hero)
{
	visibleSize = Director::getInstance()->getVisibleSize();
	helpManager = (HelpManager *)layer->getChildByName("HelpManager");
	setClickOk(false);
	systemState = myEnum::kSystemState::kSSInit;
	physicsWorld = ((GameScene*)layer)->GetPhysicsWorld();
}
SystemManager::~SystemManager()
{

}

SystemManager * SystemManager::create(cocos2d::Layer * layer, Hero * hero)
{
	auto pSprite = new SystemManager(layer, hero);
	pSprite->autorelease();
	pSprite->InitSystemData();
	return pSprite;
}

void SystemManager::InitSystemData()
{
	node = CSLoader::createNode("Pause/Pause.csb");
	bg = node->getChildByName("bg");
	bg->setOpacity(128);
	pause = node->getChildByName("pause");
	dead = node->getChildByName("dead");
	pause->setVisible(false);
	dead->setVisible(false);

	you = node->getChildByName("youNode");
	for (int i = 1; i <= 2; i++)
	{
		buddiesList.pushBack(node->getChildByName(String::createWithFormat("buddyNode%d", i)->getCString()));
	}
	//buddy1 = node->getChildByName("buddyNode1");
	//buddy2 = node->getChildByName("buddyNode2");

	ball1 = node->getChildByName("ballNode1");;
	ball2 = node->getChildByName("ballNode2");;
	ball3 = node->getChildByName("ballNode3");;

	bomb = node->getChildByName("bombNode");
	weapon = node->getChildByName("weaponNode");

	for (int i = 0; i < 24; i++)
	{
		auto obj = node->getChildByName(String::createWithFormat("item%d", i)->getCString());
		itemList.pushBack(obj);
	}

	btnResume = (Button*)node->getChildByName("resume");
	btnSave = (Button*)node->getChildByName("save");
	btnHome = (Button*)node->getChildByName("home");

	btnResume->setUserData(this);
	btnSave->setUserData(this);
	btnHome->setUserData(this);

	SaveBtnEnabled(false);

	struct callBackFunctorResume
	{
		void operator() (Ref* sender) const
		{
			static_cast<SystemManager*>(static_cast<Node*>(sender)->getUserData())->ResumeClicked();
		}
	};
	Widget::ccWidgetClickCallback callBackResume = callBackFunctorResume();
	btnResume->addClickEventListener(callBackResume);
	struct callBackFunctorSave
	{
		void operator() (Ref* sender) const
		{
			static_cast<SystemManager*>(static_cast<Node*>(sender)->getUserData())->SaveClicked();
		}
	};
	Widget::ccWidgetClickCallback callBackSave = callBackFunctorSave();
	btnSave->addClickEventListener(callBackSave);
	struct callBackFunctorHome
	{
		void operator() (Ref* sender) const
		{
			static_cast<SystemManager*>(static_cast<Node*>(sender)->getUserData())->HomeClicked();
		}
	};
	Widget::ccWidgetClickCallback callBackHome = callBackFunctorHome();
	btnHome->addClickEventListener(callBackHome);

//	node->setPosition(-visibleSize.width*0.5f, visibleSize.height*0.5f);
	node->setVisible(false);

	layer->addChild(node, ZINDEX_PAUSE_BG);
}

void SystemManager::ResumeClicked()
{
//	CCLOG("RESUME");
	((GameScene*)layer)->SetResume();
}
void SystemManager::SaveClicked()
{	
	MapManager::getInstance()->SaveAll();
	hero->Save();
	HeroData::getInstance()->SaveData();

}
void SystemManager::HomeClicked()
{
//	CCLOG("HOME");
//	((GameScene*)layer)->SetResume();
	auto scene = MainMenuScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(0.5f, scene));
}



void SystemManager::SetSystemState(int systemState)
{
	this->systemState = systemState;

	switch (systemState)
	{
	case myEnum::kSystemState::kSSInit:
		//layer->pause();
		layer->resume();
		physicsWorld->setSpeed(0);
		break;
	case myEnum::kSystemState::kSSPlaying:
		layer->resume();
		physicsWorld->setSpeed(1);
		//		this->scheduleUpdate();
		break;
	case myEnum::kSystemState::kSSPause:
		layer->pause();
		physicsWorld->setSpeed(0);
		// someThing
		break;
	case myEnum::kSystemState::kSSWin:
	{
		//CCLOG("WIN!!!");
		//layer->pause();
		//(*physicsWorld)->setSpeed(0);

		break;
	}
	case myEnum::kSystemState::kSSDie:
		layer->pause();
		physicsWorld->setSpeed(0);
		// someThing
		CCLOG("DIE!!!");
		break;
	}

}

void SystemManager::ShowPause()
{
	bool isAlive = hero->IsAlive();
//	node->runAction(MoveTo::create(0.5f, Vec2(visibleSize.width*0.5f, visibleSize.height*0.5f)));
	node->setVisible(true);
	node->setOpacity(0);
	node->runAction(FadeIn::create(0.5f));
	pause->setVisible(isAlive);
	dead->setVisible(!isAlive);
	if (!isAlive)
	{
		btnResume->setBright(false);
		btnResume->setEnabled(false);
		btnResume->setOpacity(128);
		btnSave->setBright(false);
		btnSave->setEnabled(false);
		btnSave->setOpacity(128);
	}
	SetAndStartAllPauseData();
}

void SystemManager::SaveBtnEnabled(bool b)
{
	btnSave->setBright(b);
	btnSave->setEnabled(b);
	if (b)
		btnSave->setOpacity(255);
	else
		btnSave->setOpacity(128);
}


void SystemManager::HidePause()
{
	node->runAction(FadeOut::create(0.5f));
	node->setVisible(false);
	node->setVisible(true);
	pause->setVisible(false);
	dead->setVisible(false);

	RemoveAllPauseData();
}
void SystemManager::SetAndStartAllPauseData()
{
	bool isAlive = hero->IsAlive();
	// ball
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Ball/Ball.plist", "Ball/Ball.png");
	auto ballSpr = Sprite::createWithSpriteFrameName(String::createWithFormat("Ball/%s.png", hero->getBallName().c_str())->getCString());
	ball1->addChild(ballSpr,ZINDEX_PAUSE_UPPER_MENU);
	ball1->setScale(5);
	ball1->runAction(RepeatForever::create(RotateBy::create(0.5f, 180)));
	if(hero->HasItem(ITEM_TRINITY))
	{ 
		auto ballSpr2 = Sprite::createWithSpriteFrameName(String::createWithFormat("Ball/%s.png", hero->getBallName().c_str())->getCString());
		ball2->addChild(ballSpr2, ZINDEX_PAUSE_UPPER_MENU);
		ball2->setScale(5);
		ball2->runAction(RepeatForever::create(RotateBy::create(0.5f, 180)));

		auto ballSpr3 = Sprite::createWithSpriteFrameName(String::createWithFormat("Ball/%s.png", hero->getBallName().c_str())->getCString());
		ball3->addChild(ballSpr3, ZINDEX_PAUSE_UPPER_MENU);
		ball3->setScale(5);
		ball3->runAction(RepeatForever::create(RotateBy::create(0.5f, 180)));
	}

	// bomb
	auto bombSpr = Bomb::create(layer, hero);
	bomb->setScale(3);
	bomb->addChild(bombSpr, ZINDEX_PAUSE_UPPER_MENU);

	// weapon
	auto weaponSpr = Weapon::create(layer, hero, hero->getWeaponType().c_str(), hero->getWeaponName().c_str(), false);
	weapon->addChild(weaponSpr, ZINDEX_PAUSE_UPPER_MENU);

	// item
	int itemSize = hero->itemList.size();
	for (int i = 0; i < itemSize; i++)
	{
		auto itemSpr = ChestItem::create(layer, hero, hero->itemList.at(i), false);
		itemSpr->setScale(0.67);
		itemList.at(i)->addChild(itemSpr, ZINDEX_PAUSE_UPPER_MENU);
	}
	// buddies
	int buddiesSize = hero->helperList.size();
	for (int i = 0; i < buddiesSize; i++)
	{
		int hmID = hero->helperList.at(i);
		auto buddySpr = helpManager->createHelperMan(hmID);
		buddiesList.at(i)->addChild(buddySpr, ZINDEX_PAUSE_UPPER_MENU);
	}

	Hero * cloneYou = Hero::create(hero);
	you->addChild(cloneYou, ZINDEX_PAUSE_UPPER_MENU);
	cloneYou->setScaleX(hero->getScaleX());
	if (!isAlive) cloneYou->Animate("Die", myEnum::kAction::kActionDie);
}
void SystemManager::RemoveAllPauseData()
{
	RemoveMethod(ball1);
	RemoveMethod(ball2);
	RemoveMethod(ball3);
	RemoveMethod(bomb);
	RemoveMethod(weapon);
	RemoveMethod(&itemList);
	RemoveMethod(&buddiesList);
	RemoveMethod(you);
}

void SystemManager::RemoveMethod(cocos2d::Node * target)
{
	auto vect = target->getChildren();
	int size = vect.size();
	for (int i = 0; i < size; i++)
	{
		auto obj = vect.at(i);
		//obj->removeAllChildrenWithCleanup(true);
		obj->removeFromParentAndCleanup(true);
		//layer->removeChild(obj);
	}
}

void SystemManager::RemoveMethod(cocos2d::Vector<cocos2d::Node *> * target)
{
	int size = target->size();
	for (int i = 0; i < size; i++)
	{
		RemoveMethod(target->at(i));
	}
//	target->clear();
}




//void SystemManager::SetDoorEnabled(cocos2d::MenuItem * item, bool b)
//{
//	item->setEnabled(b);
//}

