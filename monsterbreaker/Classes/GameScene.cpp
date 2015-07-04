#include "GameScene.h"

USING_NS_CC;
using namespace ui;

Scene* GameScene::createScene()
{	
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setGravity(Vec2(0, 0));
//	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

    // 'layer' is an autorelease object
	auto layer = GameScene::create();
	layer->SetPhysicsWorld(scene->getPhysicsWorld());

    // add layer as a child to scene
    scene->addChild(layer);
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
	rightTick = visibleSize.width / 35;
	//touchDoor = false;

	auto spr_bg = Sprite::create("GameScene/BG.png");
	spr_bg->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(spr_bg, 0);

	// only debug
	auto item1 = MenuItemImage::create("CloseNormal.png", "CloseSelected.png", CC_CALLBACK_1(GameScene::test, this));
	item1->setPosition(Vec2(300, 200));
	auto item2 = MenuItemImage::create("CloseNormal.png", "CloseSelected.png", CC_CALLBACK_1(GameScene::test2, this));
	item2->setPosition(Vec2(350, 200));
	auto item3 = MenuItemImage::create("CloseNormal.png", "CloseSelected.png", CC_CALLBACK_1(GameScene::test3, this));
	item3->setPosition(Vec2(400, 200));

	auto menu = Menu::create(item1, item2, item3, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 100);

	pauseNode = CSLoader::createNode("Icon/pauseBtn.csb");
	pauseBtn = (Button *)pauseNode->getChildByName("btn");
	pauseImage = (Sprite*)pauseNode->getChildByName("image");
	pauseNode->setPosition(pauseBtn->getContentSize().width*0.5f, pauseBtn->getContentSize().height * 0.5f);
	addChild(pauseNode, 10000, "pauseNode");
	
	pauseBtn->addTouchEventListener(CC_CALLBACK_2(GameScene::onPauseBtnClicked, this));

	// contact Listener
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin, this);
	contactListener->onContactSeperate = CC_CALLBACK_1(GameScene::onContactSeperate, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);	

	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	touchListener->onTouchCancelled = CC_CALLBACK_2(GameScene::onTouchCancelled, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

    return true;
}


void GameScene::onPauseBtnClicked(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type)
{
	switch (type){
	case Widget::TouchEventType::BEGAN:
		break;
	case Widget::TouchEventType::MOVED:
		break;
	case Widget::TouchEventType::ENDED:
	{
		pauseLogic();
	}
	break;
	case Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}
}

void GameScene::pauseLogic()
{
	//CCLOG("Current System State :: %d", systemManager->systemState);
	//CCLOG("temp System State :: %d", temp);
	auto cache = SpriteFrameCache::getInstance();
	pauseImage = (Sprite*)pauseNode->getChildByName("image");
	if (systemManager->systemState == myEnum::kSystemState::kSSPause)
	{
		pauseImage->setDisplayFrame(cache->getSpriteFrameByName("Icon/pauseIcon.png"));
		SetResume();
	}
	else
	{
		pauseImage->setDisplayFrame(cache->getSpriteFrameByName("Icon/resumeIcon.png"));
		SetPause();
	}

}

void GameScene::onEnter()
{
	CCLayer::onEnter();

	// init data
	HeroData * heroData = HeroData::getInstance();
	if(heroData->getName().compare("Warrior") == 0)
		hero = Warrior::create();
	else if (heroData->getName().compare("Magician") == 0)
		hero = Magician::create();
	hero->Move(Vec2(visibleSize.width / 2, hero->getContentSize().height));
	hero->Draw(this);

	statusManager = StatusManager::create(hero);
	statusManager->DrawStatus(this);
	statusManager->scheduleUpdate();

	collisionManager.SetLayer(this);

	mapManager = MapManager::getInstance();
	if (!(mapManager->GetCurrentRoomData().type == myEnum::kRoomType::kRTSecret))
	{
		mapManager->CheckSideRoom(hero->HasItem(ITEM_SCAVENGER) || hero->HasItem(ITEM_SECRET_MASTER), hero->HasItem(ITEM_SECRET_MASTER));
	}
	mapManager->setCurse(false);
	mapManager->setAllView(hero->HasItem(ITEM_THE_MAP));	
	mapManager->setAllViewType(hero->HasItem(ITEM_THE_COMPASS));

	mapManager->DrawMap(this);

	bombManager = BombManager::create(this,hero);
	this->addChild(bombManager);
	bombManager->scheduleUpdate();

	monsterManager = MonsterManager::create(this, mapManager->getLevelName().c_str());
	this->addChild(monsterManager, 0, "MonsterManager");

	doorManager = DoorManager::create(hero);
	this->addChild(doorManager, 0, "DoorManager");
	//	tileManager = new TileManager();
	//	tileManager->InitMapTypeData(&mapManager, hero);
	doorManager->setSecretView(hero->HasItem(ITEM_SCAVENGER) || hero->HasItem(ITEM_SECRET_MASTER));	// 	tileManager.setSecretView(hero.HasItem("SecretViewer") || hero.HasItem("XRAY"));
	doorManager->setSecretViewLockOpen(hero->HasItem(ITEM_SECRET_MASTER));	//	tileManager.setSecretViewLockOpen(hero.HasItem("XRAY"));
	doorManager->Draw(this);

	skillManager = SkillManager::create(hero);
	skillManager->DrawAndSetPosition(this);
	
	effectManager = EffectManager::create(this);
	this->addChild(effectManager, 0, "EffectManager");

	secretManager = SecretManager::create(this, hero);
	this->addChild(secretManager, 0, "SecretManager");

	helpManager = HelpManager::create(this, hero);
	this->addChild(helpManager, 0, "HelpManager");
	helpManager->createHeroHelperMan();

	dataManager = DataManager::create(this, hero);
	this->addChild(dataManager, 0, "DataManager");

	systemManager = SystemManager::create(this, hero);
	this->addChild(systemManager, 0, "SystemManager");
	//systemManager.Init(this, &sceneWorld, hero, helpManager);
	
	tutorialManager = TutorialManager::create(this, hero);
	this->addChild(tutorialManager, 0, "TutorialManager");

	int type = mapManager->GetCurrentRoomData().type;
	switch (type)
	{
	case myEnum::kRoomType::kRTBoss:
		if (mapManager->GetCurrentRoomData().exp)
			SetWin();
		else
		{
			monsterManager->CreateBossMonster();
			monsterManager->scheduleUpdate();
			helpManager->startAIBeforeBattle();
			helpManager->startHelperUpdateAI();
			SetInit();
			SoundManager::getInstance()->changeBG("BossBG");
		}
		break;
	case myEnum::kRoomType::kRTHelp:
		SetWin();
		helpManager->createCageAndData();
		break;
	case myEnum::kRoomType::kRTMonster:
		if (mapManager->GetCurrentRoomData().exp)
			SetWin();
		else
		{
			monsterManager->DrawMonsters();
			monsterManager->scheduleUpdate();
			helpManager->startAIBeforeBattle();
			helpManager->startHelperUpdateAI();
			SetInit();
		}
		break;
	case myEnum::kRoomType::kRTSecret:
		SetWin();
		secretManager->createSecretItem();
		break;
	case myEnum::kRoomType::kRTShop:
		shopManager = ShopManager::create(this, hero);
		this->addChild(shopManager, 0, "ShopManager");
		shopManager->createShopItem();

		SetWin();
		break;
	case myEnum::kRoomType::kRTStart:
		if (mapManager->getLevelName().compare("G") == 0)
		{
			tutorialManager->createTutorialBtn();
		}
		SetWin();
		break;
	case myEnum::kRoomType::kRTTreasure:
		treasureManager = TreasureManager::create(this, hero);
		this->addChild(treasureManager, 0, "TreasureManager");
		treasureManager->createTreasure();

		SetWin();
		break;
	}

	dataManager->LoadData();
	this->scheduleUpdate();


	// only debug 

	//auto w = Weapon::create(this, hero, "Sword", "FireSword", true);
	//w->setPosition(visibleSize.width*0.5f, visibleSize.height*0.5f);
	//this->addChild(w, ZINDEX_CHEST_ITEM);

	////auto hm = HMWarrior::create(this, hero, true);
	////hm->setPosition(visibleSize.width*0.5f, visibleSize.height*0.5f);
	////addChild(hm, 1000);
	////hero->IncreaseKeyCount(5);

	//auto chest = Chest::create(hero, this);
	//chest->setPosition(Vec2(visibleSize.width * 0.3f + origin.x, visibleSize.height* 0.5f + origin.y));
	//this->addChild(chest, ZINDEX_CHEST_SPRITE);

	//chest->SetItem(ITEM_STONE_OF_DAVID);

	//auto chest2 = Chest::create(hero, this);
	//chest2->setPosition(Vec2(visibleSize.width * 0.7f + origin.x, visibleSize.height* 0.5f + origin.y));
	//this->addChild(chest2, ZINDEX_CHEST_SPRITE);

	//chest2->SetItem(ITEM_BLACK_AND_WHITE);

	//doorManager->ShowEndingDoor();
	//doorManager->scheduleUpdate();


	//auto m = Orc::create();
	//m->setPosition(visibleSize.width*0.5f, visibleSize.height*0.5f);
	//m->Draw(this);
	//m->StartAnimation();
	//m->scheduleUpdate();


	//hero->IncreaseMoneyCount(5);
	//hero->setAttackPoint(10);
	//hero->IncreaseBombCount(10);
	//hero->IncreaseKeyCount(10);
}

void GameScene::SetInit()
{
	systemManager->SetSystemState(myEnum::kSystemState::kSSInit);
	monsterManager->PauseMonsters();
	bombManager->pause();
	effectManager->PauseAllEffects();
	helpManager->pause();
	skillManager->setClickEnabled(false);
	tutorialManager->pause();
	SoundManager::getInstance()->pauseAllSound();
}
void GameScene::SetPlay()
{
	systemManager->SetSystemState(myEnum::kSystemState::kSSPlaying);
	monsterManager->ResumeMonsters();
	bombManager->resume();
	effectManager->ResumeAllEffects();
	helpManager->resume();
	skillManager->setClickEnabled(true);
	tutorialManager->resume();
	SoundManager::getInstance()->resumeAllSound();
}
void GameScene::SetPause()
{
	temp = systemManager->systemState;
	systemManager->SetSystemState(myEnum::kSystemState::kSSPause);
	monsterManager->PauseMonsters();
	bombManager->pause();
	effectManager->PauseAllEffects();
	helpManager->pause();
	skillManager->setClickEnabled(false);
	tutorialManager->pause();
	systemManager->ShowPause();
}
void GameScene::SetResume()
{
	systemManager->HidePause();
	switch (temp)
	{
	case myEnum::kSystemState::kSSInit:
//		CCLOG("Resume Init");
		SetInit();
		break;
	case myEnum::kSystemState::kSSPlaying:
//		CCLOG("Resume Play");
		SetPlay();
		break;
	case myEnum::kSystemState::kSSWin:
//		CCLOG("Resume Win");
		SetWin();
		break;
	}
}
void GameScene::SetDie()
{
	systemManager->SetSystemState(myEnum::kSystemState::kSSDie);
	monsterManager->PauseMonsters();
	bombManager->pause();
//	effectManager->PauseAllEffects();
	helpManager->pause();
	skillManager->setClickEnabled(false);
	tutorialManager->pause();
	systemManager->ShowPause();

	auto def = UserDefault::getInstance();
	def->setBoolForKey("saveState", false);
	def->flush();

	auto cache = SpriteFrameCache::getInstance();
	pauseBtn->setEnabled(false);
	pauseBtn->setBright(false);
	pauseImage->setDisplayFrame(cache->getSpriteFrameByName("Icon/resumeIcon.png"));
	pauseNode->setOpacity(128);
	//SoundManager::getInstance()->pauseAllSound();
	SoundManager::getInstance()->changeBG("DieBG");

}
void GameScene::SetWin()
{
//	SoundManager::getInstance()->pauseAllSound();
	systemManager->SetSystemState(myEnum::kSystemState::kSSWin);
	systemManager->SaveBtnEnabled(true);

	bombManager->CanceledTimer();
	bombManager->resume();
	helpManager->pause();
	tutorialManager->resume();
	effectManager->ResumeAllEffects();
	if (hero->getSkillID() == SKILL_FIRST_AID)
		skillManager->setClickEnabled(true);
	else
		skillManager->setClickEnabled(false);

	//hero->IncreaseSkillPoint(1);

	//monsterManager->PauseMonsters();
	// ball delete
	auto bodies = sceneWorld->getAllBodies();
	int size = bodies.size();
	//CCLOG("HB %d | MB %d | NB %d ", HERO_BALL_COLLISION_BITMASK, MONSTER_BALL_COLLISION_BITMASK, NEUTRAL_BALL_COLLISION_BITMASK);
	for (int i = 0; i < size; i++)
	{
		auto obj = bodies.at(i);
		//CCLOG("obj %d ", obj->getCollisionBitmask());
		if (obj->getCollisionBitmask() == HERO_BALL_COLLISION_BITMASK 
			|| obj->getCollisionBitmask() == MONSTER_BALL_COLLISION_BITMASK
			|| obj->getCollisionBitmask() == NEUTRAL_BALL_COLLISION_BITMASK
			|| obj->getCollisionBitmask() == COIN_BALL_COLLISION_BITMASK
			|| obj->getCollisionBitmask() == NEUTRAL_COIN_BALL_COLLISION_BITMASK)
		{
			collisionManager.DeleteObject(obj);
		}
	}

	int x = mapManager->getHeroX();
	int y = mapManager->getHeroY();
	//mapManager->GetCurrentRoomData().exp = true;
	bool exp = mapManager->map[x][y].exp;
	if (exp != true)
	{
		mapManager->map[x][y].exp = true;
		helpManager->startAIAfterBattle();
		//auto hero = (Hero *)layer->getChildByName("Hero");
		hero->IncreaseSkillPoint(1);
		if (hero->HasItem(ITEM_SOUL_EATER))
			hero->IncreaseCurrentSp(1);
		if (mapManager->GetCurrentRoomData().type == myEnum::kRoomType::kRTBoss)
		{
			SoundManager::getInstance()->changeBG("MainBG");
		}
	}
	//mapManager->map[x][y].exp = true;


	//	mapManager->setClearCountRoom(mapManager->getClearCountRoom() + 1);

	//mapManager.Save();

	hero->Save();

	doorManager->SetDoorClickEnable(true);
	doorManager->OpenDoors();
//	doorManager->visibleAllSecretDoor(hero->HasItem(ITEM_SCAVENGER));
//	doorManager->OpenAllSecretDoor(hero->HasItem(ITEM_SECRET_MASTER));

	if (MapManager::getInstance()->GetCurrentRoomData().type == myEnum::kRoomType::kRTBoss)
	{
		doorManager->ShowEndingDoor();
		doorManager->scheduleUpdate();
	}

//	doorManager->ShowEndingDoor();
}
void GameScene::onExit()
{
	setTouchEnabled(false);
	CCLayer::onExit();

	// Check item
	if (doorManager->getIsMovindLoadingScene() == false)
	{
		dataManager->ClearData();
		dataManager->SaveData();

	}
	
}
void GameScene::test(Ref *pSender)
{
	monsterManager->Debug2();
}

void GameScene::test2(Ref *pSender)
{	
	mapManager->setAllView(true);
	mapManager->setAllViewType(true);
	mapManager->ReDrawMap();

	//	// for debug
	//	auto r = mapManager->GetCurrentRoomData();
	//	
	////	mapManager->setLevelName("HC");
	////	mapManager->setLevelName("MC");
	//	mapManager->setLevelName("HV");
	//	mapManager->map[r.x + 1][r.y].type = myEnum::kRoomType::kRTBoss;
	//	mapManager->map[r.x - 1][r.y].type = myEnum::kRoomType::kRTBoss;
	//	mapManager->map[r.x][r.y + 1].type = myEnum::kRoomType::kRTBoss;
	//	mapManager->map[r.x][r.y - 1].type = myEnum::kRoomType::kRTBoss;
	//SetResume();
	//hero->Damaged(100);

	
}

void GameScene::test3(cocos2d::Ref *pSender)
{
	// for debug
	auto r = mapManager->GetCurrentRoomData();
	
	mapManager->setLevelName("MM");
//	mapManager->setLevelName("MC");
	mapManager->map[r.x + 1][r.y].type = myEnum::kRoomType::kRTBoss;
	mapManager->map[r.x - 1][r.y].type = myEnum::kRoomType::kRTBoss;
	mapManager->map[r.x][r.y + 1].type = myEnum::kRoomType::kRTBoss;
	mapManager->map[r.x][r.y - 1].type = myEnum::kRoomType::kRTBoss;

//	hero->SetSkill(SKILL_LIGHTNING);
//	skillManager->SetSkillImage();

//	SetInit();
//	SetPause();
//	hero->Damaged(100);
}


void GameScene::update(float dt)
{
	switch (systemManager->systemState)
	{
	case myEnum::kSystemState::kSSInit:
		break;
	case myEnum::kSystemState::kSSPlaying:
		if (!(hero->IsAlive()))
		{
			SetDie();
			//systemManager.SetSystemState(myEnum::kSystemState::kSSDie);

		}
		if (hero->getBallCurrentCount() <= 0)
		{
			//systemManager.SetSystemState(myEnum::kSystemState::kSSInit);
			hero->Damaged(1);
			if (hero->IsAlive())
				SetInit();
			else
				SetDie();
		}
		//		monsterManager.update(dt);
		if (monsterManager->getMonsterClear())
		{
			SetWin();
		}
		break;
	case myEnum::kSystemState::kSSPause:
		break;
	case myEnum::kSystemState::kSSWin:
		break;
	case myEnum::kSystemState::kSSDie:
		break;
	}

}

bool GameScene::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
	switch (systemManager->systemState)
	{
	case myEnum::kSystemState::kSSInit:
	{
		//std::string ballName = hero->getBallName();
		auto cache = SpriteFrameCache::sharedSpriteFrameCache();
		cache->addSpriteFramesWithFile("Ball/Ball.plist", "Ball/Ball.png");

		ball = Node::create();

		if (hero->HasItem(ITEM_TRINITY))
		{
			auto b1 = Sprite::createWithSpriteFrameName(String::createWithFormat("Ball/%s.png", hero->getBallName().c_str())->getCString());
			auto b2 = Sprite::createWithSpriteFrameName(String::createWithFormat("Ball/%s.png", hero->getBallName().c_str())->getCString());
			auto b3 = Sprite::createWithSpriteFrameName(String::createWithFormat("Ball/%s.png", hero->getBallName().c_str())->getCString());
			b1->setPosition(0, b1->getContentSize().height * 0.5f);
			b2->setPosition(-b2->getContentSize().width*0.5f, -b2->getContentSize().height*0.5f);
			b3->setPosition(+b3->getContentSize().width*0.5f, -b3->getContentSize().height*0.5f);
			ball->addChild(b1);
			ball->addChild(b2);
			ball->addChild(b3);
		}
		else
		{
			auto b1 = Sprite::createWithSpriteFrameName(String::createWithFormat("Ball/%s.png", hero->getBallName().c_str())->getCString());
			ball->addChild(b1);
		}

		ball->setPosition(touch->getLocation());
		this->addChild(ball, ZINDEX_HERO_BALL);
	}
	break;
	case myEnum::kSystemState::kSSPlaying:
		if (touch->getLocation().y < visibleSize.height / 10 * 8 && touch->getLocation().y >= visibleSize.height / 10 * 4)
		{
			// Monster Zone Click
			bombManager->SetTimer();
		}
		else if (touch->getLocation().y < visibleSize.height / 10 * 4)
		{
			Move(touch);
		}
		//if (hero->getBoundingBox().containsPoint(touch->getLocation()))
		//{
		//	Move(touch);
		////	CCLOG("@@@@@@@@@");
		////	CCLOG("@@@@@@@@@");
		////	CCLOG("@@@@@@@@@");
		//}
		break;
	case myEnum::kSystemState::kSSPause:
		break;
	case myEnum::kSystemState::kSSWin:
	{
		if (touch->getLocation().y < visibleSize.height / 10 * 8)
			bombManager->SetTimer();

		//if (hero->getBoundingBox().containsPoint(touch->getLocation()))
		//{
		//	//CCLOG("@@@@@@@@@");
		//	//CCLOG("@@@@@@@@@");
		//	//CCLOG("@@@@@@@@@");
		//}
	}
		break;
	case myEnum::kSystemState::kSSDie:
		break;
	}

	return true;
}
void GameScene::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event)
{
	switch (systemManager->systemState)
	{
	case myEnum::kSystemState::kSSInit:
	{
		if (ball != NULL)
		{
			auto startPoint = hero->paddle->getPosition();
			startPoint.y += hero->paddle->getContentSize().height;
			auto endPoint = touch->getLocation();
			ball->setPosition(endPoint);
		}

	}
		break;
	case myEnum::kSystemState::kSSPlaying:
		if (touch->getLocation().y < visibleSize.height / 10 * 8 && touch->getLocation().y >= visibleSize.height / 10 * 4)
		{
			// Monster Zone Click
			//CCLOG("Monster Zone Clicked");
		}
		else if (touch->getLocation().y < visibleSize.height / 10 * 4)
		{
			//CCLOG("Hero Zone Clicked");
			//hero->Move(Vec2(touch->getLocation().x, hero->getPositionY()));
			Move(touch);
		}
		break;
	case myEnum::kSystemState::kSSPause:
		break;
	case myEnum::kSystemState::kSSWin:
		break;
	case myEnum::kSystemState::kSSDie:
		break;
	}
}
void GameScene::onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *event)
{

}
void GameScene::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event)
{
	switch (systemManager->systemState)
	{
	case myEnum::kSystemState::kSSInit:
	{
		//systemManager.SetSystemState(myEnum::kSystemState::kSSPlaying);

		if (ball != NULL)
		{
			auto startPoint = hero->paddle->getPosition();
			startPoint.y += hero->paddle->getContentSize().height;
			ball->removeFromParentAndCleanup(true);
			//this->removeChild(ball);
			ball = NULL;
			if (hero->HasItem(ITEM_TRINITY))
			{
				hero->Fire(this, startPoint, touch->getLocation());
				hero->Fire(this, startPoint, touch->getLocation());
				hero->Fire(this, startPoint, touch->getLocation());
			}
			else
			{
				hero->Fire(this, startPoint, touch->getLocation());
			}
			SetPlay();
		}

	}
		break;
	case myEnum::kSystemState::kSSPlaying:
	{
		if (touch->getLocation().y < visibleSize.height / 10 * 8 && touch->getLocation().y >= visibleSize.height / 10 * 4)
		{
			// Monster Zone Click
			//		CCLOG("Monster Zone Click ended");
			if (hero->getBombCount() > 0)
			{
				if (bombManager->SetBomb(touch->getLocation()))
				{
					hero->DecreaseBombCount(1);
				}
			}
			if (hero->getSkillUseState())
			{
				hero->DoSkillEvent(touch->getLocation());
				hero->setSkillUseState(false);
			}
		}
		else if (touch->getLocation().y < visibleSize.height / 10 * 4)
		{
			Move(touch);
			//bombManager.CanceledTimer();
			//		CCLOG("Hero Zone Click ended");
		}
	}
		break;
	case myEnum::kSystemState::kSSPause:
		break;
	case myEnum::kSystemState::kSSWin:
	{
		if (touch->getLocation().y < visibleSize.height / 10 * 8)
		{
			if (hero->getBombCount() > 0)
			{
				if (bombManager->SetBomb(touch->getLocation()))
				{
					hero->DecreaseBombCount(1);
				}
			}
		}
	}
		break;
	case myEnum::kSystemState::kSSDie:
		break;
	}

}
void GameScene::onContactSeperate(cocos2d::PhysicsContact &contact)
{

}

bool GameScene::onContactBegin(cocos2d::PhysicsContact &contact)
{
	PhysicsBody *a = contact.getShapeA()->getBody();
	PhysicsBody *b = contact.getShapeB()->getBody();
	switch (systemManager->systemState)
	{
	case myEnum::kSystemState::kSSInit:
		break;
	case myEnum::kSystemState::kSSPlaying:
		if (true == collisionManager.HasPhysicsBodiesCollided(contact, MONSTER_BODY_COLLISION_BITMASK, HERO_BALL_COLLISION_BITMASK)
			|| true == collisionManager.HasPhysicsBodiesCollided(contact, MONSTER_BODY_COLLISION_BITMASK, NEUTRAL_BALL_COLLISION_BITMASK)
			|| true == collisionManager.HasPhysicsBodiesCollided(contact, MONSTER_BODY_COLLISION_BITMASK, NEUTRAL_COIN_BALL_COLLISION_BITMASK))
		{
			if (a->getCollisionBitmask() == MONSTER_BODY_COLLISION_BITMASK)
			{
				collisionManager.GetObjectData(a)->Damaged(collisionManager.GetObjectData(b)->getAttackPoint());
			}
			else
			{
				collisionManager.GetObjectData(b)->Damaged(collisionManager.GetObjectData(a)->getAttackPoint());
			}
		}
		else if (true == collisionManager.HasPhysicsBodiesCollided(contact, SINGLE_BRICK_COLLISION_BITMASK, HERO_BALL_COLLISION_BITMASK)
			|| true == collisionManager.HasPhysicsBodiesCollided(contact, SINGLE_BRICK_COLLISION_BITMASK, NEUTRAL_BALL_COLLISION_BITMASK)
			|| true == collisionManager.HasPhysicsBodiesCollided(contact, SINGLE_BRICK_COLLISION_BITMASK, NEUTRAL_COIN_BALL_COLLISION_BITMASK))
		{
			if (a->getCollisionBitmask() == SINGLE_BRICK_COLLISION_BITMASK)
			{
				collisionManager.DestroyBrick(a);
			}
			else
			{
				collisionManager.DestroyBrick(b);
			}
		}
		else if (true == collisionManager.HasPhysicsBodiesCollided(contact, DOUBLE_BRICK_COLLISION_BITMASK, HERO_BALL_COLLISION_BITMASK)
			|| true == collisionManager.HasPhysicsBodiesCollided(contact, DOUBLE_BRICK_COLLISION_BITMASK, NEUTRAL_BALL_COLLISION_BITMASK)
			|| true == collisionManager.HasPhysicsBodiesCollided(contact, DOUBLE_BRICK_COLLISION_BITMASK, NEUTRAL_COIN_BALL_COLLISION_BITMASK))
		{
			if (a->getCollisionBitmask() == DOUBLE_BRICK_COLLISION_BITMASK)
			{
				collisionManager.DestroyBrick(a);
			}
			else
			{
				collisionManager.DestroyBrick(b);
			}
		}
		else if (true == collisionManager.HasPhysicsBodiesCollided(contact, SOLID_BRICK_COLLISION_BITMASK, HERO_BALL_COLLISION_BITMASK)
			|| true == collisionManager.HasPhysicsBodiesCollided(contact, SOLID_BRICK_COLLISION_BITMASK, NEUTRAL_BALL_COLLISION_BITMASK)
			|| true == collisionManager.HasPhysicsBodiesCollided(contact, SOLID_BRICK_COLLISION_BITMASK, NEUTRAL_COIN_BALL_COLLISION_BITMASK))
		{
			// sound
			SoundManager::getInstance()->playMySoundLogic("Solid");
		}
		else if (true == collisionManager.HasPhysicsBodiesCollided(contact, SINGLE_NEUTRAL_BRICK_COLLISION_BITMASK, HERO_BALL_COLLISION_BITMASK)
			|| true == collisionManager.HasPhysicsBodiesCollided(contact, SINGLE_NEUTRAL_BRICK_COLLISION_BITMASK, MONSTER_BALL_COLLISION_BITMASK)
			|| true == collisionManager.HasPhysicsBodiesCollided(contact, SINGLE_NEUTRAL_BRICK_COLLISION_BITMASK, NEUTRAL_BALL_COLLISION_BITMASK)
			|| true == collisionManager.HasPhysicsBodiesCollided(contact, SINGLE_NEUTRAL_BRICK_COLLISION_BITMASK, COIN_BALL_COLLISION_BITMASK)
			|| true == collisionManager.HasPhysicsBodiesCollided(contact, SINGLE_NEUTRAL_BRICK_COLLISION_BITMASK, NEUTRAL_COIN_BALL_COLLISION_BITMASK))
		{
			if (a->getCollisionBitmask() == SINGLE_NEUTRAL_BRICK_COLLISION_BITMASK)
			{
				collisionManager.DestroyBrick(a);
			}
			else
			{
				collisionManager.DestroyBrick(b);
			}
		}

		else if (true == collisionManager.HasPhysicsBodiesCollided(contact, HERO_BODY_COLLISION_BITMASK, MONSTER_BALL_COLLISION_BITMASK)
			|| true == collisionManager.HasPhysicsBodiesCollided(contact, HERO_BODY_COLLISION_BITMASK, NEUTRAL_BALL_COLLISION_BITMASK)
			|| true == collisionManager.HasPhysicsBodiesCollided(contact, HERO_BODY_COLLISION_BITMASK, COIN_BALL_COLLISION_BITMASK)
			|| true == collisionManager.HasPhysicsBodiesCollided(contact, HERO_BODY_COLLISION_BITMASK, NEUTRAL_COIN_BALL_COLLISION_BITMASK))
		{
			if (a->getCollisionBitmask() == HERO_BODY_COLLISION_BITMASK)
			{
				if (b->getCollisionBitmask() == COIN_BALL_COLLISION_BITMASK || b->getCollisionBitmask() == NEUTRAL_COIN_BALL_COLLISION_BITMASK)
					hero->IncreaseMoneyCount(collisionManager.GetObjectData(b)->getAttackPoint());
				else
					collisionManager.GetObjectData(a)->Damaged(collisionManager.GetObjectData(b)->getAttackPoint());

				((Character*)collisionManager.GetObjectData(b))->DecreaseBallCount();
				collisionManager.DeleteObject(b);
			}
			else
			{
				if (a->getCollisionBitmask() == COIN_BALL_COLLISION_BITMASK || a->getCollisionBitmask() == NEUTRAL_COIN_BALL_COLLISION_BITMASK)
					hero->IncreaseMoneyCount(collisionManager.GetObjectData(a)->getAttackPoint());
				else
					collisionManager.GetObjectData(b)->Damaged(collisionManager.GetObjectData(a)->getAttackPoint());
				
				((Character*)collisionManager.GetObjectData(a))->DecreaseBallCount();
				collisionManager.DeleteObject(a);

			}
		}
		else if (true == collisionManager.HasPhysicsBodiesCollided(contact, DEATH_COLLISION_BITMASK, HERO_BALL_COLLISION_BITMASK)
			|| true == collisionManager.HasPhysicsBodiesCollided(contact, DEATH_COLLISION_BITMASK, MONSTER_BALL_COLLISION_BITMASK)
			|| true == collisionManager.HasPhysicsBodiesCollided(contact, DEATH_COLLISION_BITMASK, NEUTRAL_BALL_COLLISION_BITMASK)
			|| true == collisionManager.HasPhysicsBodiesCollided(contact, DEATH_COLLISION_BITMASK, COIN_BALL_COLLISION_BITMASK)
			|| true == collisionManager.HasPhysicsBodiesCollided(contact, DEATH_COLLISION_BITMASK, NEUTRAL_COIN_BALL_COLLISION_BITMASK))
		{
			if (a->getCollisionBitmask() == DEATH_COLLISION_BITMASK)
			{
				((Character*)collisionManager.GetObjectData(b))->DecreaseBallCount();
				collisionManager.DeleteObject(b);
			}
			else
			{
				((Character*)collisionManager.GetObjectData(a))->DecreaseBallCount();
				collisionManager.DeleteObject(a);
			}
		}

		else if (true == collisionManager.HasPhysicsBodiesCollided(contact, MONSTER_BODY_COLLISION_BITMASK, BOMB_RANGE_COLLISION_BITMASK))
		{
			//		CCLOG("Bomb!!");
			if (a->getCollisionBitmask() == MONSTER_BODY_COLLISION_BITMASK)
			{
				// a is monster & b is bomb
				collisionManager.GetObjectData(a)->Damaged(((Bomb*)collisionManager.GetObjectData(b))->GetAttackPoint());
			}
			else
			{
				// a is bomb & b is monster
				collisionManager.GetObjectData(b)->Damaged(((Bomb*)collisionManager.GetObjectData(a))->GetAttackPoint());
			}
		}
		else if (true == collisionManager.HasPhysicsBodiesCollided(contact, PADDLE_COLLISION_BITMASK, HERO_BALL_COLLISION_BITMASK)
			|| true == collisionManager.HasPhysicsBodiesCollided(contact, PADDLE_COLLISION_BITMASK, MONSTER_BALL_COLLISION_BITMASK)
			|| true == collisionManager.HasPhysicsBodiesCollided(contact, PADDLE_COLLISION_BITMASK, NEUTRAL_BALL_COLLISION_BITMASK)
			|| true == collisionManager.HasPhysicsBodiesCollided(contact, PADDLE_COLLISION_BITMASK, COIN_BALL_COLLISION_BITMASK)
			|| true == collisionManager.HasPhysicsBodiesCollided(contact, PADDLE_COLLISION_BITMASK, NEUTRAL_COIN_BALL_COLLISION_BITMASK))
		{
			if (a->getCollisionBitmask() == PADDLE_COLLISION_BITMASK)
			{
				if (b->getCollisionBitmask() == MONSTER_BALL_COLLISION_BITMASK)
					b->setCollisionBitmask(NEUTRAL_BALL_COLLISION_BITMASK);
				else if (b->getCollisionBitmask() == COIN_BALL_COLLISION_BITMASK)
					b->setCollisionBitmask(NEUTRAL_COIN_BALL_COLLISION_BITMASK);
			}
			else
			{
				if (a->getCollisionBitmask() == MONSTER_BALL_COLLISION_BITMASK)
					a->setCollisionBitmask(NEUTRAL_BALL_COLLISION_BITMASK);
				else if (a->getCollisionBitmask() == COIN_BALL_COLLISION_BITMASK)
					a->setCollisionBitmask(NEUTRAL_COIN_BALL_COLLISION_BITMASK);

			}
			hero->Swing();
		}

		// TODO

		else if (true == collisionManager.HasPhysicsBodiesCollided(contact, MONSTER_BODY_COLLISION_BITMASK, SKILL_FIRE_BALL_SPRITE_COLLISION_BITMASK))
		{
			if (a->getCollisionBitmask() == MONSTER_BODY_COLLISION_BITMASK)
			{
				collisionManager.GetObjectData(a)->Damaged(SKILL_FIRE_BALL_DAMAGE);
				collisionManager.DeleteObject(b);
			}
			else
			{
				collisionManager.GetObjectData(b)->Damaged(SKILL_FIRE_BALL_DAMAGE);
				collisionManager.DeleteObject(a);
			}
		}
		else if (true == collisionManager.HasPhysicsBodiesCollided(contact, HERO_BODY_COLLISION_BITMASK, SKILL_LIGHTNING_COLLISION_BITMASK))
		{
			if (a->getCollisionBitmask() == SKILL_LIGHTNING_COLLISION_BITMASK)
			{
				auto obj = (Lightning*)a->getNode()->getUserData();
				hero->Damaged(obj->getAttackPoint());
			}
			else
			{
				auto obj = (Lightning*)b->getNode()->getUserData();
				hero->Damaged(obj->getAttackPoint());
			}
		}
		else if (true == collisionManager.HasPhysicsBodiesCollided(contact, MONSTER_BODY_COLLISION_BITMASK, SKILL_LIGHTNING_COLLISION_BITMASK))
		{
			if (a->getCollisionBitmask() == MONSTER_BODY_COLLISION_BITMASK)
			{
				auto obj = (Lightning*)b->getNode()->getUserData();
				collisionManager.GetObjectData(a)->Damaged(obj->getAttackPoint());
				//collisionManager.DeleteObject(b);
			}
			else
			{
				auto obj = (Lightning*)a->getNode()->getUserData();
				collisionManager.GetObjectData(b)->Damaged(obj->getAttackPoint());
				//collisionManager.GetObjectData(b)->Damaged(2);
				//collisionManager.DeleteObject(a);
			}
		}
		else if (true == collisionManager.HasPhysicsBodiesCollided(contact, HERO_BODY_COLLISION_BITMASK, DRAGON_BREATH_COLLISION_BITMASK))
		{
			hero->Damaged(1);
		}


		break;
	case myEnum::kSystemState::kSSPause:
		break;
	case myEnum::kSystemState::kSSWin:
	{
		//CCLOG("secret %d | bomb %d ", SECRET_DOOR_COLLISION_BITMASK, BOMB_RANGE_COLLISION_BITMASK);
		//CCLOG("a %d | b %d ", a->getCollisionBitmask(), b->getCollisionBitmask());
		if (true == collisionManager.HasPhysicsBodiesCollided(contact, SECRET_DOOR_COLLISION_BITMASK, BOMB_RANGE_COLLISION_BITMASK))
		{
			if (a->getCollisionBitmask() == SECRET_DOOR_COLLISION_BITMASK)
			{
				auto ptr = static_cast<SecretDoor*> (a->getNode()->getUserData());
				ptr->setLock(false);
				ptr->setVisible(true);
				ptr->Open();
				mapManager->map[ptr->getGoToX()][ptr->getGoToY()].lock = false;
				mapManager->map[ptr->getGoToX()][ptr->getGoToY()].visible = true;
				SoundManager::getInstance()->playMySoundLogic("FindSecret");
//				mapManager.Save();
			}
			else
			{
				auto ptr = static_cast<SecretDoor*> (b->getNode()->getUserData());
				ptr->setLock(false);
				ptr->setVisible(true);
				ptr->Open();
				mapManager->map[ptr->getGoToX()][ptr->getGoToY()].lock = false;
				mapManager->map[ptr->getGoToX()][ptr->getGoToY()].visible = true;
				SoundManager::getInstance()->playMySoundLogic("FindSecret");
				//				mapManager.Save();
			}
		}
		if (true == collisionManager.HasPhysicsBodiesCollided(contact, MERCHANT_COLLISION_BITMASK, BOMB_RANGE_COLLISION_BITMASK))
		{
			if (a->getCollisionBitmask() == MERCHANT_COLLISION_BITMASK)
			{
				auto ptr = static_cast<Merchant*> (a->getNode()->getUserData());
				ptr->Die();
				collisionManager.DeleteObject(a);
			}
			else
			{
				auto ptr = static_cast<Merchant*> (b->getNode()->getUserData());
				ptr->Die();
				collisionManager.DeleteObject(b);
			}
		}

	}
		break;
	case myEnum::kSystemState::kSSDie:
		break;
	}

	return true;
}

void GameScene::Move(cocos2d::Touch * touch)
{
	if (touch->getLocation().x < hero->getContentSize().width - rightTick)	// left
		hero->Move(Vec2(hero->getContentSize().width - rightTick, hero->getPositionY()));
	else  if (touch->getLocation().x > visibleSize.width - hero->getContentSize().width + origin.x + rightTick)	// right
		hero->Move(Vec2(visibleSize.width - hero->getContentSize().width + origin.x + rightTick, hero->getPositionY()));
	else  // center
		hero->Move(Vec2(touch->getLocation().x, hero->getPositionY()));
}
